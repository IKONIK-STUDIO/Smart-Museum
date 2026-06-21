# Smart Museum

An intelligent museum automation system developed for the WRO Future Innovators competition.

The project combines renewable energy, environmental monitoring, climate management, water management and security systems into a single coordinated control system powered by two Arduino Uno boards.

## Project Overview

The goal of the project is to demonstrate how modern technologies can help museums become more sustainable while maintaining optimal conditions for preserving valuable artworks.

The museum automatically monitors its environment and reacts to changing conditions through multiple independent subsystems working together in real time.

Main features include:

- Intelligent temperature control
- Solar tracking system
- Water management system
- Smoke detection
- Security monitoring
- LCD information display
- Renewable energy simulation

---

# Software Architecture

One of the main goals during development was creating a system capable of handling multiple tasks simultaneously.

Instead of relying on blocking code and long delays, the project was designed around independent state machines.

Most beginner Arduino projects use structures similar to:

```cpp
delay(1000);
```

which completely stops the controller during execution.

In this project, every subsystem progresses one small step during each loop iteration:

```cpp
switch(napelemStep){
    case 1:
        ...
        break;

    case 2:
        ...
        break;
}
```

This allows:

- Responsive sensor monitoring
- Parallel subsystem execution
- Easier debugging
- Better scalability
- Improved reliability

Each major subsystem has its own dedicated control function:

```cpp
napelemMain();
lcdMain();
vizHomeroMain();
infraMain();
```

This modular architecture makes future expansion significantly easier.

---

# Hardware Architecture

The project uses two Arduino Uno boards.

## Arduino #1 – Monitoring Controller

Responsible for collecting environmental information:

- Temperature monitoring
- Humidity monitoring
- Smoke detection
- Alarm monitoring
- Environmental data acquisition

## Arduino #2 – Automation Controller

Responsible for:

- Solar tracking
- LCD display management
- Water management
- Renewable energy simulation
- Actuator control

Communication between the controllers takes place through serial communication.

This separation reduces complexity and allows each controller to focus on a specific set of responsibilities.

---

# Solar Tracking System

One of the project's primary innovations is its solar tracking system.

Two light sensors continuously monitor incoming light levels.

Instead of reacting to a single reading, the software samples each sensor multiple times and calculates an average value:

```cpp
if(napelemFor1Count <= 10){
    szum += analogRead(fenyBal);
}
```

After sampling:

```cpp
bal = szum / 10;
jobb = szum / 10;
```

The system calculates the difference between both sensors:

```cpp
diff = bal - jobb;
```

To avoid constant micro-adjustments, a dead zone is used:

```cpp
if(abs(diff) > halottZona)
```

Only meaningful differences trigger movement.

The servo position is then adjusted:

```cpp
poz = napelemIf2Side ? poz + 5 : poz - 5;
```

and constrained within safe limits:

```cpp
poz = constrain(poz, minPoz, maxPoz);
```

This approach minimizes unnecessary movement and improves long-term reliability.

---

# Environmental Monitoring

The museum continuously monitors both indoor and outdoor conditions.

Values received include:

- Indoor temperature
- Indoor humidity
- Outdoor temperature
- Outdoor humidity

Data is transferred between the controllers using a lightweight custom serial protocol.

Example:

```cpp
belsoHomerseklet = s1.toFloat();
belsoParatartalom = s2.toFloat();
kulsoHomerseklet = s3.toFloat();
kulsoParatartalom = s4.toFloat();
```

The environmental data is used to support intelligent climate management decisions.

---

# Serial Communication

The project uses a simple custom communication protocol between the two controllers.

The receiving controller waits for a synchronization character:

```cpp
if(teszt == "a")
```

and then processes incoming values.

This protocol transfers:

- Indoor temperature
- Indoor humidity
- Outdoor temperature
- Outdoor humidity
- Smoke status
- Alarm status

The approach is lightweight, efficient and easy to debug.

---

# LCD Information System

A dedicated state machine manages the LCD display.

Instead of continuously refreshing the entire screen, information is updated in stages:

```cpp
lcd.setCursor(0,0);
lcd.print("B:");
lcd.print(belsoHomerseklet);
```

Displayed information includes:

- Indoor temperature
- Outdoor temperature
- Indoor humidity
- Outdoor humidity
- Alarm messages
- System status

This reduces flickering and improves readability.

---

# Water Management System

The project includes an automated water temperature management system.

Temperature is measured using a DS18B20 sensor:

```cpp
sensors.requestTemperatures();
vizHomerseklet = sensors.getTempCByIndex(0);
```

The controller evaluates the current temperature and reacts accordingly.

Example conditions:

```cpp
vizHomerseklet < 23
```

```cpp
vizHomerseklet > 28
```

Based on the measured values, the system activates the required outputs.

---

# Safety System

The museum continuously monitors smoke and alarm conditions.

When an alarm condition occurs:

```cpp
if(beriaszt)
```

the system enters emergency mode.

Non-essential outputs are disabled:

```cpp
digitalWrite(napelemLed, LOW);
digitalWrite(szeleromuLed, LOW);
```

The LCD immediately displays warning information and the system transitions into a safe state.

This ensures predictable behavior during emergency situations.

---

# Engineering Highlights

## State Machine Design

Multiple independent state machines operate simultaneously throughout the system.

Benefits:

- Non-blocking execution
- Improved responsiveness
- Easier maintenance
- Scalable architecture

---

## Sensor Averaging

Sensor readings are averaged before processing:

```cpp
bal = szum / 10;
```

Benefits:

- Reduced noise
- Increased stability
- More accurate decisions

---

## Dead-Zone Control

The solar tracker only reacts when the difference exceeds a predefined threshold:

```cpp
if(abs(diff) > halottZona)
```

Benefits:

- Eliminates servo jitter
- Reduces mechanical wear
- Improves reliability

---

## Modular Software Structure

Subsystems operate independently:

```cpp
napelemMain();
lcdMain();
vizHomeroMain();
infraMain();
```

Benefits:

- Cleaner code
- Easier debugging
- Simple future expansion

---

# Future Improvements

Potential future developments include:

- Cloud-based monitoring
- Historical data logging
- Mobile application integration
- AI-assisted decision making
- Predictive maintenance
- Advanced energy optimization

---

# Technologies Used

- Arduino Uno
- C++
- DS18B20 Temperature Sensor
- LDR Light Sensors
- Servo Motors
- LCD Display
- Serial Communication
- State Machine Architecture

---

**Artists Create It. We Protect It.**