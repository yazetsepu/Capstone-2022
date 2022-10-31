#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <Arduino.h>
#include <ArduinoJson.h>


//Digital Pins
#define SD_CS 4     //SD enable pin
#define ETH_CS 10   //Ethernet enable pin
#define Cam_1_CS 48 //Arducam 1 enable pin

//Setup 
bool setupSD();
//Server
void connectToServer();
void loopData();
//Serial
void sendImage();
void sendDataFile();
void sendLastPicture();
bool sendFile(String path);
//SD save
void saveLog(int code, String name, int severity, String message); 
void saveDataToSD(String data[], int sizeData);
//File To Server
void flagData();
void flagImage(String path);
//File Addresses
String getImageFolder(); //Return Image Folder (To save Images)
String getLightScheduleAddress(); //Return the Address to the Light Schedule File 
void infoSD(); //To Serial

#endif
