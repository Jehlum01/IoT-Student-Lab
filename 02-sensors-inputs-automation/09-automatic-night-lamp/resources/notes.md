# Project 09 — Learning Notes

## Core Concept

Unlike a push button, an LDR does not simply provide ON/OFF information.

It provides a variable electrical signal.

```text
LIGHT
  ↓
LDR
  ↓
Voltage Divider
  ↓
Analog Pin
  ↓
analogRead()
  ↓
Sensor Value
  ↓
Threshold
  ↓
LED


What is an LDR?

LDR means:

Light Dependent Resistor

Its resistance changes depending on the amount of light falling on it.

The Arduino cannot directly measure resistance.

The voltage divider converts the resistance change into a voltage that the analog input can measure.

analogRead()

Arduino reads the analog input using:

analogRead(A0);

On the Arduino Uno, this produces a value in the approximate range:

0 → 1023

The exact value depends on the voltage present at the analog input.

Threshold

The program defines:

const int DARK_THRESHOLD = 500;

Then:

if (lightLevel < DARK_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
}

The threshold is the decision boundary.

Sensor Value
      │
      ├── Below threshold → DARK → LED ON
      │
      └── Above threshold → LIGHT → LED OFF
Calibration

There is no universal perfect threshold.

Students should first observe the Serial Monitor.

Record:

Bright environment: ______

Normal room:         ______

Dark environment:   ______

Then choose a threshold appropriate for the environment.

Experiment 1

Change:

const int DARK_THRESHOLD = 500;

Try:

300

Then:

700

Observe when the LED turns ON.

##Experiment 2

Cover the LDR completely.

Record the sensor value.

Then expose it to strong light.

Compare both readings.

##Key Takeaway

A sensor does not have to produce a simple ON/OFF signal.

It can provide a continuous range of values that software can interpret and use to make decisions.
