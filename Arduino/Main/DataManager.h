#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <Arduino.h>

void connectToServer();
void setupSD();
void setupCameras();
void loopData();
void sendImage();
void sendDataFile();
void sendLastPicture();
void capturePictureSD();
String infoSD();
void saveDataToSD(String data[], int sizeData);

#endif
