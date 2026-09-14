# Project 10 — Smart Street Light Wiring

## Components

- Arduino Uno
- LDR
- 10 kΩ resistor
- 3 × LEDs
- 3 × 220 Ω resistors
- Breadboard
- Jumper wires

## Pin Mapping

| Component | Arduino Pin |
|---|---:|
| LDR voltage divider | A0 |
| Street Light 1 | D8 |
| Street Light 2 | D9 |
| Street Light 3 | D10 |

## LDR Voltage Divider

```text
5V
 │
[LDR]
 │
 ├──────── A0
 │
[10kΩ]
 │
GND

## Street Lights
D8  → 220Ω → LED 1 → GND
D9  → 220Ω → LED 2 → GND
D10 → 220Ω → LED 3 → GND

Every LED requires its own resistor.

## System
              LIGHT
                ↓
               LDR
                ↓
             A0 INPUT
                ↓
          analogRead()
                ↓
            THRESHOLD
             ↙      ↘
          DARK      BRIGHT
            ↓          ↓
       3 LIGHTS ON   ALL OFF

##Testing
1. Upload the program.
2. Open Serial Monitor at 9600 baud.
3. Observe the LDR value.
4. Expose the LDR to light.
5. Cover the LDR.
6. All three LEDs should turn ON in darkness.
7. All three LEDs should turn OFF in bright conditions.
8. Adjust DARK_THRESHOLD if required.

##Safety
1. Use one resistor per LED.
2. Check LED polarity.
3. Do not connect real mains-powered street lights to Arduino GPIO pins.
4. This project controls low-voltage LEDs only.
