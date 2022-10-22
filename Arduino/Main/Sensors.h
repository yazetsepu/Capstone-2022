#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <DS3231.h>

//Analog Pins
#define WaterLevel 2 //Analog Water Level Sensor
#define SoilMoisture0 8 //Soil Moisture Sensor 0
#define SoilMoisture1 9 //Soil Moisture Sensor 1
//Digital Pins
#define DHTPIN 2     // Digital pin connected to the DHT sensor 

//Setup
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
//Analog Water Level
float measureWaterLevel();

#endif
