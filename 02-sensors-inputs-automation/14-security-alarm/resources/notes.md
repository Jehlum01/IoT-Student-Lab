# Project 14 — Learning Notes

## The Big Idea

This project combines several Level 2 concepts into one automatic security system.

```text
Sense
  ↓
Detect
  ↓
Decide
  ↓
Act
  ↓
Wait
  ↓
Reset

The PIR sensor detects movement.

The Arduino decides that the movement should trigger an alarm.

The LED and buzzer provide the response.

System Architecture
       PIR SENSOR
            │
            ▼
       Digital Input
            │
            ▼
       Arduino Logic
            │
       ┌────┴────┐
       ▼         ▼
      LED      Buzzer
       │         │
       └────┬────┘
            ▼
        Alarm Event


##State Variable

The program uses:
bool alarmActive = false;

This variable represents the current state of the alarm.

There are two possible states:

false → Alarm inactive
true  → Alarm active
Starting the Alarm

When motion is detected:

if (motionState == HIGH && !alarmActive)

the program activates the alarm.

It also records the starting time:

alarmStartTime = millis();
Timing

The alarm duration is:

const unsigned long ALARM_DURATION = 5000;

The program checks:

millis() - alarmStartTime >= ALARM_DURATION

When the duration has elapsed, the alarm is turned OFF.

Why Use State?

Without a state variable, the Arduino could repeatedly execute the alarm-start code while the PIR output remains HIGH.

The state tells the program:
Has the alarm already started?
This is an important embedded-systems programming pattern.

##Experiment 1 — Change Alarm Duration

Try:

const unsigned long ALARM_DURATION = 10000;

The alarm should remain active for approximately 10 seconds.

##Experiment 2 — Add a Second LED

Add another LED to indicate:
System armed
Possible behavior:

Alarm OFF → Armed indicator ON
Alarm ON  → Armed indicator OFF

##Experiment 3 — Flash the Alarm LED

Instead of keeping the LED continuously ON, make it flash while the alarm is active.
Think about how millis() could be used instead of delay().

##Experiment 4 — Add a Reset Button

Add a button that manually stops the alarm.

This introduces another important concept:

Automatic event
+
Manual override

##Challenge
Create three system states:

ARMED
  ↓
MOTION DETECTED
  ↓
ALARM
  ↓
TIMEOUT
  ↓
ARMED

Then add a manual button that can switch the system between:

1. ARMED
2. DISARMED


##Real-World Connection

Security systems commonly combine:

Motion sensors
Door/window sensors
Alarm indicators
Timers
User controls
Access systems
Event logging

The architecture learned here is a simplified version of those systems.

Level 2 Progression

The projects in this level build progressively:

07  Push Button
       ↓
08  Toggle State
       ↓
09  Analog Light Sensor
       ↓
10  Automated Street Light
       ↓
11  Temperature Monitoring
       ↓
12  Temperature-Controlled Fan
       ↓
13  Motion Detection Light
       ↓
14  Security Alarm

The overall pattern is:

Sense → Decide → Act

Learning Outcome

Students should now understand:

Digital sensors
Analog sensors
Sensor thresholds
State variables
Conditional logic
Timing
millis()
Actuator control
Event-driven behavior
Basic automation architecture
Basic alarm-system design
