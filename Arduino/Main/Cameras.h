#ifndef CAMERAS_H
#define CAMERAS_H
#include <Arduino.h>

//SPI Enable Digital Pins
#define Cam_1_CS 48 //Arducam 1 enable pin
#define Cam_2_CS 49 //Arducam 2 enable pin
#define Cam_3_CS 46 //Arducam 3 enable pin
#define Cam_4_CS 47 //Arducam 4 enable pin

//Setup
void setupCameras();
//Image Capture (camera 1,2,3,4)
String captureImageToSD(int camera); //Returns the Image Address

#endif
