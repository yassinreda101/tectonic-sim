# Tectonic-Sim

## Overview
Tectonic-Sim is an **ESP32-based** mini tectonic plate simulator developed for the ECE 3011 Junior Design project. This project simulates the physical movement and interaction of tectonic plates using **DC motors**, **touch sensors**, and **a buzzer** to mimic real-world geological behavior.

## Features
- Simulates tectonic plate movement using DC motors
- Models different types of plate interactions (convergent, divergent, transform boundaries)
- Controlled via an ESP32 microcontroller with touch-sensitive inputs
- Speed control via potentiometer
- Real-time visualization through LED indicators
- Countdown start with buzzer feedback

## Hardware Requirements
- **ESP32 microcontroller**
- **DC motors** (minimum 2) with motor drivers
- **Touch sensors** for motor control
- **Potentiometer** for speed adjustment
- **Buzzer** for auditory feedback
- **LEDs** for speed indication
- **Power supply** (appropriate voltage for ESP32 and motors)
- **Breadboard and jumper wires**

## Installation
### Prerequisites
- **Arduino IDE** (with ESP32 board package installed)
- Required Arduino libraries:
  - `Arduino.h` (included)
  - `Wire.h` (included for I2C communication if needed)

### Clone the Repository
```bash
git clone https://github.com/yourusername/Tectonic-Sim.git
cd Tectonic-Sim
```

### Upload Code to ESP32
1. Open `tectonic_sim.ino` in the Arduino IDE.
2. Connect the ESP32 board to your computer via USB.
3. Select **ESP32 Dev Module** under **Tools > Board**.
4. Select the correct port under **Tools > Port**.
5. Click **Upload** to flash the code to the ESP32.


## Configuration
Edit `config.h` to modify:
- **Motor speed settings** (`SPEED_LEVELS`)
- **Plate boundary behavior** (`PLATE_MODE`)
- **Buzzer settings** (`BEEP_DURATION`, `BEEP_PAUSE`, `NUM_BEEPS`)

## Usage
1. Power on the ESP32.
2. Adjust speed using the potentiometer.
3. Use touch sensors to activate motors.
4. Observe motor movement simulating tectonic plate interactions.
5. Monitor LED indicators for speed and buzzer for auditory feedback.
