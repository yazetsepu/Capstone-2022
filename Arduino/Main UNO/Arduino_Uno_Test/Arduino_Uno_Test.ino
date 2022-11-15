#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE    DHT22     // DHT 22
DHT_Unified dht(DHTPIN, DHTTYPE);
int delayMS; //delay for loop

#define WaterPump 3 
#define SoilMoisture1 A3
#define ContainerWaterLevel A4
//#define SolenoidValve 6
#define ReservoirWaterLevel1 5
#define ReservoirWaterLevel2 6
#define ReservoirWaterLevel3 7
#define ReservoirWaterLevel4 8


int water;
int dry1 = 550;
int wet1 = 209;
//const int dry = 550;
//const int wet = 209;
String wetval, dryval, soilMoisture;
int wetval1, dryval1, soilMoisture1;

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
  pinMode(ReservoirWaterLevel1, INPUT);
  digitalWrite(ReservoirWaterLevel1, HIGH);
  pinMode(ReservoirWaterLevel2, INPUT);
  digitalWrite(ReservoirWaterLevel2, HIGH);
  pinMode(ReservoirWaterLevel3, INPUT);
  digitalWrite(ReservoirWaterLevel3, HIGH);
  pinMode(ReservoirWaterLevel4, INPUT);
  digitalWrite(ReservoirWaterLevel4, HIGH);
}

void loop() {
   //Perform Commands sent by PC connection
  if(Serial.available()){
    String data = Serial.readString();
    runCommand(data);
  }

  /*Temperature and Humidity*/
  //Serial.println("Temperature: "+(String)measureTemperature());
  //Serial.println("Humidity: "+(String)measureHumidity());

  /*Reservoir Water Level*/
  getReservoirWaterLevel();

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
  /*float moisture = measureMoisture(1);
  if(moisture < 50){
    //saveLog(20, "Watering Start", 0, "Moisture Level: "+(String)moisture);
    waterPlant();
  }*/

  delay(delayMS);
}

void runCommand(String command){
  Serial.println("Command received: " + command+"\n");
  if(command.indexOf("Water On") >= 0) {Serial.println("On"); digitalWrite(WaterPump, HIGH);}
  else if(command.indexOf("Water Off") >= 0) {Serial.println("Off"); digitalWrite(WaterPump, LOW);}
  else if(command == "Water Plant"){
    waterPlant();
  } 
  else if(command.indexOf("Calibrate Moisture") >= 0){ //Ex Calibrate Moisture5602502
    int index0 = command.indexOf('e');
    wetval = command.substring(index0+1, index0+4);
    dryval = command.substring(index0+4, index0+7);
    soilMoisture = command.substring(index0+7);
    wetval1 = wetval.toInt();
    dryval1 = dryval.toInt();
    soilMoisture1 = soilMoisture.toInt();
    calibrateMoisture(dryval1,wetval1,soilMoisture1);
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
    Serial.println("Time: " + (String)currentTime);
    if(currentTime > (long int)10000){
        //Stop the Container Water System
        //digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(WaterPump, LOW);
        Serial.println("Container Water System Fail");
        return;
    }
  }
  //Container Water level reached turn off water pump
  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WaterPump, LOW);
  Serial.println("Container Water System has been successful");
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
  delay(100);
}

/*Measure all Reservoir Water Levels (HIGH or LOW)*/
int measureReservoirWaterLevel(int sensor){
  
  if(sensor == 1){
    return (int)digitalRead(ReservoirWaterLevel1);
  }
  else if(sensor == 2){
    return (int)digitalRead(ReservoirWaterLevel2);
  }
  else if(sensor == 3){
    return (int)digitalRead(ReservoirWaterLevel3);
  }
  else if(sensor == 4){
    return (int)digitalRead(ReservoirWaterLevel4);
  }
  else{
    return -1;
  }
}

/*Reservoir Water Level(VERY HIGH, HIGH, MEDIUM, LOW ,VERY LOW)*/
/*Depends on the measurements obtained from the different reservoir water levels*/
String getReservoirWaterLevel(){
  if(measureReservoirWaterLevel(1) == HIGH){
    Serial.println("VERY HIGH");
  }
  else if(measureReservoirWaterLevel(1) == LOW && measureReservoirWaterLevel(2) == HIGH){
    Serial.println("HIGH");
  }
  else if(measureReservoirWaterLevel(2) == LOW && measureReservoirWaterLevel(3) == HIGH){
    Serial.println("MEDIUM");
  }
  else if(measureReservoirWaterLevel(3) == LOW && measureReservoirWaterLevel(4) == HIGH){
    Serial.println("LOW");
  }
  else{ //measureReservoirWaterLevel(4) == LOW
    Serial.println("VERY LOW");
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
    /*float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    Serial.println(val);
    return val;*/
  }
  else return -1; //Invalid Sensor Option
  float val = (float)analogRead(sensorPin); //Sense analog read
  Serial.println(val);
  val = 100 - map(val, cal_wet, cal_dry, 0, 100); //Calibration (250(dry)-583(wet))
  val = constrain(val, 0 , 100); //Contrain the values if needed
  Serial.println(val);
  return val;
 /* else if(sensor == 2) (1-(float)analogRead(SoilMoisture1)/1023)*100; //TEST
  else if(sensor == 3) return analogRead(SoilMoisture1); // TEST soil 1 analog purely
  else if(sensor == 4) return analogRead(SoilMoisture4); // Uncalibrated
  else if(sensor == 5) return analogRead(SoilMoisture5); // Uncalibrated
  else if(sensor == 6) return analogRead(SoilMoisture6); // Uncalibrated
  else if(sensor == 7) return analogRead(SoilMoisture7); // Uncalibrated */
  //return (1-(float)analogRead(sensorPin)/1023)*100; //Equation of ADC Convertion in %
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
