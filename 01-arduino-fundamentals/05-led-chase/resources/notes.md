# Project 05 — Learning Notes

## Main Concept

This project introduces loops for controlling multiple outputs efficiently.

Instead of writing:

```cpp
digitalWrite(8, HIGH);
delay(100);
digitalWrite(8, LOW);

digitalWrite(9, HIGH);
delay(100);
digitalWrite(9, LOW);

we can use a loop.

Array

The LED pins are stored in:

const int LED_PINS[LED_COUNT] = {
  8, 9, 10, 11, 12, 13
};

The program can then access each pin using an index.

For Loop
for (int i = 0; i < LED_COUNT; i++) {
    ...
}

The loop automatically moves through all six LEDs.

Why Loops Matter

Loops allow the same operation to be repeated without duplicating code.

This makes programs:

shorter
easier to modify
easier to maintain
easier to scale
Experiments

Try changing:

const int STEP_DELAY = 120;

Try:

const int STEP_DELAY = 50;

Then:

const int STEP_DELAY = 300;

Observe how the animation changes.

Challenge 1

Make the LEDs move only from left to right.

Challenge 2

Make two adjacent LEDs remain ON while moving.

Challenge 3

Create a pattern where all LEDs turn ON one by one and then turn OFF one by one.

Challenge 4

Change the number of LEDs.

Modify:

const int LED_COUNT

and update the pin array.

Engineering Connection

The same loop concept is useful when controlling:

LED displays
motor sequences
relay banks
sensor arrays
addressable LEDs
automation systems
Key Takeaway

Loops allow one piece of logic to control many hardware outputs.

Project progression:

Project 03
Multiple Outputs
      ↓
Project 04
Input + Conditions
      ↓
Project 05
Loops + Multiple GPIOs
