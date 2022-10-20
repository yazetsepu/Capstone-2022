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
 * Pin 4: SD Enable (SPI)
 * Pin 31: Water Pump
 * Pin 7: Ethernet Enable (SPI)
 * Pin 48: Arducam 1 Enable (SPI)
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
 * MOSI (50): SD, Ethernet and Arducam
 * MISO (51): SD, Ethernet and Arducam
 * SCK (52): SD, Ethernet and Arducam
 * 
 * Author: Michael Alvarado
 */
 
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <DS3231.h>
#include <BH1750.h>
#include <SD.h>
#include "DataManager.h"
 
//Digital Pins
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22     // DHT 22
DHT_Unified dht(DHTPIN, DHTTYPE);
#define LedPin 3 //TEST LED
//Analog Pins
#define WaterLevel 2 //Analog Water Level Sensor
#define SoilMoisture0 8 //Soil Moisture Sensor 0
#define SoilMoisture1 9 //Soil Moisture Sensor 1

//Actuators Pins
#define WaterPump 31

//RTC variable
RTClib myRTC;
//dateTime function to set DateTime on Files
void dateTime(uint16_t* date, uint16_t* time){
  DateTime RTC = myRTC.now();
  *date = FAT_DATE(RTC.year(), RTC.month(), RTC.day());
  *time = FAT_TIME(RTC.hour(),RTC.minute(), RTC.second());
}

//Light Sensor
BH1750 lightMeter;

//Communication variables
String data;
int count;

//Actuators Parameter;
int dimLevel=255;

//Loop Delay
uint32_t delayMS;

//Timer Variable
unsigned long startDataTime;
unsigned long startPictureTime;

void setup() {
  // initialize serial communication:
  Serial.begin(57600);
  
      //Set RTC
    Wire.begin();

    //Setup SD
    SdFile::dateTimeCallback(dateTime); //Calls dateTime function for getting datetime in files
    setupSD();

    //Setup Camera
    setupCameras();
    
    //Setup server
    //connectToServer();
    
    //Set DHT Sensor
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    // Set delay between sensor readings based on sensor details.
    delayMS = sensor.min_delay / 1000;

    //Set Light Sensor
    lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

    //Set Water Pump
    pinMode(WaterPump, OUTPUT);
    digitalWrite(WaterPump, LOW);
    
    //Set up timer
    startDataTime = millis();
    startPictureTime = millis();
    Serial.println("Boot complete");
}

void loop() {
  //Perform Commands sent by PC connection
  if(Serial.available()){
    data = Serial.readString();
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
  doc["Time"] = timeNow();
  serializeJson(doc, Serial); 
  Serial.write("\n"); //This is to mark end of data (expected on GUI side)

  //Save data if timer pass value (10s)
  if((millis()-startDataTime)>= 10000){
    Serial.println("Data Collection Started:");
    int ColumnNumber = 13;
    String data[ColumnNumber] = {timeNow(), (String)measureLight(), (String)measureTemperature(), (String)measureHumidity(), (String)measureMoisture(0), (String)measureMoisture(1),
      (String)measureMoisture(2), (String)measureMoisture(3), (String)measureMoisture(4), (String)measureMoisture(5), (String)measureMoisture(6), (String)measureMoisture(7),
      (String)measureWaterLevel()};
    saveDataToSD(data, ColumnNumber);
    startDataTime = millis();
    Serial.println("Data Collection Done");
  }

  //Take picture
  if(millis()-startPictureTime>=20000){
        Serial.println("Image Collection Started:");
        capturePictureSD();
        //connectToServer();
        startPictureTime = millis();
        Serial.println("Image Collection Done");
  }

  //Water Check
  if(measureMoisture() < 20){
      //wateringLoop();
  }
  
  delay(delayMS); //Loop delay
}

//Watering Check (TODO Check Water is flowing)
void wateringLoop(){
  //Safety Check Variables
  long int startWaterTime = millis();
  float startWaterLevel = measureWaterLevel();
  if(startWaterLevel >= 100){Serial.println("Water Level already Full"); return;}
  //Check if water Level have been reached
  float waterLevel = measureWaterLevel();
  //Check Water Levels
  while (waterLevel < 100){
    //Water Pump On
      //Turn Water Pump On
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(WaterPump, HIGH);
      waterLevel = measureWaterLevel();
      Serial.println(waterLevel);
      //Safety Check
      delay(100);
      //If some time has passed and water level has not filled
      long int timeNow = millis()-startWaterTime;
      Serial.println("Time: " + (String)timeNow);
      if(timeNow > (long int)1000){
          //Stop the Water System
          digitalWrite(LED_BUILTIN, LOW);
          digitalWrite(WaterPump, LOW);
          Serial.println("Water System Fail");
          return;
        }
      }
  //Water level reached turn off water pump
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WaterPump, LOW);
  Serial.println("Water System has been successful");
}

//Run commands according to string received
void runCommand(String command){
  Serial.println("Command received: " + command+"\n");
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
    else if(command == "Water On"){
      digitalWrite(WaterPump, HIGH);
    }
    else if (command == "Water Off"){
      digitalWrite(WaterPump, LOW);
    }
    else if(command == "Water Plant"){
      wateringLoop();
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
    
}

//Using BH1750
float measureLight(){
  while (!lightMeter.measurementReady(true)); //Wait for measurement to be ready
  float lux = lightMeter.readLightLevel();
  lightMeter.configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  return lux;
}


//Using Temperature DHT
float measureTemperature() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    return -1; //Error
  }
  else {
    return event.temperature;
  }
}

//Using Humidity DHT
float measureHumidity(){
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    return -1;   //Error
  }
  else {
    return event.relative_humidity;
  }
}

//Water Level Sensor
float measureWaterLevel(){
  return (float)analogRead(WaterLevel);
}

String timeNow(){
  DateTime now = myRTC.now();
  return (String) now.year() + "/"
  + (String)now.month() + "/"
  + (String)now.day()+ " "
  + (String)now.hour()+ ":"
  + (String)now.minute()+ ":"
  + (String)now.second();
}


float measureMoisture(){
  return (1-(float)analogRead(SoilMoisture1)/1023)*100;
}

//Measure Soil Moisture (0,1,2,3,4,5,6,7) returns -1 if not valid input
float measureMoisture(int sensor){
  int sensorPin;
  if (sensor == 0) sensorPin = SoilMoisture0;
  else if (sensor == 1) sensorPin = SoilMoisture1;
  else return -1;
  return (1-(float)analogRead(sensorPin)/1023)*100;
}


//NOT TESTED To increase accuracy it would be good to average multiple values taken in short term
float averagedAnalogRead(int N, int pin){
  float temp = 0;
  for(int i=0; i=N; i++){
      temp += analogRead(pin);
      delay(50);
  }
  return temp/N;
}
