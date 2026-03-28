# Smart-Greenhouse-Monitor
# Smart Greenhouse Monitor 🌱

## About the Project
An automated monitoring system designed to track soil moisture and ambient temperature. I built this project to learn how to integrate multiple analog sensors, map hardware data to real-world values, and implement error handling for faulty sensor readings.

## Key Features
* **Real-time Monitoring:** Reads and displays temperature (Celsius) and soil moisture percentages on an LCD.
* **State Machine Control:** Logic is divided into `Verification`, `Action` (Watering), and `Error` states.
* **Hardware Error Handling:** Detects if sensor wires are disconnected or if values fall way outside physical possibilities (e.g., negative voltage readings), triggering a visual error instead of failing silently.
* **Smooth UI:** Optimized the LCD refresh rate to avoid screen flickering by overwriting data instead of clearing the screen entirely.

## Hardware Used
* Arduino Uno
* TMP36 Temperature Sensor
* Analog Soil Moisture Sensor
* 16x2 LCD Display
* Tinkercad (for initial circuit simulation and testing)

## Learning Outcomes
This project was a great hands-on experience with sensor calibration (mapping dry/wet values to 0-100%), voltage math, and writing clean, structured embedded C++ code.
