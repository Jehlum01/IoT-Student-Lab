# Project 14 — Automatic Security
 Alarm Wiring

## Components

- Arduino Uno
- PIR motion sensor
- LED
- 220Ω resistor
- Active buzzer
- Breadboard
- Jumper wires

## PIR Sensor

For a common HC-SR501 PIR module:

| PIR Pin | Arduino |
|---|---|
| VCC | 5V |
| OUT | D2 |
| GND | GND |

Check the labels/pinout of the exact PIR module being used.

## LED

| Connection | Destination |
|---|---|
| Arduino D8 | 220Ω resistor |
| Resistor | LED anode (+) |
| LED cathode (-) | GND |

## Buzzer

For a small active buzzer suitable for direct GPIO control:

| Buzzer | Arduino |
|---|---|
| + | D9 |
| - | GND |

> If the buzzer requires more current than the Arduino GPIO can safely provide, use a transistor driver instead.

## System Diagram

```text
                    PIR SENSOR
                  +-------------+
             5V --| VCC         |
            D2 ---| OUT         |
            GND --| GND         |
                  +------+------+
                         |
                         | Motion signal
                         ▼
                  +-------------+
                  | ARDUINO UNO |
                  |             |
                  | D2  INPUT   |
                  |             |
                  | D8  OUTPUT  |---- 220Ω ---- LED ---- GND
                  |             |
                  | D9  OUTPUT  |------------- BUZZER -- GND
                  +-------------+
