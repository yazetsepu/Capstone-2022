/*
 * Wiznet Ethernet Shield Memory and Web-Client control.
 * This class manage Data Store locally and data transfer to the server/serial
 *
 * Author: Michael Alvarado
 */
#include "DataManager.h"
#include "Sensors.h"
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

#define RootFolder "CSS/"                 //Root Folder where all CSS data is stored
#define DataFlagFile "CSS/DataFlag.txt"   //Flag Data for unupdated files in server (All data is here in JSON format already)
#define ImageFlagFile "CSS/PathFlag.txt"  //Flag Image for unupdated images in server (Only paths are saved here)

String latestPic = "";                    //TEST Set latest pic address to send serial
String FileAddress = RootFolder;          //Root Address Folder (Index subfolder will be provided at setup)
String getImageFolder() {return FileAddress+F("Images/");}           //Return Folder Address to save images 
String getLogAddress() {return FileAddress+F("LOG.csv");}            //Return Log File Address
String getDataAddress() {return FileAddress+F("DATA.csv");}          //Return Data File Address
String getLightScheduleAddress() {return FileAddress+F("Light.csv");}//Return Light Schedule list File Address
String getCalibrationAddress() {return (String)RootFolder+F("Cal.csv");}//Return Light Schedule list File Address
String getPlantStatusAddress() {return FileAddress+F("Plant.csv");}//Return Light Schedule list File Address


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address

// Server IP Address
//IPAddress server(52, 146, 9, 96);                               // numeric IP
char server[] = "css.eastus.cloudapp.azure.com";                  // name address for TCP Deep Learn Server (using DNS)
char serverBackEnd[] = "cssrumapi.azurewebsites.net";             // name address for BackEnd Server (using DNS)
char serverHttp[] = "google.com";                                 // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;      //TCP Image Client
EthernetClient clientHttp;  //HTTP Back End Client

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement
bool sdAvailable = false;

/*
* Setup
*/
//dateTime function to set DateTime on Files
void dateTime(uint16_t* date, uint16_t* time){
  DateTime RTC = currentTime();
  *date = FAT_DATE(RTC.year(), RTC.month(), RTC.day());
  *time = FAT_TIME(RTC.hour(),RTC.minute(), RTC.second());
}

//Setup hardware and session files/folders
bool setupSD(){
  // PinMode and disable
  pinMode(ETH_CS,OUTPUT);
  digitalWrite(ETH_CS, HIGH);

  pinMode(SD_CS,OUTPUT);
  //SD Start
  Serial.print("Starting SD..");
  if(!SD.begin(SD_CS)) {Serial.println("failed"); return false;}
  else {
    Serial.println("ok");
    //Set the SD dateTime to RTC
    SdFile::dateTimeCallback(dateTime); //Calls dateTime function for getting datetime in files

    //Create a Session folder to store files (Adds a folder with increasing number)
    int fileNumber = 0;
    while(SD.exists(FileAddress+(String)fileNumber)) fileNumber++;  //Check last index to create folder
    FileAddress = FileAddress+(String)fileNumber+"/";               //Add Index to Session FileAddress
    //FileAddress = FileAddress+dateNowStringDashed()+"/";              //Add Date format
    if(!SD.exists(FileAddress)){
      //Initialize all files
      Serial.println("Create Folder: " + FileAddress);
      if(!SD.mkdir(FileAddress)) Serial.println("ERROR File Path");       //Create Session Folder
      if(!SD.mkdir(getImageFolder())) Serial.println("ERROR Image Path"); //Create Image Session Folder

      //Create Data CSV File and header titles
      File dataFile = SD.open(getDataAddress(), FILE_WRITE);
      delay(1000); //Load Delay
      if(dataFile){
        //Add header Title
        dataFile.println("TimeStamp(YYYY/MM/DD HH:MM:SS),Light (lux),Temperature (C),Humidity(%RH),Soil Moisture 0 (%),Soil Moisture 1 (%),Soil Moisture 2 (%),Soil Moisture 3 (%),Soil Moisture 4 (%),Soil Moisture 5 (%),Soil Moisture 6 (%),Soil Moisture 7 (%),Water Level, Reservoir Water Level");
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
  digitalWrite(SD_CS, HIGH);
  sdAvailable = true;
  return true;
}


/*
* File Managment
*/
//This method save all data in the array into a CSV file called Data.csv
void saveDataToSD(String data[], int sizeData){
  if(!sdAvailable){
    return; //Return if no SD
  }
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

//Save Log with given parameter into the log.csv file
void saveLog(int code, String name, int severity, String message){
  if(!sdAvailable){
    return; //Return if no SD
  }
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
    Serial.println("Log saved to SD: " + name);
  } else {
    // if the file didn't open, print an error:
    Serial.println("error saving log to SD");
  }
}

//Flag JSON Data as un-updated on server (DataFlagFile)
void flagData(){
  if(!sdAvailable){
    return;
  }
  //Get JSON Data
  StaticJsonDocument<1000> doc;
  doc["Light"] = measureLight();
  doc["Temperature"] = measureTemperature();
  doc["Humidity"] = measureHumidity();
  doc["Soil_Moisture_0"] = measureMoisture(0);
  doc["Soil_Moisture_1"] = measureMoisture(1);
  doc["Water_Level"] = measureWaterLevel();
  doc["Time"] = timeNowString();
  //Write Json Data to File
  File myFile = SD.open(DataFlagFile, FILE_WRITE);
  delay(1000);

  if(myFile){
    serializeJson(doc, myFile); 
    myFile.close(); // close the file:
    Serial.println("Data Flagged");
  }
  else {
    Serial.println("Error in Data Flag File");
  }
}

//Flag the given Image Address as un-updated on server (ImageFlagFile)
void flagImage(String path){
  if(!sdAvailable){
    return; //Return if no SD
  }
   //Write Json Data to File
  File myFile = SD.open(ImageFlagFile, FILE_WRITE);
  delay(1000);

  if(myFile){
    myFile.println(path);
    myFile.close(); // close the file:
    Serial.println("Image Flagged");
    latestPic = path; //TEST
  }
  else {
    Serial.println("Error in Image Flag File");
  }
}


/*
* Serial Communication
*/
//Send file with given Address by Serial
bool sendFile(String path){
  if(!sdAvailable){
    return; //Return if no SD
  }
  File dataFile = SD.open(path);
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    Serial.println("File Complete");
    dataFile.close();
    return true;
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening");
    return false;
  }
}

//Send the Data.csv File via Serial
void sendDataFile(){
  if(!sdAvailable){
    return; //Return if no SD
  }
  File dataFile = SD.open(getDataAddress());
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
  if(!sdAvailable){
    return; //Return if no SD
  }
  //Get the File from SD
  File myFile = SD.open(latestPic); 
  
  //Calculation of packets needed to send
  int packetSize = 100; //This is limited by RAM. (Bigger better if RAM available)
  int packets = (myFile.size() + (packetSize - 1)) / packetSize; //Round up division
  //Serial.println("File Size: " + String(myFile.size()));
  //Serial.println("Expected Packets: " + String(packets));
  
  //Send the Server the Number of Packets to expect
  // byte tBuffer[32];
  // sprintf(tBuffer,"packets (%u)",packets);
  // client.write(tBuffer, 32);
  // delay(100);
  
  //Send the File in packets
  if (myFile) {
    byte buffer[packetSize];
    int clientCount = 0;
      
    while(myFile.available())
    {
      buffer[clientCount] = myFile.read();
      clientCount++;

      if(clientCount > packetSize-1)
      {
        //Serial.println("Packet");
        Serial.write(buffer,packetSize);
        clientCount = 0;
        packets++;
      }
    }
    //final <PacketSize byte cleanup packet
    if(clientCount > 0) {
      Serial.write(buffer,clientCount); 
      packets++; 
    }          
    Serial.println(""); 
    Serial.println("File Complete JPG");
    //Serial.println("Done: " + String(packets) + " packets sent");
    // close the file:
    myFile.close();
  }
}

//Prints in Serial the SD info (storage and file addresses)
void infoSD(){
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


/*
* Server Communication
*/
//Get JSON Data from Flag and send it to server
void GetDataFlag(){
  File dataFile = SD.open(DataFlagFile);
  String json = "";
  if (dataFile) {
    //Get Next JSON Data
    while (dataFile.available()) {
      char c = dataFile.read(); //read char by char
      Serial.write(c); //print Serial
      json += c; //Add to json String
      //end of line
      if(c == "/n"){
        break;
      }
    }
    String dataLeft = "";
    //Get the all the other Data
    while (dataFile.available()) {
      char c = dataFile.read(); //read char by char
      dataLeft += c; //Add to json String
      //end of line
      if(c == "/n"){
        break;
      }
    }

    //Convert to JSON (TODO)

    //Send JSON to Client (TODO)

    //If sent succesfully erase that line from file (TODO)
    //If not save log error (TODO)


    Serial.println("File Complete");
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {Serial.println("error opening");}
  return;
}

//TEST
void HTTPRequest(){
      // Make a HTTP request:
    clientHttp.println("GET /search?q=arduino HTTP/1.1");
    clientHttp.println("Host: "+String(serverHttp));
    clientHttp.println("Connection: close");
   // client.print(F("Content-Length: ")); //File Leg
    //client.println(file.size()); //File Size
    clientHttp.println();
      delay(3000);

  int len = clientHttp.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    clientHttp.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
  }
}

void backEndGet(){
  // Make a HTTP request:
  clientHttp.println("GET /environmentaldata/classid HTTP/1.1");
  clientHttp.println("Host: "+String(serverBackEnd));
  //clientHttp.println("Access-Control-Allow-Origin: *");
  clientHttp.println("Connection: close");
  // client.print(F("Content-Length: ")); //File Leg
  //client.println(file.size()); //File Size
  clientHttp.println(); //End HTTP Request

  while(clientHttp.connected()){
    if(clientHttp.available()){
      char c = clientHttp.read();
      Serial.print(c);
    }
  }
}

void JSONSendHttp(int pic_Id){
     if (!clientHttp.connect(serverBackEnd, 80)){
     Serial.println("Error connecting to Server Back-End");
     return;
  } 

  //String json = "{\"temperature\":28.5,\"humidity\":83.8,\"soil moisture\":68,\"water level\":890,\"times_tamps\":\"2022/11/14 20:52:40\"}";
  StaticJsonDocument<300> doc;
  doc["light"] = measureLight();
  doc["temperature"] = measureTemperature();
  doc["humidity"] = measureHumidity();
  doc["soil_Moisture_1"] = measureMoisture(0);
  doc["soil_Moisture_2"] = measureMoisture(1);
  doc["soil_Moisture_3"] = measureMoisture(2);
  doc["soil_Moisture_4"] = measureMoisture(3);
  doc["soil_Moisture_5"] = measureMoisture(4);
  doc["soil_Moisture_6"] = measureMoisture(5);
  doc["soil_Moisture_7"] = measureMoisture(6);
  doc["soil_Moisture_8"] = measureMoisture(7);
  doc["water_Level"] = measureWaterLevel();
  doc["reservoir_Water_Level"] = getReservoirWaterLevel();
  if(pic_Id != -1) {doc["pictures_Id"] = pic_Id;}
  serializeJson(doc, Serial); 
   // Make a HTTP request:
  clientHttp.println("POST /environmentaldata/ HTTP/1.1");
  clientHttp.println("Host: "+String(serverBackEnd));
  //clientHttp.println("User-Agent: Arduino/1.0");
  clientHttp.println("Connection: close");
  clientHttp.println("Content-Type: application/json");
  clientHttp.print("Content-Length: ");
  clientHttp.println(measureJson(doc));
  clientHttp.println();                 //End HTTP Header
  //Serial.println(json);
  //clientHttp.println(json);            //Send Data JSON
  serializeJson(doc, clientHttp);   //Send Data to Server
  //clientHttp.println();               //End of Http Request
  
  //delay(1000);

  while(clientHttp.connected()){   //read Http Response
    if(clientHttp.available()){
      char c = clientHttp.read();
      Serial.print(c);
    }
  }
  Serial.println();
}

int CommandGetHttp(String *command, String *value){
   if (!clientHttp.connect(serverBackEnd, 80)){
     Serial.println("Error connecting to Server Back-End");
     return -1;
  } 
  String json = "{ }";  //Expected Empty JSON (Body must be JSON)

  // Make a HTTP request:
  clientHttp.println("PUT /Commands/Command_Read HTTP/1.1");
  clientHttp.println("Host: "+String(serverBackEnd));
  //clientHttp.println("User-Agent: Arduino/1.0");
  //clientHttp.println("Connection: keep-alive");
  clientHttp.println("Connection: close");
  clientHttp.println("Content-Type: application/json");
  clientHttp.print("Content-Length: ");
  clientHttp.println(json.length());
  clientHttp.println();                 //End HTTP Header
  //Serial.println(json);  
  clientHttp.println(json);            //Send Data JSON BODY
  //clientHttp.println();

  //Read HTTP Response
  // Check HTTP status
  char status[32] = {0};
  clientHttp.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    //Serial.print(F("Unexpected response: "));
    //Serial.println(status);
    clientHttp.stop();
    return 500;
  }
  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!clientHttp.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    clientHttp.stop();
    return -1;
  }

  //Skip the Header in the JSON 
  char jsonSize[32] = {0};
  clientHttp.readBytesUntil('\r\n', jsonSize, sizeof(jsonSize));
  //Serial.println(jsonSize);

  String jsonResponse = ""; 
  jsonResponse = clientHttp.readStringUntil('\r\n');
  Serial.println(jsonResponse);
  Serial.println("Size of: " + (String)jsonResponse.length());

  //Initialize JSON Document
  DynamicJsonDocument doc(350);

  // Parse JSON object
  Serial.println("RAM available: "+(String)FreeRam());
  DeserializationError error = deserializeJson(doc, jsonResponse);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    clientHttp.stop();
    return -1;
  }
  *command = (String)((char*) doc["command_String"]);
  *value = (String)((char*) doc["command_Value"]);

  client.stop();
  return 200;
}

void CommandPerformedHttp(String log){
   if (!clientHttp.connect(serverBackEnd, 80)){
     Serial.println("Error connecting to Server Back-End");
     return;
  } 
  String json = "{ \"logs\" : {\"log_Text\" : \"" + log + "\" } }";  //Expected Empty JSON (Body must be JSON)

  // Make a HTTP request:
  clientHttp.println("PUT /Commands/Command_Performed HTTP/1.1");
  clientHttp.println("Host: "+String(serverBackEnd));
  //clientHttp.println("User-Agent: Arduino/1.0");
  clientHttp.println("Connection: close");
  clientHttp.println("Content-Type: application/json");
  clientHttp.print("Content-Length: ");
  clientHttp.println(json.length());
  clientHttp.println();                 //End HTTP Header
  Serial.println(json);  
  clientHttp.println(json);            //Send Data JSON BODY
  //clientHttp.println();
  //Read HTTP Response
  String response = "";
  while(clientHttp.connected()){   //read Http Response
    if(clientHttp.available()){
      char c = clientHttp.read();
      response += c;
      //Serial.print(c);
    }
  }
  //Parse HTTP JSON Body
  // String jsonRespond = response.substring(response.indexOf('{'), response.indexOf('}')+1);  //Get JSON in Body
  // //Serial.println("Response: "+jsonRespond);
  // StaticJsonDocument<200> doc;                    //JSON Variable
  // deserializeJson(doc, jsonRespond);              //Parse JSON
}

//Send JSON Enviromental Data to TCP Server
void JSONSend(){
  if (client.connect(server, 54010)) {
    client.write("JSON");       //Send header for JSON data
    delay(100);
    //Get Data JSON
    StaticJsonDocument<100> doc;
    doc["light"] = measureLight();
    doc["temperature"] = measureTemperature();
    doc["humidity"] = measureHumidity();
    doc["soil_Moisture_1"] = measureMoisture(0);
    doc["soil_Moisture_2"] = measureMoisture(1);
    doc["water_Level"] = measureWaterLevel();
    //doc["times_tamps"] = timeNowString();
    serializeJson(doc, client);   //Send Data to Server
    delay(100);
    client.write("*");       //Send tail of connection
    //client.stop();
  }
}

//Send image byte[] to server
void TCPSendImage(int cam){  
  File myFile = SD.open(latestPic);   //Get the File from SD
  //Calculation of packets needed to send
  int packetSize = 100;   //This is limited by RAM. (Bigger better if RAM available)
  int packets = (myFile.size() + (packetSize - 1)) / packetSize; //Round up division
  Serial.println("File Size: " + String(myFile.size()));
  Serial.println("Expected Packets: " + String(packets));
  
  //Send the Server the Number of Packets to expect
  byte tBuffer[32];                         //Header Buffer
  memset(tBuffer, 0, sizeof(tBuffer));      //Allocate memory for the buffer  
  sprintf(tBuffer,"packets (%u) (%u)",packets, cam);  //Format the Header "packets (#packets)"
  if(sprintf < 0){Serial.println("Error sprintf");} 
  client.write(tBuffer, 32);                //Send header to Server
  delay(300);                               //Delay to make sure server is ready
  //free(tBuffer);                            //Deallocate memory for the buffer

  //Send the File in packets
  if (myFile) {
    byte clientBuf[packetSize];     //File Buffer
    memset(clientBuf, 0, sizeof(packetSize));      //Allocate memory for the buffer  
    int clientCount = 0;            //Buffer index
      
    while(myFile.available())       //File Loop
    {
      clientBuf[clientCount] = myFile.read(); //Add packet size bytes from file to buffer
      clientCount++;                        

      if(clientCount > packetSize-1)          //Buffer full (up to packet size)
      {
        if(!client.availableForWrite()){break;}         //If disconnected stop process
        client.write(clientBuf,packetSize);   //Send packet to server
        clientCount = 0;                      //Reset buffer index
      }
    }
    if(clientCount > 0) {                     //final packet 
      client.write(clientBuf,clientCount);    //Send remainder bytes from files
    }   
    // close the file:
    Serial.println("Done: " + String(packets) + " packets sent");
    //free(clientBuf);
    myFile.close();                           //Close file
  }
}

//Read/Write Image to TCP Server
String TCPImageTransfer(int cam){
  // if you get a connection, report back via serial:
  if (client.connect(server, 54010)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    TCPSendImage(cam);                        //Send Image with TCP format
    delay(2000);                        //Wait some time for the reply
    int len = client.available();       //byte available to read
    if(len>0){                          //If Data Available read
      byte buffer[80];                    //Set Buffer
      memset(buffer, 0, sizeof(buffer));  //Allocate memory for buffer
      client.read(buffer, len);           //Read reply from server
      Serial.write(buffer, len);          //Print Results
      Serial.println();
      return String((char *)buffer);      //Convert byte[] to String
    }
    return "";
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    return "";
  }
}  

void initializeEthernet(){
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        Serial.println("Stuck");
        delay(100); // do nothing, no point running without Ethernet hardware
        //initializeEthernet();
        return;
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  }
  else {
    Serial.print("DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  //Connect to TCP Server
  if (client.connect(server, 54010)){ 
    Serial.println("TCP Server active"); 
    client.write("Ping");               //Ping the Server
    client.setTimeout(1000);
  }
  else Serial.println("TCP Server Offline"); 

  //Connect to Backend web server (HTTP)
  if (clientHttp.connect(serverBackEnd, 80)){
     Serial.println("HTTP Server active");
     //backEndGet();
     //JSONSendHttp();
     //HTTPRequest();
     clientHttp.stop();
  } 
  else Serial.println("HTTP Server Offline"); 
}

//Save the plant image response
void logPlantStatus(String imagePath, String status){
  //Write to SD
  File myFile = SD.open(getPlantStatusAddress(), FILE_WRITE);
  delay(1000);
  // if the file opened okay, write to it:
  if (myFile) {
    String dataEntry = timeNowString() + ","+ imagePath + ","+ status;
    myFile.println(dataEntry); //Add row
    // close the file:
    myFile.close();
    Serial.println("Log Plant Status saved to SD");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error saving log to SD");
  }
}

//Connects to server 
void sendImageTCP(String imagePath, int cam) {
  //Check Ethernet Connection
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    return;
  }

  //Send image to the TCP server
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");
  //delay(1000);
  String result = TCPImageTransfer(cam);      //Send image to server and get respond
  logPlantStatus(imagePath, result);      //Log result
  //beginMicros = micros();
}  


int EndCapture(){
  if (client.connect(server, 54010)) {
    //Send the Server the Number of Packets to expect
    byte tBuffer[32];                         //Header Buffer
    memset(tBuffer, 0, sizeof(tBuffer));      //Allocate memory for the buffer  
    sprintf(tBuffer,"End Capture");  //Format the Header "packets (#packets)"
    if(sprintf < 0){Serial.println("Error sprintf");} 
    client.write(tBuffer, 32);                //Send header to Server
    delay(200);                               //Delay to make sure server is ready

    //Read Pic_ID reply
    while(!client.available()){if(!client.connected())break;}         //Wait Reply
    int len = client.available();       //byte available to read
    if(len>0){                          //If Data Available read
      String reply = client.readString();
      int pic_Id = reply.toInt();
      return pic_Id;      //Convert byte[] to String
    }
    else{
      Serial.write("No Reply");
    }
  }
  return -1;
}

//Loop to fetch server respond (UNTESTED)
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

    // // do nothing forevermore:
    // while (true) {
    //   delay(1);
    // }
  }
}
