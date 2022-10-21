
# Chamaecrista Sustainability System
## Capstoneers Team

![Capstoneers trans](https://user-images.githubusercontent.com/47261571/196817226-5c319b4a-13ed-48ca-ab45-da2550528cda.png)
Table of contents
=================
<!--ts-->
   * [Table of contents](#table-of-contents)
   * [Hardware](#hardware)
	   * [Microcontroller](#microcontroller)
	   * [Sensors](#sensors)
	   * [Ethernet and Storage](#ethernet-and-storage) 
	   * [Connection](#connection)
   * [Schematics](#schematics)
   * [Flowchart](#flowchart)
<!--te-->

# Hardware 
## Microcontroller 
The CSS is design with the use of a Arduino Mega 2560 Rev3 to connect multiple sensors, cameras, water pump, water valve, PWM for LEDS and ethernet connection
| ![microcontroller](https://m.media-amazon.com/images/I/61HWKZzJoyL.jpg) | 
|:--:| 
| *Arduino Mega 2560* |

## Sensors:
CSS system has Humidity, Temperature, Soil Moisture, Light and Real Time Clock sensors as well as a four (4) 5MP camera observer the plant growth and circadian cycles. 

| Sensor | Device | Quantity |
| ------ | ------ | ------ |
| Humidity & Temperature | DHT22 | 1 |
| Soil Moisture | Capacitive Soil Moisture Sensor v2.0 | 8 |
| Light | BH1750 | 1 |
| Real Time Clock | DS3231 | 1 |
| Camera | Arducam OV5642 5MP Plus | 4 |

![image](https://user-images.githubusercontent.com/47261571/197027732-2f80bb87-4baa-44e9-acaf-68e66c87043c.png)
| ![camera](https://www.arducam.com/wp-content/uploads/2019/03/B0068-01-600x600.png)| 
|:--:| 
| *Arducam OV5642 Mini 5MP Plus* |
## Ethernet and Storage
In order to connect to server and keep all the data collected locally store the design uses a W5100 Ethernet Shield with a 32GB micro-SD card.
| ![Capstoneers trans](https://media.naylampmechatronics.com/746-superlarge_default/shield-ethernet-w5100.jpg)| 
|:--:| 
| *W5100 Ethernet Shield* |

## Connection
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
| MISO (50) | BH1750, RTC and Arducam |
| MOSI (51) | BH1750, RTC and Arducam |
| SCK (52) | BH1750, RTC and Arducam |
| D4 | SD Enable |
| D7 | Ethernet Enable |
| D48 | Arducam 1 Enable |


# Schematics
![CSS_Mega_schematic](https://user-images.githubusercontent.com/47261571/197084906-7c535ea8-2976-4c50-b3dc-58fcc68ec1c2.png)

![CSS_Mega_bb](https://user-images.githubusercontent.com/47261571/197085551-87504bf1-0b9b-459f-9fd4-cf604f3f13c4.png)

# Flowchart
| ![Arduino FlowChart](https://user-images.githubusercontent.com/47261571/197080398-4bb89d93-62b2-4a13-b803-3472d3429018.png)| 
|:--:| 
| *Flowchart* |


    

