# Project 22 — Automatic Door Wiring

> **Project Type:** Arduino + Ultrasonic Sensor + Servo Motor  
> **Platform:** Arduino Uno  
> **Core Concept:** Distance Detection → Decision → Servo Actuation

---

## 1. Project Overview

This project builds a **miniature automatic door** using an Arduino Uno, an HC-SR04 ultrasonic sensor, and an SG90 servo motor.

The ultrasonic sensor detects when a person or object approaches the doorway. The Arduino measures the distance and decides whether the door should open.

```text
Person / Object
      │
      ▼
┌───────────────┐
│    HC-SR04    │
│ Distance      │
│ Sensor        │
└───────┬───────┘
        │
        │ Distance
        ▼
┌───────────────┐
│  Arduino Uno  │
│               │
│ Decision      │
└───────┬───────┘
        │
        │ Servo command
        ▼
┌───────────────┐
│   SG90 Servo  │
└───────┬───────┘
        │
        ▼
    Door OPEN
```

---

# 2. Components Required

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main controller |
| HC-SR04 ultrasonic sensor | 1 | Detects approaching objects |
| SG90 servo motor | 1 | Opens and closes the model door |
| Breadboard | 1 | Prototyping connections |
| Jumper wires | As required | Electrical connections |
| USB cable | 1 | Programming and power during development |

---

# 3. Arduino Uno Pin Mapping

| Component | Pin / Terminal | Arduino Uno |
|---|---|---|
| HC-SR04 | VCC | 5V |
| HC-SR04 | TRIG | D8 |
| HC-SR04 | ECHO | D9 |
| HC-SR04 | GND | GND |
| SG90 Servo | Signal | D10 |
| SG90 Servo | VCC | 5V* |
| SG90 Servo | GND | GND* |

> **Power note:** For a small classroom prototype, the SG90 may be powered from the Arduino 5V supply depending on the mechanical load and power arrangement. If the Arduino resets, the servo jitters, or movement is unreliable, use a suitable external 5V supply for the servo and connect the grounds together.

---

# 4. Complete Wiring Summary

```text
                    ARDUINO UNO
                 ┌───────────────┐
                 │               │
HC-SR04 VCC ─────┤ 5V            │
HC-SR04 GND ─────┤ GND           │
HC-SR04 TRIG ────┤ D8            │
HC-SR04 ECHO ────┤ D9            │
Servo Signal ────┤ D10           │
                 │               │
                 └───────────────┘
                      │
                      │
                  SG90 SERVO
                ┌─────────────┐
                │ Signal → D10│
                │ VCC    → 5V │
                │ GND    → GND│
                └─────────────┘
```

---

# 5. HC-SR04 Wiring

The HC-SR04 has four main pins:

```text
┌─────────────────────┐
│      HC-SR04        │
│                     │
│ VCC  TRIG  ECHO GND │
└─────────────────────┘
```

Connect it as follows:

```text
HC-SR04 VCC   → Arduino 5V
HC-SR04 TRIG  → Arduino D8
HC-SR04 ECHO  → Arduino D9
HC-SR04 GND   → Arduino GND
```

### Connection Table

| HC-SR04 Pin | Connect To | Function |
|---|---|---|
| VCC | Arduino 5V | Sensor power |
| TRIG | D8 | Trigger pulse |
| ECHO | D9 | Echo pulse |
| GND | Arduino GND | Ground/reference |

---

# 6. How the HC-SR04 Is Positioned

Point the front of the HC-SR04 toward the area from which the person/object approaches.

```text
                    DOORWAY

Person
  │
  │ approaches
  ▼
  🚶
  │
  │     Distance
  │◄──────────────►
  │
  ▼
┌──────────────┐
│   HC-SR04    │
│   ◉      ◉   │
└──────────────┘
       │
       ▼
    Arduino
```

For a classroom model, mount the sensor so its ultrasonic beams point toward the expected detection area.

Avoid placing obstacles directly in front of the sensor unless they are intended to be detected.

---

# 7. HC-SR04 Signal Flow

The sensor operates using a trigger and echo process:

```text
Arduino
   │
   │ Trigger pulse
   ▼
HC-SR04
   │
   │ Ultrasonic pulse
   ▼
Object / Person
   │
   │ Reflection
   ▼
HC-SR04
   │
   │ Echo duration
   ▼
Arduino
   │
   ▼
Distance calculation
```

The Arduino can then compare the measured distance against a threshold such as:

```text
30 cm
```

Example logic:

```text
Distance < 30 cm
       │
       ▼
Person/object detected
       │
       ▼
Open door
```

---

# 8. Servo Wiring

The SG90 is a three-wire servo.

Its connections are:

```text
Servo Signal → Arduino D10
Servo VCC    → 5V
Servo GND    → GND
```

### Servo Connection Table

| Servo Connection | Arduino / Supply | Purpose |
|---|---|---|
| Signal | D10 | Position-control signal |
| VCC | 5V or suitable external 5V | Servo power |
| GND | GND | Electrical reference |

> **Important:** SG90 wire colors are not guaranteed to be identical across every manufacturer. Verify the servo's signal, VCC, and GND connections from its documentation or markings.

---

# 9. Servo Movement

The servo converts the Arduino's position command into mechanical door movement.

For example:

```text
0°   → Door CLOSED
90°  → Door OPEN
```

The actual angles should be adjusted according to the physical model.

```text
             DOOR

CLOSED                    OPEN
   │                        │
   ▼                        ▼

┌───────┐                ┌──
│       │                │
│ DOOR  │                │
│       │                │
└───────┘                └────────
   ▲                        ▲
   │                        │
Servo 0°                  Servo 90°
```

Do not force the servo beyond the mechanical limits of the model.

---

# 10. Complete Physical Arrangement

A simple classroom arrangement can look like:

```text
                  PERSON
                    │
                    ▼
                 ┌─────┐
                 │ 🚶  │
                 └──┬──┘
                    │
              Detection Zone
                    │
                    ▼
             ┌─────────────┐
             │   HC-SR04   │
             └──────┬──────┘
                    │
                    │ D8 / D9
                    ▼
             ┌─────────────┐
             │  ARDUINO    │
             │     UNO     │
             └──────┬──────┘
                    │ D10
                    ▼
             ┌─────────────┐
             │ SG90 SERVO  │
             └──────┬──────┘
                    │
                    ▼
                MODEL DOOR
```

---

# 11. Detection-to-Action Flow

The intended operation is:

```text
        Object detected
              │
              ▼
       Measure distance
              │
              ▼
      Distance < 30 cm?
          │          │
         NO         YES
          │          │
          ▼          ▼
       Keep       Open door
       closed         │
                      ▼
                Keep door open
                      │
                      ▼
             Object moves away?
                      │
                 ┌────┴────┐
                NO        YES
                 │          │
                 ▼          ▼
              Keep       Start/finish
              open       close timing
                            │
                            ▼
                       Close door
```

---

# 12. Door Closing Behavior

The door should not simply close immediately after one sensor reading becomes larger than the threshold.

A better design is:

```text
Object detected
      ↓
Open door
      ↓
Monitor distance
      ↓
Object still present?
   │            │
  YES           NO
   │            │
   ▼            ▼
Keep open    Begin close timer
                │
                ▼
        Timer expired?
           │       │
          NO      YES
           │       │
           └──┐    ▼
              │ Close door
              │
              └──────────► Continue monitoring
```

This reduces unwanted rapid open/close behavior.

---

# 13. Detection Threshold

A typical classroom threshold can be:

```text
30 cm
```

Example:

```text
Distance = 45 cm
      ↓
No detection
      ↓
Door remains closed
```

But:

```text
Distance = 20 cm
      ↓
Object detected
      ↓
Door opens
```

The threshold can be changed in software.

For example:

```cpp
const int DETECTION_DISTANCE = 30;
```

---

# 14. Wiring Checklist

Before powering the circuit, verify every connection.

### HC-SR04

- [ ] VCC → 5V
- [ ] GND → GND
- [ ] TRIG → D8
- [ ] ECHO → D9

### Servo

- [ ] Signal → D10
- [ ] VCC → 5V or suitable external 5V
- [ ] GND → GND
- [ ] External supply ground connected to Arduino GND if external power is used

### Mechanical

- [ ] HC-SR04 faces the detection area
- [ ] Servo is securely mounted
- [ ] Servo horn is firmly attached
- [ ] Door moves freely
- [ ] Servo does not hit a hard mechanical stop

---

# 15. Servo Power Considerations

A servo is a motorized load and can require significantly more current than a digital LED.

Possible symptoms of inadequate power include:

```text
Servo starts moving
       ↓
Current demand increases
       ↓
Supply voltage drops
       ↓
Arduino resets / servo jitters
```

If this happens, use an appropriate external 5V supply.

### External Servo Supply

```text
             External 5V Supply
                 ┌─────────┐
                 │         │
5V ──────────────┤         │
GND ─────────────┤         │
                 └────┬────┘
                      │
              ┌───────┴───────┐
              ▼               ▼
          Servo VCC       Servo GND
                              │
                              │
                         Arduino GND
                              │
                              ▼
                         Common Ground

Arduino D10 ─────────────► Servo Signal
```

### Critical Rule

When an external supply is used:

```text
External GND
     │
     ├──── Servo GND
     │
     └──── Arduino GND
```

The Arduino and servo supply should share a common ground so the control signal has the correct reference.

---

# 16. Safety

This project is intended for a **small classroom-scale model**.

Do not connect the Arduino directly to:

- Full-size doors
- Mains-powered motors
- High-current actuators
- Industrial mechanisms
- Heavy mechanical loads

A real automatic door requires appropriate:

- Motor drivers
- Relays/contactors where applicable
- Power supplies
- Limit switches
- Safety sensors
- Emergency-stop systems
- Mechanical protection
- Controller safety logic

For this project:

```text
Arduino
   ↓
Small servo
   ↓
Lightweight model door
```

---

# 17. Testing Procedure

### Test 1 — Sensor

Place an object in front of the HC-SR04.

Verify that the Arduino can detect a changing distance.

```text
Object far
   ↓
Large distance

Object near
   ↓
Small distance
```

### Test 2 — Servo

Test the servo independently.

Verify:

```text
Closed angle → Door closed
Open angle   → Door open
```

### Test 3 — Automatic operation

Approach the sensor.

Expected:

```text
Approach
   ↓
Distance < threshold
   ↓
Arduino detects object
   ↓
Servo opens door
```

### Test 4 — Departure

Move the object away.

Expected:

```text
Object leaves
   ↓
Distance increases
   ↓
Close condition becomes valid
   ↓
Servo closes door
```

---

# 18. Troubleshooting

| Problem | Possible Cause | Check |
|---|---|---|
| HC-SR04 gives no useful reading | Incorrect wiring | Check VCC, GND, TRIG, ECHO |
| Distance behaves randomly | Poor wiring or unsuitable target | Secure connections and test with a suitable flat object |
| Servo does not move | Signal/power problem | Check D10, VCC, GND |
| Arduino resets | Servo power demand | Use suitable external 5V supply |
| Servo jitters | Weak/noisy supply or mechanical load | Improve power and mounting |
| Door opens immediately | Detection threshold too large or sensor sees an object | Check sensor placement |
| Door never opens | Threshold too small or sensor wiring/code problem | Test distance readings |
| Door rapidly opens/closes | No hysteresis/timer/state logic | Add stable close conditions |
| Door movement is too large | Servo angle too high | Reduce open/closed angles |

---

# 19. Final Circuit Concept

```text
                       AUTOMATIC DOOR

                   ┌───────────────┐
                   │    PERSON     │
                   └───────┬───────┘
                           │
                           ▼
                   ┌───────────────┐
                   │    HC-SR04    │
                   │  D8 / D9      │
                   └───────┬───────┘
                           │
                       Distance
                           │
                           ▼
                   ┌───────────────┐
                   │  ARDUINO UNO  │
                   │               │
                   │  Decision     │
                   │  Timing       │
                   │  State        │
                   └───────┬───────┘
                           │
                         D10
                           │
                           ▼
                   ┌───────────────┐
                   │   SG90 SERVO  │
                   └───────┬───────┘
                           │
                           ▼
                     MODEL DOOR
```

---

# 20. Quick Reference

### Sensor

```text
VCC  → 5V
GND  → GND
TRIG → D8
ECHO → D9
```

### Servo

```text
Signal → D10
VCC    → 5V / suitable external 5V
GND    → GND
```

### Typical detection threshold

```text
30 cm
```

### Concept

```text
Distance
   ↓
Decision
   ↓
Servo
   ↓
Door
```

### Safety rule

```text
Small Arduino servo
       +
Lightweight model
       =
Classroom prototype
```

Never treat this wiring as a design for a full-size automatic door.

---

# 21. Student Wiring Verification

Before connecting USB power, trace each wire from one end to the other.

```text
HC-SR04 TRIG ─────────────► D8
HC-SR04 ECHO ─────────────► D9
HC-SR04 VCC  ─────────────► 5V
HC-SR04 GND  ─────────────► GND

Servo Signal ─────────────► D10
Servo VCC ────────────────► 5V / external 5V
Servo GND ────────────────► GND
```

### Final check

```text
                 ┌──────────────┐
                 │  ALL WIRES   │
                 │    CHECKED?  │
                 └──────┬───────┘
                        │
                  ┌─────┴─────┐
                 NO           YES
                  │             │
                  ▼             ▼
              Recheck       Power ON
                               │
                               ▼
                           Test sensor
                               │
                               ▼
                           Test servo
                               │
                               ▼
                         Test complete
                         automatic door
```

---

# 22. Key Wiring Takeaways

1. The **HC-SR04** is the input/sensing device.
2. D8 provides the trigger signal.
3. D9 receives the echo signal.
4. The Arduino processes the measured distance.
5. D10 sends the servo control signal.
6. The servo physically moves the model door.
7. Servo power must be adequate for reliable operation.
8. External servo power requires a common ground with the Arduino.
9. The sensor should face the intended detection zone.
10. The model door must move freely without overloading the servo.

> **Core wiring concept:**
>
> ```text
> SENSOR → ARDUINO → SERVO → DOOR
> ```
