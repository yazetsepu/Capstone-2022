#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <Arduino.h>

//Digital Pins
#define SD_CS 4     //SD enable pin
#define ETH_CS 7    //Ethernet enable pin
#define Cam_1_CS 48 //Arducam 1 enable pin

//Setup 
void setupSD();
//Server
void connectToServer();
void loopData();
//Serial
void sendImage();
void sendDataFile();
void sendLastPicture();
//SD save
void saveLog(int code, String name, int severity, String message); 
void saveDataToSD(String data[], int sizeData);
//File Addresses
String getImageFolder(); //Return Image Folder (To save Images)
String getLightScheduleAddress(); //Return the Address to the Light Schedule File 
String infoSD();

#endif
