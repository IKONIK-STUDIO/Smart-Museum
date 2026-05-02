# Smart Tájház Automation System (WRO Project)

## Overview

This project is a **traditional Hungarian “tájház” automation system**, developed for the **WRO (World Robot Olympiad)** competition.

The system simulates a smart rural house using **two Arduino boards** working together. It integrates environmental monitoring, automation, renewable energy simulation, and safety systems.

> ⚠️ Note: This README was written with the help of AI, but **all source code was written by the developer**. I am just bad at writing...

---

## System Architecture

The project is divided into two main parts:

```
/MAIN_AR1 → Core house control (sensors, safety, automation)
/MAIN_AR2 → Display, energy systems, water heating, solar tracking
```

### Arduino 1 (MAIN_AR1)

Handles:

* Temperature & humidity (inside + outside)
* Light and motion detection
* Smoke detection (fire safety)
* Water level monitoring
* WC pump system
* Window automation (servo)
* Heating (fireplace), cooling (AC)
* Lighting automation
* Alarm system (laser + sound)
* Demo mode
* Serial data transmission to Arduino 2

### Arduino 2 (MAIN_AR2)

Handles:

* LCD display (live system data)
* Solar panel tracking (light-based servo control)
* Wind & solar energy indicators
* Water temperature monitoring
* Hand detection (infra sensor)
* Hot water system (heating/cooling control)
* Pump control for water circulation
* Serial data reception from Arduino 1

---

## Key Features

### Smart Environment Control

* Automatically decides between:

  * Fireplace (heating)
  * Air conditioning (cooling)
  * Window opening (natural ventilation)

### Safety System

* Smoke detection triggers full system override
* Laser-based intrusion detection
* Audible alarm using speaker
* System reset into safe state

### Automation Logic

* Fully **non-blocking**, based on:

  * `millis()` timing
  * Step-based state machines

### Renewable Energy Simulation

* Solar panel tracks light direction using 2 sensors
* Wind and solar input detection via analog signals
* LED indicators for energy activity

### Water System

* WC pump controlled by button + water level
* Smart hot water system:

  * Heating if too cold
  * Cooling if too hot
* Infrared hand detection for water usage

### LCD Interface

* Displays:

  * Indoor/outdoor temperature
  * Humidity
* Warning screen for smoke detection
* Multi-page system with timed switching

---

## Communication

The two Arduinos communicate via **Serial (UART)**:

* Arduino 1 → sends:

  * Temperatures
  * Humidity
  * Smoke status
  * Alarm state

* Arduino 2 → receives and processes data for display

---

## Technologies Used

* Arduino (C/C++)
* PlatformIO
* Sensors:

  * DHT11 (temperature & humidity)
  * LDR (light sensors)
  * Water level sensor
  * Smoke detector
  * Infrared sensor
* Actuators:

  * Servo motors
  * Relays
  * LEDs
  * Speaker
* Display:

  * I2C LCD

---

## Installation (PlatformIO)

### 1. Install PlatformIO

* Install **Visual Studio Code**
* Open Extensions
* Install **PlatformIO**

### 2. Open Project

* Open the project folder in VS Code
* PlatformIO will automatically detect both environments

### 3. Upload Code

#### Arduino 1:

```
MAIN_AR1/src/main.ino
```

#### Arduino 2:

```
MAIN_AR2/src/main.ino
```

Select the correct board and COM port, then click **Upload**.

---

## How It Works

The system does **NOT** rely on delays. Instead:

* Each subsystem runs in small steps (`step variables`)
* Functions are repeatedly called inside `loop()`
* Timing is controlled using `millis()`

Example:

* Sensors update periodically
* Decisions are made incrementally
* Outputs update without blocking execution

This allows:

* Smooth multitasking
* Fast response time
* Stable system behavior

---

## Demo Mode

* Activated via input pin
* Automatically cycles between:

  * Heating
  * Window opening
  * Cooling

Useful for:

* Presentations
* Testing without real sensor changes

---

## Alarm Mode

Triggered by:

* Laser interruption (intrusion)
* Smoke detection

Effects:

* Disables normal operation
* Activates sound alarm
* Forces safe system state
* Displays warning on LCD

---

## Notes

* The code is intentionally written using **state machines** instead of delays
* Designed for reliability and competition demonstration
* Easily extendable with additional sensors or modules
* It's still in WIP, radical changes might happen at any time
* The **latest STABLE version** does not contain this many features
* The **latest version** may not be stable, everything is still being updated