# Project 08 — LED Toggle Wiring

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
D8 → 220 Ω resistor → LED anode
LED cathode → GND

##Button
D2 → Push button → GND

The button uses:

INPUT_PULLUP

Therefore:

Released → HIGH
Pressed  → LOW
##Behaviour

Unlike Project 07, the LED does not directly follow the button.

Instead, each button press changes the stored system state.

BUTTON PRESS
     ↓
Detect event
     ↓
Toggle state
     ↓
Update LED
Testing

Press and release the button.

Expected:

Press 1 → ON
Press 2 → OFF
Press 3 → ON
Press 4 → OFF

The LED should remain in its selected state after the button is released.
