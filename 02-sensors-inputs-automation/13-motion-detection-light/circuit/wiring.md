# Project 13 — Motion Detection Light Wiring

## Components

- Arduino Uno
- PIR motion sensor
- LED
- 220Ω resistor
- Breadboard
- Jumper wires

## PIR Connections

For a common HC-SR501 PIR module:

| PIR Pin | Arduino |
|---|---|
| VCC | 5V |
| OUT | D2 |
| GND | GND |

> Check the pin labels on the exact PIR module being used.

## LED Connections

| Component | Connection |
|---|---|
| Arduino D8 | 220Ω resistor |
| Resistor | LED anode (+) |
| LED cathode (-) | GND |

## Complete Connection

```text
             PIR SENSOR
           +-------------+
      5V --| VCC         |
      D2 --| OUT         |
     GND --| GND         |
           +-------------+

                 │
                 │ Motion Signal
                 ▼

             ARDUINO UNO
           +-------------+
           |             |
        D2 | PIR INPUT   |
           |             |
        D8 | LED OUTPUT  |──── 220Ω ──── LED ──── GND
           |             |
           +-------------+
