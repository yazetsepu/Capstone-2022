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
 * Pin A10: Soil Moisture 2
 * Pin A11: Soil Moisture 3
 * Pin A12: Soil Moisture 4
 * Pin A13: Soil Moisture 5
 * Pin A14: Soil Moisture 6
 * Pin A15: Soil Moisture 7
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
unsigned long startDataTime;
unsigned long startPictureTime;

void setup() {
  // initialize serial communication:
  Serial.begin(57600);

  //Setup RTC
  setupRTC();

  //Setup SD
  setupSD();

  //Setup Sensors
  setupSensors();

  //Setup Camera
  setupCameras();
  
  //Setup server
  //connectToServer();

  //Setup Water System
  setupWaterSystem();

  //Setup Light System
  setupLightSystem();

  //Set up timer
  startDataTime = millis();
  startPictureTime = millis();

  //Log the boot of system
  saveLog(1, "Boot Complete", 0, "Boot Time: "+millis());
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
  doc["Soil_Moisture_2"] = measureMoisture(2);
  doc["Soil_Moisture_3"] = measureMoisture(3);
  doc["Soil_Moisture_4"] = measureMoisture(4);
  doc["Soil_Moisture_5"] = measureMoisture(5);
  doc["Soil_Moisture_6"] = measureMoisture(6);
  doc["Soil_Moisture_7"] = measureMoisture(7);
  doc["Container_Water_Level"] = measureContainerWaterLevel();
  doc["Reservoir_Water_Level"] = getReservoirWaterLevel(); //String VERY HIGH, HIGH, MEDIUM, LOW, VERY LOW
  doc["Time"] = timeNowString();
  serializeJson(doc, Serial); 
  Serial.write("\n"); //This is to mark end of data (expected on GUI side)

  //Save data if timer pass value (10s)
  if((millis()-startDataTime)>= 10000){
    Serial.println("Data Collection Started:");
    digitalWrite(LED_BUILTIN, HIGH); //LED for Visual TEST
    int ColumnNumber = 14; //Number of parameter
    //Measure All data and save it in array as String
    String data[ColumnNumber] = {timeNowString(), (String)measureLight(), (String)measureTemperature(), (String)measureHumidity(), (String)measureMoisture(0), (String)measureMoisture(1),
      (String)measureMoisture(2), (String)measureMoisture(3), (String)measureMoisture(4), (String)measureMoisture(5), (String)measureMoisture(6), (String)measureMoisture(7),
      (String)measureContainerWaterLevel(), (String)getReservoirWaterLevel()}; 
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
        Serial.println("Image Location: "+ captureImageToSD(1)); //Take Picture
        //connectToServer();
        startPictureTime = millis();
        saveLog(10, "Capture Image", 0, "");
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Image Collection Done");
  }

  //Water Check
  float moistureSum = measureMoisture(0) + measureMoisture(1) + measureMoisture(2) + measureMoisture(3) + 
  measureMoisture(4) + measureMoisture(5) + measureMoisture(6) + measureMoisture(7);
  
  float moistureAverage = moistureSum / 8.0;

  if(moistureAverage < 50){
      saveLog(20, "Watering Start", 0, "Moisture Level: "+(String)moistureAverage);
      waterPlant();
  }

  //Reservoir Check 
  getReservoirWaterLevel(); //Not necessary?

  checkSchedule();

  delay(delayMS); //Loop delay
}


//Run commands according to string received
void runCommand(String command){
  Serial.println("Command received: " + command+"\n");
  saveLog(16, "Command Received", 0, command);
  if (command == "LED ON"){
    dimRed(250);
    dimGreen(250);
    dimBlue(250);
    dimWhite(250);
    Serial.write("On");
  }
  else if (command == "LED OFF"){
    dimRed(0);
    dimGreen(0);
    dimBlue(0);
    dimWhite(0);
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
  }
  else if(command.indexOf("LED DIM") >= 0){ //Ex. DIM {R},{G},{B},{W}  DIM {250},{20},{10},{0} 
    int index0 = command.indexOf("{");
    int index1 = command.indexOf("}");
    int index2 = command.indexOf("{", index1 + 1);
    int index3 = command.indexOf("}", index1 + 1);
    int index4 = command.indexOf("{", index3 + 1);
    int index5 = command.indexOf("}", index3 + 1);
    int index6 = command.indexOf("{", index5 + 1);
    int index7 = command.indexOf("}", index5 + 1);
    
    int dimValue1 = command.substring(index0 + 1, index1).toInt();
    int dimValue2 = command.substring(index2 + 1, index3).toInt();
    int dimValue3 = command.substring(index4 + 1, index5).toInt();
    int dimValue4 = command.substring(index6 + 1, index7).toInt();

    dimRed(dimValue1);
    dimGreen(dimValue2);
    dimBlue(dimValue3);
    dimWhite(dimValue4);
    
    /*String dimValue = command.substring(command.indexOf("(")+1, command.indexOf(")"));
    dimBlue(dimValue.toInt());*/
  }
  else if(command == "Water Plant"){
    waterPlant();
  }
  else if(command.indexOf("Calibrate Moisture") >= 0){ //Ex Calibrate Moisture {dry},{wet},{sensor}  Calibrate Moisture {550},{209},{1} 
    int index0 = command.indexOf("{");
    int index1 = command.indexOf("}");
    int index2 = command.indexOf("{", index1 + 1);
    int index3 = command.indexOf("}", index1 + 1);
    int index4 = command.indexOf("{", index3 + 1);
    int index5 = command.indexOf("}", index3 + 1);
    int dryval = command.substring(index0 + 1, index1).toInt();
    Serial.println(dryval);
    int wetval = command.substring(index2 + 1, index3).toInt();
    Serial.println(wetval);
    int soilMoisture = command.substring(index4 + 1, index5).toInt();
    Serial.println(soilMoisture);
    calibrateMoisture(dryval,wetval,soilMoisture);
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
  /*else if(command.indexOf("Add time Schedule") >= 0){ 
    addSchedule(17, 19, 0, 0, 100, 250);
  }*/
  else if(command.indexOf("Schedule Dim") >= 0){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, command.substring(12));
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    addSchedule((int)doc["hour"], (int)doc["minute"], (int)doc["W"], (int)doc["R"], (int)doc["G"], (int)doc["B"]);
  }
  else if(command == "Light Schedule"){
    getScheduleSerial();
  }
  else {//INVALID Command
    Serial.println("Invalid Command");
    saveLog(19, "Invalid Command", 2, command);
  } 
}


