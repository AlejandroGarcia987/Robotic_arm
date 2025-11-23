# ESP8266 WiFi Servo Controller – Robotic Arm Project (In Development)

This repository contains an **in-progress** firmware project aimed at controlling
servo motors over WiFi using a NodeMCU ESP8266 board.

The project is currently in its early stages and will evolve from **basic servo control**
to a **full control system** for the Adeept 5-DoF robotic arm, including
multi-servo coordination, WiFi APIs, and eventually computer-vision tracking.

---

## 🚀 Project Status: *Work in Progress*

This project is intentionally built in stages:

1. **Stage 1 – Basic WiFi servo control** *(current)*  
   ESP8266 receives an angle from Postman and moves a servo.

2. **Stage 2 – Multi-servo support**  
   Control of all 5 joints of the Adeept arm.

3. **Stage 3 – JSON-based API**  
   Structured commands for angles, sequences, poses, speed control.

4. **Stage 4 – Migration to ESP32 (LilyGO TTGO)**  
   More powerful MCU for parallel tasks and improved timing.

5. **Stage 5 – BeagleBone AI → ESP32 link**  
   Hand-tracking or gesture recognition via camera → wireless commands.

6. **Stage 6 – Full robotic arm controller**  
   Smooth motion, safety features, posture control, ROS integration.

This repo grows with the project, commit by commit.

---

## 🔧 Hardware Used (Current Stage)

At this point we use the **NodeMCU ESP8266 V3**, because:

- It has pre-soldered headers.  
- It can be programmed directly via USB.  
- It includes WiFi support without additional modules.

The **LilyGO TTGO ESP32** board will be introduced later, when soldering is completed
and higher performance is required.

---

## 🛠 Features (current firmware)

- Connects to WiFi (station mode)  
- Exposes an HTTP endpoint for servo angle control  
- Accepts 0–180° via GET or POST  
- Moves a single servo (for now)  
- LED feedback on command reception  
- WiFi credentials stored in `wifi_config.h` (ignored by Git)  

---

## 📡 API Usage

### Endpoint
http://IP_FROM_NODEMCU/set?val=<angle>  

### Methods
- GET  
- POST (form-url-encoded)

Example: GET http://XXX.XXX.X.XX/set?val=180

## 🔌 Hardware Setup

### Required
- NodeMCU ESP8266 V3  
- External 5V power supply for the servos  
- Common GND between servo supply and NodeMCU  
- SG90/MG90S/Adeept AD002 servo  

### Wiring

| Servo Wire | Connect To |
|------------|------------|
| Red (+5V)  | External 5V supply |
| Brown/Black (GND) | External GND (shared with NodeMCU GND) |
| Orange/Yellow (signal) | NodeMCU D1 (GPIO5) |

⚠️ **Do NOT power servos from the NodeMCU 3.3V pin.**

## 🔒 WiFi Credentials

To avoid committing sensitive data:

- `wifi_config.h` contains private credentials  
- `wifi_config_template.h` is provided as a template


## 📈 Future Work (planned features)

- Full 5-servo control for Adeept 5-DoF arm  
- JSON API for multi-joint commands  
- Motion smoothing and safe limits  
- Sequence/pose playback  
- Migration to ESP32 (LilyGO TTGO)  
- Integration with BeagleBone AI and computer vision  
- ROS compatibility  
- OTA updates and security improvements  

---

## 🧑‍💻 Author

Alejandro García  
Embedded Systems & AI Engineer
2025
