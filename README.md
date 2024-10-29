# Gas-Leakage-Detection-System
An IoT-based gas leakage detection system using Arduino and ESP32
## Overview
This project aims to detect gas leaks and control a regulator using an Arduino board and ESP32, with remote monitoring via the Blynk app. It also activates a buzzer, LED, and servo motor to take necessary actions upon gas detection.

## Components Used
- **ESP32** 
- **Arduino Uno**
- **MQ6 Gas Sensor**
- **Buzzer**
- **Servo Motor (SG90)**
- **LED**
- **16x2 LCD with I2C Module**
- **Breadboard, Jumper Wires, Resistors**

## Features
- **Blynk App Integration:** Monitor and control via smartphone.
- **Gas Sensor Alert:** Activates buzzer and LED on gas detection.
- **Servo Control:** Automatically closes/open gas regulator upon leakage.
- **LCD Display:** Real-time gas levels displayed on LCD.
- **Failsafe WiFi Reconnect:** ESP32 auto-reconnects to WiFi.

## Code Explanation
### ESP32 Code
- Connects to Blynk and WiFi for remote control.
- Controls servo motor based on input from the Blynk app.

### Arduino Code
- Monitors gas levels using MQ6 sensor.
- Activates buzzer, LED, and servo when leakage is detected.

## Usage
1. **Upload ESP32 code** to your ESP32 module.
2. **Upload Arduino code** to your Arduino board.
3. Use the **Blynk App** to monitor and control the servo remotely.
4. Power both boards and observe the readings on the LCD.

## Connections
- **MQ6 Sensor** → A0 (Arduino)
- **Servo Motor** → Pin 9 (Arduino), Pin 23 (ESP32)
- **Buzzer** → Pin 7 (Arduino)
- **LED** → Pin 13 (Arduino)
- **I2C LCD** → I2C pins on Arduino

## WiFi Configuration
Update the WiFi credentials in your ESP32 code:
```cpp
char ssid[] = "Your_SSID";
char pass[] = "Your_PASSWORD";
#define BLYNK_TEMPLATE_ID "TMPL3-74NMujS"
#define BLYNK_TEMPLATE_NAME "GAS LEAK"
#define BLYNK_AUTH_TOKEN "3VVmL5-IdmvqqBPP60RT7P_7DbnekNLf"
