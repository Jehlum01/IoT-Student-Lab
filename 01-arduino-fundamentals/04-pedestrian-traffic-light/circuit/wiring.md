# Pedestrian Traffic Light — Wiring

## Components

- Arduino Uno
- Red LED
- Yellow LED
- Green LED
- 3 × 220 Ω resistors
- Push button
- Breadboard
- Jumper wires

---

## Traffic Light Connections

| Component | Arduino Pin | Connection |
|---|---:|---|
| Red LED | D8 | D8 → 220 Ω → LED anode |
| Yellow LED | D9 | D9 → 220 Ω → LED anode |
| Green LED | D10 | D10 → 220 Ω → LED anode |
| LED cathodes | GND | Cathode → GND |

Each LED must have its own current-limiting resistor.

---

## Push Button

The push button uses Arduino's internal pull-up resistor.

| Button connection | Arduino |
|---|---|
| One side | D2 |
| Other side | GND |

The code uses:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);


                         Arduino UNO

             D8 ── 220Ω ──► RED LED ──► GND

             D9 ── 220Ω ──► YELLOW LED ──► GND

            D10 ── 220Ω ──► GREEN LED ──► GND


             D2 ───────────┐
                           │
                       [ PUSH BUTTON ]
                           │
                           └────────── GND
