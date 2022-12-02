#include "HardwareSerial.h"
#include "LightSystem.h"
#include "Sensors.h"
#include "DataManager.h"
#include <SD.h>
#include <DS3231.h>

//Actuators Parameter;
int dimLevel=255; //TEST 
int nextW = 0;
int nextR = 0;
int nextG = 0;
int nextB = 0;
//Next Schedule
DateTime nextSchedule;
void fetchNextSchedule();
void dimAllToLevel(int level);
void setupLightSystem(){
  pinMode(LedPin, OUTPUT);

  //Create Light Schedule CSV File 
  File scheduleFile = SD.open(getLightScheduleAddress(), FILE_WRITE);
  delay(1000); //Load Delay
  if(scheduleFile){ 
    //Add header Title
    int hour = currentTime().hour(); //Test 
    int minute = currentTime().minute(); //Test 
    scheduleFile.println((String)hour+","+(String)(minute+1)+","+"250,0,100,100"); //(H,M,W,R,G,B) Sample Test
    scheduleFile.println((String)hour+","+(String)(minute+2)+","+"100,200,50,50"); //(H,M,W,R,G,B) Sample Test
    scheduleFile.println((String)hour+","+(String)(minute+3)+","+"50,50,200,250"); //(H,M,W,R,G,B) Sample Test
    scheduleFile.println((String)hour+","+(String)(minute+4)+","+"30,50,200,250"); //(H,M,W,R,G,B) Sample Test
    scheduleFile.println((String)hour+","+(String)(minute+5)+","+"20,50,200,250"); //(H,M,W,R,G,B) Sample Test
    scheduleFile.println((String)hour+","+(String)(minute+6)+","+"0,0,0,0"); //(H,M,W,R,G,B) Sample Test

    //scheduleFile.println("17,20,0,0,100,255"); //(H,M,W,R,G,B) Sample Test
    scheduleFile.close();   // close the file:
  }
  else{
    Serial.println("Error Creating Light Schedule File");
  }
  //nextSchedule = DateTime(0,0,0,14,17,0); //Test Schedule
  nextSchedule = DateTime(0,0,0,0,0,0);
  dimAllToLevel(0);
  fetchNextSchedule();
}


void dimRed(int pwm){
  analogWrite(RedLedPin, pwm);
}

void dimWhite(int pwm){
  analogWrite(WhiteLedPin, pwm);
}

void dimGreen(int pwm){
  analogWrite(GreenLedPin, pwm);
}

void dimBlue(int pwm){
  analogWrite(BlueLedPin, pwm);
}

//(Private) Dim to schedule level
void dimAllToLevel(){
  dimBlue(nextB);
  dimGreen(nextG);
  dimRed(nextR);
  dimWhite(nextW);
}

//(Private) Dim given level
void dimAllToLevel(int level){
  dimBlue(level);
  dimGreen(level);
  dimRed(level);
  dimWhite(level);
}

//Check if next schedule is meet and change intensity when schedule meets
void checkSchedule(){
  if(currentTime().hour() >= nextSchedule.hour() && currentTime().minute() >= nextSchedule.minute()){
    dimAllToLevel();
    Serial.println("Schedule meet: "+(String)nextSchedule.hour() + ":" + (String)nextSchedule.minute()+ " W:"+(String)nextW);
    fetchNextSchedule();
  }
}

//(Private) Fetch in memory the next Light Schedule
void fetchNextSchedule(){
  //Open Schedule File
  File scheduleFile = SD.open(getLightScheduleAddress());
  //Temporary variables
  String schedule = "";
  char tempChar = ' ';
  //Read File
  if (scheduleFile) {
    //Get the CSV Row for schedule
    while (scheduleFile.available()) {
      //Read Char by char to complete row
      tempChar = scheduleFile.read();
      schedule += tempChar;
      //End of Row (Complete row)
      if(tempChar == '\n'){
          // delimiter CSV ','
          int index0 = schedule.indexOf(',');
          int index1 = schedule.indexOf(',', index0+1);
          int index2 = schedule.indexOf(',', index1+1);
          int index3 = schedule.indexOf(',', index2+1);
          int index4 = schedule.indexOf(',', index3+1);
          
          // Parse Data Schedule (Hour,Minute,White,Red,Green,Blue)
          int hour = schedule.substring(0, index0).toInt();
          int minute = schedule.substring(index0+1, index1).toInt();
          //Set Color Intensities
          nextW = schedule.substring(index1+1, index2).toInt();
          nextR = schedule.substring(index2+1, index3).toInt();
          nextG = schedule.substring(index3+1, index4).toInt();
          nextB = schedule.substring(index4+1).toInt();
          dimLevel = nextB;

          //Find the next schedule by comparing times
          if(hour >= currentTime().hour() && minute > currentTime().minute()){
            Serial.println("Time Schedule: "+(String)hour+":"+(String)minute);
            //Set time schedule
            nextSchedule = DateTime(0,0,0,hour,minute,0);
            scheduleFile.close(); //Close File
            saveLog(30, "Schedule Set", 1, "Next Schedule: "+(String)nextSchedule.hour() + ":" + (String)nextSchedule.minute());
            return;
          }
          schedule = ""; //Reset Row String
      }
    }
    scheduleFile.close(); //Close File
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening");
    return;
  }
  //No Schedule Available for the day
  nextSchedule = DateTime(0,0,0,24,59,59); //Set to new day
  dimAllToLevel(); //Set the last WRGB levels 
  saveLog(30, "Schedule Set", 1, "Last Schedule until midnight");
}

//Add the new schedule where it belongs in increasing order
void addSchedule(int hours, int minutes, int W, int R, int G, int B){
  //Open Schedule File
  File scheduleFile = SD.open(getLightScheduleAddress());
  //File data
  String timeBefore = "";
  String timeAfter = "";
  //Temporary variables
  String schedule = "";
  char tempChar = ' ';
  //Read File
  if (scheduleFile) {
    //Get the CSV Row for schedule
    while (scheduleFile.available()) {
      //Read Char by char to complete row
      tempChar = scheduleFile.read();
      schedule += tempChar;
      //End of Row (Complete row)
      if(tempChar == '\n'){
          // delimiter CSV ','
          int index0 = schedule.indexOf(',');
          int index1 = schedule.indexOf(',', index0+1);
          
          // Parse Data Schedule (Hour,Minute,White,Red,Green,Blue)
          int hour = schedule.substring(0, index0).toInt();
          int minute = schedule.substring(index0+1, index1).toInt();

          //Find the next schedule by comparing times
          if(hour >= hours && minute > minutes){
            Serial.println("Time next found: "+(String)hour+":"+(String)minute);
            timeAfter = schedule;
            while (scheduleFile.available()){
              timeAfter += (char)scheduleFile.read();
            }
            break;
          }
          timeBefore += schedule;
          schedule = ""; //Reset Row String
      }
    }
    scheduleFile.close(); //Close File
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening");
    return;
  }
  //Write to SD
  scheduleFile = SD.open(getLightScheduleAddress(), O_RDWR);
  delay(1000);
  // if the file opened okay, write to it:
  if (scheduleFile) {
    String dataEntry = (String)hours+","+(String)minutes+","+(String)W+","+(String)R+","+(String)G+","+(String)B;
    Serial.println(timeBefore+dataEntry+timeAfter);
    scheduleFile.println(timeBefore+dataEntry+timeAfter); //Write all Schedule with the new row located where it needed
    // close the file:
    scheduleFile.close();
    Serial.println("Data saved to SD");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error saving data to SD");
    return;
  }
  fetchNextSchedule(); //Get the Next Schedule (To mark sure its set to the properly light schedule)
  saveLog(31, "Schedule Added", 1, "Added Schedule: "+(String)hours + ":" + (String)minutes);
}

//Send File Serial (Mostly debugging)
void getScheduleSerial(){
   File scheduleFile = SD.open(getLightScheduleAddress());
  if (scheduleFile) {
    while (scheduleFile.available()) {
      Serial.write(scheduleFile.read());
    }
    scheduleFile.close();
  }
  else {
    Serial.println("Error Opening Light Schedule");
  }
}
