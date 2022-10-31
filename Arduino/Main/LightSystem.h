#ifndef LIGHT_SYSTEM_H
#define LIGHT_SYSTEM_H
#include <Arduino.h>

// Digital Pins
#define LedPin 3      //TEST LED
#define WhiteLedPin 8 //
#define RedLedPin 7   //
#define GreenLedPin 6 //
#define BlueLedPin 5  //



// Setup
void setupLightSystem();
// Light Control
void dimRed(int pwm);
void dimWhite(int pwm);
void dimGreen(int pwm);
void dimBlue(int pwm);
// Light Time Schedule
void checkSchedule();
void addSchedule(int hour, int minute, int W, int R, int G, int B);
void getScheduleSerial();

#endif
