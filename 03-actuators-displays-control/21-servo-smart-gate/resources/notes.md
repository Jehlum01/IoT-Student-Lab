# Project 21 — Servo Smart Gate
## Detailed Learning Notes

> **Project Type:** Arduino + Servo Motor + Digital Input  
> **Platform:** Arduino Uno  
> **Difficulty:** Beginner → Intermediate  
> **Core Pattern:** Input → Decision → Actuator → Timed Action

---

# 1. What Are We Building?

In this project, we build a **miniature automatic gate** using an Arduino Uno, a push button, and an SG90 servo motor.

When a user presses the push button:

1. The Arduino detects a new button press.
2. The Arduino commands the servo to rotate to the open position.
3. The gate remains open for **five seconds**.
4. After five seconds, the Arduino commands the servo back to the closed position.
5. The system returns to its waiting state.

The project demonstrates an important embedded-systems pattern:

```text
          INPUT
            │
            ▼
       BUTTON PRESS
            │
            ▼
         DECISION
            │
            ▼
       SERVO MOTOR
            │
            ▼
       GATE OPENS
            │
            ▼
       WAIT 5 SECONDS
            │
            ▼
       GATE CLOSES
            │
            └──────────────► WAIT FOR NEXT PRESS
```

Although the model is simple, the same idea appears in **automatic barriers, parking gates, access-control systems, robotic mechanisms, and industrial machines**.

---

# 2. Learning Objectives

After completing this project, students should be able to:

- Explain what a servo motor does.
- Identify the power, ground, and signal connections of an SG90 servo.
- Control a servo using the Arduino Servo library.
- Read a push button using `INPUT_PULLUP`.
- Understand active-LOW button logic.
- Detect a new button event rather than continuously reacting to a held button.
- Explain switch bounce and debouncing.
- Store system information using a Boolean state variable.
- Use `millis()` for non-blocking timing.
- Build a simple automatic actuator system.
- Troubleshoot servo power and wiring problems.
- Extend the project using sensors and additional outputs.

---

# 3. The Learning Model

The project can be understood using four stages:

```text
┌──────────────┐
│    INPUT     │
│  Push Button │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   DECISION   │
│ Arduino Logic│
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   ACTUATOR   │
│ Servo Motor  │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ TIMED ACTION │
│ 5-sec Open   │
└──────────────┘
```

### The four concepts

| Stage | Project Component | Purpose |
|---|---|---|
| Input | Push button | Requests gate operation |
| Decision | Arduino | Determines what should happen |
| Actuator | SG90 servo | Physically moves the gate |
| Timed action | `millis()` | Determines when the gate should close |

This pattern is reusable in many automation projects.

---

# 4. Project Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| SG90 servo motor | Moves the gate |
| Push button | Provides the opening command |
| Breadboard | Makes prototyping easier |
| Jumper wires | Electrical connections |
| USB cable | Programming and power during testing |

### Main connections

```text
Arduino Uno
│
├── D2 ──────────► Push Button
│
└── D9 ──────────► Servo Signal

5V ──────────────► Servo VCC
GND ─────────────► Servo GND
GND ─────────────► Push Button
```

> **Important:** Servo wire colors can vary between manufacturers. Identify the signal, VCC, and GND wires from the servo documentation or labeling rather than relying only on color.

---

# 5. What Is a Servo Motor?

A **servo motor** is an actuator designed to move to a commanded position.

A conventional DC motor primarily provides continuous rotation. A positional servo, such as the SG90, is designed so the controller can request a particular angular position.

For this project:

```text
             GATE MOVEMENT

       CLOSED              OPEN
          │                  │
          ▼                  ▼

        ┌───┐              ┌─────┐
        │   │              │     │
        │   │              │     │
────────┘   └──────    ─────┘     └──────
        0°                 90°
```

A typical classroom configuration is:

```text
0°  → Gate closed
90° → Gate open
```

The exact angles are **not universal**. They depend on:

- Servo mounting position
- Servo horn orientation
- Gate linkage
- Gate size
- Mechanical travel
- Physical limits of the mechanism

Therefore, students should tune the angles for their particular model.

---

# 6. How a Servo Receives Commands

The Arduino does not normally tell the servo:

> "Move continuously at this speed."

Instead, it provides a control signal representing the desired position.

The Arduino Servo library hides much of the low-level pulse-generation detail.

Conceptually:

```text
Arduino
   │
   │ Position command
   ▼
Servo electronics
   │
   ├── Compares requested position
   │
   ├── Drives motor
   │
   └── Moves toward target
          │
          ▼
       Gate moves
```

The important programming instruction is:

```cpp
gateServo.write(90);
```

This requests a servo position of approximately 90 degrees.

---

# 7. The Arduino Servo Library

The project uses the built-in Arduino Servo library.

Include it with:

```cpp
#include <Servo.h>
```

Then create a servo object:

```cpp
Servo gateServo;
```

The object represents the servo that the program will control.

Next, attach it to the control pin:

```cpp
gateServo.attach(SERVO_PIN);
```

Finally, command its position:

```cpp
gateServo.write(90);
```

### Complete conceptual sequence

```text
#include <Servo.h>
        │
        ▼
Servo gateServo;
        │
        ▼
gateServo.attach(D9);
        │
        ▼
gateServo.write(90);
        │
        ▼
Servo moves toward 90°
```

---

# 8. Why We Use Constants

Instead of scattering numbers throughout the program, define meaningful constants.

Example:

```cpp
const int BUTTON_PIN = 2;
const int SERVO_PIN = 9;

const int GATE_CLOSED_ANGLE = 0;
const int GATE_OPEN_ANGLE = 90;

const unsigned long OPEN_TIME = 5000;
```

This makes the program easier to understand.

Compare:

```cpp
gateServo.write(90);
```

with:

```cpp
gateServo.write(GATE_OPEN_ANGLE);
```

The second version communicates the purpose of the value.

It also makes experimentation easier.

For example:

```cpp
const int GATE_OPEN_ANGLE = 120;
```

changes the opening position without searching through the entire program.

---

# 9. Understanding the Push Button

The push button is our **input device**.

The Arduino needs to determine whether the button is being pressed.

For this project, we can use the Arduino's internal pull-up resistor:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
```

This is extremely useful because an external resistor is not required for the basic circuit.

---

# 10. Understanding INPUT_PULLUP

With `INPUT_PULLUP`, the logic is inverted compared with many beginner examples.

### Button released

```text
5V
 │
Internal pull-up
 │
D2 ───────────── HIGH
 │
Button open
 │
GND
```

The input reads:

```text
HIGH
```

### Button pressed

```text
5V
 │
Internal pull-up
 │
D2 ───────┐
          │
       BUTTON
          │
          ▼
         GND
```

The input reads:

```text
LOW
```

Therefore:

```text
Button released → HIGH
Button pressed  → LOW
```

This is called **active-LOW logic**.

---

# 11. Why INPUT_PULLUP Is Useful

Without a pull-up or pull-down resistor, a digital input can become **floating**.

A floating input may randomly read:

```text
HIGH
LOW
HIGH
HIGH
LOW
...
```

even though nobody is pressing the button.

Using:

```cpp
INPUT_PULLUP
```

provides a defined default state.

```text
             INPUT_PULLUP

Button OFF ───────────────► HIGH

Button ON
    │
    ▼
   GND
    │
    ▼
Arduino pin ──────────────► LOW
```

This is one of the most useful simple techniques for Arduino input circuits.

---

# 12. Button Event vs Button State

There is an important difference between:

### Button state

> Is the button currently pressed?

and:

### Button event

> Has the button just been pressed?

Suppose the user holds the button down for two seconds.

The Arduino may execute its loop hundreds or thousands of times during those two seconds.

If the program simply checks:

```cpp
if (digitalRead(BUTTON_PIN) == LOW) {
    openGate();
}
```

then the condition remains true repeatedly.

For many systems, we want to recognize only the **new press event**.

---

# 13. Detecting a Button Transition

A useful concept is **edge detection**.

For an active-LOW button:

```text
HIGH ───────────────┐
                    │
                    ▼
                  PRESS
                    │
                    ▼
LOW ────────────────┘
```

The important transition is:

```text
HIGH → LOW
```

This tells us:

> The button has just been pressed.

A simplified concept is:

```text
Previous state = HIGH
Current state  = LOW
        │
        ▼
   NEW PRESS EVENT
```

After detecting the event, the program updates the previous state.

---

# 14. Switch Bounce

Mechanical buttons do not always produce one perfectly clean transition.

When the contacts touch, they can physically bounce.

A simplified signal may look like:

```text
Ideal:

HIGH ────────────────┐
                     │
                     └──────── LOW


Real button:

HIGH ────────────┐
                 │ ┌─┐
                 └─┘ └─┐
                       └──── LOW
```

The Arduino may interpret these rapid transitions as several button presses.

This phenomenon is called:

> **Switch bounce**

---

# 15. Debouncing

To prevent false button events, the program can use **debouncing**.

One simple approach is a short debounce interval:

```cpp
const unsigned long DEBOUNCE_DELAY = 50;
```

The idea is:

```text
Button transition detected
          │
          ▼
     Wait briefly
          │
          ▼
   Read button again
          │
          ▼
Stable state?
     │        │
    YES       NO
     │        │
     ▼        ▼
Accept      Ignore
event       transition
```

A 50 ms debounce interval is a common starting point for mechanical push buttons, though the ideal value can vary.

---

# 16. State Variables

The program needs to remember whether the gate is currently open.

We can use:

```cpp
bool gateOpen = false;
```

A Boolean variable has two possible values:

```text
false
true
```

For this project:

```text
false → CLOSED
true  → OPEN
```

The state can be visualized as:

```text
                 ┌───────────────┐
                 │    CLOSED     │
                 │ gateOpen=false│
                 └───────┬───────┘
                         │
                  Button pressed
                         │
                         ▼
                 ┌───────────────┐
                 │     OPEN      │
                 │ gateOpen=true │
                 └───────┬───────┘
                         │
                    5 seconds
                         │
                         ▼
                 ┌───────────────┐
                 │    CLOSED     │
                 └───────────────┘
```

---

# 17. Why State Matters

Consider the question:

> "Should the Arduino close the gate now?"

The controller needs to know:

1. Is the gate open?
2. When did it open?
3. Has the required amount of time passed?

Without stored state, the program cannot reliably manage the sequence.

This is why **state machines** are fundamental in embedded systems.

---

# 18. The Gate State Machine

The project can be represented using two primary states:

```text
┌─────────────────────┐
│       CLOSED        │
│                     │
│ Waiting for button  │
└──────────┬──────────┘
           │
     Button pressed
           │
           ▼
┌─────────────────────┐
│        OPEN         │
│                     │
│ Start 5-sec timer   │
└──────────┬──────────┘
           │
      5 seconds
           │
           ▼
┌─────────────────────┐
│       CLOSED        │
└─────────────────────┘
```

This is a simple **finite state machine**.

---

# 19. What Is millis()?

Arduino provides:

```cpp
millis()
```

which returns the number of milliseconds that have elapsed since the board started running the current program.

For example:

```text
1 second  ≈ 1000 ms
5 seconds ≈ 5000 ms
10 seconds ≈ 10000 ms
```

Instead of stopping the processor for five seconds, we can remember when the gate opened.

---

# 20. Recording the Opening Time

When the gate opens:

```cpp
gateOpenTime = millis();
```

Suppose:

```text
gateOpenTime = 12000 ms
```

Later:

```text
current time = 14500 ms
```

Then:

```text
14500 - 12000
= 2500 ms
= 2.5 seconds
```

The gate has been open for 2.5 seconds.

---

# 21. Automatic Closing Logic

The key condition is:

```cpp
if (gateOpen && millis() - gateOpenTime >= OPEN_TIME) {
    closeGate();
}
```

Break it into pieces:

```text
gateOpen
   │
   ├── Is the gate currently open?
   │
   ▼
millis() - gateOpenTime
   │
   ├── How long has it been open?
   │
   ▼
>= OPEN_TIME
   │
   ├── Has the required time passed?
   │
   ▼
closeGate()
```

This is much easier to understand when expressed as a decision tree:

```text
              Is gate open?
                   │
             ┌─────┴─────┐
            NO           YES
             │             │
             ▼             ▼
          Nothing      Check elapsed time
                          │
                    ┌─────┴─────┐
                   NO           YES
                    │             │
                    ▼             ▼
                 Keep open     Close gate
```

---

# 22. Why Not Use delay(5000)?

A simple program might use:

```cpp
gateServo.write(90);
delay(5000);
gateServo.write(0);
```

This is easy to understand, but `delay()` blocks the main loop.

During the delay:

```text
Button processing      PAUSED
Sensor reading         PAUSED
Other decisions        PAUSED
Serial processing      PAUSED
Other automation       PAUSED
```

The Arduino is effectively waiting.

---

# 23. Non-Blocking Timing

With `millis()`, the Arduino can continue running its main loop.

Conceptually:

```text
Open gate
   │
   ├───────────────► Read button
   │
   ├───────────────► Check sensors
   │
   ├───────────────► Update outputs
   │
   ├───────────────► Check timer
   │
   ├───────────────► Perform other tasks
   │
   └───────────────► Repeat
```

When five seconds have elapsed:

```text
Timer complete
     │
     ▼
Close gate
```

This approach scales much better when the project becomes more complex.

---

# 24. Timing Comparison

| Method | Advantage | Limitation |
|---|---|---|
| `delay(5000)` | Very simple | Blocks the program |
| `millis()` | Non-blocking | Requires more logic |
| Timer/state machine | Scales to complex systems | More programming concepts |

For beginner demonstrations, `delay()` can be useful for understanding the sequence. For real automation logic, `millis()` is usually the better foundation.

---

# 25. Complete System Architecture

```text
                    PROJECT 21
                 SERVO SMART GATE

              ┌──────────────────┐
              │   PUSH BUTTON    │
              │      INPUT       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │   ARDUINO UNO    │
              │                  │
              │ Button Detection │
              │ Debounce Logic   │
              │ State Management │
              │ Timer Management │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │    SG90 SERVO    │
              │    ACTUATOR      │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │   MODEL GATE     │
              │                  │
              │ OPEN / CLOSED    │
              └──────────────────┘
```

---

# 26. Full Operating Sequence

The complete sequence is:

```text
START
  │
  ▼
Initialize Arduino
  │
  ├── Configure button
  ├── Attach servo
  └── Close gate
  │
  ▼
WAIT
  │
  ▼
Button pressed?
  │
 ┌┴───────────────┐
NO                YES
 │                  │
 ▼                  ▼
Keep waiting     Debounce
                   │
                   ▼
              Confirm press
                   │
                   ▼
              Open gate
                   │
                   ▼
          Record opening time
                   │
                   ▼
            Gate remains open
                   │
                   ▼
            Has 5 sec passed?
                   │
             ┌─────┴─────┐
            NO           YES
             │             │
             └─────┐       ▼
                   │    Close gate
                   │       │
                   └───────┘
                           │
                           ▼
                         WAIT
```

---

# 27. Functional Decomposition

A clean program can divide responsibilities into functions.

For example:

```cpp
void openGate() {
    gateServo.write(GATE_OPEN_ANGLE);
    gateOpen = true;
    gateOpenTime = millis();
}

void closeGate() {
    gateServo.write(GATE_CLOSED_ANGLE);
    gateOpen = false;
}
```

This makes the program easier to read.

Instead of:

```cpp
gateServo.write(GATE_OPEN_ANGLE);
gateOpen = true;
gateOpenTime = millis();
```

we can simply write:

```cpp
openGate();
```

The function name explains the operation.

---

# 28. Recommended Program Structure

A well-organized program can follow this structure:

```text
1. Include libraries
        ↓
2. Define pins
        ↓
3. Define configuration values
        ↓
4. Create servo object
        ↓
5. Create state variables
        ↓
6. setup()
        ↓
7. loop()
        ↓
8. Helper functions
```

Example:

```cpp
#include <Servo.h>

// Pins
const int BUTTON_PIN = 2;
const int SERVO_PIN = 9;

// Servo positions
const int GATE_CLOSED_ANGLE = 0;
const int GATE_OPEN_ANGLE = 90;

// Timing
const unsigned long OPEN_TIME = 5000;
const unsigned long DEBOUNCE_DELAY = 50;

// Servo object
Servo gateServo;

// State
bool gateOpen = false;

// Timer
unsigned long gateOpenTime = 0;
```

---

# 29. Setup Stage

The `setup()` function runs once when the Arduino starts.

Typical tasks:

```cpp
void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    gateServo.attach(SERVO_PIN);
    gateServo.write(GATE_CLOSED_ANGLE);
}
```

The system now starts with:

```text
Button → configured
Servo  → attached
Gate   → closed
State  → closed
```

---

# 30. Main Loop

The `loop()` function repeatedly checks what is happening.

Conceptually:

```text
LOOP
 │
 ├── Read button
 │
 ├── Detect new press
 │
 ├── Open gate if required
 │
 ├── Check timer
 │
 ├── Close gate if time expired
 │
 └── Repeat
```

This repeated loop is the heart of most Arduino programs.

---

# 31. A Robust Button-Handling Concept

The button logic should distinguish:

```text
Released
   │
   ▼
Pressed
   │
   ▼
New event detected
   │
   ▼
Process event once
   │
   ▼
Wait for release
```

This prevents one long button press from being treated as many separate commands.

A complete implementation can use:

- Previous button state
- Current button state
- Debounce timer
- Stable button state

This is a good next step after learning basic `digitalRead()`.

---

# 32. Servo Power Requirements

The servo is a motorized load.

This is different from a small LED.

A servo can draw significantly more current when:

- Starting movement
- Accelerating
- Holding a load
- Encountering mechanical resistance
- Approaching a stall condition

A weak supply can cause:

```text
Servo moves
    ↓
Voltage drops
    ↓
Arduino becomes unstable
    ↓
Arduino resets
```

---

# 33. Why the Arduino May Reset

A common symptom is:

> The servo moves, then the Arduino suddenly restarts.

One possible cause is inadequate power.

Conceptually:

```text
Servo movement
      │
      ▼
Higher current demand
      │
      ▼
Supply voltage dips
      │
      ▼
Arduino brownout/reset
      │
      ▼
Program starts again
```

For a small classroom prototype, the SG90 may work from the Arduino 5V supply depending on the setup and load.

For a more reliable design, use a suitable external 5V supply for the servo.

### Critical rule

If using an external servo supply:

```text
External 5V ─────► Servo VCC
External GND ────► Servo GND
                    │
                    └────► Arduino GND
```

The grounds must normally be common so the servo control signal has a shared electrical reference.

---

# 34. Mechanical Design Matters

The electronics can be correct while the gate still fails mechanically.

Check:

- Servo is firmly mounted.
- Servo horn is secure.
- Gate moves freely.
- Linkage is aligned.
- Gate is not too heavy.
- Servo is not forced against a hard stop.
- Opening and closing angles are within safe mechanical limits.

Think of the project as:

```text
ELECTRICAL SYSTEM
       +
MECHANICAL SYSTEM
       =
FUNCTIONAL ROBOTIC SYSTEM
```

---

# 35. Servo and Gate Geometry

The servo's angular movement must be converted into gate movement.

Example:

```text
Servo horn
     │
     │ linkage
     ▼
    ●──────────── Gate
   /
  /
Servo
```

A small change in servo angle may produce a large change in gate movement depending on the linkage.

Therefore:

```text
Software angle
       ↓
Servo rotation
       ↓
Mechanical linkage
       ↓
Gate movement
```

This is why the correct opening angle must be experimentally determined.

---

# 36. Experiment 1 — Change the Opening Angle

Start with:

```cpp
const int GATE_OPEN_ANGLE = 90;
```

Try:

```cpp
const int GATE_OPEN_ANGLE = 60;
```

Then:

```cpp
const int GATE_OPEN_ANGLE = 120;
```

Record the results.

| Angle | Gate movement | Observation |
|---:|---|---|
| 60° | | |
| 90° | | |
| 120° | | |

### Question

Which angle provides sufficient gate opening without putting unnecessary mechanical stress on the servo?

---

# 37. Experiment 2 — Change the Opening Time

Start with:

```cpp
const unsigned long OPEN_TIME = 5000;
```

Try:

```cpp
const unsigned long OPEN_TIME = 10000;
```

The gate should remain open for approximately ten seconds.

Try:

```cpp
const unsigned long OPEN_TIME = 3000;
```

Compare the behavior.

### Student task

Create a table:

| Opening time | Expected result | Actual result |
|---:|---|---|
| 3 sec | | |
| 5 sec | | |
| 10 sec | | |

---

# 38. Experiment 3 — Add a Green LED

Add a green LED that indicates:

```text
GREEN = GATE OPEN
```

System:

```text
Gate opens
   │
   ├── Servo → OPEN
   │
   └── LED → ON
```

When the gate closes:

```text
Servo → CLOSED
LED   → OFF
```

This introduces **status indication**.

---

# 39. Experiment 4 — Add a Red LED

Add another LED:

```text
RED = GATE CLOSED
GREEN = GATE OPEN
```

The system now gives visual feedback.

```text
       GATE STATE

    CLOSED       OPEN
       │           │
       ▼           ▼
     RED ON     GREEN ON
       │           │
       ▼           ▼
     Servo 0°    Servo 90°
```

This is similar to status indicators used in real control panels.

---

# 40. Experiment 5 — Add an Ultrasonic Sensor

The push button can eventually be replaced or supplemented by an HC-SR04 ultrasonic sensor.

The system becomes:

```text
        Vehicle
           │
           ▼
      HC-SR04 Sensor
           │
           ▼
       Distance
           │
           ▼
      Threshold Check
           │
           ▼
       Arduino
           │
           ▼
      Servo Gate
```

Example:

```text
Distance < threshold
        │
        ▼
   Open gate
        │
        ▼
 Wait configured time
        │
        ▼
 Close gate
```

This combines concepts from earlier ultrasonic and automation projects.

---

# 41. Combining Projects 19, 20 and 21

A more advanced parking system could be:

```text
              VEHICLE
                 │
                 ▼
          ┌─────────────┐
          │   HC-SR04   │
          └──────┬──────┘
                 │
                 ▼
             Distance
                 │
                 ▼
        ┌────────────────┐
        │ Arduino Decision│
        └────────┬───────┘
                 │
          Vehicle detected?
             │        │
            NO       YES
             │        │
             ▼        ▼
           Wait    Open gate
                      │
                      ▼
                Keep open
                      │
                      ▼
                Close gate
```

A robust version can additionally prevent closure while a vehicle is still detected.

---

# 42. Advanced Challenge — Automatic Parking Gate

Build a complete automatic parking gate.

### Requirements

1. Detect an approaching vehicle.
2. Measure its distance.
3. Compare the distance against a threshold.
4. Open the servo gate.
5. Keep the gate open for a configurable period.
6. Close the gate automatically.
7. Add red and green status LEDs.
8. Prevent the gate from closing while an object is still detected.
9. Add a buzzer for warning.
10. Display the distance on the Serial Monitor or an LCD.

### Architecture

```text
            ┌──────────────┐
            │    HC-SR04   │
            └──────┬───────┘
                   │
                   ▼
              Distance
                   │
                   ▼
          ┌────────────────┐
          │ Arduino Control│
          └───────┬────────┘
                  │
        ┌─────────┼──────────┐
        ▼         ▼          ▼
      Servo      LEDs      Buzzer
        │
        ▼
      Gate
```

---

# 43. Advanced Safety Logic

A simple system says:

```text
Open → Wait 5 sec → Close
```

A safer parking gate can say:

```text
Open
  │
  ▼
Wait
  │
  ▼
Vehicle still detected?
  │
 ┌┴───────┐
YES      NO
 │         │
 ▼         ▼
Keep      Close
open      gate
 │
 └────► Check again
```

This is a significant improvement because the timer alone does not know whether something is still underneath the gate.

---

# 44. Possible Real-World Applications

The project demonstrates principles used in:

### Automatic barriers

```text
Vehicle → Sensor → Controller → Barrier
```

### Access control

```text
Card / PIN / Sensor
        ↓
    Controller
        ↓
     Door Lock
```

### Railway crossing models

```text
Train detected
      ↓
Controller
      ↓
Barrier closes
      ↓
Train passes
      ↓
Barrier opens
```

### Robotics

```text
Sensor
  ↓
Decision
  ↓
Servo actuator
  ↓
Mechanical movement
```

### Industrial automation

```text
Input
  ↓
PLC / Microcontroller
  ↓
State logic
  ↓
Motor / Actuator
```

---

# 45. Troubleshooting Guide

## Problem 1 — Servo Does Not Move

Check:

- Servo signal is connected to D9.
- Servo VCC is connected correctly.
- Servo GND is connected correctly.
- `#include <Servo.h>` is present.
- `gateServo.attach(SERVO_PIN);` is executed.
- `gateServo.write(...)` is being called.
- The servo is not mechanically jammed.

---

## Problem 2 — Arduino Resets When Servo Moves

Likely causes:

- Servo power supply is insufficient.
- Servo is mechanically overloaded.
- Wiring is loose.
- Ground connection is poor.
- Power is being drawn through an unsuitable USB/5V arrangement.

Try:

```text
Use suitable external 5V servo power
             +
Connect grounds together
```

---

## Problem 3 — Servo Jitters

Possible causes:

- Weak or noisy power.
- Poor ground connection.
- Loose jumper wires.
- Mechanical resistance.
- Servo is under excessive load.

Start by checking the power and mechanical setup.

---

## Problem 4 — Gate Moves Too Far

Reduce the opening angle.

For example:

```cpp
const int GATE_OPEN_ANGLE = 70;
```

instead of:

```cpp
const int GATE_OPEN_ANGLE = 120;
```

Never force the servo against its mechanical limits.

---

## Problem 5 — Gate Opens Repeatedly

Possible causes:

- Button bounce.
- Incorrect edge detection.
- Button wiring is wrong.
- The code is responding continuously to `LOW`.
- Previous button state is not being updated correctly.

Check:

```text
INPUT_PULLUP
     ↓
Released = HIGH
Pressed  = LOW
```

---

## Problem 6 — Button Seems Backwards

This is expected when using:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
```

Remember:

```text
HIGH = released
LOW  = pressed
```

---

## Problem 7 — Gate Closes Too Early

Check:

```cpp
const unsigned long OPEN_TIME = 5000;
```

Remember:

```text
5000 ms = 5 seconds
```

If the value is too small, the gate will close sooner.

---

# 46. Testing Procedure

Test the project systematically.

### Test 1 — Power-up

Expected:

```text
Arduino starts
       ↓
Servo attaches
       ↓
Gate moves to CLOSED position
```

### Test 2 — Button press

Expected:

```text
Press button
     ↓
Servo moves
     ↓
Gate opens
```

### Test 3 — Timing

Expected:

```text
Gate opens
     ↓
Approximately 5 seconds
     ↓
Gate closes
```

### Test 4 — Second press

After closing:

```text
Press again
    ↓
Gate opens again
```

### Test 5 — Long press

Hold the button.

Expected:

```text
One press event
     ↓
One gate-opening action
```

The system should not continuously trigger the opening routine simply because the button remains held.

---

# 47. Student Observation Sheet

Record your observations.

| Test | Input | Expected Output | Actual Output | Pass/Fail |
|---|---|---|---|---|
| 1 | Power ON | Gate closed | | |
| 2 | Button press | Gate opens | | |
| 3 | Wait 5 sec | Gate closes | | |
| 4 | Press again | Gate reopens | | |
| 5 | Hold button | No repeated triggers | | |
| 6 | Change angle | Different movement | | |
| 7 | Change timer | Different open duration | | |

---

# 48. Debugging With Serial Monitor

For more advanced testing, students can print useful information.

Example:

```cpp
Serial.println("Button pressed");
```

or:

```cpp
Serial.println("Gate opened");
```

and:

```cpp
Serial.println("Gate closed");
```

This creates a simple event log:

```text
Arduino started
Gate closed
Button pressed
Gate opened
5 seconds elapsed
Gate closed
```

Serial debugging helps students understand what the program is doing internally.

---

# 49. Common Programming Mistakes

### Mistake 1 — Forgetting the library

Incorrect:

```cpp
Servo gateServo;
```

without:

```cpp
#include <Servo.h>
```

---

### Mistake 2 — Forgetting attach()

Incorrect:

```cpp
gateServo.write(90);
```

before attaching the servo.

Correct sequence:

```cpp
gateServo.attach(SERVO_PIN);
gateServo.write(90);
```

---

### Mistake 3 — Incorrect button logic

With `INPUT_PULLUP`:

```cpp
if (digitalRead(BUTTON_PIN) == HIGH)
```

does **not** mean the button is pressed.

Normally:

```cpp
LOW = pressed
HIGH = released
```

---

### Mistake 4 — Blocking the controller

Avoid building complex automation around:

```cpp
delay(5000);
```

when other tasks need to run during the five seconds.

Use:

```cpp
millis()
```

for scalable timing.

---

# 50. Engineering Thinking

This project teaches students to think beyond:

> "Which line of code makes the servo move?"

Instead, ask:

### Input

```text
What event starts the process?
```

### Decision

```text
What condition must be true?
```

### State

```text
What does the system currently remember?
```

### Actuator

```text
What physical device performs the action?
```

### Timing

```text
When should the next action happen?
```

This is the foundation of embedded automation.

---

# 51. The Complete Engineering Pattern

The project can be summarized as:

```text
┌─────────────┐
│    INPUT    │
│ Push Button │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   DECISION  │
│   Arduino   │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│    STATE    │
│ Open/Closed │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  ACTUATOR   │
│    Servo    │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ TIMED ACTION│
│   5 seconds │
└──────┬──────┘
       │
       ▼
   CLOSE GATE
```

This pattern is reusable across many automation projects.

---

# 52. Key Concepts Learned

By completing Project 21, students encounter:

- Digital input
- Push-button interfacing
- `INPUT_PULLUP`
- Active-LOW logic
- Edge/event detection
- Switch debouncing
- Boolean state variables
- Servo control
- Arduino Servo library
- Position-based actuation
- `millis()` timing
- Non-blocking programming
- Finite-state-machine thinking
- Electrical power considerations
- Mechanical actuator considerations
- Sensor-to-actuator automation

---

# 53. Quick Reference

## Pins

```text
Push Button → D2
Servo Signal → D9
Servo VCC → 5V / suitable servo supply
Servo GND → GND
```

## States

```text
false → CLOSED
true  → OPEN
```

## Servo positions

```text
0°  → Closed
90° → Open
```

## Timing

```text
5000 ms = 5 seconds
```

## Button logic

```text
Released → HIGH
Pressed  → LOW
```

## Main library

```cpp
#include <Servo.h>
```

## Main servo commands

```cpp
gateServo.attach(SERVO_PIN);
gateServo.write(GATE_OPEN_ANGLE);
gateServo.write(GATE_CLOSED_ANGLE);
```

## Timer concept

```cpp
millis() - gateOpenTime >= OPEN_TIME
```

---

# 54. Mini Quiz

### Q1. What is the main purpose of a servo motor?

A. Measure temperature  
B. Control physical position  
C. Store data  
D. Detect light

**Answer:** B

### Q2. With `INPUT_PULLUP`, what does LOW normally mean?

A. Button released  
B. Button pressed  
C. Arduino off  
D. Servo disconnected

**Answer:** B

### Q3. Why is debouncing required?

A. To increase servo speed  
B. To remove mechanical button noise  
C. To power the Arduino  
D. To measure distance

**Answer:** B

### Q4. What does `millis()` provide?

A. Servo angle  
B. Distance  
C. Elapsed time since program start  
D. Button voltage

**Answer:** C

### Q5. Why can `delay(5000)` be problematic?

A. It destroys the servo  
B. It blocks program execution during the delay  
C. It changes the button wiring  
D. It disables the Arduino permanently

**Answer:** B

---

# 55. Final Challenge

Modify the project so that it behaves like a real parking gate.

### Level 1

```text
Button
  ↓
Servo Gate
```

### Level 2

```text
Button
  ↓
Servo
  ↓
5-sec automatic closing
```

### Level 3

```text
Button
  ↓
Servo
  ↓
Red/Green LEDs
```

### Level 4

```text
Ultrasonic Sensor
        ↓
Distance Detection
        ↓
Arduino
        ↓
Servo Gate
```

### Level 5

```text
Vehicle Detection
        ↓
Distance Check
        ↓
Open Gate
        ↓
Vehicle Still Present?
     │          │
    YES        NO
     │          │
     ▼          ▼
 Keep Open   Close Gate
     │
     └────────► Check Again
```

### Level 6 — Smart Parking Gate

Add:

- Entry detection
- Exit detection
- Vehicle counting
- Red/green availability indicator
- Buzzer warning
- LCD/OLED display
- Gate safety logic
- Servo position feedback
- Automatic timeout
- Multiple parking slots

At this point, the project becomes a miniature **embedded access-control system**.

---

# 56. Real-World System Analogy

Our classroom project:

```text
Push Button
     ↓
Arduino
     ↓
Servo
     ↓
Mini Gate
```

A real system may use:

```text
RFID / Camera / Sensor
          ↓
      Controller
          ↓
   Motor Controller
          ↓
   Barrier Mechanism
          ↓
      Real Gate
```

The components change, but the engineering logic remains similar.

That is the most important lesson.

---

# 57. Final Takeaways

The Servo Smart Gate is more than a project about making a servo rotate.

It introduces the architecture of a real automation controller:

```text
SENSE / RECEIVE
       ↓
     DECIDE
       ↓
     REMEMBER
       ↓
      ACT
       ↓
     WAIT
       ↓
     ACT AGAIN
```

Students learn that an embedded system must not only **perform an action**, but also understand:

- what triggered the action,
- what state the system is in,
- how long an action has been active,
- when the next action should occur,
- and how electrical and mechanical limitations affect the system.

The fundamental pattern is:

```text
INPUT
  ↓
DECISION
  ↓
STATE
  ↓
ACTUATOR
  ↓
TIMED ACTION
  ↓
NEW STATE
```

Once students understand this pattern, they can move from simple Arduino experiments toward **robotics, smart homes, access-control systems, parking automation, industrial control, and IoT systems**.

---

# 58. Glossary

| Term | Meaning |
|---|---|
| Actuator | A device that produces physical movement or action |
| Servo | Position-controlled motor/actuator |
| GPIO | General-purpose input/output pin |
| `INPUT_PULLUP` | Configures an input using the Arduino's internal pull-up resistor |
| Active LOW | A logic design where LOW represents the active condition |
| Debouncing | Filtering unwanted rapid transitions from mechanical switches |
| State | The current condition of a system |
| Boolean | A variable with `true` or `false` values |
| `millis()` | Function that reports elapsed milliseconds since program start |
| Non-blocking | Code that allows other tasks to continue while waiting |
| Edge detection | Detecting a transition between digital states |
| Threshold | A value used to trigger a decision |
| Common ground | Shared electrical reference between connected circuits |
| Finite State Machine | A system modeled using defined states and transitions |

---

# 59. Project Completion Checklist

- [ ] Arduino Uno connected
- [ ] Push button wired to D2
- [ ] Button connected to GND
- [ ] `INPUT_PULLUP` configured
- [ ] SG90 signal connected to D9
- [ ] Servo power connected correctly
- [ ] Common ground verified
- [ ] Servo library included
- [ ] Gate starts closed
- [ ] Button press opens gate
- [ ] Gate remains open for five seconds
- [ ] Gate closes automatically
- [ ] Button event is debounced
- [ ] Servo does not hit mechanical limits
- [ ] No unexpected Arduino resets
- [ ] Experiments completed
- [ ] Advanced challenge attempted

---

# Project 21 Summary

```text
                SERVO SMART GATE

              ┌──────────────┐
              │ PUSH BUTTON  │
              └──────┬───────┘
                     │
                     ▼
              ┌──────────────┐
              │   ARDUINO    │
              │              │
              │ Input        │
              │ Decision     │
              │ State        │
              │ Timer        │
              └──────┬───────┘
                     │
                     ▼
              ┌──────────────┐
              │  SG90 SERVO  │
              └──────┬───────┘
                     │
                     ▼
              ┌──────────────┐
              │ MODEL GATE   │
              │              │
              │ OPEN → WAIT  │
              │      ↓       │
              │    CLOSE     │
              └──────────────┘
```

> **Core idea:** A microcontroller can convert a simple input event into a controlled physical action, remember the system state, and automatically perform the next action based on time.
