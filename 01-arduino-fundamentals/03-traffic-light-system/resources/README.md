# 🚦 Project 03 — Traffic Light System

> **Control multiple outputs and turn them into a coordinated system.**

---

## 🎯 Project Story

A single LED is easy to control.

But real systems rarely have only one output.

A traffic signal must coordinate multiple lights so that the system follows a meaningful sequence.

In this project, three LEDs are controlled by an Arduino to simulate a basic traffic light.

The hardware introduces **multiple GPIO outputs**, while the software introduces **sequencing, timing, and system states**.

---

## 🧠 What You Will Learn

By completing this project, you will understand:

- Multiple digital output pins
- GPIO configuration
- Sequential program execution
- System states
- Timed state transitions
- Functions
- Coordinating multiple outputs
- Basic automation logic

The source curriculum identifies Project 03 as **“Traffic Light System”** with the main concept **multiple outputs + sequencing**. :contentReference[oaicite:2]{index=2}

---

## 📈 Learning Progression

```text
Project 01
Blinking LED
Digital Output
      ↓
Project 02
Random LED Glow
Variables + Randomness
      ↓
Project 03
Traffic Light
Multiple Outputs + Sequencing

The course progression is deliberately moving from one output toward coordinated system behaviour.

🎯 Objective

Build a three-light traffic signal using an Arduino Uno.

The system will cycle through:

RED → GREEN → YELLOW → RED → ...

The source curriculum describes the objective as managing several digital output signals according to an ordered timeline.

🧰 Hardware
Component	Quantity
Arduino Uno	1
Red LED	1
Yellow LED	1
Green LED	1
220 Ω resistor	3
Breadboard	1
Jumper wires	Several

The source specifically specifies an Arduino Uno, three LEDs, and three 220 Ω current-limiting resistors.

🔌 Pin Mapping
Arduino	Function
D8	Red LED
D9	Yellow LED
D10	Green LED
🔧 Circuit

See the detailed wiring guide:

circuit/wiring.md

Basic connection
D8  → 220 Ω → Red LED    → GND
D9  → 220 Ω → Yellow LED → GND
D10 → 220 Ω → Green LED  → GND
🔄 How It Works

The Arduino repeatedly executes three states.

State 1 — RED
RED    → ON
YELLOW → OFF
GREEN  → OFF

Duration: 5 seconds

State 2 — GREEN
RED    → OFF
YELLOW → OFF
GREEN  → ON

Duration: 5 seconds

State 3 — YELLOW
RED    → OFF
YELLOW → ON
GREEN  → OFF

Duration: 2 seconds

Then the system returns to RED.

🧭 System Flow
             START
               │
               ▼
        Configure GPIOs
               │
               ▼
        🔴 RED = ON
        🟡 YELLOW = OFF
        🟢 GREEN = OFF
               │
             5 sec
               │
               ▼
        🔴 RED = OFF
        🟡 YELLOW = OFF
        🟢 GREEN = ON
               │
             5 sec
               │
               ▼
        🔴 RED = OFF
        🟡 YELLOW = ON
        🟢 GREEN = OFF
               │
             2 sec
               │
               └──────────────► RED
💻 Code

The complete program is available in:

code/traffic_light.ino

The key idea is to represent each traffic-light state explicitly:

setLights(HIGH, LOW, LOW);
delay(RED_TIME);

setLights(LOW, LOW, HIGH);
delay(GREEN_TIME);

setLights(LOW, HIGH, LOW);
delay(YELLOW_TIME);
🔍 Code Walkthrough
Pin definitions
const int RED_LED = 8;
const int YELLOW_LED = 9;
const int GREEN_LED = 10;

These give meaningful names to the GPIO pins.

GPIO configuration
pinMode(RED_LED, OUTPUT);
pinMode(YELLOW_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT);

All three pins are configured as outputs.

State control
setLights(HIGH, LOW, LOW);

means:

RED    = ON
YELLOW = OFF
GREEN  = OFF
Timing
delay(RED_TIME);

keeps the current state active for the configured duration.

🧪 Testing Procedure
Test 1 — Power

Connect the Arduino and verify that the board powers normally.

Test 2 — Red

The red LED should turn ON first.

Test 3 — Green

After approximately 5 seconds, green should turn ON.

Test 4 — Yellow

After approximately 5 seconds, yellow should turn ON.

Test 5 — Repeat

The sequence should continuously repeat.

✅ Expected Behaviour
RED    → 5 sec
GREEN  → 5 sec
YELLOW → 2 sec
RED    → repeat

Only one traffic light should be ON during each programmed state.

🐛 Troubleshooting
No LED turns on

Check:

Arduino power
GND connection
Breadboard connections
LED polarity
Resistors
One LED does not work

Check:

Correct GPIO pin
LED orientation
Resistor connection
Breadboard row
Wrong LED turns on

Compare the physical wiring against:

D8  → RED
D9  → YELLOW
D10 → GREEN
Two LEDs turn on together

Check for:

Incorrect breadboard connections
Shorted rows
Incorrect wiring
LED legs placed in the same connected row
🧪 Experiments

Change:

const unsigned long RED_TIME = 5000;

Try:

const unsigned long RED_TIME = 3000;

Then experiment with:

Green timing
Yellow timing
Different LED sequences

Record how the system behaviour changes.

🧩 Challenge

Create a more realistic sequence:

🔴 RED
   ↓
🔴🟡 RED + YELLOW
   ↓
🟢 GREEN
   ↓
🟡 YELLOW
   ↓
🔴 RED

Before coding, write down the required state of each GPIO for every stage.

🧠 Knowledge Check
Why does each LED require its own resistor?
Why are three different GPIO pins required?
What does HIGH mean for an LED output?
Why are named timing constants useful?
What is a system state?
How does changing software change the behaviour of the same circuit?
📊 Assessment
Skill	Beginner	Developing	Confident
Identify GPIOs	☐	☐	☐
Wire 3 LEDs	☐	☐	☐
Configure outputs	☐	☐	☐
Understand states	☐	☐	☐
Understand sequencing	☐	☐	☐
Modify timing	☐	☐	☐
Create a new sequence	☐	☐	☐
Troubleshoot independently	☐	☐	☐
🌍 Real-World Connection

The circuit is a simplified model of a much larger control problem.

Real traffic-control systems involve:

Multiple signal states
Timing
Sensors
Safety constraints
Intersections
State machines
Fault detection

This project introduces the fundamental idea:

A real-world system can be represented as a sequence of defined states controlled by software.
