# Project 09 — Automatic Night Lamp Wiring

## Components

- Arduino Uno
- LDR (photoresistor)
- 10 kΩ resistor
- LED
- 220 Ω resistor
- Breadboard
- Jumper wires

## Pin Mapping

| Component | Arduino |
|---|---:|
| LDR voltage divider | A0 |
| LED | D8 |

---

## LDR Voltage Divider

Use the LDR and 10 kΩ resistor as a voltage divider.

```text
5V
 │
[LDR]
 │
 ├──────────── A0
 │
[10kΩ]
 │
GND

(Arduino D8 ── 220Ω ──► LED ──► GND)

#LED
D8 → 220 Ω resistor → LED anode (+)
LED cathode (-) → GND
