#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2 
#define DHTTYPE    DHT22     // DHT 22
DHT_Unified dht(DHTPIN, DHTTYPE);
int delayMS; //delay for loop

#define WaterPump 6 

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //Set DHT Sensor
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  //Set Water Pump Pin
  pinMode(WaterPump, OUTPUT);
}

void loop() {
   //Perform Commands sent by PC connection
  if(Serial.available()){
    String data = Serial.readString();
    runCommand(data);
  }

  // put your main code here, to run repeatedly:
  Serial.println("Temperature: "+(String)measureTemperature());
  Serial.println("Humidity: "+(String)measureHumidity());

  delay(delayMS);
}

void runCommand(String command){
  if(command.indexOf("Water On") >= 0) {Serial.println("On"); digitalWrite(WaterPump, LOW); digitalWrite(LED_BUILTIN, HIGH);}
  if(command.indexOf("Water Off") >= 0) {Serial.println("Off"); digitalWrite(WaterPump, HIGH); digitalWrite(LED_BUILTIN, LOW);}
}

//Using Temperature DHT
float measureTemperature() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    return -1; //Error
  }
  else {
    return event.temperature;
  }
}

//Using Humidity DHT
float measureHumidity(){
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    return -1;   //Error
  }
  else {
    return event.relative_humidity;
  }
}
