#ifndef Water_SYSTEM_H
#define Water_SYSTEM_H
#include <Arduino.h>

//Digital Pins
#define WaterPump 31

void setupWaterSystem();
void waterPlant();
float measureWaterLevel();

#endif
