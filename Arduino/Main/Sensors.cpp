/*
 * DHT22 : Humidity and temperature Sensor
 * BH1750: Light Sensor
 * DS3231: RTC 
 * (8) Analog Soil Moisture Sensor
 * Analog Water Level Sensor
 *
 * Author: Michael Alvarado
 */
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

//Soil Moisture
int dry0, wet0, dry1, wet1, dry2, wet2, dry3, wet3, dry4, wet4, dry5, wet5, dry6, wet6, dry7, wet7;


void setupRTC(){
  //Set RTC
  Wire.begin();
}

void setupSensors(){
  //Set DHT Sensor
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  //Set Light Sensor
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  //Set Reservoir Water Level Sensors
  pinMode(ReservoirFloatSensor1, INPUT);
  digitalWrite(ReservoirFloatSensor1, HIGH);
  pinMode(ReservoirFloatSensor2, INPUT);
  digitalWrite(ReservoirFloatSensor2, HIGH);
  pinMode(ReservoirFloatSensor3, INPUT);
  digitalWrite(ReservoirFloatSensor3, HIGH);
  pinMode(ReservoirFloatSensor4, INPUT);
  digitalWrite(ReservoirFloatSensor4, HIGH);
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

void calibrateMoisture(int dry, int wet, int sensor){
  if(sensor == 0){
    dry0 = dry;
    wet0 = wet;
  }
  if(sensor == 1){
    dry1 = dry;
    wet1 = wet;
  }
  if(sensor == 2){
    dry2 = dry;
    wet2 = wet;
  }
  if(sensor == 3){
    dry3 = dry;
    wet3 = wet;
  }
  if(sensor == 4){
    dry4 = dry;
    wet4 = wet;
  }
  if(sensor == 5){
    dry5 = dry;
    wet5 = wet;
  }
  if(sensor == 6){
    dry6 = dry;
    wet6 = wet;
  }
  if(sensor == 7){
    dry7 = dry;
    wet7 = wet;
  }
}

//Measure Soil Moisture (0,1,2,3,4,5,6,7) returns -1 if not valid input
float measureMoisture(int sensor){

  int sensorPin;
  int cal_dry;
  int cal_wet;

  if (sensor == 0){
    sensorPin = SoilMoisture0;
    cal_dry = dry0;
    cal_wet = wet0;
  } 
  else if (sensor == 1){
    sensorPin = SoilMoisture1;
    cal_dry = dry1;
    cal_wet = wet1;
  } 
  else if (sensor == 2){
    sensorPin = SoilMoisture2;
    cal_dry = dry2;
    cal_wet = wet2;
  } 
  else if (sensor == 3) {
    sensorPin = SoilMoisture3;
    cal_dry = dry3;
    cal_wet = wet3;
  }
  else if (sensor == 4){
    sensorPin = SoilMoisture4;
    cal_dry = dry4;
    cal_wet = wet4;
  } 
  else if (sensor == 5){
    sensorPin = SoilMoisture5;
    cal_dry = dry5;
    cal_wet = wet5;
  }
  else if (sensor == 6){
    sensorPin = SoilMoisture6;
    cal_dry = dry6;
    cal_wet = wet6;
  }
  else if (sensor == 7){
    sensorPin = SoilMoisture7;
    cal_dry = dry7;
    cal_wet = wet7;
  }
  else return -1;

  float val = (float)analogRead(sensorPin); //Sense analog read
  val = 100 - map(val, cal_wet, cal_dry, 0, 100); //Calibration (250(dry)-583(wet))
  val = constrain(val, 0 , 100); //Contrain the values if needed
  return val;

  /*else if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
    }
  else if(sensor == 2) (1-(float)analogRead(SoilMoisture1)/1023)*100; //TEST
  else if(sensor == 3) return analogRead(SoilMoisture1); // TEST soil 1 analog purely
  else if(sensor == 4) return analogRead(SoilMoisture4); // Uncalibrated
  else if(sensor == 5) return analogRead(SoilMoisture5); // Uncalibrated
  else if(sensor == 6) return analogRead(SoilMoisture6); // Uncalibrated
  else if(sensor == 7) return analogRead(SoilMoisture7); // Uncalibrated
  else return -1; //Invalid Sensor Option
  return (1-(float)analogRead(sensorPin)/1023)*100; //Equation of ADC Convertion in %*/
}

float measureMoisture(){
  return measureMoisture(1);
}

//Container Water Level Sensor
float measureContainerWaterLevel(){
  return (float)analogRead(ContainerWaterLevel);
}


//Reservoir Float Switch Sensor
/*Measure all Reservoir Float Switch Sensors (HIGH or LOW)*/
int measureReservoirFloatSensor(int sensor){
  if(sensor == 1){
    return (int)digitalRead(ReservoirFloatSensor1);
  }
  else if(sensor == 2){
    return (int)digitalRead(ReservoirFloatSensor2);
  }
  else if(sensor == 3){
    return (int)digitalRead(ReservoirFloatSensor3);
  }
  else if(sensor == 4){
    return (int)digitalRead(ReservoirFloatSensor4);
  }
  else{
    return -1;
  }
}

/*Reservoir Water Level(VERY HIGH, HIGH, MEDIUM, LOW ,VERY LOW)*/
/*Depends on the measurements obtained from the different reservoir float sensors*/
String getReservoirWaterLevel(){
  int ReservoirFloatSensor_1 = measureReservoirFloatSensor(1);
  int ReservoirFloatSensor_2 = measureReservoirFloatSensor(2);
  int ReservoirFloatSensor_3 = measureReservoirFloatSensor(3);
  int ReservoirFloatSensor_4 = measureReservoirFloatSensor(4);

  if(ReservoirFloatSensor_1 == HIGH && ReservoirFloatSensor_2 == HIGH && ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH ){
    Serial.println("VERY HIGH");
    return "VERY HIGH";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == HIGH && ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH){
    Serial.println("HIGH");
    return "HIGH";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == LOW && ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH){
    Serial.println("MEDIUM");
    return "MEDIUM";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == LOW && ReservoirFloatSensor_3 == LOW && ReservoirFloatSensor_4 == HIGH){
    Serial.println("LOW");
    return "LOW";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == LOW && ReservoirFloatSensor_3 == LOW && ReservoirFloatSensor_4 == LOW){
    Serial.println("VERY LOW");
    saveLog(25, "Very Low Reservoir Water Level", 4, "Very Low water level in reservoir");
    return "VERY LOW";
  }
  else{ 
    Serial.println("ERROR"); //add savelog that shows all measureReservoirWaterLevel() so they can spot the float switch that is giving problems.
    saveLog(28, "Reservoir Water Level Error", 4, (String)("Float sensors conflicting values: ") + "Reservoir Float Sensor 1: " + (String)ReservoirFloatSensor_1 + " Reservoir Float Sensor 2: " 
    + (String)ReservoirFloatSensor_2 + " Reservoir Float Sensor 3: " + (String)ReservoirFloatSensor_3 + " Reservoir Float Sensor 4: " + (String)ReservoirFloatSensor_4);
    return "ERROR";
    
  }
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