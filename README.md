# Soft Tactile Force Sensor

> A low-cost soft tactile force sensing system based on magnetic field variation using an ESP32, MLX90393 magnetometer, and a 3D-printed TPU hexagonal structure.

![License](https://img.shields.io/badge/License-MIT-green.svg)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange.svg)
![Sensor](https://img.shields.io/badge/Sensor-MLX90393-red.svg)

---

## Project Overview

This project presents the design, implementation, and experimental validation of a **soft tactile force sensor** that estimates applied force by measuring variations in the magnetic field. The sensing mechanism consists of a flexible 3D-printed TPU hexagonal structure, a permanent magnet, and an MLX90393 three-axis magnetometer interfaced with an ESP32 microcontroller.

When an external force compresses the TPU structure, the distance between the magnet and the magnetometer decreases, resulting in a measurable increase in magnetic field intensity. After sensor calibration, the measured magnetic field is converted into displacement using an inverse magnetic field-distance model. The displacement is then mapped to the corresponding force through experimentally obtained Universal Testing Machine (UTM) calibration data.

The project demonstrates an inexpensive and compact alternative to conventional force sensing technologies such as load cells and strain gauges while maintaining real-time measurement capability.

---

## Key Features

- Soft tactile force sensing using magnetic field variation
- 3D printed TPU compliant hexagonal sensing structure
- ESP32-based embedded data acquisition
- MLX90393 three-axis digital magnetometer
- Automatic hard-iron and soft-iron calibration
- Earth magnetic field compensation
- Distance estimation from calibrated magnetic field measurements
- Force estimation using UTM-based interpolation
- Real-time wireless data transmission over Wi-Fi
- Modular and low-cost hardware design suitable for research and educational applications

---

## Project Highlights

| Feature | Description |
|----------|-------------|
| Microcontroller | ESP32 |
| Sensor | MLX90393 Triple-Axis Magnetometer |
| Material | Thermoplastic Polyurethane (TPU) |
| Manufacturing | FDM 3D Printing |
| Communication | Wi-Fi (HTTP POST) |
| Programming Language | C++ (Arduino Framework) |
| Calibration | Hard Iron, Soft Iron and Earth Field Compensation |
| Force Estimation | UTM-based Calibration Curve |
| Application | Soft Robotics, Wearable Sensors, Tactile Sensing |

---

## Working Principle

The proposed soft tactile force sensor operates by converting mechanical deformation into magnetic field variation. A permanent neodymium magnet and an MLX90393 three-axis magnetometer are mounted at opposite ends of a compliant TPU hexagonal structure. When an external force is applied, the structure compresses, reducing the distance between the magnet and the sensor.

The MLX90393 continuously measures the magnetic field vector. After performing hard-iron correction, soft-iron correction, and Earth magnetic field compensation, the resultant magnetic field magnitude is used to estimate the separation distance between the magnet and the sensor using an experimentally calibrated inverse magnetic field-distance relationship. The calculated displacement is then mapped to the corresponding applied force using data obtained from Universal Testing Machine (UTM) testing.

The ESP32 performs all signal processing in real time and transmits the calculated force values wirelessly to a remote server over Wi-Fi for visualization and logging.

---

### Sensing Workflow

```text
Applied Force
      │
      ▼
TPU Hexagonal Structure Compresses
      │
      ▼
Magnet Moves Towards MLX90393
      │
      ▼
Magnetic Field Changes
      │
      ▼
Magnetometer Measures Bx, By, Bz
      │
      ▼
Sensor Calibration
(Hard Iron + Soft Iron + Earth Field Compensation)
      │
      ▼
Magnetic Field Magnitude (|B|)
      │
      ▼
Distance Estimation
      │
      ▼
Displacement Calculation
      │
      ▼
Force Estimation using UTM Calibration
      │
      ▼
ESP32 Wi-Fi Transmission
```

---

# Mechanical Design

The sensing element is based on a compliant hexagonal geometry manufactured using Thermoplastic Polyurethane (TPU). Unlike conventional rigid force sensors, the flexible structure deforms elastically under compression while maintaining repeatable mechanical behaviour. The internal cavity accommodates both the permanent magnet and the magnetometer, ensuring controlled relative motion during loading.

The geometry was designed in SolidWorks and fabricated using FDM 3D printing. The hexagonal topology provides high compliance, allowing measurable displacement under relatively small applied loads while maintaining structural integrity.

<p align="center">
<img src="images/sensor_dimension.png" width="450">
</p>

---

# Electronic Circuit

The electronic system consists of an ESP32 development board interfaced with an MLX90393 three-axis magnetometer over the I²C communication protocol. The ESP32 supplies power to the sensor, performs real-time magnetic field acquisition, executes calibration and force estimation algorithms, and transmits processed data over Wi-Fi.

The default ESP32 I²C pins are used in the firmware:

| ESP32 Pin | MLX90393 Pin |
|-----------|--------------|
| 3.3 V | VCC |
| GND | GND |
| GPIO21 (SDA) | SDA |
| GPIO22 (SCL) | SCL |

<p align="center">
<img src="hardware/schematic.png" width="700">
</p>

---

# Hardware Components

| Component | Specification |
|----------|---------------|
| Microcontroller | ESP32 Development Board |
| Magnetometer | MLX90393 Triple-Axis Digital Magnetometer |
| Permanent Magnet | Neodymium Cube Magnet |
| Structure Material | Thermoplastic Polyurethane (TPU) |
| Fabrication Method | FDM 3D Printing |
| Communication | Wi-Fi (HTTP POST) |
| Power Supply | USB 5 V |

---

# Firmware Architecture

The embedded firmware running on the ESP32 performs the following operations:

- Initialization of the MLX90393 sensor
- Hard-iron calibration
- Soft-iron calibration
- Earth magnetic field compensation
- Magnetic field acquisition
- Magnetic field magnitude calculation
- Distance estimation using calibration data
- Force estimation through interpolation
- Wi-Fi communication
- HTTP POST transmission to a remote server

The firmware is written using the Arduino framework in C++ and follows a modular processing pipeline for real-time force estimation.

---

## Working Principle

The proposed soft tactile force sensor operates by converting mechanical deformation into magnetic field variation. A permanent neodymium magnet and an MLX90393 three-axis magnetometer are mounted at opposite ends of a compliant TPU hexagonal structure. When an external force is applied, the structure compresses, reducing the distance between the magnet and the sensor.

The MLX90393 continuously measures the magnetic field vector. After performing hard-iron correction, soft-iron correction, and Earth magnetic field compensation, the resultant magnetic field magnitude is used to estimate the separation distance between the magnet and the sensor using an experimentally calibrated inverse magnetic field-distance relationship. The calculated displacement is then mapped to the corresponding applied force using data obtained from Universal Testing Machine (UTM) testing.

The ESP32 performs all signal processing in real time and transmits the calculated force values wirelessly to a remote server over Wi-Fi for visualization and logging.

---

### Sensing Workflow

```text
Applied Force
      │
      ▼
TPU Hexagonal Structure Compresses
      │
      ▼
Magnet Moves Towards MLX90393
      │
      ▼
Magnetic Field Changes
      │
      ▼
Magnetometer Measures Bx, By, Bz
      │
      ▼
Sensor Calibration
(Hard Iron + Soft Iron + Earth Field Compensation)
      │
      ▼
Magnetic Field Magnitude (|B|)
      │
      ▼
Distance Estimation
      │
      ▼
Displacement Calculation
      │
      ▼
Force Estimation using UTM Calibration
      │
      ▼
ESP32 Wi-Fi Transmission
```

---

# Mechanical Design

The sensing element is based on a compliant hexagonal geometry manufactured using Thermoplastic Polyurethane (TPU). Unlike conventional rigid force sensors, the flexible structure deforms elastically under compression while maintaining repeatable mechanical behaviour. The internal cavity accommodates both the permanent magnet and the magnetometer, ensuring controlled relative motion during loading.

The geometry was designed in SolidWorks and fabricated using FDM 3D printing. The hexagonal topology provides high compliance, allowing measurable displacement under relatively small applied loads while maintaining structural integrity.

<p align="center">
<img src="images/sensor_dimension.png" width="450">
</p>

---

# Electronic Circuit

The electronic system consists of an ESP32 development board interfaced with an MLX90393 three-axis magnetometer over the I²C communication protocol. The ESP32 supplies power to the sensor, performs real-time magnetic field acquisition, executes calibration and force estimation algorithms, and transmits processed data over Wi-Fi.

The default ESP32 I²C pins are used in the firmware:

| ESP32 Pin | MLX90393 Pin |
|-----------|--------------|
| 3.3 V | VCC |
| GND | GND |
| GPIO21 (SDA) | SDA |
| GPIO22 (SCL) | SCL |

<p align="center">
<img src="hardware/schematic.png" width="700">
</p>

---

# Hardware Components

| Component | Specification |
|----------|---------------|
| Microcontroller | ESP32 Development Board |
| Magnetometer | MLX90393 Triple-Axis Digital Magnetometer |
| Permanent Magnet | Neodymium Cube Magnet |
| Structure Material | Thermoplastic Polyurethane (TPU) |
| Fabrication Method | FDM 3D Printing |
| Communication | Wi-Fi (HTTP POST) |
| Power Supply | USB 5 V |

---

# Firmware Architecture

The embedded firmware running on the ESP32 performs the following operations:

- Initialization of the MLX90393 sensor
- Hard-iron calibration
- Soft-iron calibration
- Earth magnetic field compensation
- Magnetic field acquisition
- Magnetic field magnitude calculation
- Distance estimation using calibration data
- Force estimation through interpolation
- Wi-Fi communication
- HTTP POST transmission to a remote server

The firmware is written using the Arduino framework in C++ and follows a modular processing pipeline for real-time force estimation.

---

# Repository Structure

```
Soft-Tactile-Force-Sensor
│
├── firmware/          # ESP32 firmware (Arduino)
├── server/            # Flask server for data acquisition
├── hardware/          # Circuit schematic and hardware documentation
├── CAD/               # SolidWorks, STEP and STL models
├── data/              # Calibration and experimental datasets
├── docs/              # Project report and supporting documentation
├── images/            # Figures used in documentation
├── media/             # Demonstration videos
│
├── README.md
├── LICENSE
├── .gitignore
├── CHANGELOG.md
├── CONTRIBUTING.md
├── CODE_OF_CONDUCT.md
└── CITATION.cff
```

---

# Software Requirements

- Arduino IDE 2.x
- ESP32 Arduino Core
- Python 3.10+
- Flask
- SolidWorks (for CAD modification)
- COMSOL Multiphysics (for magnetic field simulation)

---

# Hardware Requirements

| Component | Quantity |
|-----------|:--------:|
| ESP32 Development Board | 1 |
| MLX90393 Magnetometer | 1 |
| Neodymium Cube Magnet | 1 |
| TPU Hexagonal Structure | 1 |
| USB Cable | 1 |
| Jumper Wires | As Required |

---

# Arduino Libraries

Install the following libraries before uploading the firmware.

- Adafruit MLX90393 Library
- Wire
- WiFi
- HTTPClient

---

# Installation

## Clone the Repository

```bash
git clone https://github.com/<username>/Soft-Tactile-Force-Sensor.git
```

```bash
cd Soft-Tactile-Force-Sensor
```

---

## Upload Firmware

Open

```
firmware/tactile_force_sensor/
```

using Arduino IDE.

Select

- ESP32 Development Board
- Correct COM Port

Upload the firmware.

---

## Configure Wi-Fi

Create a file named

```
secrets.h
```

inside the firmware directory.

```cpp
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
```

This file is ignored by Git to prevent publishing private credentials.

---

## Start the Server

Navigate to the server directory.

```bash
cd server
```

Install dependencies.

```bash
pip install -r requirements.txt
```

Run the Flask server.

```bash
python app.py
```

---

# Future Improvements

Several extensions can further improve the sensing system.

- Multi-point tactile sensing array
- Flexible PCB integration
- Bluetooth Low Energy communication
- ROS 2 interface
- Machine learning based force estimation
- Higher resolution magnetic sensors
- Wearable tactile sensing glove
- Helmet impact sensing system
- Closed-loop force feedback
- Wireless battery-powered operation

---

# Applications

The proposed sensing system can be used in

- Soft Robotics
- Prosthetic Devices
- Rehabilitation Systems
- Human-Robot Interaction
- Wearable Electronics
- Medical Instrumentation
- Tactile Grippers
- Structural Health Monitoring
- Helmet Impact Detection
- Research and Education

---

# Team

**Design Lab – I (ME-205)**

Indian Institute of Technology Ropar

### Team Members

- Hadiya Pratik Ghanshyambhai
- Kanav Dumra
- Kodepaka Aravind Stalin
- Manav Gulati
- Pratyush Sahu

Supervisor

**Dr. Prabhat K. Agnihotri**

---

# References

1. ASTM Standards for TPU Mechanical Testing
2. ESP32 Technical Documentation
3. MLX90393 Triple-Axis Magnetometer Datasheet
4. COMSOL Multiphysics Documentation
5. Research literature on magnetic tactile sensing and soft robotics

---

# Acknowledgements

The authors would like to thank the Department of Mechanical Engineering, Indian Institute of Technology Ropar, for providing laboratory facilities, guidance, and testing equipment throughout the development of this project.

Special thanks to **Dr. Prabhat K. Agnihotri** for his continuous guidance and valuable suggestions during the Design Lab course.

---

# License

This project is licensed under the MIT License.

See the **LICENSE** file for more information.