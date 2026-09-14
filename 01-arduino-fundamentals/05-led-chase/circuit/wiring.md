# Project 05 — LED Chase Wiring

## Components

- Arduino Uno
- 6 × LEDs
- 6 × 220 Ω resistors
- Breadboard
- Jumper wires

## Pin Mapping

| LED | Arduino Pin |
|---|---:|
| LED 1 | D8 |
| LED 2 | D9 |
| LED 3 | D10 |
| LED 4 | D11 |
| LED 5 | D12 |
| LED 6 | D13 |

## Connections

Each LED must have its own 220 Ω resistor.

```text
Arduino D8  → 220Ω → LED 1 → GND
Arduino D9  → 220Ω → LED 2 → GND
Arduino D10 → 220Ω → LED 3 → GND
Arduino D11 → 220Ω → LED 4 → GND
Arduino D12 → 220Ω → LED 5 → GND
Arduino D13 → 220Ω → LED 6 → GND

LED polarity:

Long leg = anode (+)
Short leg = cathode (-)
Cathodes connect toward GND.
Important

Use a separate resistor for every LED.

Do not connect LEDs directly between GPIO pins and GND.

Testing

After uploading:

LED 1 should turn ON.
LED 1 turns OFF and LED 2 turns ON.
The active LED moves toward LED 6.
The sequence reverses.
The pattern repeats continuously.
