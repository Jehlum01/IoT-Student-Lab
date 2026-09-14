# Project 07 — Learning Notes

## Core Idea

This project introduces the fundamental embedded-system relationship:

INPUT → PROCESSING → OUTPUT

The button provides the input.

The Arduino processes the input.

The LED provides the output.

---

## Digital Input

A digital input has two basic states:

HIGH
LOW

Arduino reads a digital input with:

```cpp
digitalRead(BUTTON_PIN);

INPUT_PULLUP

This project uses:

pinMode(BUTTON_PIN, INPUT_PULLUP);

The Arduino's internal pull-up resistor keeps the input HIGH when the button is released.

Pressing the button connects the input to GND.

Therefore:

Released → HIGH
Pressed  → LOW

This is called active-low input logic.

Decision Making

The program checks:

if (buttonState == LOW)

If the condition is true:

digitalWrite(LED_PIN, HIGH);

Otherwise:

digitalWrite(LED_PIN, LOW);
Experiment 1

Change the program so the LED is:

OFF when button is pressed
ON when button is released

What needs to change in the if statement?

Experiment 2

Move the LED from D8 to D7.

Change the pin definition:

const int LED_PIN = 7;

Does the program still work?

Experiment 3

Add a second LED.

Try controlling both LEDs from the same button.

Challenge

Make the button control two LEDs:

Button released:
LED 1 ON
LED 2 OFF

Button pressed:
LED 1 OFF
LED 2 ON
Think Like an Engineer

Ask:

What happens if the button is disconnected?
Why does the button read LOW when pressed?
Why don't we need an external resistor?
What happens if the LED resistor is removed?
What is the difference between INPUT and OUTPUT?
Key Takeaway

The microcontroller can now interact with the physical world:

Physical Input
      ↓
   Read
      ↓
   Decide
      ↓
  Physical Output

This is the foundation of automation.
