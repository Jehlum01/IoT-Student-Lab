# Project 12 — Learning Notes

## The Big Idea

Project 11 only measured temperature.

Project 12 makes the system respond to temperature automatically.

The system now follows:

**Sense → Decide → Act**

```text
Temperature
     ↓
   Sensor
     ↓
 Arduino
     ↓
 Decision
     ↓
 Fan

## What is an Actuator?

A sensor collects information.

An actuator performs an action.

Examples:

Sensor	Actuator
Temperature sensor	Fan
LDR	Light
PIR	Light / Buzzer
Soil sensor	Water pump
Ultrasonic sensor	Servo / Buzzer

The fan in this project is the actuator.

Threshold Logic

The controller compares the measured temperature against defined limits.

if (!fanState && temperatureC >= FAN_ON_TEMP)

means:

If the fan is currently OFF and the temperature reaches the ON threshold, turn the fan ON.

Similarly:

if (fanState && temperatureC <= FAN_OFF_TEMP)

means:

If the fan is currently ON and the temperature falls to the OFF threshold, turn the fan OFF.

Hysteresis

The project deliberately uses two thresholds:

Fan ON  → 30°C
Fan OFF → 28°C

This is called hysteresis.

It prevents rapid switching around a single threshold.

Why Not Connect the Fan Directly?

A microcontroller GPIO is a control output.

A motor/fan can require considerably more current and can generate electrical transients.

Therefore:

Arduino GPIO
     ↓
Driver
     ↓
Fan

is the correct architecture.

Engineering Principle

Separate:

Control signal

from:

Power delivery

The Arduino decides when the fan should operate.

The driver handles the electrical power required by the fan.

Experiment 1 — Change the Threshold

Try:

const float FAN_ON_TEMP = 28.0;
const float FAN_OFF_TEMP = 26.0;

Observe how the system behaves.

Experiment 2 — Remove Hysteresis

Temporarily use the same threshold for ON and OFF.

Observe what happens when the temperature is close to the threshold.

Question:

Why could this cause rapid switching?

Experiment 3 — Add a Warning LED

Add an LED that indicates:

Temperature < 30°C → Normal
Temperature ≥ 30°C → Cooling
Experiment 4 — Add Multiple Fan Speeds

Research how PWM could be used to control fan speed.

Possible concept:

Low temperature  → Fan OFF
Medium temperature → Low speed
High temperature → High speed
Challenge

Modify the system to display:

Temperature: 27.5°C
Fan: OFF
Status: NORMAL

and:

Temperature: 32.4°C
Fan: ON
Status: COOLING
Real-World Connection

The same fundamental architecture appears in:

Computer cooling
HVAC systems
Server-room cooling
Industrial equipment
Greenhouses
Smart buildings
Refrigeration systems

The hardware becomes more sophisticated, but the core control loop remains:

Measure
   ↓
Compare
   ↓
Decide
   ↓
Act
   ↓
Measure Again
Learning Outcome

After completing this project, students should understand:

Analog sensor measurement
Temperature calculation
Threshold-based control
Boolean state
Hysteresis
Actuator control
Transistor/MOSFET switching
Flyback protection
Separation of control and power
