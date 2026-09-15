# Project 19 — Ultrasonic Distance Meter · Learning Notes

## 1. The Big Idea

This project measures **distance using sound**.

Unlike an LDR or a temperature sensor, the Arduino does not receive a direct value such as “25 cm” from the HC-SR04.

Instead, the system:

1. Sends an ultrasonic pulse.
2. Waits for the reflected sound.
3. Measures the travel time.
4. Applies a mathematical model.
5. Converts the time into an estimated distance.

```text
              ULTRASONIC DISTANCE MEASUREMENT

Trigger
   │
   ▼
Send ultrasonic pulse
   │
   ▼
Sound travels to object
   │
   ▼
Reflection returns
   │
   ▼
Wait for ECHO
   │
   ▼
Measure time
   │
   ▼
Calculate distance
   │
   ▼
Display result
```

### The core engineering pattern

```text
┌─────────────┐
│   Measure   │
└──────┬──────┘
       ↓
┌─────────────┐
│    Model    │
└──────┬──────┘
       ↓
┌─────────────┐
│  Calculate  │
└──────┬──────┘
       ↓
┌─────────────┐
│  Interpret  │
└─────────────┘
```

> **Key idea:** The Arduino is measuring **time**, then using physics and mathematics to estimate **distance**.

---

# 2. What is Ultrasonic Sound?

Sound is produced by vibrations travelling through a medium such as air.

Humans can normally hear frequencies roughly from **20 Hz to 20 kHz**. Sound above this range is called **ultrasound** or **ultrasonic sound**.

```text
Sound frequency

Low frequency                              High frequency
      │                                           │
      ▼                                           ▼
─────── Human hearing range ───────────────────────
                        ~20 Hz          ~20 kHz
                                           │
                                           ▼
                                    Ultrasonic sound
```

The HC-SR04 uses ultrasonic sound at approximately **40 kHz**, which is above normal human hearing.

### Why use ultrasound?

Ultrasonic waves are useful because they can:

- travel through air,
- reflect from objects,
- and provide timing information that can be measured electronically.

This allows the Arduino to estimate how far away an object is.

---

# 3. Understanding the HC-SR04

The HC-SR04 contains two ultrasonic transducers:

```text
             HC-SR04

        ┌─────────────────┐
        │                 │
        │   ◯       ◯     │
        │   TX      RX    │
        │                 │
        └─────────────────┘
              │
              │
        Ultrasonic waves
              │
              ▼
           Object
```

One transducer is used to transmit the ultrasonic signal, while the other detects the returning signal.

The module also contains the electronics required to generate and detect the ultrasonic pulse.

---

# 4. TRIG and ECHO

The two most important control pins are:

```text
TRIG → Arduino tells the sensor to transmit

ECHO → Sensor reports how long the echo took to return
```

### Signal relationship

```text
Arduino                         HC-SR04

D8 ───────────────► TRIG
                    │
                    │ Send ultrasonic burst
                    ▼
                 Object
                    │
                    │ Reflection
                    ▼
D9 ◄────────────── ECHO
```

The Arduino therefore has two jobs:

- **TRIG:** Start the measurement.
- **ECHO:** Measure the result.

---

# 5. Step-by-Step Measurement Process

A single distance measurement happens very quickly.

### Step 1 — Trigger

The Arduino briefly sets the TRIG pin HIGH.

```text
TRIG

LOW  ───────────┐
                │
                │ ~10 µs
                │
HIGH ───────────┘
```

### Step 2 — Ultrasonic Burst

The HC-SR04 transmits a short ultrasonic burst.

```text
HC-SR04
   │
   │ )))))))))))))))))))))))))
   │
   ▼
 Object
```

### Step 3 — Reflection

The ultrasonic wave hits an object and reflects.

```text
Sensor                              Object
  │                                   │
  │ )))))))))))))))))))))))))))))) ►  │
  │                                   │
  │ ◄ ((((((((((((((((((((((((((((((  │
  │                                   │
```

### Step 4 — Echo Pulse

The ECHO pin goes HIGH for the measured round-trip travel time.

```text
ECHO

LOW  ──────────────┐
                   │
                   │
                   │<──── time ────>
                   │
                   └────────────────
                         HIGH
```

### Step 5 — Calculation

The Arduino converts the measured time into distance.

```text
Echo duration
      ↓
Speed of sound
      ↓
Round-trip distance
      ↓
Divide by 2
      ↓
Distance to object
```

---

# 6. Time of Flight

The fundamental physics relationship is:

```text
Distance = Speed × Time
```

This is commonly called **time of flight**.

The system determines distance by measuring how long a sound wave takes to travel.

```text
                    TIME OF FLIGHT

Sensor ───────────────────────────► Object
       Ultrasonic wave travels

Sensor ◄─────────────────────────── Object
       Reflected wave returns

             ↑
             │
       Total travel time
```

But there is an important detail.

The measured time is **not** the time for the sound to travel only from the sensor to the object.

It is:

```text
Sensor → Object → Sensor
```

Therefore the measured path is twice the actual distance.

---

# 7. Why Divide by Two?

Suppose an object is 50 cm away.

The sound travels:

```text
50 cm → from sensor to object

50 cm → from object back to sensor

Total = 100 cm
```

So the sensor measures the time required to travel **100 cm**, while we want the one-way distance of **50 cm**.

Therefore:

```text
                Speed × Time
Distance = ─────────────────────
                       2
```

Or:

```text
Distance = Speed × Time ÷ 2
```

### Visual explanation

```text
              Actual distance
           ◄──────────────────►

Sensor                         Object
  ●─────────────────────────────●
   ───────────►
     outgoing

   ◄───────────
      return

Measured path = outgoing + return
              = 2 × actual distance
```

> **Common student mistake:** Forgetting the `/ 2` produces a distance approximately twice the actual distance.

---

# 8. Speed of Sound

The speed of sound in air is approximately:

```text
343 m/s
```

at around room temperature.

For Arduino calculations, this can be expressed approximately as:

```text
0.0343 cm/µs
```

Therefore:

```text
Distance (cm)
=
Echo time (µs) × 0.0343
────────────────────────
            2
```

This can also be written approximately as:

```text
Distance (cm) ≈ Echo time (µs) ÷ 58
```

### Why is it an approximation?

The speed of sound changes with environmental conditions, particularly temperature.

Therefore, the HC-SR04 provides a practical distance estimate rather than a precision laboratory measurement.

---

# 9. Understanding `pulseIn()`

The Arduino program uses:

```cpp
pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT);
```

`pulseIn()` measures the duration of a digital pulse.

In this project, it measures:

> **How long the ECHO pin remains HIGH.**

```text
ECHO

       ┌─────────────────────┐
_______│                     │_______
       │<------ duration ---->│
       └─────────────────────┘
                 HIGH
```

The returned value is measured in **microseconds (µs)**.

### Example

Suppose:

```text
Echo time = 1160 µs
```

Then approximately:

```text
Distance ≈ 1160 ÷ 58

Distance ≈ 20 cm
```

So the Arduino converts a timing measurement into a physical distance.

---

# 10. Why Use a Timeout?

The program defines:

```cpp
const unsigned long ECHO_TIMEOUT = 30000UL;
```

This represents a maximum waiting period for the echo.

Without a timeout, software could potentially wait indefinitely if the expected external event never occurs.

```text
                 Start measurement
                        │
                        ▼
                  Wait for ECHO
                        │
             ┌──────────┴──────────┐
             │                     │
        Echo received          No echo
             │                     │
             ▼                     ▼
       Calculate distance       Timeout
                                   │
                                   ▼
                            Handle no reading
```

### Engineering lesson

A timeout is a general software engineering technique.

Whenever a program waits for something outside its direct control—such as:

- a sensor response,
- network response,
- button event,
- serial data,
- or hardware signal—

a timeout can prevent the program from becoming stuck indefinitely.

---

# 11. Understanding the Complete System

The project combines three layers:

```text
┌──────────────────────────────────────┐
│          PHYSICAL WORLD              │
│                                      │
│       Object + Sound waves           │
└──────────────────┬───────────────────┘
                   ↓
┌──────────────────────────────────────┐
│             SENSOR                   │
│                                      │
│   Converts echo timing into signal   │
└──────────────────┬───────────────────┘
                   ↓
┌──────────────────────────────────────┐
│             ARDUINO                  │
│                                      │
│   Measures time and performs math    │
└──────────────────┬───────────────────┘
                   ↓
┌──────────────────────────────────────┐
│             OUTPUT                   │
│                                      │
│       Distance displayed to user     │
└──────────────────────────────────────┘
```

This is a useful example of how embedded systems connect the physical world with software.

---

# 12. Experiment 1 — Change the Target

Test different objects:

- Book
- Cardboard
- Wall
- Hand
- Box

Record the measurements.

| Target | Distance | Reading | Stability |
|---|---:|---:|---|
| Book | | | |
| Cardboard | | | |
| Wall | | | |
| Hand | | | |
| Box | | | |

### Think about it

Which surfaces produce the most stable measurements?

Why might a large, hard, flat surface be easier to measure than a soft or irregular surface?

---

# 13. Experiment 2 — Change the Distance

Choose a fixed target and measure several distances.

```text
10 cm
20 cm
30 cm
50 cm
100 cm
```

Record your results:

| Actual Distance | Measured Distance | Difference |
|---:|---:|---:|
| 10 cm | | |
| 20 cm | | |
| 30 cm | | |
| 50 cm | | |
| 100 cm | | |

### Observation

As the object moves farther away:

```text
More distance
     ↓
Longer sound travel
     ↓
Longer ECHO pulse
     ↓
Larger calculated distance
```

---

# 14. Experiment 3 — Calculate Measurement Error

Real sensors are not perfectly accurate.

For each measurement, record:

```text
Actual distance
Measured distance
Difference
```

Calculate:

```text
Error = Measured − Actual
```

For example:

```text
Actual     = 30 cm
Measured   = 31 cm

Error = 31 − 30
      = +1 cm
```

If the sensor reports 29 cm:

```text
Error = 29 − 30
      = −1 cm
```

### Optional percentage error

You can also calculate:

```text
Percentage Error
=
|Measured − Actual|
──────────────────── × 100
       Actual
```

This introduces an important engineering concept:

> A sensor reading is an **estimate with uncertainty**, not necessarily an exact value.

---

# 15. Experiment 4 — Add an LED

Extend the project by adding an LED.

Requirement:

```text
Distance < 20 cm
       ↓
     LED ON
```

System behavior:

```text
Object far away
       │
       ▼
 Distance ≥ 20 cm
       │
       ▼
    LED OFF


Object close
       │
       ▼
 Distance < 20 cm
       │
       ▼
     LED ON
```

This turns the distance meter into a simple **proximity detector**.

---

# 16. Challenge 1 — Three-Level Proximity Indicator

Create three distance states:

```text
┌──────────────────────────────┐
│ Distance > 50 cm             │
│          ↓                   │
│          SAFE                │
├──────────────────────────────┤
│ Distance 20–50 cm             │
│          ↓                   │
│        CAUTION               │
├──────────────────────────────┤
│ Distance < 20 cm              │
│          ↓                   │
│        WARNING               │
└──────────────────────────────┘
```

Use different LEDs for each state.

### Suggested logic

```text
Read distance
     │
     ▼
Distance > 50?
   │       │
  YES      NO
   │       │
 SAFE   Distance > 20?
           │      │
          YES     NO
           │       │
        CAUTION  WARNING
```

The important part is not copying a circuit, but deciding how the thresholds and outputs should behave.

---

# 17. Challenge 2 — Parking Sensor

Design a simple parking-assistance system using:

- HC-SR04
- LEDs
- Buzzer

### Required behavior

```text
                 OBJECT APPROACHES

Far away
    │
    ▼
Slow indication
    │
    ▼
Getting closer
    │
    ▼
Faster indication
    │
    ▼
Very close
    │
    ▼
Continuous warning
```

### Conceptual behavior

```text
Distance
   │
100 cm ─────── Slow beep
   │
 50 cm ─────── Faster beep
   │
 20 cm ─────── Very fast beep
   │
 10 cm ─────── Continuous warning
   │
   └────────────────────────────►
```

### Design task

Do not simply copy Project 20.

Decide:

- What distance thresholds should be used?
- How should the beep interval change?
- When should the LED state change?
- What should happen if no echo is received?
- What should happen when the object moves away again?

This turns the project from a wiring exercise into a **control-system design problem**.

---

# 18. Why Readings Can Become Unstable

Ultrasonic sensing depends on reflected sound.

Not every object reflects sound in exactly the same way.

### Potential causes

```text
                Unstable reading
                       │
        ┌──────────────┼──────────────┐
        ↓              ↓              ↓
    Angled object   Soft surface   Very close
        │              │              │
        ↓              ↓              ↓
   Reflection       Weak echo       Blind zone
    elsewhere
```

Other causes include:

- irregular surfaces,
- object edges,
- multiple reflections,
- sensor movement,
- electrical noise,
- unsuitable measurement angles.

### Better measurement setup

```text
        HC-SR04
           │
           │
           │
           ▼
      ┌─────────┐
      │  FLAT   │
      │ TARGET  │
      └─────────┘

Sensor should face target as directly as possible.
```

---

# 19. Real-World Connection

Ultrasonic distance measurement is used in many practical systems.

| Application | What the sensor does |
|---|---|
| Parking assistance | Detects distance to nearby vehicles/objects |
| Robotics | Detects obstacles |
| Tank-level estimation | Estimates the distance to a liquid surface |
| Object detection | Detects whether an object is present |
| Industrial sensing | Measures positions and distances |
| Autonomous systems | Provides environmental information |

### Example: Robot obstacle detection

```text
Robot
  │
  │ HC-SR04
  ▼
)))))))))))))))))) ► Obstacle
◄((((((((((((((((
  │
  ▼
Distance calculated
  │
  ▼
Robot decides:
STOP / TURN / MOVE
```

The sensor itself does not decide what the robot should do.

It provides **data**.

The controller interprets that data and makes a decision.

---

# 20. Sensor → Data → Decision

This project introduces a very important embedded-systems architecture:

```text
Physical world
      ↓
     Sensor
      ↓
  Raw signal
      ↓
Measurement
      ↓
Calculation
      ↓
Useful data
      ↓
Decision
      ↓
Actuator / Output
```

For this project:

```text
Object
  ↓
Ultrasonic reflection
  ↓
ECHO timing
  ↓
Microseconds
  ↓
Distance in cm
  ↓
Threshold comparison
  ↓
LED / buzzer / robot action
```

This same pattern appears in much more advanced systems.

---

# 21. Engineering Lesson — Measure → Model → Calculate → Interpret

This project demonstrates a fundamental engineering workflow.

## Measure

The Arduino measures:

```text
ECHO pulse duration
```

## Model

We use the physical model:

```text
Distance = Speed × Time ÷ 2
```

## Calculate

The Arduino performs the required mathematical conversion.

```text
Time → Distance
```

## Interpret

The program can then decide what the measurement means.

```text
Distance < 20 cm
       ↓
Object is close
       ↓
Turn warning LED ON
```

### The complete pattern

```text
┌───────────┐
│  Measure  │
└─────┬─────┘
      ↓
┌───────────┐
│   Model   │
└─────┬─────┘
      ↓
┌───────────┐
│ Calculate │
└─────┬─────┘
      ↓
┌───────────┐
│ Interpret │
└───────────┘
```

---

# 22. Important Concepts to Remember

### Concept 1 — TRIG starts the measurement

```text
TRIG → Start transmission
```

### Concept 2 — ECHO carries timing information

```text
ECHO HIGH duration → Travel time
```

### Concept 3 — Distance is calculated

```text
Distance = Speed × Time ÷ 2
```

### Concept 4 — The time is round-trip time

```text
Sensor → Object → Sensor
```

### Concept 5 — `pulseIn()` measures pulse duration

```cpp
pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT);
```

### Concept 6 — Timeout prevents indefinite waiting

```cpp
const unsigned long ECHO_TIMEOUT = 30000UL;
```

### Concept 7 — Measurements contain error

```text
Measured value ≠ necessarily Actual value
```

---

# 23. Learning Outcome

After completing this project, students should understand:

- How the **HC-SR04** works.
- What **TRIG** and **ECHO** signals do.
- How ultrasonic sound can be used for distance measurement.
- The concept of **time of flight**.
- How `pulseIn()` measures a digital pulse.
- Why the measured round-trip time is divided by **2**.
- How the **speed of sound** is used in the calculation.
- Why a sensor may produce measurement error.
- Why a software **timeout** is important.
- How sensor data can be converted into a useful decision.
- How physical phenomena can become digital data.

---

# 24. Review Questions

### Conceptual Questions

1. What is ultrasonic sound?
2. Why does the HC-SR04 use ultrasonic waves instead of ordinary audible sound?
3. What is the purpose of the TRIG pin?
4. What is the purpose of the ECHO pin?
5. What does `pulseIn()` measure?
6. Why is the measured travel time divided by two?
7. What is meant by time of flight?
8. Why can an angled object produce an unstable reading?
9. Why is a timeout useful in the program?
10. Why can measured distance differ from actual distance?

### Think Like an Engineer

11. What would happen if the ECHO wire were disconnected?
12. What would happen to the ECHO duration if the object moved twice as far away?
13. How could you make a parking sensor beep faster as an object approaches?
14. How could you reduce the effect of noisy readings?
15. How could temperature compensation improve the distance calculation?

---

# 25. Student Checklist

Before considering the project complete:

```text
☐ I can identify the HC-SR04 pins.
☐ I understand TRIG and ECHO.
☐ I understand how the ultrasonic wave travels.
☐ I understand time-of-flight measurement.
☐ I can explain why distance is divided by 2.
☐ I understand what pulseIn() does.
☐ I understand why a timeout is needed.
☐ I can calculate measurement error.
☐ I tested multiple target distances.
☐ I tested different target surfaces.
☐ I can create a distance-based LED condition.
☐ I can explain at least one real-world application.
```

---

# 26. Final Takeaway

The most important lesson from this project is not simply how to connect an HC-SR04.

It is understanding how an embedded system can use **physics + timing + mathematics + programming** to measure something in the physical world.

```text
              PHYSICAL WORLD
                    │
                    ▼
             Ultrasonic wave
                    │
                    ▼
              Echo returns
                    │
                    ▼
             Time measurement
                    │
                    ▼
             Mathematical model
                    │
                    ▼
              Distance value
                    │
                    ▼
               Decision
                    │
                    ▼
              Useful action
```

> **Measure → Model → Calculate → Interpret**

This pattern is one of the foundations of sensor-based embedded systems.
