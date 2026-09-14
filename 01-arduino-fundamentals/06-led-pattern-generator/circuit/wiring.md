# Project 06 — LED Pattern Generator Wiring

## Components

- Arduino Uno
- 8 × LEDs
- 8 × 220 Ω resistors
- Breadboard
- Jumper wires

## Pin Mapping

| LED | Arduino Pin | Binary Bit |
|---|---:|---:|
| LED 1 | D2 | Bit 0 |
| LED 2 | D3 | Bit 1 |
| LED 3 | D4 | Bit 2 |
| LED 4 | D5 | Bit 3 |
| LED 5 | D6 | Bit 4 |
| LED 6 | D7 | Bit 5 |
| LED 7 | D8 | Bit 6 |
| LED 8 | D9 | Bit 7 |

## Connections

Every LED requires its own resistor.

```text
D2 → 220Ω → LED 1 → GND
D3 → 220Ω → LED 2 → GND
D4 → 220Ω → LED 3 → GND
D5 → 220Ω → LED 4 → GND
D6 → 220Ω → LED 5 → GND
D7 → 220Ω → LED 6 → GND
D8 → 220Ω → LED 7 → GND
D9 → 220Ω → LED 8 → GND
