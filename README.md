# 🚨 IoT Industry Protection System

A **smart IoT-based safety system** designed to monitor **fire, gas leaks, temperature, and light** levels in industrial environments using **Arduino and ESP32**.  
This system automatically detects hazards and sends alerts to **ThingSpeak Cloud** for data monitoring and **MATLAB Analysis** for visualization.

---

## 🧠 Features
- 🔥 **Flame Detection** using IR Flame Sensor  
- 💨 **Gas Detection** using MQ-2 Sensor  
- 🌡️ **Temperature Monitoring** using LM35 Sensor  
- 💡 **LDR Sensor** for light intensity monitoring  
- 📶 **ESP32 WiFi connectivity** to upload data to ThingSpeak  
- 📊 **MATLAB Analysis** for cloud data visualization  
- 🔔 **Buzzer Alert System** for emergency indication  
- 🖥️ **OLED Display** to show live sensor readings  

---

## ⚙️ Hardware Components
| Component | Description |
|------------|-------------|
| ESP32 Dev Board | Main microcontroller for IoT connectivity |
| MQ-2 Sensor | Detects gas or smoke |
| LM35 Sensor | Measures temperature |
| Flame Sensor | Detects presence of fire |
| LDR | Detects ambient light level |
| OLED Display (0.96”) | Displays sensor values |
| Buzzer | Sound alert for emergency |
| Jumper Wires | Circuit connections |

---

## 📂 Repository Structure

├── Arduino_Code/        → Arduino program (.ino)
├── ThingSpeak_Setup/    → Channel configuration details
├── MATLAB_Code/         → MATLAB script for ThingSpeak email alerts
├── Circuit_Diagram.png  → Circuit connection diagram
└── README.md
