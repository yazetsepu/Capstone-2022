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
  saveLog(00, "Setup Sensors", 0 , "");

  //Set Reservoir Float Switch Sensors
  pinMode(ReservoirFloatSensor1, INPUT_PULLUP);
  pinMode(ReservoirFloatSensor2, INPUT_PULLUP);
  pinMode(ReservoirFloatSensor3, INPUT_PULLUP);
  pinMode(ReservoirFloatSensor4, INPUT_PULLUP);
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
  return (String) now.year() + "-"
  + (String)now.month() + "-"
  + (String)now.day()+ "T"
  + (String)now.hour()+ ":"
  + (String)now.minute()+ ":"
  + (String)now.second() + "-04:00";
}

//For Time HH-MM-SS Naming
String timeNowStringDashed() {
  DateTime now = myRTC.now();
  return (String)now.hour() + "-"
  + (String)now.minute();
}

//For Time YYYY-MM-DD Naming
String dateNowStringDashed() {
 DateTime now = myRTC.now();
  return (String) now.year() + ""
  + (String)now.month() + ""
  + (String)now.day();
}

DateTime currentTime(){
  return myRTC.now();
}

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
                  byte& hour, byte& minute, byte& second, String inString) {
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    boolean gotString = false;
    char inChar;
    byte temp1, temp2;
    
    Serial.println(inString);
    // Read year first
    temp1 = (byte)inString[0] -48;
    temp2 = (byte)inString[1] -48;
    year = temp1*10 + temp2;
    // now month
    temp1 = (byte)inString[2] -48;
    temp2 = (byte)inString[3] -48;
    month = temp1*10 + temp2;
    // now date
    temp1 = (byte)inString[4] -48;
    temp2 = (byte)inString[5] -48;
    date = temp1*10 + temp2;
    // now Day of Week
    dOW = (byte)inString[6] - 48;
    // now hour
    temp1 = (byte)inString[7] -48;
    temp2 = (byte)inString[8] -48;
    hour = temp1*10 + temp2;
    // now minute
    temp1 = (byte)inString[9] -48;
    temp2 = (byte)inString[10] -48;
    minute = temp1*10 + temp2;
    // now second
    temp1 = (byte)inString[11] -48;
    temp2 = (byte)inString[12] -48;
    second = temp1*10 + temp2;
}

void setRTC(String timeString){
  DS3231 clockRTC;

  byte year;
  byte month;
  byte date;
  byte dOW;
  byte hour;
  byte minute;
  byte second; 

  getDateStuff(year, month, date, dOW, hour, minute, second, timeString);
  
  clockRTC.setClockMode(false);  // set to 24h
  //setClockMode(true); // set to 12h
  clockRTC.setYear(year);
  clockRTC.setMonth(month);
  clockRTC.setDate(date);
  clockRTC.setDoW(dOW);
  clockRTC.setHour(hour);
  clockRTC.setMinute(minute);
  clockRTC.setSecond(second);
}

//Measure Soil Moisture (0,1,2,3,4,5,6,7) returns -1 if not valid input
float measureMoisture(int sensor){
  int sensorPin;
  if (sensor == 0) {
    sensorPin = SoilMoisture0;
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
    }
  else if(sensor == 2) {
    sensorPin = SoilMoisture2; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 3) return analogRead(SoilMoisture1); // TEST soil 1 analog purely
  else if(sensor == 4) return analogRead(SoilMoisture4); // Uncalibrated
  else if(sensor == 5) return analogRead(SoilMoisture5); // Uncalibrated
  else if(sensor == 6) return analogRead(SoilMoisture6); // Uncalibrated
  else if(sensor == 7) return analogRead(SoilMoisture7); // Uncalibrated
  else return -1; //Invalid Sensor Option
  return (1-(float)analogRead(sensorPin)/1023)*100; //Equation of ADC Convertion in %
}

float measureMoisture(){
  return measureMoisture(1);
}

//Water Level Sensor
float measureWaterLevel(){
  return (float)analogRead(WaterLevel);
}

/*Reservoir Float Switch Sensor*/
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
  Serial.println(ReservoirFloatSensor_1);
  delay(100);
  int ReservoirFloatSensor_2 = measureReservoirFloatSensor(2);
  Serial.println(ReservoirFloatSensor_2);
  delay(100);
  int ReservoirFloatSensor_3 = measureReservoirFloatSensor(3);
  Serial.println(ReservoirFloatSensor_3);
  delay(100);
  int ReservoirFloatSensor_4 = measureReservoirFloatSensor(4);
   Serial.println(ReservoirFloatSensor_4);
  delay(100);

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
    Serial.println("ERROR"); 
    //add savelog that shows all measureReservoirWaterLevel() so they can spot the float switch that is giving problems.
    saveLog(28, "Reservoir Water Level Error", 4, (String)("Float sensors conflicting values: ") + "Reservoir Float Sensor 1: " + (String)ReservoirFloatSensor_1 + ", Reservoir Float Sensor 2: " 
    + (String)ReservoirFloatSensor_2 + ", Reservoir Float Sensor 3: " + (String)ReservoirFloatSensor_3 + ", Reservoir Float Sensor 4: " + (String)ReservoirFloatSensor_4);
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