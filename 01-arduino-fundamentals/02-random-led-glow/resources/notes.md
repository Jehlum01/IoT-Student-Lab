# 📚 Project 02 — Learning Notes

## 🎲 Random LED Glow & Variable Timing

This project introduces three important programming concepts:

1. 📦 Variables
2. 🎲 Random numbers
3. ⏱️ Variable timing

---

# 📦 1. What Is a Variable?

A variable is a named location used to store a value.

For example:

```cpp
int onTime = 1000;

Here:

int → data type
onTime → variable name
1000 → stored value

The value can change while the program runs.

2. Random Numbers

Arduino provides the random() function for generating pseudo-random numbers.

Example:

random(200, 2000);

This produces a value within the specified range.

We can store that value in a variable:

int onTime = random(200, 2000);

Now onTime contains a randomly selected timing value.

⏱️ 3. Variable Timing

Project 01 used a fixed delay:

delay(1000);

Every cycle therefore behaved approximately the same way.

Project 02 uses a variable:

delay(onTime);

The delay can now change from one cycle to another.

🔄 4. Fixed vs Variable Behaviour
Project 01
1000 ms
   ↓
LED ON
   ↓
1000 ms
   ↓
LED OFF
   ↓
Repeat

The behaviour is predictable.

🧠 5. Pseudo-Random Numbers

The Arduino random() function does not produce truly random physical events.

It generates a pseudo-random sequence.

A starting value, called a seed, can be supplied using:

randomSeed(...);

In this project:

randomSeed(analogRead(A0));

is used to obtain a varying starting value.

No external sensor is required.

🔢 6. Understanding the Range

The program defines:

const int MIN_DELAY = 200;
const int MAX_DELAY = 2000;

Then:

random(MIN_DELAY, MAX_DELAY);

is used to generate the timing value.

This gives the program a defined operating range instead of allowing unlimited values.

🧩 7. Why Use Constants?

The program uses:

const int MIN_DELAY = 200;
const int MAX_DELAY = 2000;

instead of repeatedly writing numerical values.

This makes the program easier to understand and modify.

For example, changing:

const int MAX_DELAY = 2000;

to:

const int MAX_DELAY = 5000;

changes the maximum timing range.

🔬 8. Experiment

Try changing:

const int MIN_DELAY = 200;
const int MAX_DELAY = 2000;

to:

const int MIN_DELAY = 100;
const int MAX_DELAY = 5000;

Observe the LED.

Record:

Minimum visible delay
Maximum visible delay
How predictable the pattern feels
💭 9. Think Like an Engineer

Ask yourself:

What changed?

The program now generates timing values.

What stayed the same?

The LED circuit.

What caused the new behaviour?

The software.
