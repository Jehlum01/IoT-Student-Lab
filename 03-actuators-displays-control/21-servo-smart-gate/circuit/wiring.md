# Project 21 — Servo Smart Gate Wiring

> 🚪 **Build a simple smart gate using an Arduino Uno, an SG90 micro servo, and a push button.**

---

## 🔌 Components

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main controller |
| SG90 Micro Servo | 1 | Opens and closes the gate |
| Push Button | 1 | User input to control the gate |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | As required | Electrical connections |

---

# 📍 Pin Mapping

| Component | Pin | Arduino Uno | Purpose |
|---|---|---|---|
| Push Button | One terminal | **D2** | Reads button state |
| Push Button | Other terminal | **GND** | Ground reference |
| SG90 Servo | Signal | **D9** | Servo control signal |
| SG90 Servo | VCC | **5V** | Power |
| SG90 Servo | GND | **GND** | Common ground |

---

# 🧭 Complete Wiring Overview

```text
                         ARDUINO UNO
                  ┌──────────────────────┐
                  │                      │
                  │              5V ─────┼──────► Servo VCC
                  │                      │
                  │             GND ─────┼──────► Servo GND
                  │                      │
                  │              D9 ─────┼──────► Servo Signal
                  │                      │
                  │              D2 ◄────┼─────── Push Button
                  │                      │
                  └───────────┬──────────┘
                              │
                              ▼
                         Push Button
                              │
                              ▼
                             GND
```

---

# 🔘 1. Push Button

Connect the push button between **Arduino D2** and **GND**.

```text
Arduino D2
     │
     │
     ▼
┌────────────┐
│   BUTTON   │
└──────┬─────┘
       │
       ▼
      GND
```

### Connection

```text
Arduino D2 ───── Push Button ───── GND
```

A common software approach is to configure D2 using the Arduino's internal pull-up resistor:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
```

With this configuration:

```text
Button released → D2 reads HIGH

Button pressed  → D2 reads LOW
```

### Button Logic

```text
             BUTTON
                │
        ┌───────┴───────┐
        │               │
     RELEASED         PRESSED
        │               │
        ▼               ▼
      HIGH             LOW
```

> **Important:** Because `INPUT_PULLUP` is used, the button logic is **active LOW**. Pressing the button connects D2 to GND.

---

# ⚙️ 2. SG90 Servo

An SG90 servo normally has three connections:

```text
        SG90 SERVO
       ┌───────────┐
       │           │
       │    ⚙️     │
       │           │
       └───────────┘
          │ │ │
          │ │ │
         VCC GND SIGNAL
          │  │   │
          ▼  ▼   ▼
         5V GND  D9
```

### Connections

```text
Servo VCC    → Arduino 5V
Servo GND    → Arduino GND
Servo Signal → Arduino D9
```

The **signal wire** is controlled by the Arduino using the Servo library.

> ⚠️ **Wire colors can vary between servo manufacturers.** Check the servo's datasheet or labeling rather than relying only on wire color.

---

# 🔄 3. How the Servo Controls the Gate

A servo can rotate to a commanded angle.

For example, a simple prototype might use:

```text
0°  → CLOSED
90° → OPEN
```

```text
          GATE CLOSED
               │
               ▼
              0°
               │
        ───────┘
```

When the button is pressed:

```text
Button Press
     │
     ▼
Arduino detects input
     │
     ▼
Servo rotates
     │
     ▼
Gate opens
```

The exact angles depend on how the physical gate mechanism is mounted.

---

# 🧠 4. Complete System Flow

```text
              START
                │
                ▼
        Read push button
                │
                ▼
        Is button pressed?
           │           │
          NO          YES
           │           │
           │           ▼
           │      Open / change gate
           │           │
           │           ▼
           │       Servo moves
           │
           ▼
        Keep gate
        in current state
```

A toggle-style implementation can alternate between OPEN and CLOSED:

```text
                 BUTTON PRESS
                       │
                       ▼
                Current state?
                 ┌─────┴─────┐
                 ▼           ▼
              CLOSED        OPEN
                 │           │
                 ▼           ▼
                OPEN        CLOSE
                 │           │
                 ▼           ▼
                90°          0°
```

---

# 🔌 5. Complete Circuit

```text
                        ARDUINO UNO
                 ┌─────────────────────┐
                 │                     │
                 │ D2 ◄─────────────┐  │
                 │                  │  │
                 │ GND ─────────────┼──┼────► Button
                 │                  │  │
                 │ D9 ──────────────┼──┼────► Servo Signal
                 │                  │  │
                 │ 5V ──────────────┼──┼────► Servo VCC
                 │                  │  │
                 │ GND ─────────────┼──┼────► Servo GND
                 │                  │  │
                 └──────────────────┘  │
                                      │
                              ┌───────┴───────┐
                              │               │
                              ▼               ▼
                         Push Button      SG90 Servo
                              │               │
                              ▼               ▼
                             GND         Gate mechanism
```

---

# ⚡ 6. Servo Power Considerations

The SG90 is a small servo, but servos can draw more current when:

- Starting movement
- Changing direction
- Carrying a mechanical load
- Holding a position against resistance

For a simple, lightly loaded classroom prototype, the servo may work from the Arduino 5V supply.

However, if you experience:

```text
Arduino resets
Servo jitters
Servo moves unpredictably
Servo fails to move
Voltage drops
```

consider using a suitable **external 5V supply** for the servo.

### External Servo Supply

```text
External 5V ─────────► Servo VCC
External GND ────────► Servo GND
                         │
Arduino GND ────────────┘
```

The Arduino and external servo supply must share a **common ground**.

> ⚠️ Do not power a mechanically loaded servo from an unsuitable supply. Choose a supply capable of providing the required current.

---

# 🧱 7. Mechanical Gate Setup

The servo horn should be securely attached to the gate mechanism.

A simple classroom model could look like:

```text
             SERVO
              ⚙
              │
              │ Servo horn
              ▼
        ─────────────
        │   GATE    │
        ─────────────
              │
              │
             BASE
```

### Closed position

```text
       │
       │
       │
───────┴────────────
      GATE
```

### Open position

```text
       /
      /
     /
────/──────────────
   GATE
```

> The physical geometry determines the exact servo angles. Start with small movements and adjust the angles so the servo does not hit a mechanical stop.

---

# 🧪 8. Testing Procedure

After completing the wiring:

1. Check all electrical connections.
2. Confirm the servo signal is connected to **D9**.
3. Confirm servo VCC and GND are correct.
4. Confirm the button is connected between **D2** and **GND**.
5. Upload the servo control program.
6. Observe the initial gate position.
7. Press the button.
8. Observe the servo movement.
9. Release the button.
10. Test repeated presses.
11. Check that the gate moves freely without excessive mechanical resistance.

### Basic test sequence

```text
Power ON
   │
   ▼
Servo moves to initial position
   │
   ▼
Press button
   │
   ▼
Servo moves
   │
   ▼
Gate opens/closes
   │
   ▼
Press again
   │
   ▼
Gate changes state
```

---

# 🔍 9. Troubleshooting

| Problem | Possible Cause | What to Check |
|---|---|---|
| Servo does not move | Incorrect signal connection | Check **D9 → Servo Signal** |
| Servo does not power up | Power problem | Check **5V and GND** |
| Button does not respond | Incorrect wiring | Check **D2 → Button → GND** |
| Button logic appears reversed | `INPUT_PULLUP` is active LOW | Pressed = LOW, released = HIGH |
| Servo jitters | Power instability or mechanical load | Check supply and gate mechanism |
| Arduino resets when servo moves | Servo current demand is too high | Consider external 5V supply |
| Servo hits the gate stop | Angle too large | Reduce servo angle |
| Gate does not move smoothly | Mechanical friction | Reposition horn/linkage |
| Servo moves in wrong direction | Mechanical geometry | Change servo angle mapping or linkage |
| Servo moves but gate does not | Loose horn/mechanical connection | Secure servo horn and gate |

---

# ⚠️ 10. Important Electrical Notes

### Common Ground

The Arduino and servo must share the same ground reference:

```text
Arduino GND
     │
     ├────────► Servo GND
     │
     └────────► Button GND
```

### Servo Load

Do not assume that every servo can be safely powered directly from an Arduino board.

A lightly loaded SG90 prototype is suitable for basic classroom experimentation, but larger loads require an appropriate external power source.

### Mechanical Load

Never force the servo against a physical stop.

```text
GOOD

Servo ───► Gate
           │
       moves freely


BAD

Servo ───► Gate
           │
           ▼
       HARD STOP
           ✕
```

---

# 🧩 11. Optional `INPUT_PULLUP` Wiring

Using the Arduino's internal pull-up resistor keeps the button circuit simple.

```text
Arduino D2
    │
    │
    ├───────────────┐
    │               │
 Internal        Push Button
 Pull-up             │
    │                │
    └───────────────►GND
```

The software configures:

```cpp
pinMode(2, INPUT_PULLUP);
```

Therefore:

```text
┌─────────────────────────────┐
│ Button released → HIGH      │
│ Button pressed  → LOW       │
└─────────────────────────────┘
```

No external pull-down resistor is required for this wiring arrangement.

---

# 📌 12. Quick Reference

```text
┌────────────────────────────────────┐
│        PROJECT 21 PIN MAP          │
├────────────────────────────────────┤
│ Push Button → D2                   │
│ Push Button → GND                  │
│                                    │
│ Servo Signal → D9                  │
│ Servo VCC    → 5V                  │
│ Servo GND    → GND                 │
└────────────────────────────────────┘
```

### Core Wiring

```text
D2  → Push Button → GND

D9  → Servo Signal
5V  → Servo VCC
GND → Servo GND
```

---

# ✅ 13. Wiring Checklist

Before powering the project:

```text
☐ Push button connected to D2
☐ Push button connected to GND
☐ Servo signal connected to D9
☐ Servo VCC connected to 5V
☐ Servo GND connected to GND
☐ Arduino and servo share common GND
☐ Button is securely placed on the breadboard
☐ Servo horn is securely attached
☐ Gate mechanism moves freely
☐ Servo is not mechanically overloaded
☐ Servo angle limits have been considered
☐ External power is used if the servo requires more current
```

---

# 🚪 Final Circuit Concept

```text
                  USER
                   │
                   │ Press
                   ▼
             ┌───────────┐
             │  BUTTON   │
             └─────┬─────┘
                   │
                   │ D2
                   ▼
             ┌───────────┐
             │  ARDUINO  │
             │    UNO    │
             └─────┬─────┘
                   │
                   │ D9
                   ▼
             ┌───────────┐
             │ SG90 SERVO│
             └─────┬─────┘
                   │
                   ▼
             🚪 GATE MOVES
```

> **Core concept:** The push button provides the **input**, the Arduino processes the input, and the SG90 servo provides the **physical action** by opening or closing the gate.
