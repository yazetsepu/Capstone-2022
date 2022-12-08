#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <DS3231.h>

//Analog Pins
#define WaterLevel 2     //Analog Water Level Sensor
#define SoilMoisture0 8  //Soil Moisture Sensor 0
#define SoilMoisture1 9  //Soil Moisture Sensor 1
#define SoilMoisture2 10 //Soil Moisture Sensor 2
#define SoilMoisture3 11 //Soil Moisture Sensor 3
#define SoilMoisture4 12 //Soil Moisture Sensor 4
#define SoilMoisture5 13 //Soil Moisture Sensor 5
#define SoilMoisture6 14 //Soil Moisture Sensor 6
#define SoilMoisture7 15 //Soil Moisture Sensor 7
#define ReservoirFloatSensor1 22     //Digital Reservoir Float Switch Sensor 1
#define ReservoirFloatSensor2 23     //Digital Reservoir Float Switch Sensor 2
#define ReservoirFloatSensor3 24     //Digital Reservoir Float Switch Sensor 3
#define ReservoirFloatSensor4 25     //Digital Reservoir Float Switch Sensor 4
//Digital Pins
#define DHTPIN 2         // Digital pin connected to the DHT sensor 

//Setup
void setupRTC();
void setupSensors();
//BH1750
float measureLight();
//DHT
float measureTemperature();
float measureHumidity();
//RTC
String timeNowString();
String timeNowStringDashed();
String dateNowStringDashed();
DateTime currentTime();
void setRTC(String timeString);
//Analog Soil Moisture
float measureMoisture();
float measureMoisture(int sensor);
//Analog Water Level
float measureWaterLevel();
//Digital Reservoir Water Level
int measureReservoirFloatSensor(int sensor);
String getReservoirWaterLevel();

#endif
