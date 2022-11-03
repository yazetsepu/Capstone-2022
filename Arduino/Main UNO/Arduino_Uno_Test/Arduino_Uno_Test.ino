#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2 
#define DHTTYPE    DHT22     // DHT 22
DHT_Unified dht(DHTPIN, DHTTYPE);
int delayMS; //delay for loop

#define WaterPump 3 
#define SoilMoisture1 A3
#define ContainerWaterLevel A4
#define SolenoidValve 6
#define ReservoirWaterLevel A5

int water;
const int dry = 550;
const int wet = 209;

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
}

void loop() {
   //Perform Commands sent by PC connection
  if(Serial.available()){
    String data = Serial.readString();
    runCommand(data);
  }

  // put your main code here, to run repeatedly:
 // Serial.println("Temperature: "+(String)measureTemperature());
  //Serial.println("Humidity: "+(String)measureHumidity());

  /*int soilMoistureValue = analogRead(SoilMoisture1);
  int percentageHumidity = map(soilMoistureValue, wet, dry, 100, 0);
  Serial.print(percentageHumidity);
  Serial.println("%");
  delay(100);*/

  /*digitalWrite(WaterPump, LOW); //activated 
  delay(5000);
  digitalWrite(WaterPump, HIGH); //deactivated
  delay(5000);*/

  /*digitalWrite(SolenoidValve, HIGH); //deactivated
  delay(7000);
  digitalWrite(SolenoidValve, LOW); //activated 
  delay(7000);*/
  

  //Serial.println(measureWaterLevel());


  //Water Check
  float moisture = measureMoisture(1);
  if(moisture < 50){
    //saveLog(20, "Watering Start", 0, "Moisture Level: "+(String)moisture);
    waterPlant();
  }

  if(ReservoirWaterLevel <= 0){
    fillReservoir();
  }

  

  delay(delayMS);
}

void runCommand(String command){
  if(command.indexOf("Water On") >= 0) {Serial.println("On"); digitalWrite(WaterPump, LOW); digitalWrite(LED_BUILTIN, HIGH);}
  if(command.indexOf("Water Off") >= 0) {Serial.println("Off"); digitalWrite(WaterPump, HIGH); digitalWrite(LED_BUILTIN, LOW);}
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
    if(currentTime > (long int)20000){
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
void fillReservoir(){
  //Safety Check Variables
  long int startWaterTime = millis();
  float startWaterLevel = measureReservoirWaterLevel();
  //Check Initial Reservoir Water Level
  if(startWaterLevel >= 100){
    Serial.println("Reservoir Water Level already Full");  
    return;
  }
  //Check if Reservoir Water Level have been reached
  float waterLevel = measureReservoirWaterLevel();
  //Log initialize Reservoir Watering Proccess
  //Check Reservoir Water Levels
  while (waterLevel < 100){
    //Solenoid Valve On
    //Turn Solenoid Valve On
    //digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(SolenoidValve, HIGH);
    waterLevel = measureReservoirWaterLevel();
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
}

float measureContainerWaterLevel(){
  return (float)analogRead(ContainerWaterLevel);
}

float measureReservoirWaterLevel(){
  return (float)analogRead(ReservoirWaterLevel);
}

float measureMoisture(int sensor){
  int sensorPin;
  //if (sensor == 0) sensorPin = SoilMoisture0;
  if (sensor == 1) {
    sensorPin = SoilMoisture1; //Pin the sensor is located
    float val = (float)analogRead(sensorPin); //Sense analog read
    val = 100 - map(val, 200, 583, 0, 100); //Calibration (250(dry)-583(wet))
    val = constrain(val, 0 , 100); //Contrain the values if needed
    Serial.println(val);
    return val;
    }
 /* else if(sensor == 2) (1-(float)analogRead(SoilMoisture1)/1023)*100; //TEST
  else if(sensor == 3) return analogRead(SoilMoisture1); // TEST soil 1 analog purely
  else if(sensor == 4) return analogRead(SoilMoisture4); // Uncalibrated
  else if(sensor == 5) return analogRead(SoilMoisture5); // Uncalibrated
  else if(sensor == 6) return analogRead(SoilMoisture6); // Uncalibrated
  else if(sensor == 7) return analogRead(SoilMoisture7); // Uncalibrated */
  else return -1; //Invalid Sensor Option
  //return (1-(float)analogRead(sensorPin)/1023)*100; //Equation of ADC Convertion in %
}

float measureMoisture(){
  return measureMoisture(1);
}
