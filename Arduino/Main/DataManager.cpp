/*
 * Arducam Mini OV5642 Mini 5MP Plus, Wiznet Ethernet Shield
 *
 * Author: Michael Alvarado
 */
#include "DataManager.h"
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduCAM.h>
#include <Wire.h>
#include "memorysaver.h"

//Define Digital Pins
#define SD_CS 4 //SD enable pin
#define ETH_CS 7 //Ethernet enable pin
#define Cam_1_CS 48 //Arducam 1 enable pin
#define Cam_1_PW 46 //Arducam 1 Power Pin

//Call Camera memorysaver
#if !(defined OV5642_MINI_5MP_PLUS || defined OV5642_MINI_5MP_BIT_ROTATION_FIXED || defined OV2640_MINI_2MP || defined OV3640_MINI_3MP)
  #error Please select the hardware platform and camera module in the ../libraries/ArduCAM/memorysaver.h file
#endif

//Camera Variables
#define   FRAMES_NUM    0x06
ArduCAM myCAM(OV5642, Cam_1_CS); //OVS5460_Mini_5MP_Plus 
uint8_t read_fifo_burst(ArduCAM myCAM);
bool is_header = false;
int total_time = 0;
String latestPic = ""; //TEST Set latest pic address to send serial
String pictureAddress = "Pictures/"; //picture Address Folder (folder with Timestamp is later added on setup)


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address

// Server IP Address
IPAddress server(10, 0, 0, 78);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void setupSD(){
    // disable w5100 while setting up SD
  pinMode(ETH_CS,OUTPUT);
  digitalWrite(ETH_CS,HIGH);
  Serial.print("Starting SD..");
  if(!SD.begin(SD_CS)) Serial.println("failed");
  else {
    Serial.println("ok");
    //Create a folder to store image files
    int fileNumber = 0;
    while(SD.exists(pictureAddress+(String)fileNumber)) fileNumber++; //Check last index to create folder
    pictureAddress = pictureAddress+(String)fileNumber;
    Serial.println("Create Folder: " + pictureAddress);
    SD.mkdir(pictureAddress);
  }
}

void setupCameras(){
  uint8_t vid, pid;
  uint8_t temp;
  Wire.begin();
  Serial.println(F("ArduCAM Start!"));
  //set the PW as output
  pinMode(Cam_1_PW, OUTPUT);
  digitalWrite(Cam_1_PW, HIGH);
  
  //set the CS as an output:
  pinMode(Cam_1_CS,OUTPUT);
  digitalWrite(Cam_1_CS, HIGH);
  
  delay(1000);
  // initialize SPI:
  SPI.begin();
    
  //Reset the CPLD
  myCAM.write_reg(0x07, 0x80);
  delay(100);
  myCAM.write_reg(0x07, 0x00);
  delay(100);
    
  while(1){
    //Check if the ArduCAM SPI bus is OK
    myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
    temp = myCAM.read_reg(ARDUCHIP_TEST1);
    
    if (temp != 0x55){
      Serial.println(F("SPI interface Error!"));
      delay(1000);continue;
    }else{
      Serial.println(F("SPI interface OK."));break;
    }
  }
  
  #if defined (OV2640_MINI_2MP)
    while(1){
      //Check if the camera module type is OV2640
      myCAM.wrSensorReg8_8(0xff, 0x01);
      myCAM.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
      myCAM.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
      if ((vid != 0x26 ) && (( pid != 0x41 ) || ( pid != 0x42 ))){
        Serial.println(F("Can't find OV2640 module!"));
        delay(1000);continue;
      }
      else{
        Serial.println(F("OV2640 detected."));break;
      } 
    }
  #elif defined (OV3640_MINI_3MP)
    while(1){
      //Check if the camera module type is OV3640
      myCAM.rdSensorReg16_8(OV3640_CHIPID_HIGH, &vid);
      myCAM.rdSensorReg16_8(OV3640_CHIPID_LOW, &pid);
      if ((vid != 0x36) || (pid != 0x4C)){
        Serial.println(F("Can't find OV3640 module!"));
        delay(1000);continue; 
      }else{
        Serial.println(F("OV3640 detected."));break;    
      }
   } 
  #else
    while(1){
      //Check if the camera module type is OV5642
      myCAM.wrSensorReg16_8(0xff, 0x01);
      myCAM.rdSensorReg16_8(OV5642_CHIPID_HIGH, &vid);
      myCAM.rdSensorReg16_8(OV5642_CHIPID_LOW, &pid);
      if((vid != 0x56) || (pid != 0x42)){
        Serial.println(F("Can't find OV5642 module!"));
        delay(1000);continue;
      }
      else{
        Serial.println(F("OV5642 detected."));break;
      } 
    }
  #endif
  myCAM.set_format(JPEG);
  myCAM.InitCAM();
  #if defined (OV2640_MINI_2MP)
    myCAM.OV2640_set_JPEG_size(OV2640_320x240);
  #elif defined (OV3640_MINI_3MP)
    myCAM.OV3640_set_JPEG_size(OV3640_320x240);
  #else
    myCAM.write_reg(ARDUCHIP_TIM, VSYNC_LEVEL_MASK);   //VSYNC is active HIGH
    myCAM.OV5642_set_JPEG_size(OV5642_2592x1944); //5MP
    //myCAM.OV5642_set_JPEG_size(OV5642_2048x1536); //3MP
    //myCAM.OV5642_set_Light_Mode(Auto);
  #endif
  delay(1000);
  //Turn power off
  digitalWrite(Cam_1_PW, LOW);
}

void capturePictureSD(){
  //Turn Power ON
  digitalWrite(Cam_1_PW, HIGH);

  String address;
  byte buf[256];
  static int i = 0;
  static int k = 0; //Might deleted (used for naming files)
  uint8_t temp = 0,temp_last=0;
  uint32_t length = 0;
  bool is_header = false;
  File outFile;
  //Flush the FIFO
  myCAM.flush_fifo();
  //Clear the capture done flag
  myCAM.clear_fifo_flag();
  //Start capture
  myCAM.start_capture();
  Serial.println(F("start Capture"));
  while(!myCAM.get_bit(ARDUCHIP_TRIG , CAP_DONE_MASK));
  Serial.println(F("Capture Done."));  
  length = myCAM.read_fifo_length();
  Serial.print(F("The fifo length is :"));
  Serial.println(length, DEC);
  if (length >= MAX_FIFO_SIZE) //384K
  {
    Serial.println(F("Over size."));
    return ;
  }
  if (length == 0 ) //0 kb
  {
    Serial.println(F("Size is 0."));
    return ;
  }
  //Construct a file name
  k = k + 1;
  //itoa(k, str, 10);
  address = pictureAddress +"/"+(String)k + ".jpg";
  //strcat(address, ".jpg");
  Serial.println(address);
  //Open the new file
  outFile = SD.open(address, O_WRITE | O_CREAT | O_TRUNC);
  if(!outFile){
    Serial.println(F("File open failed"));
    return;
  }
  myCAM.CS_LOW();
  myCAM.set_fifo_burst();
  while ( length-- )
  {
    temp_last = temp;
    temp =  SPI.transfer(0x00);
    //Read JPEG data from FIFO
    if ( (temp == 0xD9) && (temp_last == 0xFF) ) //If find the end ,break while,
    {
      buf[i++] = temp;  //save the last  0XD9     
      //Write the remain bytes in the buffer
      myCAM.CS_HIGH();
      outFile.write(buf, i);    
      //Close the file
      outFile.close();
      Serial.println(F("Image save OK."));
      is_header = false;
      i = 0;
      latestPic = address; //Set latest pic address to send serial
    }  
    if (is_header == true)
    { 
      //Write image data to buffer if not full
      if (i < 256)
      buf[i++] = temp;
      else
      {
        //Write 256 bytes image data to file
        myCAM.CS_HIGH();
        outFile.write(buf, 256);
        i = 0;
        buf[i++] = temp;
        myCAM.CS_LOW();
        myCAM.set_fifo_burst();
      }        
    }
    else if ((temp == 0xD8) & (temp_last == 0xFF))
    {
      is_header = true;
      buf[i++] = temp_last;
      buf[i++] = temp;   
    } 
  } 
   //Turn Power OFF
  digitalWrite(Cam_1_PW, LOW); 
}

//This method save all data in the array into a CSV file called Data.csv
void saveDataToSD(String data[], int sizeData){
   //Write to SD
  File myFile = SD.open("Data.csv", FILE_WRITE);
  delay(1000);

  // if the file opened okay, write to it:
  if (myFile) {
    String dataEntry = "";
    //Add all data with comma (,) separated value
    for(int i = 0; i < sizeData -1; i++){
      dataEntry += (String)data[i] + (String) ",";
    }
    //Add last data with no trailing comma (,)
    dataEntry += data[sizeData-1];
    
    //Serial.println(dataEntry);
    myFile.println(dataEntry);
    // close the file:
    myFile.close();
    Serial.println("Data saved to SD");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error saving data to SD");
  }
}

//Connects to server 
void connectToServer() {
  // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(100);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 54010)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    sendImage();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}

void loopData() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
}

void HTTPRequest(){
      // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
   // client.print(F("Content-Length: ")); //File Leg
    //client.println(file.size()); //File Size
    client.println();
}


void sendImage(){
  //Get the File from SD
  File myFile = SD.open(latestPic); 
  
  //Calculation of packets needed to send
  int packetSize = 100; //This is limited by RAM. (Bigger better if RAM available)
  int packets = (myFile.size() + (packetSize - 1)) / packetSize; //Round up division
  Serial.println("File Size: " + String(myFile.size()));
  Serial.println("Expected Packets: " + String(packets));
  
  //Send the Server the Number of Packets to expect
  byte tBuffer[32];
  sprintf(tBuffer,"packets (%u)",packets);
  client.write(tBuffer, 32);
  delay(100);
  
  //Send the File in packets
  if (myFile) {

            byte clientBuf[packetSize];
            int clientCount = 0;
             
            while(myFile.available())
            {
              clientBuf[clientCount] = myFile.read();
              clientCount++;

              if(clientCount > packetSize-1)
              {
                //Serial.println("Packet");
                client.write(clientBuf,packetSize);
                clientCount = 0;
                packets++;
              }
            }
            //final <PacketSize byte cleanup packet
            if(clientCount > 0) {
              client.write(clientBuf,clientCount); 
              packets++; 
            }           
            Serial.println("Done: " + String(packets) + " packets sent");
            // close the file:
            myFile.close();
          }
}

//Send the Data.csv File via Serial
void sendDataFile(){
  File dataFile = SD.open("Data.csv");
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    Serial.println("File Complete CSV\n");
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening");
  }
}

//Send latest Picture taken to Serial
void sendLastPicture(){
    File dataFile = SD.open(latestPic);
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    Serial.println("File Complete JPG\n");
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening");
  }
}

String infoSD(){
  // set up variables using the SD utility library functions:
  Sd2Card card;
  SdVolume volume;
  SdFile root;
  
   // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

// print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
  
  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }
  
  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

  
