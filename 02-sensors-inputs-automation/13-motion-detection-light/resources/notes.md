# Project 13 — Learning Notes

## The Big Idea

This project introduces event-based automation.

Instead of continuously measuring an analog value like temperature, the PIR sensor provides a digital event:

```text
Motion detected
      ↓
    HIGH

The controller then decides what action to take.

Sense → Decide → Act
       PIR
        │
        ▼
      Sense
        │
        ▼
    Motion?
     /   \
   YES    NO
    │      │
    ▼      ▼
 Light    Timer
   ON      │
           ▼
        Light OFF
What is a PIR Sensor?

PIR means:

Passive Infrared

A PIR sensor detects changes in infrared radiation within its field of view.

Human bodies emit infrared radiation, so movement can be detected when a person moves across the sensor's detection area.

Digital Sensor

The Arduino reads the PIR output using:

digitalRead(PIR_PIN);

Unlike the LDR project, we are not interested in a numerical range.

The signal is treated as:

LOW  → No motion
HIGH → Motion
Event Detection

Motion is an event.

The program responds when:

motionState == HIGH

When motion occurs, the program records:

lastMotionTime = millis();

This gives us a reference point for deciding how long the light should remain active.

Why millis()?

delay() stops the program from doing other work.

For example:

delay(5000);

would prevent normal program execution for approximately five seconds.

Instead:

millis()

allows the Arduino to continue running its main loop.

This is an important technique for responsive embedded systems.

Experiment 1 — Change Light Duration

Change:

const unsigned long LIGHT_ON_TIME = 5000;

Try:

const unsigned long LIGHT_ON_TIME = 10000;

How does the behavior change?

Experiment 2 — Make the Light Stay On Longer

Set the timeout to 15 seconds.

Then observe whether new motion events reset the timer.

Experiment 3 — Add a Buzzer

Add a buzzer that briefly sounds when motion is first detected.

Think about this carefully:

Should the buzzer sound continuously while motion remains HIGH?

Or should it sound only once for each new motion event?

This introduces the difference between:

state

and

event.

Experiment 4 — Add a Second LED

Use another LED as a status indicator.

For example:

No motion → Green indicator
Motion    → Red indicator
Challenge

Modify the system so that the light has three states:

No motion
    ↓
LIGHT OFF

Motion detected
    ↓
LIGHT ON

Motion continues
    ↓
Keep LIGHT ON

No motion for timeout
    ↓
LIGHT OFF
Real-World Applications

The same basic concept is used in:

Automatic corridor lighting
Security systems
Smart homes
Parking areas
Staircase lighting
Office automation
Occupancy detection


Learning Outcome

Students should now understand:

PIR motion sensing
Digital sensor inputs
digitalRead()
Event-based control
millis()
Timing without blocking
State tracking
Automatic lighting
