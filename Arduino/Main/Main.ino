/**
 * Capstoneer Project
 * Chamaecrista Sustainability System (CSS)
 * 
 * Functionality:
 * Light control (RGBW LED PWM)
 * Water Irrigation (Water pump, Water Valve)
 * Data Collection Humidity (RH), Temperature (C), Soil Moisture (%), Light (lux) and Images (JPG)
 * 
 * Digital Pins
 * Pin 2: DHT22
 * Pin 3: LED TEST
 * Pin 31: Water Pump
 * 
 * Analog Pins
 * Pin A2: Water Level
 * Pin A8: Soil Moisture 0
 * Pin A9: Soil Moisture 1
 * 
 * I2C Pins
 * SDA: BH1750, RTC and Arducam
 * SCL: BH1750, RTC and Arducam
 * 
 * SPI Pins
 * MISO (50): SD, Ethernet and Arducam
 * MOSI (51): SD, Ethernet and Arducam
 * SCK (52): SD, Ethernet and Arducam
 * Pin 4: SD Enable
 * Pin 7: Ethernet Enable 
 * Pin 48: Arducam 1 Enable 
 * 
 * Author: Michael Alvarado
 */
 
#include <ArduinoJson.h>
#include <SD.h>
#include "DataManager.h"
#include "Sensors.h"
#include "WaterSystem.h"

//Digital Pins
#define LedPin 3 //TEST LED

//dateTime function to set DateTime on Files
void dateTime(uint16_t* date, uint16_t* time){
  DateTime RTC = currentTime();
  *date = FAT_DATE(RTC.year(), RTC.month(), RTC.day());
  *time = FAT_TIME(RTC.hour(),RTC.minute(), RTC.second());
}

//Communication variables
int count;

//Actuators Parameter;
int dimLevel=255;

//Loop Delay
uint32_t delayMS = 500;

//Timer Variable
unsigned long startDataTime;
unsigned long startPictureTime;

void setup() {
  // initialize serial communication:
  Serial.begin(57600);

  //Setup Sensors
  setupSensors();

  //Setup SD
  SdFile::dateTimeCallback(dateTime); //Calls dateTime function for getting datetime in files
  setupSD();

  //Setup Camera
  setupCameras();
  
  //Setup server
  //connectToServer();

  //Setup Water System
  setupWaterSystem();

  //Set LED PWM
  pinMode(LedPin, OUTPUT);  // sets the pin as output

  //Set up timer
  startDataTime = millis();
  startPictureTime = millis();

  //Log the boot of system
  saveLog(01, "Boot Complete", 0, "");
  Serial.println("Boot complete");
}

void loop() {
  //Perform Commands sent by PC connection
  if(Serial.available()){
    String data = Serial.readString();
    runCommand(data);
  }

  //Measure and send all data on Serial (JSON format)
  StaticJsonDocument<1000> doc;
  doc["Light"] = measureLight();
  doc["Temperature"] = measureTemperature();
  doc["Humidity"] = measureHumidity();
  doc["Soil_Moisture_0"] = measureMoisture(0);
  doc["Soil_Moisture_1"] = measureMoisture(1);
  doc["Water_Level"] = measureWaterLevel();
  doc["Time"] = timeNowString();
  serializeJson(doc, Serial); 
  Serial.write("\n"); //This is to mark end of data (expected on GUI side)

  //Save data if timer pass value (10s)
  if((millis()-startDataTime)>= 10000){
    Serial.println("Data Collection Started:");
    digitalWrite(LED_BUILTIN, HIGH); //LED for Visual TEST
    int ColumnNumber = 13; //Number of parameter
    //Measure All data and save it in array as String
    String data[ColumnNumber] = {timeNowString(), (String)measureLight(), (String)measureTemperature(), (String)measureHumidity(), (String)measureMoisture(0), (String)measureMoisture(1),
      (String)measureMoisture(2), (String)measureMoisture(3), (String)measureMoisture(4), (String)measureMoisture(5), (String)measureMoisture(6), (String)measureMoisture(7),
      (String)measureWaterLevel()};
    //Save Data in CSV File
    saveDataToSD(data, ColumnNumber);
    //Reset Timer
    startDataTime = millis();
    digitalWrite(LED_BUILTIN, LOW); //LED for Visual TEST
    //Log the Success of Capture Data
    saveLog(10, "Capture Data", 0, "");
    Serial.println("Data Collection Done");
  }

  //Take picture if picture timer
  if(millis()-startPictureTime>=50000){
        Serial.println("Image Collection Started:");
        digitalWrite(LED_BUILTIN, HIGH);
        capturePictureSD();
        //connectToServer();
        startPictureTime = millis();
        saveLog(10, "Capture Image", 0, "");
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Image Collection Done");
  }

  //Water Check
  float moisture = measureMoisture();
  if(moisture < 50){
      saveLog(20, "Watering Start", 0, "Moisture Level: "+(String)moisture);
      //waterPlant();
  }
  
  delay(delayMS); //Loop delay
}


//Run commands according to string received
void runCommand(String command){
  Serial.println("Command received: " + command+"\n");
  saveLog(16, "Command Received", 0, command);
  if (command == "LED ON"){
      digitalWrite(LedPin, HIGH);
      Serial.write("On");
    }
    else if (command == "LED OFF"){
      digitalWrite(LedPin, LOW);
      Serial.write("Off");
    }
    else if (command == "Humidity"){
      Serial.print(measureHumidity());
    }
    else if (command == "Light"){
      Serial.print(measureLight());
    }
    else if (command == "Temperature"){
      Serial.print(measureTemperature());
      count++; //Testing command count
    }
    else if(command.indexOf("DIM") >= 0){
      String dimValue = command.substring(command.indexOf("(")+1, command.indexOf(")"));
      dimLevel = dimValue.toInt();
      analogWrite(LedPin, dimLevel);
    }
    else if(command == "Water Plant"){
      waterPlant();
    }
    else if(command == "Get Data File"){
      sendDataFile();
    }
    else if(command == "SD info"){
      infoSD();
    }
    else if(command == "Last Picture"){
      sendLastPicture();
    }
    
    else {//INVALID Command
      Serial.println("Invalid Command");
      saveLog(19, "Invalid Command", 2, command);
    } 
}


