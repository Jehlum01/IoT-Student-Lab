# 🛠️ Level 2: Microcontroller Lab Challenges

A series of progressive embedded systems challenges focusing on sensor integration, finite state machines, non-blocking timing, and actuator automation.

## 📋 Challenge Overview

| Challenge | Topic | Focus Areas | 
 | ----- | ----- | ----- | 
| **02** | Smart Street Light | LDR, Multi-threshold logic, GPIO control | 
| **03** | Temperature Warning | Analog sensors, Thresholds, Serial telemetry | 
| **04** | Smart Fan | Multi-state control, DC motor / Transistor switching | 
| **05** | Motion-Activated Timer | PIR sensor, Non-blocking timing (`millis()`) | 
| **06** | Security Alarm | State toggles, Debounce logic, Audio/visual alerting | 
| **07** | Manual + Automatic Light | Hybrid control systems, Conflict arbitration | 
| **08** | Sensor Dashboard | ASCII UI formatting, Multi-sensor streaming | 
| **09** | Automatic Room Controller | Multi-input automation, Inactivity timeouts | 
| **10** | Smart Room Automation (Capstone) | System integration, State machines, Diagnostics | 

### Challenge 02 — Smart Street Light

*Modify **Project 10**.*

#### Objectives

* Drive **three separate LEDs** via digital outputs.

* Turn lights **ON** when ambient light drops below threshold.

* Turn lights **OFF** when ambient light returns to bright conditions.

#### Extension: Staged Lighting Sequence

Implement stepped illumination based on darkness severity:

* **Dark** $\rightarrow$ Light 1 `ON`

* **Very dark** $\rightarrow$ Light 1 + Light 2 `ON`

* **Extremely dark** $\rightarrow$ Light 1 + Light 2 + Light 3 `ON`

### Challenge 03 — Temperature Warning

*Modify **Project 11**.*

#### Hardware Additions

* `1x` Green LED (Normal status)

* `1x` Red LED (High-temperature alert)

* Analog temperature sensor (e.g., TMP36, LM35, or NTC thermistor)

#### Behavioral Requirements

* $T < T_{\text{threshold}}$ **(Normal):** Green LED `ON`, Red LED `OFF`

* $T \ge T_{\text{threshold}}$ **(Overheat):** Red LED `ON`, Green LED `OFF`

* Continuously stream formatted temperature values to the **Serial Monitor**.

### Challenge 04 — Smart Fan

*Modify **Project 12**.*

#### State Machine Flow

Implement a 3-tier state controller governed by temperature readings:

```
       Low Temp (Below Threshold 1)
                  │
                  ▼
              [Fan OFF]
                  │
                  ▼
    Medium Temp (Threshold 1 to 2)
                  │
                  ▼
              [Fan ON]
                  │
                  ▼
      High Temp (Above Threshold 2)
                  │
                  ▼
       [Fan ON + Warning LED ON]

```

### Challenge 05 — Motion-Activated Timer

*Modify **Project 13**.*

#### Objectives

1. Trigger an illumination LED upon detecting motion via a **PIR sensor**.

2. Keep the LED illuminated for a configurable duration $t_{\text{hold}}$.

3. **Re-triggerable behavior:** Automatically reset the countdown timer whenever fresh motion occurs while the LED is already on.

> \[!WARNING\]
> **No Blocking Delays:** Do not use `delay()` for timing. Use non-blocking `millis()` tracking to allow the processor to stay responsive to incoming interrupts and inputs.

### Challenge 06 — Security Alarm

*Modify **Project 14**.*

#### Required Peripherals

* `1x` Push button (System arm/disarm toggle)

* `1x` PIR motion sensor

* `1x` Status indicator LED

* `1x` Piezo buzzer

#### Operational Logic

* Use the push button to switch between two main states: **ARMED** and **DISARMED**.

* When **DISARMED**, all motion events are ignored.

* When **ARMED**, any positive trigger on the PIR sensor activates an immediate audiovisual alarm pattern via the buzzer and LED.

### Challenge 07 — Manual + Automatic Light

*Combine concepts from **Projects 08, 09, and 13**.*

#### Required Components

* Push button | LDR | PIR sensor | Indicator LED

#### Behavioral Matrix

* **Manual Input:** Button press immediately forces the light state between `ON` and `OFF`.

* **Automatic Triggers:**

  * **Dark + Motion:** Turn light `ON`.

  * **Bright + No Motion:** Turn light `OFF`.

> \[!IMPORTANT\]
> **Conflict Resolution:** You must program clear priority rules defining what happens when manual overrides conflict with environmental automation rules (e.g., manual off requested while motion is actively detected in the dark).

### Challenge 08 — Sensor Dashboard

Design a human-readable ASCII telemetry display printed periodically to the **Serial Monitor**.

#### Requirements

* Integrate at least **two sensors** and **two output devices**.

* Clear and refresh the frame at a consistent interval:

```
========================
   SMART ENVIRONMENT    
========================
Light:       [Value]
Temperature: [Value] °C
Motion:      [Active / Idle]
LED:         [ON / OFF]
Fan:         [ON / OFF]
Alarm:       [ARMED / DISARMED]
========================

```

### Challenge 09 — Automatic Room Controller

#### Pin Architecture

* **Sensors:** LDR (Light), Temperature Sensor, PIR (Motion)

* **Actuators:** LED, DC Fan / Relay

#### Automation Rules

1. **Lighting Automation:** Dark + Motion $\rightarrow$ Light `ON`

2. **Climate Control:** Ambient temperature $> T_{\text{target}}$ $\rightarrow$ Fan `ON`

3. **Power Saving:** Absence of motion for $\Delta t_{\text{timeout}}$ $\rightarrow$ Light `OFF`

### Challenge 10 — Level 2 Final Challenge: Smart Room Automation System

*Design, wire, and deploy a comprehensive automation node synthesizing all Level 2 objectives.*

#### Hardware Requirements

```
Inputs:
  ├── 1x Analog Sensor (e.g., LDR, Potentiometer, Temperature)
  ├── 1x Digital Sensor (e.g., PIR Motion Detector)
  └── 1x Push Button (Debounced user input)

Outputs:
  ├── 1x Status LED
  ├── 1x Audible Buzzer
  └── 1x Actuator (DC Fan, Servo motor, or Relay module)

```

#### Core Firmware Requirements

* **Stable Sensor Acquisition:** Smooth out analog jitter using averaging or debounce filtering.

* **Finite State Machine (FSM):** Structured system modes handling inputs deterministically.

* **Non-blocking Timing:** Complete concurrent operation using `millis()`.

* **Configurable Settings:** At least one threshold parameter adjustable via hardware input or Serial commands.

* **Serial Diagnostics:** Real-time log reporting displaying state transitions, tick counts, and sensor faults.
