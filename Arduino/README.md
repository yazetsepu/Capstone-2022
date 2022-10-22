



Table of contents
=================
<!--ts-->
   * [Table of contents](#table-of-contents)
   * [Pinout](#microcontroller)
   * [Libraries](#libraries)
   * [Software](#software)
	   * [Log List](#log-list)
   * [Schematics](#schematics)
   * [Flowchart](#flowchart)
<!--te-->

## Pinout
![pinout](https://diyi0t.com/wp-content/uploads/2019/08/Arduino-Mega-Pinout.png)

**Digital Pins**
|Pin| Device |
|--|--|
| D2 | DHT22 |
| D3 | LED TEST |
| D31 | Water Pump |

**Analog Pins**
|Pin| Device |
|--|--|
| A2 | Water Level |
| A8 | Soil Moisture 0 |
| A9 | Soil Moisture 1 |

**I2C Pins**
|Pin| Devices |
|--|--|
| SDA | BH1750, RTC and Arducam |
| SCL | BH1750, RTC and Arducam |

**SPI Pins**
|Pin| Devices |
|--|--|
| MISO (50) | Ethernet, SD and Arducam |
| MOSI (51) | Ethernet, SD and Arducam |
| SCK (52) | Ethernet, SD and Arducam |
| D4 | SD Enable |
| D7 | Ethernet Enable |
| D48 | Arducam 1 Enable |

## Libraries 
List of Arduino Libraries require to compile and upload software.
 - ArduCam
 - ArduinoJson
 - BH1750
 - DHT_sensor_library
 - DS3231
 
## Software

### Command List
| Command |String Format| Parameter |  Return |
|--|--|--|--|--|
| All Light On| "LED ON"  |  |JSON (Status)
| All Light Off | "LED OFF" | | JSON (Status) 
| RGBW Light Dim | "LED DIM {0},{1},{2},{3}" | int[] (0-100) | JSON (Status) 
| Water Plant | "Water Plant" |  | JSON (Status) 
| Send SD Info | "SD info" | | JSON (SD files directory)|
| Get Current Measurements | "Get Data" | | JSON (data) |
| Capture Image | "Capture Image Cam: {0}" | int (0-3) | bytes[] (JPG) |
| Timed Dim | "Schedule Dim {0}" | JSON (Timestamp, W,R,G,B) | bytes[] (JPG) |

    {"Light":830.8333,"Temperature":30.6,"Humidity":70.1,"Soil_Moisture_0":71.74976,"Soil_Moisture_1":90,"Water_Level":0,"Time":"2022/10/21 10:58:48"}
JSON (data) example

### Log List

All action performed by the CSS system will the log for further improvements and debugging. The log includes actions, errors and checks. Codes are unique identifier for a particular set of log. Source is the name of the module affecting this log. Severity is from a scale of 0-5 being 0 Successful minor actions, 1 Successful actuator action, 2 Minor Check, 3 Critical Check, 4 Error and 5 Critical Error (Must restart). Message will show details of the error to get possible actions, solutions and easier debugging. All log has the time stamp of the moment it was logged and saved into Log.csv file in SD.
    
    
    void saveLog(int code, String name, int severity, String message);


#### Setup
| Code |Source | Name | Severity | Message
|--|--|--|--|--|
| 00 | Setup | Setup Sensors | 0 |  |
|  01 | Setup | Boot Complete | 0 |  |
| 02 | Setup | Error Sensor | 4 | Sensor not connecting {Device_Name} |
| 03 | Setup | Boot Error | 5 | Critical components (SD, RTC) are not connected. (Must restart) |


#### Data Management
| Code |Source | Name | Severity | Message
|--|--|--|--|--|
| 10 | Data | Capture Data | 0 | |
| 11 | Data | Capture Image | 0 | |
| 12 | Data | Error Capture Data Device| 3 | Devices {Device_name} disconnected | 
| 13 | Data | Error Capture Image | 3 | Camera {Camera_Num} disconnected | 
| 14 | Data | Error File Data | 4 | Error saving Data file | 
| 15 | Data | Error File Image | 4 | Error saving Image | 
| 16 | Data | Command Received | 0 | {command} |
| 17 | Data | Command Successful | 1 | {command} |
| 18 | Data | Command Unsuccessful | 3 | {command} |
| 19 | Data | Invalid Command | 2 | {command} |



#### Water System
| Code |Source | Name | Severity | Message
|--|--|--|--|--|
| 20 | Water System | Watering Start | 0 |  |
| 21 | Water System | Watering Check | 2 | Log the water level process
| 22 | Water System | Watering Successful | 1 |  |
| 23 | Water System | Watering Error | 4 | Water level not rising when watering |
| 24 | Water System | Watering Full Level | 3 | Water level in plant container is already full |
| 25 | Water System | Low Reservoir Level | 4 | Low water level in reservoir |
| 26 | Water System | Watering Check | 2 | Water Level above {Threshold+%}| 
| 27 | Water System | Watering Critical Check | 3 | Water Level above {critical}| 

Threshold is a value where contact with water is true. 


#### Light System (TODO)
| Code |Source | Name | Severity | Message
|--|--|--|--|--|
|  |  |  |  |  |




 
## Schematics
![CSS_Mega_schematic](https://user-images.githubusercontent.com/47261571/197084906-7c535ea8-2976-4c50-b3dc-58fcc68ec1c2.png)



## Flowchart
| ![Arduino FlowChart](https://user-images.githubusercontent.com/47261571/197080398-4bb89d93-62b2-4a13-b803-3472d3429018.png)| 
|:--:| 
| *Flowchart* |


    

