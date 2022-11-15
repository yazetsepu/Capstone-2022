/*
 * Arducam Mini OV5642 Mini 5MP Plus, Wiznet Ethernet Shield
 * This class manage Data Store locally and data transfer to the server/serial
 *
 * Author: Michael Alvarado
 */
#include "DataManager.h"
#include "Sensors.h"
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

String latestPic = ""; //TEST Set latest pic address to send serial
String FileAddress = "CSS/"; //Root Address Folder (Index subfolder will be provided at setup)
String getImageFolder() {return FileAddress+"Images";} //Return Folder Address to save images 
String getLogAddress() {return FileAddress+"LOG.csv";}
String getDataAddress() {return FileAddress+"DATA.csv";}
String getLightScheduleAddress() {return FileAddress+"Light.csv";}


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

//dateTime function to set DateTime on Files
void dateTime(uint16_t* date, uint16_t* time){
  DateTime RTC = currentTime();
  *date = FAT_DATE(RTC.year(), RTC.month(), RTC.day());
  *time = FAT_TIME(RTC.hour(),RTC.minute(), RTC.second());
}


void setupSD(){
  pinMode(SD_CS,OUTPUT);
  // disable w5100 while setting up SD
  pinMode(ETH_CS,OUTPUT);
  digitalWrite(ETH_CS, HIGH);
  //SD Start
  Serial.print("Starting SD..");
  if(!SD.begin(SD_CS)) Serial.println("failed");
  else {
    Serial.println("ok");
    //Set the SD dateTime to RTC
    SdFile::dateTimeCallback(dateTime); //Calls dateTime function for getting datetime in files

    //Create a Session folder to store files (Adds a folder with increasing number)
    int fileNumber = 0;
    while(SD.exists(FileAddress+(String)fileNumber)) fileNumber++; //Check last index to create folder
    FileAddress = FileAddress+(String)fileNumber+"/"; //Add Session number to path (unique int)
    Serial.println("Create Folder: " + FileAddress);
    SD.mkdir(FileAddress); //Create Session Folder
    SD.mkdir(getImageFolder()); //Create Image Session Folder


    //Create Data CSV File and header titles
    File dataFile = SD.open(getDataAddress(), FILE_WRITE);
    delay(1000); //Load Delay
    if(dataFile){
      //Add header Title
      dataFile.println("TimeStamp(YYYY/MM/DD HH:MM:SS),Light (lux),Temperature (C),Humidity(%RH),Soil Moisture 0 (%),Soil Moisture 1 (%),Soil Moisture 2 (%),Soil Moisture 3 (%),Soil Moisture 4 (%),Soil Moisture 5 (%),Soil Moisture 6 (%),Soil Moisture 7 (%),Container Water Level, Reservoir Water Level");
      dataFile.close();   // close the file:
    }
    
    //Create Log CSV File and header titles
    File logFile = SD.open(getLogAddress(), FILE_WRITE);
    delay(1000); //Load Delay
    if(logFile){ 
      //Add header Title
      logFile.println("Time Stamp,Code,Source,Name,Severity,Message");
      logFile.close();   // close the file:
    }
  }
}

//This method save all data in the array into a CSV file called Data.csv
void saveDataToSD(String data[], int sizeData){
   //Write to SD
  File myFile = SD.open(getDataAddress(), FILE_WRITE);
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

void saveLog(int code, String name, int severity, String message){
  //Write to SD
  File myFile = SD.open(getLogAddress(), FILE_WRITE);
  delay(1000);
  //Get the Source from the code
  String source = "";
  if (code<10) source = "Setup";
  else if (code<20) source = "Data";
  else if (code<30) source = "Water System";
  else if (code<30) source = "Light System";

  // if the file opened okay, write to it:
  if (myFile) {
    String dataEntry = timeNowString() + ","+ (String)code + ","+ source + "," + name + "," + (String)severity, message;
    myFile.println(dataEntry); //Add row
    // close the file:
    myFile.close();
    Serial.println("Log saved to SD");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error saving log to SD");
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

//TEST
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

  
