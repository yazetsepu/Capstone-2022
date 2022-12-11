#include "Arduino.h"
#include "WaterSystem.h"
#include "DataManager.h"
#include "Sensors.h"

void setupWaterSystem(){
  //Set Water Pump
  pinMode(WaterPump, OUTPUT);
  digitalWrite(WaterPump, LOW);
}

float average(float list[], int size){
  float average = 0;
  for(int i = 0; i < size; i++){
    average += list[i];
  }
  return average/size;
}

//Watering Process (Return the Status of the proccess)
String waterPlant(){
  //Safety Check Variables
  int waterLevelThreshold = 400;
  long int startWaterTime = millis();               //Start Timer
  float startWaterLevel = measureWaterLevel();      //Start Water Level
  int waterSamples = 7;                             //Samples to Average
  float waterLevels[waterSamples] = {0,0,0,0,0};    //Average of Water Levels
  int i = 0;                                        //Index of Water Levels 

  // if(getReservoirWaterLevel()  == "VERY LOW"){
  //   Serial.println("No Water on the Water Tank");  
  //   saveLog(25, "Low Water Reservoir", 3, "No Water on the Water Tank");
  //   return "FAIL, No Water on the Water Tank";
  // }
  //Check Initial Water Level
  if(startWaterLevel >= waterLevelThreshold){
    Serial.println("Water Level already Full");  
    saveLog(24, "Watering Full Level", 3, "Water Level is already full");
    return "FAIL, Water Level is already full";
  }
  //Check if water Level have been reached
  float waterLevel = measureWaterLevel();
  //Log initialize Watering Proccess
  saveLog(20, "Watering Start", 0, "");
  //Check Water Levels
  while (waterLevel < waterLevelThreshold){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(WaterPump, HIGH);     //Turn Water Pump On
    //waterLevel = measureWaterLevel(); //Measure Value
    //Safety Check
    delay(100);
    long int currentTime = millis()-startWaterTime;   //timer
    waterLevels[i] = measureWaterLevel();             //Get Current Water Level
    i++;                                              //Increase Water Level Array Counter
    if(i >= waterSamples){
      waterLevel = average(waterLevels, waterSamples); //Take Average
      //waterLevels = 0;  //Reset Average
      Serial.println(waterLevel);
      i = 0;                                            //Reset Index
      Serial.println("Time: " + (String)currentTime);   //Debug Print
    }

    //If some time has passed and water level has not filled
    if(currentTime > (long int)20000){
        digitalWrite(LED_BUILTIN, LOW);         
        digitalWrite(WaterPump, LOW);  //Stop the Water System
        Serial.println("Water System Fail");
        saveLog(23, "Watering Error", 4, "Water level not rising " + (String)waterLevel);
        return "FAIL, Water level not rising " + (String)waterLevel;
    }
  }
  //Water level reached turn off water pump
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WaterPump, LOW);
  saveLog(22, "Watering Successful", 1, "");
  Serial.println("Water System has been successful");
  return "Successful";
}

