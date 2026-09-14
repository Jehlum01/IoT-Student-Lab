# Project 08 — Learning Notes

## Direct Control vs Toggle Control

Project 07:

```text
Button pressed  → LED ON
Button released → LED OFF

##Project 08:

Button press → Change LED state

The LED remembers its state after the button is released.

##State Variable

The program uses:

bool ledState = false;

A Boolean can have two values:

false
true

These represent:

false → OFF
true  → ON
Toggle Logic

The key instruction is:

ledState = !ledState;

The ! operator means NOT.

Therefore:

false → !false → true
true  → !true  → false
Detecting an Event

The program remembers the previous button state:

bool lastButtonState = HIGH;

Then compares it with the current state.

if (lastButtonState == HIGH && currentButtonState == LOW)

This means:

Previously released
        +
Now pressed
        =
NEW BUTTON PRESS

This is called edge/event detection.

Why Not Just Check LOW?

If we simply wrote:

if (digitalRead(BUTTON_PIN) == LOW)

the program would repeatedly toggle while the button remained pressed.

Instead, we detect the transition:

HIGH → LOW
Experiment 1

Remove:

delay(50);

Test the circuit.

Observe whether the button behaves differently.

Experiment 2

Change the debounce delay:

delay(100);

Then:

delay(200);

##Compare the behaviour.

Challenge 1

Add a second LED.

Make the LEDs alternate:

Press 1:
LED 1 ON
LED 2 OFF

Press 2:
LED 1 OFF
LED 2 ON
Challenge 2

Add a third state:

OFF → RED → GREEN → OFF

Now the button cycles through three states instead of two.

Engineering Connection

Toggle/event logic is common in:

light switches
control panels
user interfaces
machine controls
industrial equipment
digital counters
menu systems

The important transition is:

INPUT
 ↓
EVENT
 ↓
STATE CHANGE
 ↓
OUTPUT
Key Takeaway

A system does not always need to directly mirror an input.

It can remember what happened and maintain its own state.
