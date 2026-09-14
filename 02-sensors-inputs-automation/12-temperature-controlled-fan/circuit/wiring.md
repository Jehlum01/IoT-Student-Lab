# Project 12 — Temperature-Controlled Fan Wiring

## Components

- Arduino Uno
- LM35 temperature sensor
- Small low-voltage DC fan
- Logic-level N-channel MOSFET or suitable transistor driver
- Flyback diode
- External power supply suitable for the fan
- Breadboard
- Jumper wires

## LM35

| LM35 | Arduino |
|---|---|
| VCC | 5V |
| OUT | A0 |
| GND | GND |

Check the datasheet/pinout of the exact LM35 package before powering it.

## Fan Driver

The Arduino controls the fan through a transistor/MOSFET driver.

Conceptually:

```text
Arduino D8
    │
    ▼
MOSFET / Transistor Driver
    │
    ▼
DC Fan
    │
    ▼
External Fan Supply
