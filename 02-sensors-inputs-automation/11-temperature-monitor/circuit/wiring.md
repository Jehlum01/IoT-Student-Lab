# Project 11 — Temperature Monitor Wiring

## Component

- Arduino Uno
- LM35 temperature sensor
- Breadboard
- Jumper wires

## LM35 Connections

With the flat/front side of a common LM35 package facing you:

| LM35 Pin | Connection |
|---|---|
| Left pin | Arduino 5V |
| Middle pin | Arduino A0 |
| Right pin | Arduino GND |

> Check the datasheet or markings of the exact sensor package being used before powering it. Pin arrangements can vary between temperature-sensor packages.

## Signal Flow

```text
Temperature
     ↓
   LM35
     ↓
 Analog Voltage
     ↓
 Arduino A0
     ↓
 analogRead()
     ↓
 ADC Value
     ↓
 Voltage Calculation
     ↓
 Temperature Calculation
     ↓
 Serial Monitor
