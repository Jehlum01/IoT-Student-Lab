# 🚗 Project 20 — Arduino Parking Sensor

> ### 🚦 A hands-on Arduino project that turns ultrasonic distance measurements into a simple parking-assistance system.

[![Arduino](https://img.shields.io/badge/Platform-Arduino%20Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Sensor](https://img.shields.io/badge/Sensor-HC--SR04-blue?style=for-the-badge)](#-how-it-works)
[![Level](https://img.shields.io/badge/Level-Beginner%20%2B-green?style=for-the-badge)](#-learning-focus)
[![Project](https://img.shields.io/badge/Project-20-orange?style=for-the-badge)](#-project-overview)

---

## 🌟 Project Overview

The **Arduino Parking Sensor** builds on the ultrasonic distance measurement concepts introduced in Project 19.

Instead of simply displaying a distance, the Arduino now **interprets the distance and provides visual and audible feedback**.

Three LEDs represent different proximity zones:

```text
                 🚗 PARKING SENSOR

        ┌───────────────────────────────┐
        │          HC-SR04              │
        │      Ultrasonic Sensor        │
        └───────────────┬───────────────┘
                        │
                  Ultrasonic waves
                        │
                        ▼
                  ┌───────────┐
                  │  OBJECT   │
                  └───────────┘
                        │
                        ▼
                 Distance measured
                        │
                        ▼
                 ┌─────────────┐
                 │ Arduino Uno │
                 └──────┬──────┘
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
      🟢 GREEN       🟡 YELLOW      🔴 RED
        SAFE         CAUTION       WARNING
                        │
                        ▼
                    🔊 BUZZER
```

The project demonstrates an important embedded-systems idea:

> **Sensor data → Decision → Feedback**

---

## 🎯 Project Goals

By completing this project, students will learn how to:

- Measure object distance using an **HC-SR04 ultrasonic sensor**
- Read sensor timing data with an Arduino
- Create **distance-based conditions**
- Control multiple LEDs
- Control an active buzzer
- Build a simple proximity-warning system
- Translate sensor data into meaningful user feedback
- Think about thresholds and system behavior like an embedded-systems designer

---

## 🧩 Components Required

| Component | Qty. | Purpose |
|---|---:|---|
| 🔵 Arduino Uno | 1 | Main controller |
| 📡 HC-SR04 | 1 | Measures distance |
| 🟢 Green LED | 1 | Safe zone indicator |
| 🟡 Yellow LED | 1 | Caution zone indicator |
| 🔴 Red LED | 1 | Warning zone indicator |
| 🔊 Active buzzer | 1 | Audible warning |
| `220 Ω` resistor | 3 | Limits LED current |
| Breadboard | 1 | Circuit assembly |
| Jumper wires | — | Electrical connections |

---

# 🔌 Wiring Overview

## Pin Mapping

| Device | Pin | Arduino Uno |
|---|---|---|
| HC-SR04 | VCC | **5V** |
| HC-SR04 | TRIG | **D8** |
| HC-SR04 | ECHO | **D9** |
| HC-SR04 | GND | **GND** |
| Buzzer | + | **D10** |
| Buzzer | − | **GND** |
| Green LED | Anode | **D11 through 220 Ω** |
| Yellow LED | Anode | **D12 through 220 Ω** |
| Red LED | Anode | **D13 through 220 Ω** |
| LEDs | Cathodes | **GND** |

### 🔧 Circuit Map

```text
                         ARDUINO UNO
                    ┌──────────────────┐
                    │                  │
              5V ───┤                  │
                    │                  │
             D8 ────┤                  │
             D9 ◄───┤                  │
                    │                  │
            D10 ────┤───────► 🔊       │
            D11 ────┤──220Ω──► 🟢      │
            D12 ────┤──220Ω──► 🟡      │
            D13 ────┤──220Ω──► 🔴      │
                    │                  │
            GND ────┤                  │
                    └──────────────────┘
                 │       │       │
                 ▼       ▼       ▼
               GND     GND     GND
```

---

# 📡 HC-SR04 Connection

```text
             HC-SR04
        ┌───────────────┐
        │               │
        │   ◯       ◯   │
        │               │
        └───────────────┘
          │   │   │   │
          │   │   │   │
         VCC TRIG ECHO GND
          │   │   │   │
          ▼   ▼   ▼   ▼
         5V  D8  D9  GND
```

The Arduino sends a trigger signal through **D8** and measures the returned echo signal through **D9**.

---

# 💡 LED Connections

Every LED must use a **220 Ω current-limiting resistor**.

### 🟢 Green LED

```text
Arduino D11
     │
     ▼
   220 Ω
     │
     ▼
 LED Anode (+)
 LED Cathode (-)
     │
     ▼
    GND
```

### 🟡 Yellow LED

```text
Arduino D12
     │
     ▼
   220 Ω
     │
     ▼
 LED Anode (+)
 LED Cathode (-)
     │
     ▼
    GND
```

### 🔴 Red LED

```text
Arduino D13
     │
     ▼
   220 Ω
     │
     ▼
 LED Anode (+)
 LED Cathode (-)
     │
     ▼
    GND
```

> ⚠️ **Never connect an LED directly to an Arduino GPIO without an appropriate current-limiting resistor.**

---

# 🔊 Buzzer Connection

For a small **active buzzer**:

```text
Arduino D10 ─────────► Buzzer (+)
Arduino GND ─────────► Buzzer (-)
```

The Arduino controls the buzzer by changing the state of D10.

### ⚠️ Current Warning

Do **not** connect a high-current load directly to an Arduino GPIO pin.

This includes:

- Automotive buzzers
- Motors
- Large speakers
- Relays without suitable driver circuitry
- Other high-current loads

If the load requires more current than the Arduino GPIO should provide, use an appropriate **transistor/MOSFET driver and separate power arrangement**.

---

# 🚦 How the Parking Sensor Works

The system continuously follows this process:

```text
       START
         │
         ▼
   Trigger HC-SR04
         │
         ▼
    Measure ECHO
         │
         ▼
  Calculate distance
         │
         ▼
   Compare threshold
         │
    ┌────┼────┐
    ▼    ▼    ▼
  SAFE CAUTION WARNING
    │    │     │
    ▼    ▼     ▼
   🟢   🟡    🔴 + 🔊
    │    │     │
    └────┴─────┘
         │
         ▼
      Repeat
```

---

# 📏 Proximity Zones

The LEDs provide a simple visual interpretation of distance.

A typical design can use:

| Distance | State | Indicator |
|---|---|---|
| **> 50 cm** | 🟢 SAFE | Green LED |
| **20–50 cm** | 🟡 CAUTION | Yellow LED |
| **< 20 cm** | 🔴 WARNING | Red LED + buzzer |

> These thresholds are design choices. Students can experiment with different values to improve the system for their own setup.

### Visual Representation

```text
        FAR                                      CLOSE
         │                                           │
         ▼                                           ▼

   ─────────────────────────────────────────────────────
   │                 │                 │
   │      🟢         │       🟡        │      🔴
   │      SAFE       │     CAUTION     │    WARNING
   │                 │                 │
   ─────────────────────────────────────────────────────
        >50 cm          20–50 cm          <20 cm
```

---

# 🧠 The Core Logic

The Arduino does not simply measure distance.

It **interprets** the measurement.

```text
Measured Distance
       │
       ▼
┌──────────────────┐
│ Is distance >50? │
└────────┬─────────┘
         │
     YES │
         ▼
   🟢 SAFE
         │
         └─────────────┐
                       │
                  NO   ▼
             ┌──────────────────┐
             │ Is distance >20? │
             └────────┬─────────┘
                      │
                  YES │
                      ▼
                 🟡 CAUTION
                      │
                      └──────────┐
                                 │
                            NO   ▼
                           🔴 WARNING
                              + 🔊
```

This is a simple example of **decision logic in embedded systems**.

---

# 🔊 From Distance to Sound

The project can be extended so that the buzzer becomes more urgent as the object approaches.

```text
Object far away
       │
       ▼
    No beep
       │
       ▼
Object getting closer
       │
       ▼
   Slow beeps
       │
       ▼
Object very close
       │
       ▼
   Fast beeps
       │
       ▼
Critical distance
       │
       ▼
Continuous warning
```

This is similar to the feedback behavior found in real parking-assistance systems.

---

# 🏗️ System Architecture

```text
┌───────────────────────────────────────────┐
│                INPUT                      │
│                                           │
│           HC-SR04 Ultrasonic              │
│                  Sensor                   │
└──────────────────┬────────────────────────┘
                   │
                   │ Distance information
                   ▼
┌───────────────────────────────────────────┐
│              PROCESSING                   │
│                                           │
│              Arduino Uno                  │
│                                           │
│  Measure → Calculate → Compare → Decide  │
└──────────────────┬────────────────────────┘
                   │
                   │ Control signals
                   ▼
┌───────────────────────────────────────────┐
│                OUTPUT                     │
│                                           │
│      🟢       🟡       🔴       🔊       │
│     SAFE    CAUTION  WARNING   BUZZER    │
└───────────────────────────────────────────┘
```

---

# 🛠️ Build Sequence

### Step 1 — Place the Arduino

Position the Arduino and breadboard so the wiring remains easy to inspect.

### Step 2 — Connect the HC-SR04

```text
VCC  → 5V
TRIG → D8
ECHO → D9
GND  → GND
```

### Step 3 — Add the LEDs

Connect:

```text
D11 → 220 Ω → Green LED → GND
D12 → 220 Ω → Yellow LED → GND
D13 → 220 Ω → Red LED → GND
```

### Step 4 — Add the Buzzer

```text
D10 → Buzzer +
GND → Buzzer -
```

### Step 5 — Check the Circuit

Before powering the board, verify every connection.

### Step 6 — Upload the Program

Upload the parking-sensor program to the Arduino Uno.

### Step 7 — Test with an Object

Move an object toward and away from the sensor.

Observe:

```text
Distance changes
      ↓
Zone changes
      ↓
LED changes
      ↓
Buzzer behavior changes
```

---

# 🧪 Testing Checklist

Test at several distances:

```text
☐ ~10 cm
☐ ~20 cm
☐ ~30 cm
☐ ~50 cm
☐ ~75 cm
☐ ~100 cm
```

Record what happens:

| Distance | Green | Yellow | Red | Buzzer |
|---:|:---:|:---:|:---:|:---:|
| 10 cm | | | | |
| 20 cm | | | | |
| 30 cm | | | | |
| 50 cm | | | | |
| 75 cm | | | | |
| 100 cm | | | | |

---

# 🔍 Troubleshooting

| Problem | Possible Cause | Check |
|---|---|---|
| No ultrasonic reading | Sensor wiring issue | VCC, GND, TRIG, ECHO |
| LEDs do not light | Wrong polarity/wiring | LED anode, cathode and resistor |
| LED burns/draws excessive current | Missing resistor | Use 220 Ω resistor |
| Buzzer does not work | Wrong polarity/type | Check active buzzer connections |
| Buzzer behaves strangely | Load requires too much current | Use a suitable driver circuit |
| Distance is unstable | Poor target/reflection | Use a flat target facing the sensor |
| Wrong zone activates | Threshold/logic issue | Check distance comparisons |
| Everything is off | Missing common ground | Verify Arduino and modules share GND |

---

# ⚠️ Important Electrical Notes

### LED Protection

Always use a current-limiting resistor:

```text
Arduino GPIO
     │
     ▼
  220 Ω
     │
     ▼
    LED
     │
     ▼
    GND
```

### GPIO Load

Arduino GPIO pins are intended for small signal loads.

```text
GOOD
Arduino → LED + resistor
Arduino → small active buzzer

CAUTION
Arduino → high-current load ❌
```

For a high-current device, use a proper driver stage.

---

# 🎓 Learning Focus

This project builds on the ultrasonic measurement concepts from **Project 19** and introduces the next layer:

```text
PROJECT 19

Sensor
  ↓
Measurement
  ↓
Distance
```

becomes:

```text
PROJECT 20

Sensor
  ↓
Measurement
  ↓
Distance
  ↓
Threshold
  ↓
Decision
  ↓
LED / Buzzer
```

Students begin moving from **sensor reading** toward **embedded-system control**.

---

# 💡 What Students Should Understand

After completing the project, students should be able to explain:

- Why the HC-SR04 is used.
- What TRIG and ECHO do.
- How distance is obtained from echo timing.
- Why multiple distance thresholds are useful.
- How an Arduino controls LEDs.
- Why LEDs require current-limiting resistors.
- How an active buzzer is controlled.
- Why high-current loads require driver circuits.
- How sensor data can trigger different system states.
- How a simple parking sensor converts a physical measurement into human feedback.

---

# 🚀 Extension Ideas

Once the basic project works, try improving it.

### Challenge 1 — Adjustable Thresholds

Change the safe/caution/warning boundaries.

```text
SAFE      > 60 cm
CAUTION   30–60 cm
WARNING   < 30 cm
```

Compare this behavior with the original thresholds.

### Challenge 2 — Variable Beep Rate

Make the buzzer:

```text
Far      → slow
Closer   → faster
Very close → continuous
```

### Challenge 3 — Serial Monitor

Display:

```text
Distance: 42 cm
Status: CAUTION
```

### Challenge 4 — Smoother Measurements

Take several readings and calculate an average to reduce the effect of occasional noisy measurements.

### Challenge 5 — Build a Mini Parking Bay

Create a cardboard parking area and use the sensor to guide a toy car into the correct position.

---

# 🌍 Real-World Connection

The same basic concept appears in parking-assistance systems:

```text
        VEHICLE
           │
           ▼
   Distance sensor
           │
           ▼
      Distance data
           │
           ▼
      Control logic
           │
      ┌────┴────┐
      ▼         ▼
   Display    Buzzer
```

A real automotive system is considerably more sophisticated, but the fundamental educational concept is similar:

> **Measure the environment → interpret the measurement → provide feedback to the driver.**

---

# 📚 Project Files

Recommended project structure:

```text
Project-20-Parking-Sensor/
│
├── README.md
│
├── wiring/
│   └── Project_20_Parking_Sensor_Wiring.md
│
├── learning-notes/
│   └── Project_20_Parking_Sensor_Learning_Notes.md
│
├── code/
│   └── parking_sensor.ino
│
└── images/
    └── circuit-diagram.png
```

---

# ✅ Completion Checklist

```text
☐ Arduino Uno connected
☐ HC-SR04 connected
☐ Green LED connected through 220 Ω
☐ Yellow LED connected through 220 Ω
☐ Red LED connected through 220 Ω
☐ Active buzzer connected
☐ Common GND verified
☐ Program uploaded
☐ Distance readings tested
☐ Safe zone tested
☐ Caution zone tested
☐ Warning zone tested
☐ Buzzer tested
☐ Troubleshooting completed
```

---

## ❤️ Final Takeaway

This project takes the ultrasonic sensor from **measurement** to **decision-making**.

```text
        🌍 REAL WORLD
             │
             ▼
       📡 HC-SR04
             │
             ▼
       ⏱️ Measure Time
             │
             ▼
       📏 Calculate Distance
             │
             ▼
       🧠 Make a Decision
             │
        ┌────┼────┐
        ▼    ▼    ▼
       🟢   🟡   🔴
       SAFE CAUTION WARNING
                   │
                   ▼
                 🔊
```

### **Measure → Interpret → Decide → Respond**

That is the core pattern behind countless sensor-based embedded systems.

---


