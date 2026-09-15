# Project 20 — Parking Sensor · Learning Notes

> 🚗 **From measuring distance to making decisions:** In Project 19, the Arduino learned how to measure distance with an HC-SR04. In this project, that measurement becomes a meaningful action using LEDs and a buzzer.

---

# 1. What Are We Building?

We are building a simple **parking/proximity indicator** using:

- Arduino Uno
- HC-SR04 ultrasonic distance sensor
- Green LED
- Yellow LED
- Red LED
- Active buzzer

The system continuously measures the distance between the sensor and an object.

The Arduino then decides whether the object is:

- 🟢 **SAFE**
- 🟡 **CAUTION**
- 🔴 **STOP**

and communicates that decision through LEDs and a buzzer.

```text
                    OBJECT
                       │
                       │
               Ultrasonic waves
                       │
                       ▼
                ┌─────────────┐
                │   HC-SR04   │
                │   SENSOR    │
                └──────┬──────┘
                       │
                  Echo timing
                       │
                       ▼
                ┌─────────────┐
                │   ARDUINO   │
                │     UNO     │
                └──────┬──────┘
                       │
                Calculate distance
                       │
                       ▼
                Compare thresholds
                       │
            ┌──────────┼──────────┐
            ▼          ▼          ▼
          🟢 LED     🟡 LED     🔴 LED
           SAFE      CAUTION      STOP
                                  │
                                  ▼
                                🔊 Buzzer
```

### The key transition from Project 19

```text
PROJECT 19

Sensor
   ↓
Measure
   ↓
Distance
```

becomes:

```text
PROJECT 20

Sensor
   ↓
Measure
   ↓
Distance
   ↓
Compare
   ↓
Decide
   ↓
Act
```

This is a major step toward understanding how real embedded systems work.

---

# 2. Learning Model — Sense → Measure → Decide → Act

The entire project can be understood through four stages:

```text
┌───────────┐
│   SENSE   │
│  HC-SR04  │
└─────┬─────┘
      ↓
┌───────────┐
│  MEASURE  │
│ Distance  │
└─────┬─────┘
      ↓
┌───────────┐
│  DECIDE   │
│ Threshold │
└─────┬─────┘
      ↓
┌───────────┐
│    ACT    │
│ LED/Buzzer│
└───────────┘
```

## 2.1 Sense

The HC-SR04 interacts with the physical world.

It sends an ultrasonic pulse and detects the returning echo.

```text
Physical world
      │
      ▼
   Object
      │
      ▼
Ultrasonic reflection
      │
      ▼
   HC-SR04
```

## 2.2 Measure

The Arduino measures the duration of the ECHO pulse and converts that time into distance.

```text
Echo duration
      ↓
Speed of sound
      ↓
Distance calculation
      ↓
Distance in cm
```

## 2.3 Decide

The measured distance is compared with predefined thresholds.

```text
Distance
   │
   ▼
┌───────────────────┐
│ Compare thresholds│
└─────────┬─────────┘
          │
     ┌────┼────┐
     ▼    ▼    ▼
   SAFE CAUTION STOP
```

## 2.4 Act

The Arduino controls the outputs according to the selected zone.

```text
SAFE
  ↓
🟢 Green LED

CAUTION
  ↓
🟡 Yellow LED
  ↓
🔊 Slow beep

STOP
  ↓
🔴 Red LED
  ↓
🔊 Fast beep
```

> **Core pattern:** `Sense → Measure → Decide → Act`

This pattern appears throughout robotics, automation, IoT, and industrial control systems.

---

# 3. Distance Zones

The project divides the measured distance into three simple zones.

| Distance | Status | LED | Buzzer |
|---:|---|---|---|
| **> 50 cm** | 🟢 SAFE | Green | OFF |
| **20–50 cm** | 🟡 CAUTION | Yellow | Slow beep |
| **≤ 20 cm** | 🔴 STOP | Red | Fast beep |

These thresholds are intentionally simple for learning.

A real parking system would require:

- calibration,
- better sensor validation,
- filtering,
- environmental testing,
- multiple sensors or more sophisticated sensing,
- and carefully designed safety logic.

### Distance-zone visualization

```text
FAR                                                     CLOSE
│                                                         │
▼                                                         ▼

─────────────────────────────────────────────────────────────
        🟢 SAFE           🟡 CAUTION          🔴 STOP
         >50 cm            20–50 cm             ≤20 cm
─────────────────────────────────────────────────────────────
                              │
                              │
                         Object approaches
                              ▼
```

### Example

Suppose the sensor measures:

```text
Distance = 15 cm
```

The Arduino evaluates:

```text
15 cm ≤ 20 cm
       ↓
STOP
       ↓
🔴 Red LED
       +
🔊 Fast buzzer
```

The important point is that **15 cm is not itself an action**.

The program transforms the measurement into a decision.

---

# 4. How the HC-SR04 Works

The HC-SR04 uses ultrasonic sound to estimate distance.

The basic process is:

```text
Arduino
   │
   │ Trigger pulse
   ▼
HC-SR04
   │
   │ Ultrasonic transmission
   ▼
Object
   │
   │ Reflection
   ▼
HC-SR04
   │
   │ ECHO pulse
   ▼
Arduino
   │
   ▼
Distance calculation
```

## Step-by-step

### Step 1 — Trigger the sensor

The Arduino sends a short pulse to the TRIG pin.

```text
TRIG

LOW  ──────────┐
               │
               │ ~10 µs
               │
HIGH ──────────┘
```

### Step 2 — Ultrasonic wave is transmitted

```text
HC-SR04
   │
   │ )))))))))))))))))))))))))) ►
   │
   ▼
 Object
```

### Step 3 — Wave reflects

```text
Sensor                              Object
  │                                   │
  │ )))))))))))))))))))))))))))))) ► │
  │                                   │
  │ ◄ ((((((((((((((((((((((((((((( │
  │                                   │
```

### Step 4 — Arduino measures ECHO

The ECHO pin remains HIGH for the duration corresponding to the sound's round trip.

```text
ECHO

LOW  ──────────────┐
                   │
                   │<──── measured time ────>
                   │
                   └─────────────────────────
                           HIGH
```

---

# 5. Time of Flight

The project depends on the concept of **time of flight**.

The basic relationship is:

```text
Distance = Speed × Time
```

However, the HC-SR04 measures a **round trip**:

```text
Sensor → Object → Sensor
```

Therefore:

```text
                   Speed × Time
Distance = ─────────────────────────
                         2
```

or:

```text
Distance = Speed × Time ÷ 2
```

The program uses approximately:

```text
0.0343 cm/µs
```

for the speed of sound under typical room-temperature conditions.

### Why divide by two?

```text
              Actual distance
        ◄────────────────────────►

Sensor ●──────────────────────────● Object
       ───────────────────────────►
                 outgoing

       ◄───────────────────────────
                  return

Measured path = 2 × actual distance
```

> The Arduino is measuring the total outgoing + returning path, so division by two gives the approximate one-way distance.

---

# 6. From Distance to Parking Decision

Once the distance has been calculated, the program converts it into a zone.

```text
               Measured distance
                       │
                       ▼
                ┌─────────────┐
                │ > 50 cm ?   │
                └──────┬──────┘
                       │
                 YES   │
                       ▼
                   🟢 SAFE
                       │
                       │ NO
                       ▼
                ┌─────────────┐
                │ > 20 cm ?   │
                └──────┬──────┘
                       │
                 YES   │
                       ▼
                 🟡 CAUTION
                       │
                       │ NO
                       ▼
                  🔴 STOP
```

This is called **threshold-based decision logic**.

The sensor produces a continuous measurement, while the program converts it into a small number of useful states.

---

# 7. Why Use Thresholds?

A sensor produces data.

A controller needs to determine what that data means.

For example:

```text
Distance = 75 cm
       ↓
Greater than 50 cm
       ↓
SAFE
```

Another example:

```text
Distance = 35 cm
       ↓
Between 20 and 50 cm
       ↓
CAUTION
```

And:

```text
Distance = 12 cm
       ↓
Less than or equal to 20 cm
       ↓
STOP
```

### Continuous measurement vs. discrete decision

```text
Sensor measurement

75.2 cm
61.8 cm
48.7 cm
37.4 cm
25.1 cm
18.6 cm
11.2 cm
   │
   ▼
Threshold logic
   │
   ├── SAFE
   ├── CAUTION
   └── STOP
```

This technique is extremely common in embedded systems.

---

# 8. Understanding `digitalWrite()`

`digitalWrite()` is used to control digital outputs.

For example:

```cpp
digitalWrite(GREEN_LED, HIGH);
```

turns the green LED output ON.

And:

```cpp
digitalWrite(GREEN_LED, LOW);
```

turns it OFF.

The same basic mechanism can control the buzzer:

```cpp
digitalWrite(BUZZER_PIN, HIGH);
```

### Output control model

```text
Arduino decision
      │
      ▼
digitalWrite()
      │
 ┌────┼────┐
 ▼    ▼    ▼
LED  LED  Buzzer
```

For this project, `digitalWrite()` is therefore the bridge between **software decisions** and **physical outputs**.

---

# 9. Understanding `pulseIn()`

The Arduino needs to know how long the ECHO signal remains HIGH.

That is what `pulseIn()` measures.

```cpp
pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT);
```

Conceptually:

```text
ECHO

       ┌──────────────────────┐
_______│                      │_______
       │<------ duration ---->│
       └──────────────────────┘
                  HIGH
```

The returned duration is measured in **microseconds**.

The program then uses this value in the distance calculation.

```text
ECHO HIGH duration
        ↓
   pulseIn()
        ↓
 Time in µs
        ↓
Distance calculation
        ↓
Distance in cm
```

---

# 10. Understanding `millis()`

The buzzer needs to produce different patterns:

```text
CAUTION → slow beep
STOP    → fast beep
```

A simple approach would be to use:

```cpp
delay(700);
```

or:

```cpp
delay(180);
```

But `delay()` blocks the program.

## What does blocking mean?

Suppose the program executes:

```cpp
delay(700);
```

For approximately 700 milliseconds, the program waits before continuing with the next instructions.

```text
Measure
  ↓
delay(700)
  ↓
Continue
```

During that period, the main loop cannot progress normally through its other tasks.

That is undesirable in a responsive sensor system.

---

# 11. Non-Blocking Timing with `millis()`

`millis()` provides the number of milliseconds that have elapsed since the Arduino started running.

The program can use elapsed time to decide when to change the buzzer state.

```text
Start
  │
  ▼
millis() = current time
  │
  ▼
Compare with previous buzzer time
  │
  ▼
Enough time passed?
  │
 ┌┴─────────┐
 │          │
NO         YES
 │          │
 ▼          ▼
Continue   Toggle buzzer
              │
              ▼
        Save current time
```

### Conceptual example

```cpp
if (millis() - lastBeep >= CAUTION_INTERVAL) {
    // Change buzzer state
    lastBeep = millis();
}
```

The important idea is:

```text
Instead of:

WAIT → do nothing → WAIT

we use:

CHECK → WORK → CHECK → WORK
```

This is called **non-blocking timing**.

---

# 12. Why Non-Blocking Timing Matters

A parking sensor should continue monitoring distance while the buzzer is operating.

With blocking delays:

```text
Measure
   ↓
Beep
   ↓
WAIT
   ↓
Measure again
```

With non-blocking timing:

```text
Measure ───────────────┐
   │                   │
   ▼                   ▼
Update zone       Check buzzer timer
   │                   │
   ▼                   ▼
Measure again      Beep if needed
   │                   │
   └──────────┬────────┘
              ▼
            Repeat
```

This makes the system more responsive.

The same concept becomes extremely important when an embedded system must handle several tasks at the same time.

---

# 13. Understanding `enum` and Named Zones

The program uses named states such as:

```text
SAFE
CAUTION
STOP
```

Instead of relying on unexplained numbers.

For example:

```cpp
enum Zone {
    SAFE,
    CAUTION,
    STOP
};
```

This makes the program easier to read.

Compare:

```cpp
if (zone == 2)
```

with:

```cpp
if (zone == STOP)
```

The second version communicates the meaning immediately.

### State representation

```text
             Zone
              │
       ┌──────┼──────┐
       ▼      ▼      ▼
     SAFE   CAUTION  STOP
       │      │       │
       ▼      ▼       ▼
      🟢     🟡      🔴
```

Named states are especially useful as projects become larger and more complex.

---

# 14. Experiments

## Experiment 1 — Change the Safe Distance

The original setting is:

```cpp
const float SAFE_DISTANCE = 50.0;
```

Try:

```cpp
const float SAFE_DISTANCE = 70.0;
```

Now observe when the yellow warning begins.

### Prediction

Before running the experiment, predict:

```text
Original:
SAFE > 50 cm

New:
SAFE > 70 cm
```

The caution zone should begin farther away from the sensor.

Record your observations:

| Safe Distance | Distance where Caution Begins | Observation |
|---:|---:|---|
| 50 cm | | |
| 70 cm | | |

---

# 15. Experiment 2 — Change the Stop Distance

The original setting is:

```cpp
const float STOP_DISTANCE = 20.0;
```

Try:

```cpp
const float STOP_DISTANCE = 10.0;
```

Observe how the red warning zone changes.

```text
Original

20 cm ─────── STOP begins


New

10 cm ─────── STOP begins
```

### Think about it

Which setting gives the driver more warning distance?

Which setting allows the vehicle/object to approach closer before STOP is activated?

---

# 16. Experiment 3 — Change Warning Speed

The buzzer intervals might be defined as:

```cpp
const unsigned long CAUTION_INTERVAL = 700;
const unsigned long STOP_INTERVAL = 180;
```

The interval controls how frequently the buzzer changes state.

### Try different values

```text
CAUTION_INTERVAL = 1000
CAUTION_INTERVAL = 500
CAUTION_INTERVAL = 250
```

Then try:

```text
STOP_INTERVAL = 300
STOP_INTERVAL = 150
STOP_INTERVAL = 80
```

### Observe

```text
Larger interval
      ↓
Slower pattern

Smaller interval
      ↓
Faster pattern
```

This allows you to design the warning behavior instead of simply copying it.

---

# 17. Experiment 4 — Add a Display

Add an LCD or OLED display.

Instead of relying only on LEDs, show information such as:

```text
┌──────────────────────┐
│ Distance: 34.5 cm    │
│ Status: CAUTION      │
└──────────────────────┘
```

The complete system becomes:

```text
HC-SR04
   ↓
Distance
   ↓
Arduino
   │
   ├────► LEDs
   │
   ├────► Buzzer
   │
   └────► LCD/OLED
```

This makes the system easier for a user to understand.

---

# 18. Experiment 5 — Add an Automatic Barrier

Use a servo motor to represent a parking barrier.

For example:

```text
Object far away
      ↓
Barrier remains open


Object approaches
      ↓
System evaluates distance


Object reaches restricted zone
      ↓
Barrier changes position
```

### Conceptual system

```text
        HC-SR04
           │
           ▼
      Distance
           │
           ▼
       Arduino
           │
      ┌────┴────┐
      ▼         ▼
   Decision   Servo
                │
                ▼
             Barrier
```

This introduces the idea of an **actuator**—a device controlled by the Arduino to physically change something.

---

# 19. Troubleshooting — No Echo Detected

If the program reports:

```text
No echo detected
```

check the following:

```text
☐ TRIG wiring
☐ ECHO wiring
☐ Sensor VCC
☐ Sensor GND
☐ Breadboard connections
☐ Jumper wires
☐ Object position
```

### Signal path to check

```text
Arduino D8
   │
   ▼
TRIG
   │
   ▼
HC-SR04
   │
   ▼
Ultrasonic wave
   │
   ▼
Object
   │
   ▼
Reflected wave
   │
   ▼
ECHO
   │
   ▼
Arduino D9
```

A break anywhere in this chain can prevent a useful measurement.

---

# 20. Troubleshooting — Unstable Distance

Possible causes include:

- Object is angled.
- Object surface absorbs or scatters sound.
- Object is too close.
- Sensor is loose.
- Electrical connections are poor.
- Reflections are reaching the receiver in unexpected ways.

### Try a controlled test

Use a large flat object:

```text
        HC-SR04
           │
           │
           │
           ▼
      ┌───────────┐
      │   FLAT    │
      │  OBJECT   │
      └───────────┘
```

Keep the sensor fixed and move the object directly toward and away from it.

This gives a more repeatable experiment.

---

# 21. Troubleshooting — LEDs Do Not Work

Check:

```text
☐ LED polarity
☐ 220 Ω resistor
☐ Correct Arduino pin
☐ Common GND
☐ Breadboard row placement
☐ Program pin definitions
```

### LED polarity

```text
Arduino
   │
   ▼
220 Ω
   │
   ▼
Anode (+)
   │
  LED
   │
Cathode (-)
   │
   ▼
GND
```

If the LED is reversed, it will normally not illuminate.

---

# 22. Troubleshooting — Buzzer Does Not Sound

First verify that the buzzer is an **active buzzer** if the program expects simple HIGH/LOW control.

Check:

```text
☐ Buzzer polarity
☐ Buzzer wiring
☐ Arduino D10
☐ GND connection
☐ Buzzer type
☐ Program logic
```

If the buzzer requires significant current, do not drive it directly from the Arduino GPIO.

Use a suitable transistor or MOSFET driver.

```text
Arduino
   │
   ▼
Driver transistor
   │
   ▼
Higher-current buzzer
```

---

# 23. Challenge — Build a More Realistic Parking Assistant

Now combine everything you have learned.

### Requirements

Your system should:

- Measure distance continuously.
- Show distance on an OLED/LCD.
- Use green, yellow, and red indicators.
- Make the buzzer progressively faster as the object approaches.
- Add a maximum detection distance.
- Add a calibration mode.

### Suggested architecture

```text
                    ┌─────────────┐
                    │   HC-SR04   │
                    └──────┬──────┘
                           │
                           ▼
                    Distance reading
                           │
                           ▼
                    ┌─────────────┐
                    │   Arduino   │
                    │             │
                    │ Measurement │
                    │     ↓       │
                    │  Decision   │
                    └──────┬──────┘
                           │
              ┌────────────┼────────────┐
              ▼            ▼            ▼
          🟢 Green      🟡 Yellow     🔴 Red
                                      │
                                      ▼
                                    🔊 Buzzer

                           +
                           │
                           ▼
                       LCD / OLED
```

### Design questions

Before coding, decide:

1. What should the maximum detection distance be?
2. What distance should trigger CAUTION?
3. What distance should trigger STOP?
4. How should the beep rate change?
5. What should happen if there is no echo?
6. How will calibration work?
7. How will the display report the current state?

This is now a **system-design problem**, not just a wiring exercise.

---

# 24. Engineering Connection

The same fundamental pattern appears in many real systems.

## Parking assistance

```text
Sensor
  ↓
Distance
  ↓
Decision
  ↓
Visual / audible warning
```

## Robot obstacle detection

```text
Ultrasonic sensor
        ↓
Obstacle distance
        ↓
Decision
        ↓
STOP / TURN / MOVE
```

## Automatic doors

```text
Proximity sensor
        ↓
Person detected?
        ↓
Decision
        ↓
Open / Keep closed
```

## Industrial proximity sensing

```text
Sensor
   ↓
Object position
   ↓
Control logic
   ↓
Machine response
```

## Warehouse automation

```text
Object detected
      ↓
Distance / position
      ↓
Controller
      ↓
Robot / conveyor action
```

The application changes, but the underlying architecture remains similar.

---

# 25. The Bigger Embedded-Systems Pattern

This project demonstrates a general architecture:

```text
                 PHYSICAL WORLD
                       │
                       ▼
                  ┌─────────┐
                  │  SENSOR │
                  └────┬────┘
                       │
                       ▼
                  Raw signal
                       │
                       ▼
                  Measurement
                       │
                       ▼
               ┌───────────────┐
               │   PROCESSING  │
               │               │
               │ Calculate     │
               │ Compare       │
               │ Decide        │
               └───────┬───────┘
                       │
                       ▼
                  Control signal
                       │
             ┌─────────┼─────────┐
             ▼         ▼         ▼
           🟢 LED    🟡 LED    🔴 LED
                                 │
                                 ▼
                               🔊 Buzzer
```

This is the basic relationship between:

**Input → Processing → Output**

---

# 26. Engineering Lesson

The most important lesson is not the parking application itself.

The important lesson is:

```text
Sensor measurement
        ↓
Decision logic
        ↓
Actuator response
```

Or more generally:

> **Measure → Interpret → Decide → Respond**

This pattern is foundational to:

- Embedded systems
- Robotics
- IoT
- Automation
- Industrial control
- Smart devices
- Autonomous systems

The Arduino is acting as the decision-making layer between the physical world and the outputs.

---

# 27. Important Concepts to Remember

### 1. HC-SR04

Uses ultrasonic waves to estimate distance.

### 2. TRIG

Starts an ultrasonic measurement.

### 3. ECHO

Provides a pulse whose duration corresponds to the round-trip travel time.

### 4. Time of flight

The time required for the ultrasonic wave to travel to the object and return.

### 5. Distance calculation

```text
Distance = Speed × Time ÷ 2
```

### 6. Thresholds

Convert continuous measurements into useful states.

```text
Distance → SAFE / CAUTION / STOP
```

### 7. `digitalWrite()`

Controls digital outputs such as LEDs and a suitable active buzzer.

### 8. `pulseIn()`

Measures the duration of the ECHO pulse.

### 9. `millis()`

Enables timing without blocking the main program with long delays.

### 10. `enum`

Provides meaningful names for system states.

---

# 28. Learning Outcome

After completing this project, students should be able to:

- Explain how an HC-SR04 measures distance.
- Explain the difference between TRIG and ECHO.
- Explain time-of-flight measurement.
- Calculate approximate distance from echo timing.
- Explain why round-trip time is divided by two.
- Use thresholds to create system states.
- Control multiple digital outputs.
- Explain why `pulseIn()` is used.
- Explain why `millis()` is useful for non-blocking timing.
- Understand the purpose of named states such as `SAFE`, `CAUTION`, and `STOP`.
- Identify common ultrasonic-sensor problems.
- Design a simple sensor-driven control system.
- Connect a sensor measurement to an actuator response.

---

# 29. Review Questions

## Understanding

1. What are the four stages of the project's learning model?
2. What does the HC-SR04 measure directly?
3. Why does the Arduino need to calculate distance?
4. Why is the round-trip time divided by two?
5. What happens when the measured distance is 15 cm?
6. What is the purpose of the SAFE, CAUTION, and STOP states?

## Programming

7. What does `digitalWrite()` do?
8. What does `pulseIn()` measure?
9. Why can `delay()` be problematic in a responsive sensor system?
10. What advantage does `millis()` provide?
11. Why are named states clearer than unexplained numeric values?

## Engineering

12. Why might ultrasonic readings become unstable?
13. Why are thresholds useful?
14. What happens if no echo is received?
15. How could averaging multiple readings improve the system?
16. How could the system be made more reliable for a real vehicle?

---

# 30. Student Experiment Record

Use this table to document your experiments.

| Experiment | Change Made | Expected Result | Actual Result | Conclusion |
|---|---|---|---|---|
| Safe threshold | | | | |
| Stop threshold | | | | |
| Buzzer interval | | | | |
| Target surface | | | | |
| Target distance | | | | |
| Display added | | | | |

Good engineering practice means recording what you **expected**, what actually happened, and what you learned from the difference.

---

# 31. Student Checklist

```text
☐ I understand the Sense → Measure → Decide → Act model.
☐ I can explain how the HC-SR04 works.
☐ I understand TRIG and ECHO.
☐ I understand time of flight.
☐ I understand why the distance calculation divides by 2.
☐ I can explain how thresholds create SAFE/CAUTION/STOP states.
☐ I understand digitalWrite().
☐ I understand pulseIn().
☐ I understand why millis() is useful.
☐ I understand non-blocking timing.
☐ I understand why LEDs need resistors.
☐ I understand the buzzer current limitation.
☐ I tested different distance thresholds.
☐ I tested different buzzer intervals.
☐ I investigated unstable measurements.
☐ I can describe at least two real-world applications.
☐ I can design an improved parking assistant.
```

---

# 32. Final Takeaway

Project 20 takes the idea from Project 19 one step further.

The Arduino is no longer simply asking:

> **“How far away is the object?”**

It is now asking:

> **“What should I do based on how far away the object is?”**

```text
             🌍 PHYSICAL WORLD
                     │
                     ▼
                📡 SENSOR
                     │
                     ▼
              ⏱️ MEASUREMENT
                     │
                     ▼
              📏 DISTANCE
                     │
                     ▼
             🧠 DECISION LOGIC
                     │
          ┌──────────┼──────────┐
          ▼          ▼          ▼
        🟢 SAFE    🟡 CAUTION  🔴 STOP
                                │
                                ▼
                              🔊
                           WARNING
```

### The fundamental pattern

```text
        SENSE
          ↓
       MEASURE
          ↓
       INTERPRET
          ↓
        DECIDE
          ↓
        RESPOND
```

> **This is the heart of sensor-based embedded systems: turning information from the physical world into an intelligent response.**
