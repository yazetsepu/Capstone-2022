#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <Arduino.h>

// Setup 
void setupSD();
void setupCameras();
//Server
void connectToServer();
void loopData();
//Serial
void sendImage();
void sendDataFile();
void sendLastPicture();
//SD save
void saveLog(String dateTime, String action, String description, int errorCode);
void saveLog(int code, String Message); //TODO
void saveDataToSD(String data[], int sizeData);
void capturePictureSD();
String infoSD();

#endif
