#include "Sensors.h"
#include "DataManager.h"
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <BH1750.h>
#include <DS3231.h>

//DHT
#define DHTTYPE    DHT22     // DHT 22
DHT_Unified dht(DHTPIN, DHTTYPE);
//Light Sensor
BH1750 lightMeter;
//RTC variable
RTClib myRTC;

void setupSensors(){
  //Set RTC
  Wire.begin();
  //Set DHT Sensor
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  //Set Light Sensor
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  saveLog(00, "Setup Sensors", 0 , "");
}

//Using BH1750
float measureLight(){
  while (!lightMeter.measurementReady(true)); //Wait for measurement to be ready
  float lux = lightMeter.readLightLevel();
  lightMeter.configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  return lux;
}

//Using Temperature DHT
float measureTemperature(){
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    saveLog(12, "Error Capture Data Device", 3 , "DHT disconnected");
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
    saveLog(12, "Error Capture Data Device", 3 , "DHT disconnected");
    return -1;   //Error
  }
  else {
    return event.relative_humidity;
  }
}

String timeNowString() {
  DateTime now = myRTC.now();
  return (String) now.year() + "/"
  + (String)now.month() + "/"
  + (String)now.day()+ " "
  + (String)now.hour()+ ":"
  + (String)now.minute()+ ":"
  + (String)now.second();
}

DateTime currentTime(){
  return myRTC.now();
}

//Measure Soil Moisture (0,1,2,3,4,5,6,7) returns -1 if not valid input
float measureMoisture(int sensor){
  int sensorPin;
  if (sensor == 0) sensorPin = SoilMoisture0;
  else if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
    }
  else if(sensor == 2) (1-(float)analogRead(SoilMoisture1)/1023)*100; //TEST
  else if(sensor == 3) analogRead(SoilMoisture1); // Digital TEST
  else return -1;
  return (1-(float)analogRead(sensorPin)/1023)*100;
}

float measureMoisture(){
  return measureMoisture(1);
}

//Water Level Sensor
float measureWaterLevel(){
  return (float)analogRead(WaterLevel);
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