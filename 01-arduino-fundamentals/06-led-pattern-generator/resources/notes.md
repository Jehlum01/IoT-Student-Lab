Binary Representation

The eight LEDs represent eight binary bits:

Bit:     7 6 5 4 3 2 1 0
LED:     8 7 6 5 4 3 2 1

Example:

Decimal: 5

Binary:  00000101

LED:       OFF OFF OFF OFF OFF ON OFF ON

Example:

Decimal: 255

Binary: 11111111

All eight LEDs are ON.
Important
Use one resistor per LED.
Check LED polarity.
Connect all LED cathodes to GND.
Do not connect LEDs directly to Arduino GPIO pins.

# Project 06 — Learning Note

## From Individual LEDs to Data
Earlier projects controlled LEDs individually.

Now we treat the LEDs as a group.

```text
Software Number
      ↓
Binary Pattern
      ↓
8 LED States
      ↓
Physical Display


2. Arrays

The LED pins are stored in one array:

const int LED_PINS[LED_COUNT] = {
  2, 3, 4, 5, 6, 7, 8, 9
};

This allows the same code to work with every LED.

3. Binary Numbers

Eight LEDs can represent an 8-bit number.

There are:

2^8 = 256

possible combinations.

That gives us values:

0 → 255
4. Examples
Decimal    Binary

0          00000000
1          00000001
2          00000010
3          00000011
4          00000100
5          00000101
10         00001010
15         00001111
128        10000000
255        11111111
5. bitRead()

The program uses:

bitRead(pattern, i)

This extracts an individual binary bit from the pattern.

For example:

pattern = 5

Binary = 00000101

Bit 0 = 1
Bit 1 = 0
Bit 2 = 1

Therefore the corresponding LEDs turn ON or OFF.

6. Experiments
Experiment 1

Change:

const int PATTERN_DELAY = 500;

to:

const int PATTERN_DELAY = 100;

Observe the faster pattern.

Experiment 2

Make the LEDs display only:

00000000
11111111
00000000
11111111
Experiment 3

Create a pattern sequence manually:

00000001
00000010
00000100
00001000
00010000
00100000
01000000
10000000

This creates a moving LED.

Challenge 1 — Reverse the Direction

Make the binary pattern appear to move from the opposite side.

Challenge 2 — Alternating Pattern

Create:

10101010
01010101
10101010
01010101
Challenge 3 — Knight Rider Pattern

Create a pattern that moves:

00000001
00000010
00000100
00001000
00010000
00100000
01000000
10000000
01000000
00100000
00010000
00001000
00000100
00000010
Challenge 4 — Binary Counter

Display the decimal value represented by the LEDs using the Serial Monitor.

For example:

Value: 0
Value: 1
Value: 2
Value: 3
...
Value: 255
Engineering Connection

Binary patterns are fundamental to digital electronics.

The same concept appears in:

digital displays
GPIO registers
microcontrollers
communication protocols
computer memory
LED matrices
shift registers
embedded control systems
