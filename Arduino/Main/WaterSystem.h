#ifndef WATER_SYSTEM_H
#define WATER_SYSTEM_H
#include <Arduino.h>

//Digital Pins
#define WaterPump 31
#define SolenoidValve 32 //Check

void setupWaterSystem();
void waterPlant();
void fillReservoir();
float measureContainerWaterLevel();
float measureReservoirWaterLevel();

#endif
