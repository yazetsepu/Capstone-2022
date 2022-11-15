#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <DS3231.h>

//Analog Pins
#define ContainerWaterLevel 2     //Analog Container Water Level Sensor
#define ReservoirWaterLevel1 22     //Digital Reservoir Water Level Sensor 1
#define ReservoirWaterLevel2 23     //Digital Reservoir Water Level Sensor 2
#define ReservoirWaterLevel3 24     //Digital Reservoir Water Level Sensor 3
#define ReservoirWaterLevel4 25     //Digital Reservoir Water Level Sensor 4


#define SoilMoisture0 8  //Soil Moisture Sensor 0
#define SoilMoisture1 9  //Soil Moisture Sensor 1
#define SoilMoisture2 10 //Soil Moisture Sensor 2
#define SoilMoisture3 11 //Soil Moisture Sensor 3
#define SoilMoisture4 12 //Soil Moisture Sensor 4
#define SoilMoisture5 13 //Soil Moisture Sensor 5
#define SoilMoisture6 14 //Soil Moisture Sensor 6
#define SoilMoisture7 15 //Soil Moisture Sensor 7
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
DateTime currentTime();
//Analog Soil Moisture
float measureMoisture();
float measureMoisture(int sensor);
void calibrateMoisture(int dry, int wet, int sensor);
//Analog Water Level
float measureContainerWaterLevel();
int measureReservoirWaterLevel(int sensor);
String getReservoirWaterLevel();

#endif
