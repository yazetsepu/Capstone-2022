#include "WaterSystem.h"
#include "DataManager.h"
#include "Sensors.h"

void setupWaterSystem(){
  //Set Water Pump
  pinMode(WaterPump, OUTPUT);
  digitalWrite(WaterPump, LOW);
}

//Watering Check (TODO Check Water is flowing)
void waterPlant(){
  //Safety Check Variables
  long int startWaterTime = millis();
  float startWaterLevel = measureContainerWaterLevel();
  //Check Initial Water Level
  if(startWaterLevel >= 100){
    Serial.println("Water Level already Full");  
    saveLog(24, "Watering Full Level", 3, "Water Level is already full");
    return;
  }
  //Check if water Level have been reached
  float waterLevel = measureContainerWaterLevel();
  //Log initialize Watering Proccess
  saveLog(20, "Watering Start", 0, "");
  //Check Water Levels
  while (waterLevel < 100){
    //Water Pump On
    //Turn Water Pump On
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(WaterPump, HIGH);
    waterLevel = measureContainerWaterLevel();
    Serial.println(waterLevel);
    //Safety Check
    delay(100);
    //If some time has passed and water level has not filled
    long int currentTime = millis()-startWaterTime;
    Serial.println("Time: " + (String)currentTime);
    if(currentTime > (long int)1000){
        //Stop the Water System
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(WaterPump, LOW);
        Serial.println("Water System Fail");
        saveLog(23, "Watering Error", 4, "Water level not rising " + (String)waterLevel);
        return;
    }
  }
  //Water level reached turn off water pump
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WaterPump, LOW);
  saveLog(22, "Watering Successful", 1, "");
  Serial.println("Water System has been successful");
}

/* Fill Reservoir */
/* Adding the saveLogs is Missing */
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
    digitalWrite(SolenoidValve, LOW);
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
        digitalWrite(SolenoidValve, HIGH);
        Serial.println("Reservoir Filling Fail");
        return;
    }
  }
  //Reservoir Water level reached turn off solenoid valve
  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(SolenoidValve, LOW);
  Serial.println("Reservoir Filling has been successful");
}



