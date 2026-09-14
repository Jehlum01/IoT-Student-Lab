# Project 10 — Learning Notes

## Core Concept

Project 09 controlled one lamp using an LDR.

Project 10 scales the same idea to multiple outputs.

```text
LDR
 ↓
Measure Light
 ↓
Compare with Threshold
 ↓
Make Decision
 ↓
Control Multiple Lights

Sensor + Multiple Outputs

The Arduino reads one sensor:

int lightLevel = analogRead(LDR_PIN);

Then controls three outputs.

This demonstrates that one input can control an entire system.

Threshold Logic
if (lightLevel < DARK_THRESHOLD)

means:

Sensor value below threshold
          ↓
       DARK
          ↓
Street lights ON

Otherwise:

Sensor value above threshold
          ↓
      BRIGHT
          ↓
Street lights OFF
Calibration

The threshold is not universal.

Use the Serial Monitor to record:

Bright: ______

Room light: ______

Dark: ______

Then select a suitable threshold.

Experiment 1 — Change Threshold

Try:

const int DARK_THRESHOLD = 300;

Then:

const int DARK_THRESHOLD = 700;

Observe how the switching point changes.

Experiment 2 — Add a Fourth Light

Add another LED on D11.

Modify allLightsOff() and the dark-state logic.

Challenge 1 — Staged Lighting

Instead of switching all three LEDs together, create:

Bright:
All OFF

Medium:
1 light ON

Dark:
3 lights ON

You will need two thresholds.

For example:

BRIGHT_THRESHOLD
DARK_THRESHOLD
Challenge 2 — Street-Light Animation

When darkness is detected, turn the lights ON one after another.

Example:

Light 1 → Light 2 → Light 3
Challenge 3 — Energy Saving

Create a system where:

Dark → all lights ON
Bright → all lights OFF

Then consider how real street-light systems could reduce energy consumption.

Engineering Connection

The same basic architecture appears in:

street lighting
building automation
parking-area lighting
warehouse lighting
garden lighting
smart-city infrastructure

A real system may add:

motion sensors
real-time clocks
wireless communication
power monitoring
dimming
centralized monitoring

But the fundamental control loop remains:

SENSE → DECIDE → ACT

##Key Takeaway
A sensor can control multiple outputs.
This is the foundation of automated systems where one measurement influences an entire physical environment.
