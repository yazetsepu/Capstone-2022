#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>

#define DHTPIN 2
#define DHTTYPE    DHT22     // DHT 22
DHT_Unified dht(DHTPIN, DHTTYPE);
int delayMS; //delay for loop

#define WaterPump 3 
#define SoilMoisture1 A3
#define ContainerWaterLevel A4
//#define SolenoidValve 6
#define ReservoirFloatSensor1 5
#define ReservoirFloatSensor2 6
#define ReservoirFloatSensor3 9
#define ReservoirFloatSensor4 10

unsigned long startDataTime;

int water;
int dry1 = 550;
int wet1 = 209;
//const int dry = 550;
//const int wet = 209;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //Set DHT Sensor
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  //Set Water Pump Pin
  pinMode(WaterPump, OUTPUT);

  //Set Reservoir Float Switch Sensors
  pinMode(ReservoirFloatSensor1, INPUT_PULLUP);
  pinMode(ReservoirFloatSensor2, INPUT_PULLUP);
  pinMode(ReservoirFloatSensor3, INPUT_PULLUP);
  pinMode(ReservoirFloatSensor4, INPUT_PULLUP);
  /*pinMode(ReservoirFloatSensor1, INPUT);
  digitalWrite(ReservoirFloatSensor1, HIGH);
  pinMode(ReservoirFloatSensor2, INPUT);
  digitalWrite(ReservoirFloatSensor2, HIGH);*/
  /*pinMode(ReservoirFloatSensor3, INPUT);
  digitalWrite(ReservoirFloatSensor3, HIGH);
  pinMode(ReservoirFloatSensor4, INPUT);
  digitalWrite(ReservoirFloatSensor4, HIGH);*/

  startDataTime = millis();
}

void loop() {
  //Perform Commands sent by PC connection
  if(Serial.available()){
    String data = Serial.readString();
    runCommand(data);
  }


  if((millis()-startDataTime)>= 10000){
  //Measure and send all data on Serial (JSON format)
  StaticJsonDocument<500> doc;
  doc["Temperature"] = measureTemperature();
  doc["Humidity"] = measureHumidity();
  doc["Soil_Moisture_1"] = measureMoisture(1);
  doc["Container_Water_Level"] = measureContainerWaterLevel();
  doc["Reservoir _Water_Level"] = getReservoirWaterLevel(); //String VERY HIGH, HIGH, MEDIUM, LOW, VERY LOW
  serializeJson(doc, Serial); 
  Serial.write("\n"); //This is to mark end of data (expected on GUI side)
  startDataTime = millis();
  }

  /*Temperature and Humidity*/
 // Serial.println("Temperature: "+(String)measureTemperature());
 // Serial.println("Humidity: "+(String)measureHumidity());

  /*Reservoir Water Level*/
  //getReservoirWaterLevel();

  /*Tests*/
  /*Serial.println(digitalRead(ReservoirWaterLevel1));
  if(digitalRead(ReservoirWaterLevel1) == LOW){
    Serial.println("Reservoir Water Level LOW");
  }
  else{
    Serial.println("Reservoir Water Level HIGH");
  }
  delay(5000);
  
  Serial.println(digitalRead(ReservoirWaterLevel2));
  if(digitalRead(ReservoirWaterLevel2) == LOW){
    Serial.println("Reservoir Water Level LOW");
  }
  else{
    Serial.println("Reservoir Water Level HIGH");
  }
  delay(5000);*/


 /* digitalWrite(WaterPump, LOW); //activated 
  delay(5000);
  digitalWrite(WaterPump, HIGH); //deactivated
  delay(5000);*/

  /*digitalWrite(SolenoidValve, HIGH); //deactivated
  delay(7000);
  digitalWrite(SolenoidValve, LOW); //activated 
  delay(7000);*/


  /*Water Check*/
  float moisture = measureMoisture(1);
  //Serial.println(measureContainerWaterLevel());
  if(moisture < 50){
    //saveLog(20, "Watering Start", 0, "Moisture Level: "+(String)moisture);
    waterPlant();
  }

  delay(delayMS);
}

void runCommand(String command){
  Serial.println("Command received: " + command+"\n");
  if(command.indexOf("Water On") >= 0) {Serial.println("On"); digitalWrite(WaterPump, HIGH);}
  else if(command.indexOf("Water Off") >= 0) {Serial.println("Off"); digitalWrite(WaterPump, LOW);}
  else if(command == "Water Plant"){
    waterPlant();
  }
  else if(command.indexOf("DIM") >= 0){ // DIM {250},{20},{10},{0} DIM {R},{G},{B},{W}
    int index0 = command.indexOf("{");
    int index1 = command.indexOf("}");
    int index2 = command.indexOf("{", index1 + 1);
    int index3 = command.indexOf("}", index1 + 1);
    int index4 = command.indexOf("{", index3 + 1);
    int index5 = command.indexOf("}", index3 + 1);
    int index6 = command.indexOf("{", index5 + 1);
    int index7 = command.indexOf("}", index5 + 1);
    
    int dimValue1 = command.substring(index0 + 1, index1).toInt();
    Serial.println(dimValue1);
    int dimValue2 = command.substring(index2 + 1, index3).toInt();
    Serial.println(dimValue2);
    int dimValue3 = command.substring(index4 + 1, index5).toInt();
    Serial.println(dimValue3);
    int dimValue4 = command.substring(index6 + 1, index7).toInt();
    Serial.println(dimValue4);

    /*dimRed(dimValue1);
    dimGreen(dimValue2)
    dimBlue(dimValue3);
    dimWhite(dimValue4);*/

    /*String dimValue = command.substring(command.indexOf("(")+1, command.indexOf(")"));
    dimBlue(dimValue.toInt());*/
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

    /*int index0 = command.indexOf("("); 
    int index1 = command.indexOf("["); 
    int index2 = command.indexOf("]"); 
    int index3 = command.indexOf(")"); 
    int dryval = command.substring(index0 + 1, index1).toInt();
    Serial.println(dryval);
    int wetval = command.substring(index1 + 1, index2).toInt();
    Serial.println(wetval);
    int soilMoisture = command.substring(index2 + 1, index3).toInt();
    Serial.println(soilMoisture);
    calibrateMoisture(dryval,wetval,soilMoisture);*/
  }
  else {//INVALID Command
      Serial.println("Invalid Command");
  } 
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

/* Fill Container */
void waterPlant(){
  //Safety Check Variables
  long int startWaterTime = millis();
  float startWaterLevel = measureContainerWaterLevel();
  //Check Initial Container Water Level
  if(startWaterLevel >= 100){
    Serial.println("Container Water Level already Full");  
    return; 
  }
  //Check if water Level have been reached
  float waterLevel = measureContainerWaterLevel();
  //Log initialize Container Watering Proccess
  //Check Container Water Levels
  while (waterLevel < 100){
    //Water Pump On
    //Turn Water Pump On
    //digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(WaterPump, HIGH);
    waterLevel = measureContainerWaterLevel();
    Serial.println(waterLevel);
    //Safety Check
    delay(100);
    //If some time has passed and container water level has not filled
    //container water level or water pump damaged
    long int currentTime = millis()-startWaterTime;
    //Serial.println("Time: " + (String)currentTime);
    if(currentTime > (long int)10000){
        //Stop the Container Water System
        //digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(WaterPump, LOW);
        Serial.println("Container Water System Fail");
        delay(100);
        return;
    }
  }
  //Container Water level reached turn off water pump
  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WaterPump, LOW);
  Serial.println("Container Water System has been successful");
  delay(100);
}


/* Fill Reservoir */
/*void fillReservoir(){
  //Safety Check Variables
  long int startWaterTime = millis();
  float startWaterLevel = measureReservoirWaterLevel(1);
  //Check Initial Reservoir Water Level
  if(startWaterLevel >= 100){
    Serial.println("Reservoir Water Level already Full");  
    return;
  }
  //Check if Reservoir Water Level have been reached
  float waterLevel = measureReservoirWaterLevel(1);
  //Log initialize Reservoir Watering Proccess
  //Check Reservoir Water Levels
  while (waterLevel < 100){
    //Solenoid Valve On
    //Turn Solenoid Valve On
    //digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(SolenoidValve, HIGH);
    waterLevel = measureReservoirWaterLevel(1);
    Serial.println(waterLevel);
    //Safety Check
    delay(100);
    //If some time has passed and reservoir water level has not filled
    //water level or solenoid valve damaged
    //*** Check quantity of time
    long int currentTime = millis()-startWaterTime;
    Serial.println("Time: " + (String)currentTime);
    if(currentTime > (long int)20000){
        //Stop the Reservoir Water System
        //digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(SolenoidValve, LOW);
        Serial.println("Reservoir Filling Fail");
        return;
    }
  }
  //Reservoir Water level reached turn off solenoid valve
  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(SolenoidValve, LOW);
  Serial.println("Reservoir Filling has been successful");
}*/

float measureContainerWaterLevel(){
  return (float)analogRead(ContainerWaterLevel);
  //return (float)averagedAnalogRead(10,ContainerWaterLevel);
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
/*Depends on the measurements obtained from the different reservoir float switch sensors*/
String getReservoirWaterLevel(){
  int ReservoirFloatSensor_1 = measureReservoirFloatSensor(1);
  delay(100);
  int ReservoirFloatSensor_2 = measureReservoirFloatSensor(2);
  delay(100);
  int ReservoirFloatSensor_3 = measureReservoirFloatSensor(3);
  delay(100);
  int ReservoirFloatSensor_4 = measureReservoirFloatSensor(4);
  delay(100);

  /*if(ReservoirFloatSensor_3 == HIGH && ReservoirFloatSensor_4 == HIGH){
    //Serial.println("VERY HIGH");
    return "VERY HIGH";
  }
  else if(ReservoirFloatSensor_3 == LOW && ReservoirFloatSensor_4 == HIGH){
    //Serial.println("HIGH");
    return "HIGH";
  }*/

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
    //saveLog(25, "Very Low Reservoir Water Level", 4, "Very Low water level in reservoir");
    return "VERY LOW";
  }
  else{ 
    //Serial.println("ERROR"); //add savelog that shows all measureReservoirWaterLevel() so they can spot the float switch that is giving problems.
    /*saveLog(28, "Reservoir Water Level Error", 4, (String)("Float sensors conflicting values: ") + "Reservoir Float Sensor 1: " + (String)ReservoirFloatSensor_1 + "Reservoir Float Sensor 2: " 
    + (String)ReservoirFloatSensor_2 + "Reservoir Float Sensor 3: " + (String)ReservoirFloatSensor_3 + "Reservoir Float Sensor 4: " + (String)ReservoirFloatSensor_4);*/
    Serial.println((String)("Float sensors conflicting values: ") + "Reservoir Float Sensor 1: " + (String)ReservoirFloatSensor_1 + ", Reservoir Float Sensor 2: " 
    + (String)ReservoirFloatSensor_2 + ", Reservoir Float Sensor 3: " + (String)ReservoirFloatSensor_3 + ", Reservoir Float Sensor 4: " + (String)ReservoirFloatSensor_4);
    /*Serial.println((String)("Float sensors conflicting values: ") + "Reservoir Float Sensor 3: " + (String)ReservoirFloatSensor_3 + ", Reservoir Float Sensor 4: " 
    + (String)ReservoirFloatSensor_4);*/
    return "ERROR";
  }
}


float measureMoisture(int sensor){
  int sensorPin;
  int cal_dry;
  int cal_wet;
  //if (sensor == 0) sensorPin = SoilMoisture0;
  if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
    cal_dry = dry1;
    cal_wet = wet1;
  }
  else return -1; //Invalid Sensor Option
  float val = (float)analogRead(sensorPin); //Sense analog read
  delay(100);
  //Serial.println(val);
  val = 100 - map(val, cal_wet, cal_dry, 0, 100); //Calibration (250(dry)-583(wet))
  val = constrain(val, 0 , 100); //Contrain the values if needed
  //Serial.println(val);
  return val;
}

float measureMoisture(){
  return measureMoisture(1);
}


void calibrateMoisture(int dry, int wet, int sensor){
  if(sensor == 1){
   dry1 = dry;
   wet1 = wet;
  }
  
}

float averagedAnalogRead(int N, int pin){
  float temp = 0;
  for(int i=0; i<N; i++){
      temp += analogRead(pin);
      delay(50);
  }
  return temp/N;
}
