# Project 20 — Parking Sensor Wiring

> 🚗 **Build a simple Arduino-based parking/proximity indicator using an HC-SR04 ultrasonic sensor, three LEDs, and an active buzzer.**

---

## 🔌 Components

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main controller |
| HC-SR04 Ultrasonic Sensor | 1 | Measures distance |
| 🟢 Green LED | 1 | Safe-zone indicator |
| 🟡 Yellow LED | 1 | Caution-zone indicator |
| 🔴 Red LED | 1 | Warning-zone indicator |
| 220 Ω Resistor | 3 | Limits LED current |
| Active Buzzer | 1 | Audible warning |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | As required | Electrical connections |

---

# 📍 Pin Mapping

| Component | Pin | Arduino Uno | Purpose |
|---|---|---|---|
| HC-SR04 | VCC | **5V** | Power |
| HC-SR04 | TRIG | **D8** | Trigger pulse |
| HC-SR04 | ECHO | **D9** | Echo timing |
| HC-SR04 | GND | **GND** | Common ground |
| Buzzer | + | **D10** | Buzzer control |
| Buzzer | − | **GND** | Ground |
| Green LED | Anode (+) | **D11 through 220 Ω** | SAFE |
| Yellow LED | Anode (+) | **D12 through 220 Ω** | CAUTION |
| Red LED | Anode (+) | **D13 through 220 Ω** | WARNING |
| LEDs | Cathode (−) | **GND** | Ground |

---

# 🧭 Complete Wiring Overview

```text
                         ARDUINO UNO
                  ┌──────────────────────┐
                  │                      │
              5V ─┤──────────────────► VCC
             GND ─┤──────────────┬───► GND
                  │              │
             D8 ─┤──────────────┼───► TRIG
                  │              │
             D9 ◄─┤──────────────┼──── ECHO
                  │              │
            D10 ──┤──────────────┼───► BUZZER (+)
                  │              │
            D11 ──┤──► 220 Ω ───┼───► 🟢 GREEN
                  │              │
            D12 ──┤──► 220 Ω ───┼───► 🟡 YELLOW
                  │              │
            D13 ──┤──► 220 Ω ───┼───► 🔴 RED
                  │              │
                  └──────────────┼──────
                                 │
                                 ▼
                                GND
```

---

# 📡 1. HC-SR04 Ultrasonic Sensor

The HC-SR04 has four pins:

```text
             HC-SR04
        ┌────────────────┐
        │                │
        │   ◯        ◯   │
        │                │
        └────────────────┘
           │   │   │   │
           │   │   │   │
          VCC TRIG ECHO GND
           │   │   │   │
           ▼   ▼   ▼   ▼
          5V  D8  D9  GND
```

### Connections

```text
HC-SR04 VCC  → Arduino 5V
HC-SR04 TRIG → Arduino D8
HC-SR04 ECHO → Arduino D9
HC-SR04 GND  → Arduino GND
```

### Ultrasonic Path

```text
       HC-SR04
          │
          │  Ultrasonic wave
          │  ))))))))))))))))))►
          │
          │                  ┌──────────┐
          └─────────────────►│  OBJECT  │
                             └──────────┘
          ◄((((((((((((((((((│
             Reflected wave
```

The sensor should face the target as directly as possible for more reliable measurements.

---

# 🟢 2. Green LED — SAFE

The green LED indicates that the object is at a safe distance.

```text
Arduino D11
     │
     ▼
  ┌───────┐
  │ 220 Ω │
  └───┬───┘
      │
      ▼
 LED Anode (+)
      │
   🟢 GREEN
      │
 LED Cathode (-)
      │
      ▼
     GND
```

### Connection

```text
D11 → 220 Ω resistor → Green LED Anode (+)
Green LED Cathode (-) → GND
```

---

# 🟡 3. Yellow LED — CAUTION

The yellow LED indicates that the object is getting closer.

```text
Arduino D12
     │
     ▼
  ┌───────┐
  │ 220 Ω │
  └───┬───┘
      │
      ▼
 LED Anode (+)
      │
   🟡 YELLOW
      │
 LED Cathode (-)
      │
      ▼
     GND
```

### Connection

```text
D12 → 220 Ω resistor → Yellow LED Anode (+)
Yellow LED Cathode (-) → GND
```

---

# 🔴 4. Red LED — WARNING

The red LED indicates that the object is very close.

```text
Arduino D13
     │
     ▼
  ┌───────┐
  │ 220 Ω │
  └───┬───┘
      │
      ▼
 LED Anode (+)
      │
    🔴 RED
      │
 LED Cathode (-)
      │
      ▼
     GND
```

### Connection

```text
D13 → 220 Ω resistor → Red LED Anode (+)
Red LED Cathode (-) → GND
```

---

# 🔊 5. Active Buzzer

For a small active buzzer:

```text
Arduino D10 ─────────► Buzzer (+)
Arduino GND ─────────► Buzzer (-)
```

### Wiring

```text
        Arduino
          │
         D10
          │
          ▼
      ┌─────────┐
      │   🔊    │
      │ BUZZER  │
      └────┬────┘
           │
           ▼
          GND
```

The Arduino can switch the buzzer according to the detected distance.

---

# 🚦 6. Parking Zone Logic

The circuit provides three visual proximity zones.

```text
                         DISTANCE
                            │
              ┌─────────────┼─────────────┐
              │             │             │
              ▼             ▼             ▼
           > 50 cm       20–50 cm       < 20 cm
              │             │             │
              ▼             ▼             ▼
         🟢 SAFE        🟡 CAUTION     🔴 WARNING
                                           │
                                           ▼
                                         🔊 ON
```

A typical implementation can use:

| Distance | Status | Output |
|---|---|---|
| **> 50 cm** | 🟢 SAFE | Green LED |
| **20–50 cm** | 🟡 CAUTION | Yellow LED |
| **< 20 cm** | 🔴 WARNING | Red LED + Buzzer |

> 💡 These thresholds are software decisions and can be changed during experimentation.

---

# 🧠 7. System Signal Flow

```text
        ┌─────────────┐
        │   HC-SR04   │
        │   SENSOR    │
        └──────┬──────┘
               │
               │ Distance
               ▼
        ┌─────────────┐
        │   ARDUINO   │
        │     UNO     │
        └──────┬──────┘
               │
       ┌───────┼────────┐
       │       │        │
       ▼       ▼        ▼
      🟢      🟡       🔴
     SAFE    CAUTION  WARNING
                         │
                         ▼
                       🔊
```

The overall control process is:

```text
Measure
   ↓
Calculate distance
   ↓
Compare with thresholds
   ↓
Determine zone
   ↓
Control LED / buzzer
   ↓
Repeat
```

---

# 💡 8. Why Use 220 Ω Resistors?

Each LED needs a current-limiting resistor.

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

The resistor limits the current flowing through the LED and helps protect both the LED and the Arduino GPIO.

> ⚠️ **Do not connect an LED directly to an Arduino GPIO without appropriate current limiting.**

---

# ⚠️ 9. Buzzer and GPIO Warning

A small active buzzer may be connected directly to a GPIO **only when its electrical requirements are suitable for the Arduino output**.

Do **not** directly drive:

- Automotive buzzers
- Motors
- Large speakers
- High-current loads
- Other devices that exceed GPIO current limits

```text
Small suitable buzzer
        │
        ▼
 Arduino GPIO
        ✓


High-current load
        │
        ▼
 Arduino GPIO
        ✗
```

For a higher-current load, use an appropriate **transistor/MOSFET driver circuit** and suitable external power.

---

# 🧪 10. Testing Procedure

After completing the wiring:

1. Check every connection.
2. Confirm that all LED resistors are installed.
3. Verify LED polarity.
4. Verify that Arduino and HC-SR04 share GND.
5. Upload the parking-sensor program.
6. Place an object in front of the HC-SR04.
7. Move the object slowly toward the sensor.
8. Observe the LED changes.
9. Check the buzzer behavior.
10. Move the object away and verify that the system returns through the zones.

### Suggested Test Points

```text
100 cm ─────────────── 🟢 SAFE

 75 cm ─────────────── 🟢 SAFE

 50 cm ─────────────── 🟡 CAUTION

 30 cm ─────────────── 🟡 CAUTION

 20 cm ─────────────── 🟡/🔴 boundary

 10 cm ─────────────── 🔴 WARNING + 🔊
```

---

# 🔍 11. Troubleshooting

| Problem | Possible Cause | Check |
|---|---|---|
| No distance reading | Sensor not powered | Check VCC and GND |
| No echo | Incorrect sensor wiring | Check TRIG → D8 and ECHO → D9 |
| LEDs do not light | Incorrect polarity | Check anode and cathode |
| LED is very bright / excessive current | Missing resistor | Add 220 Ω resistor |
| Buzzer does not work | Wrong polarity or buzzer type | Check +/− and confirm it is an active buzzer |
| Buzzer behaves unexpectedly | Load too demanding | Use an appropriate driver |
| Wrong LED activates | Threshold/logic error | Check distance conditions |
| Unstable distance | Poor reflection | Use a flat target facing the sensor |
| Everything is inactive | Missing common ground | Verify GND connections |

---

# 🛠️ 12. Wiring Checklist

Before powering the project:

```text
☐ HC-SR04 VCC  → 5V
☐ HC-SR04 GND  → GND
☐ HC-SR04 TRIG → D8
☐ HC-SR04 ECHO → D9

☐ Buzzer + → D10
☐ Buzzer - → GND

☐ D11 → 220 Ω → Green LED → GND
☐ D12 → 220 Ω → Yellow LED → GND
☐ D13 → 220 Ω → Red LED → GND

☐ All three LEDs have 220 Ω resistors
☐ LED polarity is correct
☐ Arduino and sensor share GND
☐ Buzzer current requirement is suitable
☐ HC-SR04 faces the target
☐ No high-current load is connected directly to GPIO
```

---

# 📌 Quick Reference

```text
┌──────────────────────────────────────┐
│        PROJECT 20 PIN MAP            │
├──────────────────────────────────────┤
│ HC-SR04 VCC   → 5V                   │
│ HC-SR04 TRIG  → D8                   │
│ HC-SR04 ECHO  → D9                   │
│ HC-SR04 GND   → GND                  │
│                                      │
│ Buzzer +      → D10                  │
│ Buzzer -      → GND                  │
│                                      │
│ Green LED     → D11 + 220 Ω          │
│ Yellow LED    → D12 + 220 Ω          │
│ Red LED       → D13 + 220 Ω          │
│                                      │
│ LED cathodes → GND                   │
└──────────────────────────────────────┘
```

---

## 🚗 Final Circuit Concept

```text
                 OBJECT
                   ▲
                   │
            Ultrasonic waves
                   │
                   ▼
              ┌─────────┐
              │ HC-SR04 │
              └────┬────┘
                   │
              Distance data
                   │
                   ▼
             ┌───────────┐
             │ ARDUINO   │
             │    UNO    │
             └─────┬─────┘
                   │
          ┌────────┼────────┐
          │        │        │
          ▼        ▼        ▼
        🟢 LED   🟡 LED   🔴 LED
        SAFE     CAUTION  WARNING
                              │
                              ▼
                            🔊
                          BUZZER
```

> **Core wiring principle:** The HC-SR04 provides the distance information, the Arduino interprets that information, and the LEDs/buzzer provide feedback to the user.

---

