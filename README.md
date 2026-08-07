# Engine Control Unit (ECU) Simulator using STM32F411RE and FreeRTOS

## Overview

This project is a prototype Engine Control Unit (ECU) Simulator developed using the STM32F411RE Nucleo Board. It demonstrates the core functionalities of an automotive Engine Control Unit by integrating sensor interfacing, custom peripheral drivers, FreeRTOS task scheduling, and IoT-based remote monitoring through an ESP32 web dashboard.

The project is designed for learning embedded systems, automotive electronics, real-time operating systems, and IoT integration.

---

## Features

- Custom GPIO Driver (Register-Level Programming)
- Custom UART Driver (Register-Level Programming)
- SSD1306 OLED Display Interface
- FreeRTOS-Based Multitasking
- Engine Ignition Simulation
- Engine RPM Simulation
- Fuel Level Simulation
- Engine Temperature Monitoring
- RGB LED Status Indication
- UART Communication
- ESP32 Web Dashboard
- Real-Time Engine Parameter Monitoring

---

## Hardware Components

- STM32F411RE Nucleo Board
- ESP32 DevKit V4
- SSD1306 OLED Display (I²C)
- LM35 Temperature Sensor
- Two Potentiometers
- RGB LED
- Push Button
- Breadboard and Jumper Wires

---

## Software Requirements

- STM32CubeIDE
- STM32 HAL Libraries
- FreeRTOS
- Arduino IDE (ESP32)
- Embedded C
- Git

---

## Project Structure

```
ECU-Simulator/
│
├── Core/
│   ├── Inc/
│   ├── Src/
│
├── Drivers/
│   ├── GPIO/
│   ├── UART/
│   ├── SSD1306/
│
├── FreeRTOS/
│
├── ESP32/
│   └── WebDashboard/
│
├── Images/
│
├── Documentation/
│
└── README.md
```

---

## Hardware Connections

| Component | STM32 Pin |
|-----------|-----------|
| LM35 | PA0 |
| Potentiometer (Fuel) | PA4 |
| Potentiometer (RPM) | PA8 |
| Push Button | PC13 |
| OLED SDA | PB7 |
| OLED SCL | PB6 |
| RGB Red | PB3 |
| RGB Green | PB4 |
| RGB Blue | PB5 |
| ESP32 RX | PA9 (UART1 TX) |
| Serial Monitor | PA2 (UART2 TX) |

---

## System Workflow

1. Power ON
2. Initialize GPIO, ADC, UART, I²C and System Clock
3. Initialize OLED Display
4. Start FreeRTOS Scheduler
5. Detect Ignition
6. Read Sensors
7. Process Engine Parameters
8. Update OLED Display
9. Control RGB LED
10. Send Data via UART
11. ESP32 Updates Web Dashboard
12. Repeat

---

## FreeRTOS Tasks

| Task | Priority |
|------|----------|
| Ignition Task | Highest |
| Sensor Task | High |
| Processing Task | Medium |
| OLED Task | Low |
| UART Task | Lowest |

---

## IoT Dashboard

The ESP32 receives engine parameters from the STM32 through UART and hosts a web server that displays:

- Engine Temperature
- Engine RPM
- Fuel Level
- Vehicle Speed
- Ignition Status

The dashboard can be accessed from any web browser connected to the same Wi-Fi network.

---

## Project Highlights

- Register-Level Driver Development
- Modular Software Architecture
- Real-Time Task Scheduling using FreeRTOS
- Embedded GUI using OLED Display
- IoT-Based Remote Monitoring
- Educational Automotive ECU Prototype

---

## Future Enhancements

- CAN Bus Communication
- OBD-II Diagnostics
- Cloud Connectivity
- Mobile Application
- Advanced Engine Control Algorithms
- Additional Automotive Sensors
- Fault Detection and Logging

---

## License

This project is developed for educational and academic purposes.

---

## Acknowledgements

- STMicroelectronics
- FreeRTOS
- STM32CubeIDE
- Arduino ESP32 Framework
- SSD1306 OLED Library

---

