# 🎲 Project 02 — Random LED Glow & Variable Timing

<p align="center">

**🌱 IoT Student Lab**

### Learn. Build. Break. Fix. Create.

*From fixed behaviour to programmable behaviour*

</p>

---

## 🚀 Project Overview

In **Project 01**, you made an LED blink at a fixed interval.

Now we are going to make the same LED behave differently every time.

The hardware remains almost exactly the same.

The big change is in the **software**.

> 🧠 **Same hardware + different software = different behaviour**

In this project, the Arduino will generate different timing values and use them to control how long the LED stays ON and OFF.

---

# 🎯 1. Project Mission

The goal of this project is to move from **fixed behaviour** to **variable and randomized behaviour**.

🧩 2. Problem Statement

Build an Arduino-based system that makes an LED glow for a random amount of time.

The LED should:

🟢 Turn ON
🎲 Stay ON for a randomly selected duration
🔴 Turn OFF
🎲 Stay OFF for another randomly selected duration
🔄 Repeat continuously

The timing should remain within a defined minimum and maximum range.

🎓 3. Learning Objectives

After completing this project, you should be able to:

📦 Understand variables
🎲 Understand pseudo-random numbers
🧠 Use the Arduino random() function
🌱 Understand randomSeed()
⏱️ Use variables with delay()
🔢 Define minimum and maximum values
🔄 Create variable program behaviour
🧪 Experiment with timing ranges
🐞 Debug software and hardware independently
💡 Understand how software changes hardware behaviour



🧰 4. Components Required

The hardware is intentionally kept simple.

Component	Quantity	Purpose
🔵 Arduino Uno	1	Main microcontroller
💡 LED	1	Visual output
🟫 220 Ω Resistor	1	Limits LED current
🟦 Breadboard	1	Circuit assembly
🔗 Jumper Wires	2–3	Electrical connections
🔌 USB Cable	1	Programming & power

🔄 5. What Changed from Project 01?

This is an important learning point.

Project 01

The timing was fixed:

delay(1000);

Every cycle used the same value.

Project 02

The timing is stored in variables:

int onTime = random(MIN_DELAY, MAX_DELAY);

and:

int offTime = random(MIN_DELAY, MAX_DELAY);

Now the timing can change.

🔌 6. Circuit Connection

The circuit remains the same basic LED circuit from Project 01.

Arduino D8
    │
    ▼
  220 Ω
 Resistor
    │
    ▼
 LED Anode (+)
    │
 LED Cathode (-)
    │
    ▼
   GND
🔗 Wiring Table
Arduino Pin	Connect To
D8	220 Ω resistor
Resistor	LED Anode (+)
LED Cathode (-)	GND


7. Understanding random()

Arduino provides the:

random()

function for generating pseudo-random numbers.

For example:

random(200, 2000);

This generates a value within the specified range.

We can store that value:

int onTime = random(200, 2000);

Now onTime contains a randomly selected timing value.

🔢 8. Minimum and Maximum Values

Instead of directly writing numbers throughout the program, we define:

const int MIN_DELAY = 200;
const int MAX_DELAY = 2000;

This gives us a clear operating range.

The program then uses:

random(MIN_DELAY, MAX_DELAY);
Why is this useful?

If you want to change the behaviour later, you only need to change the defined limits.

For example:

const int MAX_DELAY = 5000;

would allow a longer maximum delay.

🌱 09. Understanding randomSeed()

The program also uses:

randomSeed(analogRead(A0));

This is used to provide a starting value, or seed, for the pseudo-random sequence.

The Arduino's random() function is not true physical randomness.

It generates a pseudo-random sequence.
