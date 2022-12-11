#include "SD.h"
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

int dry0,dry1,dry2,dry3,dry4,dry5,dry6,dry7;                                //Analog Dry Value Soil Moisture
int wet0,wet1,wet2,wet3,wet4,wet5,wet6,wet7;                                //Analog Wet Value Soil Moisture
int vwcDry0, vwcDry1, vwcDry2, vwcDry3, vwcDry4, vwcDry5, vwcDry6, vwcDry7; //Volumetric Water Content Dry Reference
int vwcWet0, vwcWet1, vwcWet2, vwcWet3, vwcWet4, vwcWet5, vwcWet6, vwcWet7; //Volumetric Water Content Wet Reference

void setupRTC(){
  //Set RTC
  Wire.begin();
}

//Create Calibration File if needed
void createCalibrationFile(){
  //Create Calibration File CSV 
  File calibrationFile = SD.open(getCalibrationAddress(), O_RDWR);    //Overwrite File
  delay(1000); //Load Delay
  if(calibrationFile){ 
    //Get Values
    
    calibrationFile.println("0, 0, 0, 0, 0, 0, 0, 0");                  //VWC Reference (Dry)
    calibrationFile.println("100, 100, 100, 100, 100, 100, 100, 100");  //VWC Reference (Wet)
    calibrationFile.println("580,580,580,580,580,580,580,580");         //Dry Analog Values
    calibrationFile.println("200,200,200,200,200,200,200,200");         //Wet Analog Values
    calibrationFile.close();   // close the file:
  }
  else{
    Serial.println("Error in Write Calibration Setting file");
  }
}

//Calibrate Soil Moisture with Calibration File
void setupCalibration(){
  //Create Light Schedule CSV File 
  File calibrationFile = SD.open(getCalibrationAddress());
  delay(1000); //Load Delay
  if(calibrationFile){ 
    //Initialize Temp Variables
    int index1, index2, index3, index4, index5, index6, index7;

    //Get VWC Value 
    String vwcDry = calibrationFile.readStringUntil('\n');
    // delimiter CSV ','
    index1 = vwcDry.indexOf(',');
    index2 = vwcDry.indexOf(',', index1+1);
    index3 = vwcDry.indexOf(',', index2+1);
    index4 = vwcDry.indexOf(',', index3+1);
    index5 = vwcDry.indexOf(',', index4+1);
    index6 = vwcDry.indexOf(',', index5+1);
    index7 = vwcDry.indexOf(',', index6+1);
    //Set Dry VWC Reference
    vwcDry0 =  vwcDry.substring(0, index1).toInt();
    vwcDry1 =  vwcDry.substring(index1+1, index2).toInt();
    vwcDry2 =  vwcDry.substring(index2+1, index3).toInt();
    vwcDry3 =  vwcDry.substring(index3+1, index4).toInt();
    vwcDry4 =  vwcDry.substring(index4+1, index5).toInt();
    vwcDry5 =  vwcDry.substring(index5+1, index6).toInt();
    vwcDry6 =  vwcDry.substring(index6+1, index7).toInt();
    vwcDry7 =  vwcDry.substring(index7+1).toInt();

    //Get VWC Value 
    String vwcWet = calibrationFile.readStringUntil('\n');
    // delimiter CSV ','
    index1 = vwcWet.indexOf(',');
    index2 = vwcWet.indexOf(',', index1+1);
    index3 = vwcWet.indexOf(',', index2+1);
    index4 = vwcWet.indexOf(',', index3+1);
    index5 = vwcWet.indexOf(',', index4+1);
    index6 = vwcWet.indexOf(',', index5+1);
    index7 = vwcWet.indexOf(',', index6+1);
    //Set Dry VWC Reference
    vwcWet0 =  vwcWet.substring(0, index1).toInt();
    vwcWet1 =  vwcWet.substring(index1+1, index2).toInt();
    vwcWet2 =  vwcWet.substring(index2+1, index3).toInt();
    vwcWet3 =  vwcWet.substring(index3+1, index4).toInt();
    vwcWet4 =  vwcWet.substring(index4+1, index5).toInt();
    vwcWet5 =  vwcWet.substring(index5+1, index6).toInt();
    vwcWet6 =  vwcWet.substring(index6+1, index7).toInt();
    vwcWet7 =  vwcWet.substring(index7+1).toInt();

    //Get Dry Values
    String dryValues = calibrationFile.readStringUntil('\n');
    // delimiter CSV ','
    index1 = dryValues.indexOf(',');
    index2 = dryValues.indexOf(',', index1+1);
    index3 = dryValues.indexOf(',', index2+1);
    index4 = dryValues.indexOf(',', index3+1);
    index5 = dryValues.indexOf(',', index4+1);
    index6 = dryValues.indexOf(',', index5+1);
    index7 = dryValues.indexOf(',', index6+1);
    //Set Dry Values
    dry0 =  dryValues.substring(0, index1).toInt();
    dry1 =  dryValues.substring(index1+1, index2).toInt();
    dry2 =  dryValues.substring(index2+1, index3).toInt();
    dry3 =  dryValues.substring(index3+1, index4).toInt();
    dry4 =  dryValues.substring(index4+1, index5).toInt();
    dry5 =  dryValues.substring(index5+1, index6).toInt();
    dry6 =  dryValues.substring(index6+1, index7).toInt();
    dry7 =  dryValues.substring(index7+1).toInt();

    //Get Wet Values
    String wetValues = calibrationFile.readStringUntil('\n');
    // delimiter CSV ','
    index1 = wetValues.indexOf(',');
    index2 = wetValues.indexOf(',', index1+1);
    index3 = wetValues.indexOf(',', index2+1);
    index4 = wetValues.indexOf(',', index3+1);
    index5 = wetValues.indexOf(',', index4+1);
    index6 = wetValues.indexOf(',', index5+1);
    index7 = wetValues.indexOf(',', index6+1);
    //Set Dry Values
    wet0 =  wetValues.substring(0, index1).toInt();
    wet1 =  wetValues.substring(index1+1, index2).toInt();
    wet2 =  wetValues.substring(index2+1, index3).toInt();
    wet3 =  wetValues.substring(index3+1, index4).toInt();
    wet4 =  wetValues.substring(index4+1, index5).toInt();
    wet5 =  wetValues.substring(index5+1, index6).toInt();
    wet6 =  wetValues.substring(index6+1, index7).toInt();
    wet7 =  wetValues.substring(index7+1).toInt();

    Serial.println(vwcDry);
    Serial.println(vwcWet);
    Serial.println(dryValues);
    Serial.println(wetValues);
  }
  else{
    Serial.println("Error in READ Calibration Setting file");
  }
}

float analogMeasureMoisture(int sensor);
//Change the recalibration File for the Soil Moisture
void recalibrateSensor(bool dry, int sensor, int vwc){
  File calibrationFile = SD.open(getCalibrationAddress());
  delay(1000); //Load Delay
  if(calibrationFile){
    //Initialize Temp Variables
    int index1, index2, index3, index4, index5, index6, index7;
    String result = "";
    //Read File Lines
    String vwcDry = calibrationFile.readStringUntil('\n');
    String vwcWet = calibrationFile.readStringUntil('\n');
    String dryValues = calibrationFile.readStringUntil('\n');
    String wetValues = calibrationFile.readStringUntil('\n');

    //Change Dry Value if Dry command
    if(dry){
      index1 = vwcDry.indexOf(',');
      index2 = vwcDry.indexOf(',', index1+1);
      index3 = vwcDry.indexOf(',', index2+1);
      index4 = vwcDry.indexOf(',', index3+1);
      index5 = vwcDry.indexOf(',', index4+1);
      index6 = vwcDry.indexOf(',', index5+1);
      index7 = vwcDry.indexOf(',', index6+1);
      //Set Dry VWC Reference
      String Dry0String = sensor == 0? String(vwc) : vwcDry.substring(0, index1);
      String Dry1String = sensor == 1? String(vwc) : vwcDry.substring(index1+1, index2);
      String Dry2String = sensor == 2? String(vwc) : vwcDry.substring(index2+1, index3);
      String Dry3String = sensor == 3? String(vwc) : vwcDry.substring(index3+1, index4);
      String Dry4String = sensor == 4? String(vwc) : vwcDry.substring(index4+1, index5);
      String Dry5String = sensor == 5? String(vwc) : vwcDry.substring(index5+1, index6);
      String Dry6String = sensor == 6? String(vwc) : vwcDry.substring(index6+1, index7);
      String Dry7String = sensor == 7? String(vwc) : vwcDry.substring(index7+1);
      
      vwcDry = Dry0String + "," + Dry1String + "," + Dry2String + "," + Dry3String + "," + Dry4String + "," + Dry5String + "," + Dry6String + "," + Dry7String;
   
      index1 = dryValues.indexOf(',');
      index2 = dryValues.indexOf(',', index1+1);
      index3 = dryValues.indexOf(',', index2+1);
      index4 = dryValues.indexOf(',', index3+1);
      index5 = dryValues.indexOf(',', index4+1);
      index6 = dryValues.indexOf(',', index5+1);
      index7 = dryValues.indexOf(',', index6+1);
      //Set Dry Analog Value
      Dry0String = sensor == 0? String(analogMeasureMoisture(0)) : dryValues.substring(0, index1);
      Dry1String = sensor == 1? String(analogMeasureMoisture(1)) : dryValues.substring(index1+1, index2);
      Dry2String = sensor == 2? String(analogMeasureMoisture(2)) : dryValues.substring(index2+1, index3);
      Dry3String = sensor == 3? String(analogMeasureMoisture(3)) : dryValues.substring(index3+1, index4);
      Dry4String = sensor == 4? String(analogMeasureMoisture(4)) : dryValues.substring(index4+1, index5);
      Dry5String = sensor == 5? String(analogMeasureMoisture(5)) : dryValues.substring(index5+1, index6);
      Dry6String = sensor == 6? String(analogMeasureMoisture(6)) : dryValues.substring(index6+1, index7);
      Dry7String = sensor == 7? String(analogMeasureMoisture(7)) : dryValues.substring(index7+1);

      dryValues = Dry0String + "," + Dry1String + "," + Dry2String + "," + Dry3String + "," + Dry4String + "," + Dry5String + "," + Dry6String + "," + Dry7String;
    }
    //Change Wet Value if Wet command
    else{
      index1 = vwcWet.indexOf(',');
      index2 = vwcWet.indexOf(',', index1+1);
      index3 = vwcWet.indexOf(',', index2+1);
      index4 = vwcWet.indexOf(',', index3+1);
      index5 = vwcWet.indexOf(',', index4+1);
      index6 = vwcWet.indexOf(',', index5+1);
      index7 = vwcWet.indexOf(',', index6+1);
      //Set Wet VWC Reference
      String Wet0String = sensor == 0? String(vwc) : vwcWet.substring(0, index1);
      String Wet1String = sensor == 1? String(vwc) : vwcWet.substring(index1+1, index2);
      String Wet2String = sensor == 2? String(vwc) : vwcWet.substring(index2+1, index3);
      String Wet3String = sensor == 3? String(vwc) : vwcWet.substring(index3+1, index4);
      String Wet4String = sensor == 4? String(vwc) : vwcWet.substring(index4+1, index5);
      String Wet5String = sensor == 5? String(vwc) : vwcWet.substring(index5+1, index6);
      String Wet6String = sensor == 6? String(vwc) : vwcWet.substring(index6+1, index7);
      String Wet7String = sensor == 7? String(vwc) : vwcWet.substring(index7+1);
      
      vwcWet = Wet0String + "," + Wet1String + "," + Wet2String + "," + Wet3String + "," + Wet4String + "," + Wet5String + "," + Wet6String + "," + Wet7String;
   
      index1 = wetValues.indexOf(',');
      index2 = wetValues.indexOf(',', index1+1);
      index3 = wetValues.indexOf(',', index2+1);
      index4 = wetValues.indexOf(',', index3+1);
      index5 = wetValues.indexOf(',', index4+1);
      index6 = wetValues.indexOf(',', index5+1);
      index7 = wetValues.indexOf(',', index6+1);
      //Set Wet Analog Value
      Wet0String = sensor == 0? String(analogMeasureMoisture(0)) : wetValues.substring(0, index1);
      Wet1String = sensor == 1? String(analogMeasureMoisture(1)) : wetValues.substring(index1+1, index2);
      Wet2String = sensor == 2? String(analogMeasureMoisture(2)) : wetValues.substring(index2+1, index3);
      Wet3String = sensor == 3? String(analogMeasureMoisture(3)) : wetValues.substring(index3+1, index4);
      Wet4String = sensor == 4? String(analogMeasureMoisture(4)) : wetValues.substring(index4+1, index5);
      Wet5String = sensor == 5? String(analogMeasureMoisture(5)) : wetValues.substring(index5+1, index6);
      Wet6String = sensor == 6? String(analogMeasureMoisture(6)) : wetValues.substring(index6+1, index7);
      Wet7String = sensor == 7? String(analogMeasureMoisture(7)) : wetValues.substring(index7+1);

      wetValues = Wet0String + "," + Wet1String + "," + Wet2String + "," + Wet3String + "," + Wet4String + "," + Wet5String + "," + Wet6String + "," + Wet7String;
    }
    calibrationFile.close();   // close the file:

    calibrationFile = SD.open(getCalibrationAddress(), O_RDWR);
    calibrationFile.println(vwcDry);
    calibrationFile.println(vwcWet);
    calibrationFile.println(dryValues);
    calibrationFile.println(wetValues);
    calibrationFile.close();   // close the file:

    setupCalibration();        //Calibrate
  }
}

//Setup Light sensor and DHT
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

  //Configure Soil Moisture Calibration
  if(!SD.exists(getCalibrationAddress())) { createCalibrationFile();} //If there is a Calibration File already do nothing
  setupCalibration();
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
    val = map(val, wet0, dry0, vwcWet0, vwcDry0); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet1, dry1, vwcWet1, vwcDry1); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 2) {
    sensorPin = SoilMoisture2; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet2, dry2, vwcWet2, vwcDry2); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 3) {
    sensorPin = SoilMoisture3; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet3, dry3, vwcWet3, vwcDry3); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 4){
        sensorPin = SoilMoisture4; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet4, dry4, vwcWet4, vwcDry4); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 5) {
    sensorPin = SoilMoisture5; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet5, dry5, vwcWet5, vwcDry5); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 6) {    
    sensorPin = SoilMoisture6; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet6, dry6, vwcWet6, vwcDry6); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  }
  else if(sensor == 7) {    
    sensorPin = SoilMoisture7; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = map(val, wet7, dry7, vwcWet7, vwcDry7); //Calibration (250(wet)-583(dry))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    return val;
  } 

  else if(sensor == -1) return analogRead(SoilMoisture0); // Uncalibrated
  else return -1; //Invalid Sensor Option
  return (1-(float)analogRead(sensorPin)/1023)*100; //Equation of ADC Convertion in %
}

//Return Analog Value of the specified Soil Moisture Sensor
float analogMeasureMoisture(int sensor){
  int sensorPin;
  if (sensor == 0) {
    sensorPin = SoilMoisture0;
  }
  else if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
  }
  else if(sensor == 2) {
    sensorPin = SoilMoisture2; //Pin the sensor is located
  }
  else if(sensor == 3) {
    sensorPin = SoilMoisture3; //Pin the sensor is located
  }
  else if(sensor == 4){
    sensorPin = SoilMoisture4; //Pin the sensor is located
  }
  else if(sensor == 5) {
    sensorPin = SoilMoisture5; //Pin the sensor is located
  }
  else if(sensor == 6) {    
    sensorPin = SoilMoisture6; //Pin the sensor is located
  }
  else if(sensor == 7) {    
    sensorPin = SoilMoisture7; //Pin the sensor is located
  } 
  else return -1; //Invalid Sensor Option
  return (float)analogRead(sensorPin);  //Analog Value Return
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
  //Serial.println(ReservoirFloatSensor_1);
  delay(100);
  int ReservoirFloatSensor_2 = measureReservoirFloatSensor(2);
  //Serial.println(ReservoirFloatSensor_2);
  delay(100);
  int ReservoirFloatSensor_3 = measureReservoirFloatSensor(3);
  //Serial.println(ReservoirFloatSensor_3);
  delay(100);
  int ReservoirFloatSensor_4 = measureReservoirFloatSensor(4);
  //Serial.println(ReservoirFloatSensor_4);
  delay(100);

  if(ReservoirFloatSensor_1 == HIGH && ReservoirFloatSensor_2 == HIGH && ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH ){
    //Serial.println("VERY HIGH");
    return "VERY HIGH";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == HIGH && ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH){
    //Serial.println("HIGH");
    return "HIGH";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == LOW && ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH){
    //Serial.println("MEDIUM");
    return "MEDIUM";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == LOW && ReservoirFloatSensor_3 == LOW && ReservoirFloatSensor_4 == HIGH){
    //Serial.println("LOW");
    return "LOW";
  }
  else if(ReservoirFloatSensor_1 == LOW && ReservoirFloatSensor_2 == LOW && ReservoirFloatSensor_3 == LOW && ReservoirFloatSensor_4 == LOW){
    //Serial.println("VERY LOW");
    //saveLog(25, "Very Low Reservoir Water Level", 4, "Very Low water level in reservoir");
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