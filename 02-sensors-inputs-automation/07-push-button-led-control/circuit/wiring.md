# Project 07 — Push Button LED Control Wiring

## Components

- Arduino Uno
- Push button
- LED
- 220 Ω resistor
- Breadboard
- Jumper wires

## Pin Mapping

| Component | Arduino Pin |
|---|---:|
| Push button | D2 |
| LED | D8 |

## LED

```text
Arduino D8 → 220 Ω resistor → LED anode (+)
LED cathode (-) → GND


##Push Button

Connect the button:

Button terminal 1 → Arduino D2
Button terminal 2 → GND

The program uses:

pinMode(BUTTON_PIN, INPUT_PULLUP);

Therefore:

Button released → HIGH
Button pressed  → LOW

No external pull-up resistor is required.

##System
       PUSH BUTTON
            │
            ↓
       Arduino D2
            │
       digitalRead()
            │
            ↓
       if condition
            │
            ↓
       Arduino D8
            │
            ↓
           LED
Testing
Upload the program.
Leave the button released.
LED should remain OFF.
Press the button.
LED should turn ON.
Release the button.
LED should turn OFF.
Important
Check LED polarity.
Use the 220 Ω resistor.
Connect the button to D2 and GND.
Do not connect the LED directly to D8.
