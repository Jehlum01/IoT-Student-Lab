# Project 15 — Learning Notes

## The Big Idea

This project combines:

- Digital input
- Button interaction
- Randomness
- Multiple outputs
- Pattern generation
- State-based display

The student presses one button and the Arduino produces a simulated dice roll.

```text
Button
   ↓
Detect Press
   ↓
Generate Random Number
   ↓
1–6
   ↓
Select LED Pattern
   ↓
Display Result
Random Numbers

The program uses:

random(1, 7);

Arduino's random() function generates a value from:

1, 2, 3, 4, 5, 6

The upper limit is exclusive.

Therefore:

random(1, 7)

can produce 1 through 6.

Why randomSeed()?

The program uses:

randomSeed(analogRead(A0));

to initialize the pseudo-random sequence using an analog reading.

This makes repeated power cycles less likely to produce the exact same sequence.

Button Events

The program does not simply ask:

if (button == LOW)

Instead it compares the previous and current button states.

Previous → HIGH
Current  → LOW

represents a new press.

This is called detecting an edge or transition.

Debouncing

Mechanical buttons can produce several rapid electrical transitions when pressed.

The program uses a short delay after detecting a press:

delay(DEBOUNCE_DELAY);

This is a simple debounce technique.

More advanced systems can implement non-blocking debouncing using millis().

Pattern Mapping

The dice value determines which LEDs are switched ON.

For example:

Value 1 → center LED

Value 2 → two diagonal LEDs

Value 3 → two diagonal LEDs + center

...

The Arduino is therefore converting a numerical value into a visual pattern.

Why Arrays?

The LED pins are stored in:

const int LED_PINS[LED_COUNT]

An array lets the program treat the seven LEDs as a group.

This makes the code easier to scale and modify.

Experiment 1 — Add a Rolling Animation

Before displaying the final result, create a short animation.

For example:

Pattern
   ↓
Pattern
   ↓
Pattern
   ↓
Final result
Experiment 2 — Change the Speed

Make the dice appear to roll for approximately one second before stopping.

Think about how many patterns should be displayed during the animation.

Experiment 3 — Add a Buzzer

Make the buzzer produce a short sound when the dice is rolled.

Experiment 4 — Two Dice

Duplicate the concept to create two dice.

Students will need to think about:

Additional LEDs
Additional pins
Multiple random values
Multiple displays
Total score
Challenge

Build a two-dice system.

Display:

Dice 1: 4
Dice 2: 6
Total: 10

on the Serial Monitor.

The LED displays should independently show both dice.

Real-World Connection

The underlying concept appears in:

User interfaces
Digital displays
Status indicators
Game controllers
Embedded control panels
Instrumentation
Pattern-based signaling

The important lesson is not the dice itself.

The important lesson is:

Input → Data → Processing → Output

Learning Outcome

Students should understand:

Button event detection
Debouncing
Random number generation
Arrays
Multiple GPIO outputs
Pattern mapping
Converting data into visual feedback
