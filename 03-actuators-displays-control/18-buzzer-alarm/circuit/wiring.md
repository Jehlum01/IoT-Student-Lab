# Project 18 — Buzzer Alarm Wiring

## Components

| Component | Quantity |
|---|---:|
| Arduino Uno | 1 |
| Push button | 1 |
| LED | 1 |
| 220 Ω resistor | 1 |
| Small active buzzer | 1 |
| Breadboard | 1 |
| Jumper wires | As required |

---

## 1. Push Button Wiring

Connect the push button between **D2** and **GND**.

| Button Connection | Arduino |
|---|---|
| One side | **D2** |
| Other side | **GND** |

The program uses:

```cpp
pinMode(2, INPUT_PULLUP);
```

With `INPUT_PULLUP`:

```text
Button Released → HIGH
Button Pressed  → LOW
```

### Wiring

```text
Arduino D2
    │
    ▼
  BUTTON
    │
    ▼
   GND
```

> **Note:** `INPUT_PULLUP` uses the Arduino's internal pull-up resistor, so no external pull-up resistor is required.

---

## 2. LED Wiring

Connect the LED to **D8** through a **220 Ω resistor**.

```text
Arduino D8
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

| LED Connection | Arduino |
|---|---|
| D8 | 220 Ω resistor → LED anode |
| LED cathode | GND |

> ⚠️ **Important:** Do not connect the LED directly to D8. The 220 Ω resistor limits current and protects the LED and Arduino pin.

---

## 3. Buzzer Wiring

Use a **small active buzzer** suitable for Arduino GPIO control.

| Buzzer Terminal | Arduino |
|---|---|
| `+` | **D9** |
| `−` | **GND** |

```text
Arduino D9
    │
    ▼
  BUZZER (+)
  BUZZER (-)
    │
    ▼
   GND
```

> ⚠️ If the buzzer requires more current than the Arduino GPIO can safely provide, use a suitable **transistor/MOSFET driver circuit** and an appropriate external supply.

---

## 4. Complete Wiring Diagram

```text
                         ARDUINO UNO
                    ┌──────────────────┐
                    │                  │
             D2 ────┤ BUTTON INPUT     │
                    │                  │
             D8 ────┤ LED OUTPUT       │── 220 Ω ── LED ── GND
                    │                  │
             D9 ────┤ BUZZER OUTPUT    │──────────── Buzzer ── GND
                    │                  │
            GND ────┤ COMMON GROUND    │
                    │                  │
                    └──────────────────┘
```

### Pin Summary

| Arduino Pin | Connected Component | Purpose |
|---|---|---|
| **D2** | Push button | Alarm control input |
| **D8** | LED + 220 Ω resistor | Visual alarm |
| **D9** | Active buzzer | Audible alarm |
| **GND** | Button, LED, buzzer | Common return |

---

## 5. Operating Logic

Each button press toggles the alarm state:

```text
Button Press
     ↓
Toggle Alarm State
     ↓
 ┌───┴────┐
 ▼        ▼
ON       OFF
│         │
├─ LED ON ├─ LED OFF
└─ Buzzer ON
          └─ Buzzer OFF
```

### Expected Behavior

| Button Action | LED | Buzzer | Alarm |
|---|---|---|---|
| First press | ON | ON | ON |
| Second press | OFF | OFF | OFF |
| Third press | ON | ON | ON |

---

## 6. Quick Testing

1. Upload the program.
2. Open **Serial Monitor** at `9600` baud.
3. Press the button once.
4. Confirm the LED turns **ON** and buzzer sounds.
5. Press the button again.
6. Confirm both turn **OFF**.
7. Repeat several times.

---

## 7. Troubleshooting

### Alarm Does Not Activate

Check:

- Button connection to **D2**
- Common **GND**
- `INPUT_PULLUP` configuration
- LED polarity
- 220 Ω resistor
- D8 and D9 connections

### Alarm Activates Multiple Times

Check:

- Button wiring
- Button orientation
- **Debouncing** in the program

One physical press should produce **one toggle**.

### Buzzer Does Not Sound

Check:

- Buzzer polarity
- Buzzer type — it should be an **active buzzer**
- D9 connection
- GND connection
- Buzzer current requirement

If the LED works but the buzzer does not, the buzzer may require a **driver circuit** or may be a different type.

---

## ⚠️ Wiring Checklist

- [ ] Button → **D2 + GND**
- [ ] LED → **D8 through 220 Ω resistor**
- [ ] LED cathode → **GND**
- [ ] Buzzer `+` → **D9**
- [ ] Buzzer `−` → **GND**
- [ ] All grounds connected correctly
- [ ] Check polarity before powering the circuit

---

**Project 18 · Buzzer Alarm**  
*Connect → Test → Toggle → Observe*
