/**
 * Capstoneer Project
 * Chamaecrista Sustainability System (CSS)
 * 
 * Functionality:
 *  -Light control (RGBW LED PWM)
 *  -Water Irrigation (Water pump, Water Valve)
 *  -Data Collection Humidity (RH), Temperature (C), Soil Moisture (%), Light (lux) and Images (JPG)
 *  -Web-Client (HTTP)
 *  -Serial Communication
 * 
 * PINOUT: 
 * Digital Pins:
 *  Pin 2: DHT22
 *  Pin 3: LED TEST
 *  Pin 5: Blue LED
 *  Pin 6: Green LED
 *  Pin 7: Red LED
 *  Pin 8: White LED
 *  Pin 31: Water Pump
 *  Pin 22: Float Switch 1 (Highest)
 *  Pin 23: Float Switch 2
 *  Pin 24: Float Switch 3
 *  Pin 25: Float Switch 4 (Lowest)
 * 
 * Analog Pins:
 *  Pin A2: Water Level
 *  Pin A8: Soil Moisture 0
 *  Pin A9: Soil Moisture 1
 *  Pin A10: Soil Moisture 2
 *  Pin A11: Soil Moisture 3
 *  Pin A12: Soil Moisture 4
 *  Pin A13: Soil Moisture 5
 *  Pin A14: Soil Moisture 6
 *  Pin A15: Soil Moisture 7
 * 
 * I2C Pins:
 *  SDA: BH1750, RTC and Arducam
 *  SCL: BH1750, RTC and Arducam
 * 
 * SPI Pins:
 *  MISO: (50) SD, Ethernet and Arducam
 *  MOSI: (51) SD, Ethernet and Arducam
 *  SCK:  (52) SD, Ethernet and Arducam
 *  Pin 4: SD Enable
 *  Pin 10: Ethernet Enable
 *  Pin 48: Arducam 1 Enable
 *  Pin 49: Arducam 2 Enable
 *  Pin 46: Arducam 3 Enable
 *  Pin 47: Arducam 4 Enable
 * 
 * Author: Michael Alvarado
 */

#include "DataManager.h"
#include "Sensors.h"
#include "WaterSystem.h"
#include "LightSystem.h"
#include "Cameras.h"
#include <ArduinoJson.h>
#include <SD.h>

//Loop Delay
uint32_t delayMS = 500;

//Timer Variable
unsigned long CaptureTime = 50000;
unsigned long startDataTime;
unsigned long startPictureTime;
unsigned long startWater;


void(* resetFunc) (void) = 0; //declare reset function @ address 0


void setup() {
  // initialize serial communication:
  Serial.begin(57600);

  //Setup RTC (Needed first to have proper timestamp on everything else)
  setupRTC();

  //Setup SD
  if(!setupSD()){
    Serial.println("No SD");
  }

  //Setup Sensors
  setupSensors();

  //Setup Camera
  setupCameras();

  //Setup server
  initializeEthernet();

  //Setup Water System
  setupWaterSystem();

  //Setup Light System
  setupLightSystem();

  //Set up timer
  startDataTime = millis();
  startPictureTime = millis();
  startWater = millis();

  //Log the boot of system
  saveLog(1, "Boot Complete", 0, "Boot Time: "+millis());
  Serial.println("Boot complete");
}

void loop() {
  //Serial Connection
  if(Serial){
    //Perform Commands sent by PC connection
    if(Serial.available()){
      //Expected format "Command";"Value"
      String data = Serial.readString();
      String value = "";
      int delimiter = data.indexOf(';');
      if(delimiter>0){
        value = data.substring(delimiter+1);  
        data = data.substring(0, delimiter);
      }
      runCommand(data, value, true);
    }
    
    //Measure and send all data on Serial (JSON format)
    StaticJsonDocument<200> doc;
    doc["Light"] = measureLight();
    doc["Temperature"] = measureTemperature();
    doc["Humidity"] = measureHumidity();
    doc["Soil_Moisture_0"] = measureMoisture(0);
    doc["Soil_Moisture_1"] = measureMoisture(1);
    doc["Soil_Moisture_2"] = measureMoisture(2);
    doc["Soil_Moisture_3"] = measureMoisture(3);
    doc["Soil_Moisture_4"] = measureMoisture(4);
    doc["Soil_Moisture_5"] = measureMoisture(5);
    doc["Soil_Moisture_6"] = measureMoisture(6);
    doc["Soil_Moisture_7"] = measureMoisture(7);
    doc["Water_Level"] = measureWaterLevel();
    doc["reservoir_Water_Level"] = (String)getReservoirWaterLevel(); //String VERY HIGH, HIGH, MEDIUM, LOW, VERY LOW
    doc["Time"] = timeNowString();
    serializeJson(doc, Serial); 
    Serial.write("\n"); //This is to mark end of data (expected on GUI side)
  }

  fetchCommand();
  //saveDataTimer();
  //Capture Timer
  if(millis()-startPictureTime>=CaptureTime){ //50000
        Serial.println("Image Collection Started:");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(2000);

        String path1 = captureImageToSD(1);                      //Take Picture
        if(path1 != ""){                                         //Image sucessful
          Serial.println("Image Location: "+ path1);               //Write Path
          sendImageTCP(path1, 0);                                  //Send Picture to Server
          delay(2000);                                             //Wait for server to be ready
        }else Serial.println("Error Camera 1 capture");          //Error Capture
        
        String path2 = captureImageToSD(2);                      //Take Picture
        if(path2 != ""){                                         //Image sucessful
          Serial.println("Image Location: "+ path2);               //Write Path
          sendImageTCP(path2, 1);                                  //Send Picture to Server
          delay(2000);
        }else Serial.println("Error Camera 2 capture");          //Error Capture

        String path3 = captureImageToSD(3);                      //Take Picture
        if(path3 != ""){                                         //Image sucessful
          Serial.println("Image Location: "+ path3);               //Write Path
          sendImageTCP(path3, 2);                                  //Send Picture to Server
          delay(2000);
        }else Serial.println("Error Camera 3 capture");          //Error Capture

        String path4 = captureImageToSD(4);                      //Take Picture
        if(path4 != ""){                                         //Image sucessful
          Serial.println("Image Location: "+ path4);               //Write Path
          sendImageTCP(path4, 3);                                  //Send Picture to Server
        }else Serial.println("Error Camera 4 capture");          //Error Capture

        int pic_Id = -1;
        if(path1 != "" || path2 != "" || path3 != "" || path4 != "") {
          pic_Id = EndCapture();             //End of Capture if any picture was taken
        }
        saveLog(10, "Capture Image", 0, "");                     //Log the Success of Capture Image

        //JSONSend();
        JSONSendHttp(pic_Id);

        startPictureTime = millis();                             //Reset Capture Timer
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Image Collection Done");
  }

  //Water Plants by Soil Moisture
  float moisture = measureMoisture();
  Serial.println("Average Moisture: " + (String)moisture);
  if(moisture < 50 && (millis()-startWater) >= 60000*2){ //Soil Moisture Therhold reached and safety timer 
      saveLog(20, "Watering Start", 0, "Moisture Level: "+(String)moisture);
      waterPlant();           //Water the plant
      startWater = millis();  //Reset Safety Timer (Wait Moisture to increase)
  }
  
  checkSchedule(); //Check Light Schedule

  delay(delayMS); //Loop delay
}

void saveDataTimer(){
  //Save data if timer pass value (10s)
  if((millis()-startDataTime)>= 10000){
    Serial.println("Data Collection Started:");
    digitalWrite(LED_BUILTIN, HIGH);        //LED for Visual TEST

    int ColumnNumber = 14;                  //Number of parameter
    //Measure All data and save it in array as String
    String data[ColumnNumber] = {timeNowString(), (String)measureLight(), (String)measureTemperature(), (String)measureHumidity(), (String)measureMoisture(0), (String)measureMoisture(1),
      (String)measureMoisture(2), (String)measureMoisture(3), (String)measureMoisture(4), (String)measureMoisture(5), (String)measureMoisture(6), (String)measureMoisture(7),
      (String)measureWaterLevel(), (String)getReservoirWaterLevel()};
    saveDataToSD(data, ColumnNumber);       //Save Data in CSV File
    flagData();                             //Flag Data to send to Server
    
    startDataTime = millis();               //Reset Timer
    digitalWrite(LED_BUILTIN, LOW);         //LED for Visual TEST
    saveLog(10, "Capture Data", 0, "");     //Log the Success of Capture Data
    Serial.println("Data Collection Done");
  }
}

//Fetch from Server any commands
void fetchCommand(){
  //Get Commands by Server
  String command = "", value = "";
  int response = CommandGetHttp(&command, &value);
  if(response == 200){
    Serial.println("Response: "+ (String)response);
    Serial.println("Command: "+(String)command);
    Serial.println("Value: "+(String)value);
    runCommand(command, value, false);
  }
}

//Run commands according to string received
void runCommand(String command, String value, bool serial){
  //Log Command
  Serial.println("Command received: " + command+ "\tValue received: "+ value);
  saveLog(16, "Command Received", 0, command);
  //Find Command
  /* Light System Commands */
  if (command == "LED ON"){
    dimBlue(250);
    dimGreen(250);
    dimRed(250);
    dimWhite(250);
    if(!serial){CommandPerformedHttp("Successful");}
  }
  else if (command == "LED OFF"){
    dimBlue(0);
    dimGreen(0);
    dimRed(0);
    dimWhite(0);
    CommandPerformedHttp("Successful");
  }
  else if(command.indexOf("Dim") >= 0){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, value); //12 is "Schedule Dim" size
    if (error) {
      Serial.print(F("deserializeJson() failed: ")); Serial.println(error.f_str()); 
      CommandPerformedHttp("Invalid Value");
      return;
    }
    dimRed((int)doc["R"]);
    dimGreen((int)doc["G"]);
    dimBlue((int)doc["B"]);
    dimWhite((int)doc["WW"]);
    if(!serial){CommandPerformedHttp("Successful");}
  }
  else if(command.indexOf("Schedule Dim") >= 0){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, value); //12 is "Schedule Dim" size
    if (error) {
      Serial.print(F("deserializeJson() failed: ")); Serial.println(error.f_str()); 
      if(!serial)CommandPerformedHttp("Invalid Value");
      return;
    }
    addSchedule((int)doc["hour"], (int)doc["minute"], (int)doc["W"], (int)doc["R"], (int)doc["G"], (int)doc["B"]);
    if(!serial){CommandPerformedHttp("Successful");}
  }
  /* Water System Commands */
  else if(command == "Water Plant"){
    String status = waterPlant(); //Water Plant Process
    if(!serial){CommandPerformedHttp(status);}
  }
  /* Sensor Calibration */
  else if (command.indexOf("RTC Set") >= 0){
    setRTC(value); //the order YYMMDDwHHMMSS, with an 'x' at the end.
    if(!serial){CommandPerformedHttp("DONE");}
  }
  else if (command.indexOf("CalibrateWet") >= 0){
    //Parse Values
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, value); 
    if (error) {
      Serial.print(F("deserializeJson() failed: ")); Serial.println(error.f_str()); 
      if(!serial)CommandPerformedHttp("Invalid Value");
      return;
    }
    //Calibrate Sensor
    recalibrateSensor(false, (int) doc["sensor"], (int) doc["vwc"]); 
    if(!serial){CommandPerformedHttp("Calibrated");}
  }
  else if (command.indexOf("CalibrateDry") >= 0){
    //Parse Values
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, value); 
    if (error) {
      Serial.print(F("deserializeJson() failed: ")); Serial.println(error.f_str()); 
      if(!serial)CommandPerformedHttp("Invalid Value");
      return;
    }
    //Calibrate Sensor
    recalibrateSensor(true, (int) doc["sensor"], (int) doc["vwc"]); 
    if(!serial){CommandPerformedHttp("Calibrated");}
  }
  else if (command.indexOf("DefaultCalibrate") >= 0){
    //Calibrate Sensor
    createCalibrationFile();
    setupCalibration();
    return;
  }
  //Change Time for Capture Intervals
  else if (command.indexOf("CaptureTime")>=0){
    //Parse Values
    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, value); 
    if (error) {
      Serial.print(F("deserializeJson() failed: ")); Serial.println(error.f_str()); 
      if(!serial)CommandPerformedHttp("Invalid Value");
      return;
    }
    CaptureTime = (int)doc["minutes"] * 60000;     //Change Timer (60000 is to change minutes to milliseconds)
    if(!serial){CommandPerformedHttp("Capture time set to "+(String)CaptureTime + " ms");}
    return;
  }

    //Change Time for Capture Intervals
  else if (command.indexOf("CaptureTimeMS")>=0){
    //Parse Values
    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, value); 
    if (error) {
      Serial.print(F("deserializeJson() failed: ")); Serial.println(error.f_str()); 
      if(!serial)CommandPerformedHttp("Invalid Value");
      return;
    }
    CaptureTime = (int)doc["ms"];     //Change Timer in milliseconds
    if(!serial){CommandPerformedHttp("Capture time set to "+(String)CaptureTime + " ms");}
    return;
  }
  //Reset
  else if (command.indexOf("Reset")>=0){
      resetFunc();  //call reset
  }

  /* DEBUG Commands */
  else if (command == "Http Send"){
    //JSONSendHttp();
  }
  else if(command == "Light Schedule"){
    getScheduleSerial();
  }
    /* File Manage */
  else if (command.indexOf("Get File") >= 0){
    if(sendFile(command.substring(8))) saveLog(17, "Command Succesful", 1, command);
    else saveLog(18, "Command Unsuccesful", 3, command);
  }
  else if(command.indexOf("Add time Schedule") >= 0){
    addSchedule(17, 19, 0, 0, 100, 250);
  }
   else if (command == "Humidity"){
    Serial.print(measureHumidity());
  }
  else if (command == "Light"){
    Serial.print(measureLight());
  }
  else if (command == "Temperature"){
    Serial.print(measureTemperature());
  }
  else if(command == "Get Data File"){
    sendDataFile();
  }
  else if(command.indexOf("DIM") >= 0){
    String dimValue = command.substring(command.indexOf("(")+1, command.indexOf(")"));
    dimBlue(dimValue.toInt());
  }
  else if(command == "Last Picture"){
    sendLastPicture();
  }
  else if(command == "SD info"){
    infoSD();
  }
  else {//INVALID Command
    Serial.println("Invalid Command");
    saveLog(19, "Invalid Command", 2, command);
    if(!serial){CommandPerformedHttp("Invalid Command: "+command);}
  } 
}


