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
  float startWaterLevel = measureWaterLevel();
  //Check Initial Water Level
  if(startWaterLevel >= 100){
    Serial.println("Water Level already Full");  
    saveLog(24, "Watering Full Level", 3, "Water Level is already full");
    return;
  }
  //Check if water Level have been reached
  float waterLevel = measureWaterLevel();
  //Log initialize Watering Proccess
  saveLog(20, "Watering Start", 0, "");
  //Check Water Levels
  while (waterLevel < 100){
    //Water Pump On
    //Turn Water Pump On
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(WaterPump, HIGH);
    waterLevel = measureWaterLevel();
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

