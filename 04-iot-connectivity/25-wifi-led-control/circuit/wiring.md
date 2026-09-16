# 🔌 Project 25 — ESP32 Wi-Fi LED Control Wiring

## 1. Hardware

- ESP32 development board
- LED
- 220Ω current-limiting resistor
- Breadboard
- Jumper wires
- USB cable

## 2. Pin Mapping

| ESP32 Pin | Connection | Purpose |
|---|---|---|
| GPIO 5 | LED through 220Ω resistor | LED output |
| GND | LED cathode | Return path |
| USB | Computer/USB power | Power + programming |

## 3. LED Wiring

```text
ESP32 GPIO 5
      │
      ▼
   [220Ω]
      │
      ▼
 LED Anode (+)
 LED Cathode (-)
      │
      ▼
     GND
```

The resistor limits current through the LED.

## 4. Complete Wiring

```mermaid
flowchart LR
    ESP[ESP32]
    GPIO[GPIO 5]
    R[220Ω Resistor]
    LED[LED]
    GND[GND]

    ESP --> GPIO
    GPIO --> R
    R --> LED
    LED --> GND
```

## 5. Physical Arrangement

```text
┌───────────────────────────────────┐
│             BREADBOARD            │
│                                   │
│ GPIO 5 ───► [220Ω] ───► LED ───┐ │
│                                 │ │
│ GND ────────────────────────────┘ │
└───────────────────────────────────┘
              │
              ▼
         ┌──────────┐
         │   ESP32  │
         └──────────┘
```

Keep the LED and resistor connections short and easy to inspect.

## 6. LED Polarity

A typical through-hole LED has:

```text
Longer leg  → Anode (+)
Shorter leg → Cathode (-)
```

The flat edge on many LEDs also identifies the cathode, but physical construction varies. Use the LED's markings/datasheet when uncertain.

The intended connection is:

```text
GPIO 5 → resistor → LED anode
LED cathode → GND
```

## 7. Logic Levels

ESP32 GPIO uses **3.3V logic**.

```text
GPIO HIGH → approximately 3.3V logic level
GPIO LOW  → approximately 0V
```

Do not connect a 5V signal directly to an ESP32 GPIO.

## 8. Power

The ESP32 is powered/programmed through USB.

The LED circuit uses the ESP32 GPIO and GND.

```text
USB
 │
 ▼
ESP32
 │
 ├── GPIO 5 ──► resistor ──► LED
 │
 └── GND ──────────────────► LED
```

## 9. Wiring Checklist

- [ ] ESP32 powered through USB
- [ ] GPIO 5 identified correctly
- [ ] 220Ω resistor installed
- [ ] LED polarity checked
- [ ] LED cathode connected to GND
- [ ] No direct GPIO-to-5V connection
- [ ] No short between GPIO and GND
- [ ] Breadboard rows checked

## 10. Common Wiring Errors

| Error | Likely result |
|---|---|
| LED reversed | LED does not illuminate |
| Missing resistor | Excessive LED current risk |
| Wrong GPIO | Software controls a different pin |
| No GND | Circuit does not operate correctly |
| 5V connected to GPIO | Possible ESP32 damage |
| Loose jumper | Intermittent LED behavior |

## 11. Build Order

```text
Place ESP32
    ↓
Place 220Ω resistor
    ↓
Place LED
    ↓
Connect GPIO 5 → resistor → LED
    ↓
Connect LED → GND
    ↓
Inspect polarity
    ↓
Power ESP32
    ↓
Test GPIO
    ↓
Test Wi-Fi control
```
