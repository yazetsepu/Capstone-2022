#ifndef WATER_SYSTEM_H
#define WATER_SYSTEM_H
#include <Arduino.h>

//Digital Pins
#define WaterPump 31

void setupWaterSystem();
String waterPlant();
float measureWaterLevel();

#endif
  