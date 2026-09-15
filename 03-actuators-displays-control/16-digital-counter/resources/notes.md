# Project 16 --- Digital Counter

> **Learning Notes · Arduino & Embedded Systems**
>
> **Core concept:** A counter is a simple embedded system that
> **remembers state**, responds to input events, applies logic, and
> displays its current state.

------------------------------------------------------------------------

## 📘 Learning Objectives

By the end of this project, students should be able to:

-   Understand the concept of **state** in an embedded system.
-   Increment and decrement a variable using button inputs.
-   Apply **minimum and maximum limits** to a counter.
-   Represent decimal values using **4-bit binary output**.
-   Detect a button press using **state transitions**.
-   Understand why **mechanical buttons need debouncing**.
-   Extend a basic counter into a practical embedded-system application.

------------------------------------------------------------------------

## 1. The Big Idea

A counter is a simple example of a system that **remembers
information**.

The Arduino maintains a variable:

``` cpp
int counter = 0;
```

Every button press changes that state.

### System Flow

``` mermaid
flowchart TD
    A[Button Input] --> B[Detect Event]
    B --> C[Change Counter]
    C --> D[Store New State]
    D --> E[Display State]
    E --> A
```

The important idea is that the Arduino does not simply react to a
button---it **maintains a value representing the current condition of
the system**.

------------------------------------------------------------------------

# 2. Understanding State

## What is State?

The **state** of a system is the information that describes its current
condition.

In this project, the `counter` variable represents the state.

For example:

``` text
counter = 0
counter = 1
counter = 2
counter = 3
```

The value remains stored in the variable until:

1.  The program changes it, or
2.  The Arduino resets or loses power.

### State Transition

``` mermaid
stateDiagram-v2
    [*] --> 0
    0 --> 1: UP
    1 --> 2: UP
    2 --> 3: UP
    3 --> 2: DOWN
    2 --> 1: DOWN
    1 --> 0: DOWN
```

> 💡 **Key takeaway:** In embedded systems, variables are often used to
> represent the current **state of a machine, device, or process**.

------------------------------------------------------------------------

# 3. Incrementing the Counter

The **UP button** increases the counter by one.

``` cpp
counter++;
```

This is equivalent to:

``` cpp
counter = counter + 1;
```

### Example

    Before Action     After
  -------- -------- -------
         0 UP             1
         1 UP             2
         2 UP             3
         3 UP             4

------------------------------------------------------------------------

# 4. Decrementing the Counter

The **DOWN button** decreases the counter by one.

``` cpp
counter--;
```

This is equivalent to:

``` cpp
counter = counter - 1;
```

### Example

    Before Action     After
  -------- -------- -------
         4 DOWN           3
         3 DOWN           2
         2 DOWN           1
         1 DOWN           0

------------------------------------------------------------------------

# 5. Setting Counter Limits

The project defines a minimum and maximum value:

``` cpp
const int MIN_COUNT = 0;
const int MAX_COUNT = 15;
```

These limits prevent the counter from moving outside the range that can
be represented by **four binary LEDs**.

### Counter Range

  Parameter          Value Purpose
  ---------------- ------- -----------------------------
  `MIN_COUNT`          `0` Lowest allowed value
  `MAX_COUNT`         `15` Highest allowed value
  Number of LEDs       `4` Represents four binary bits

The logic can be visualized as:

``` mermaid
flowchart LR
    A[Counter] --> B{Counter < 0?}
    B -- Yes --> C[Keep at 0]
    B -- No --> D{Counter > 15?}
    D -- Yes --> E[Keep at 15]
    D -- No --> F[Accept Value]
```

> 🔒 **Why limits matter:** A robust embedded system should prevent
> invalid states before they reach hardware or the user interface.

------------------------------------------------------------------------

# 6. Understanding Binary Display

Four LEDs can represent four binary bits:

  Bit       Binary Weight   Decimal Value
  ------- --------------- ---------------
  Bit 3              `2³`               8
  Bit 2              `2²`               4
  Bit 1              `2¹`               2
  Bit 0              `2⁰`               1

Therefore:

``` text
2⁰ = 1
2¹ = 2
2² = 4
2³ = 8
```

The largest value that four bits can represent is:

``` text
8 + 4 + 2 + 1 = 15
```

### Four-Bit Representation

``` text
        Bit 3   Bit 2   Bit 1   Bit 0
Weight    8       4       2       1
          │       │       │       │
          ●       ●       ●       ●
```

### Possible Values

Four bits provide:

**2⁴ = 16 possible combinations**

which represent:

**0 through 15**

------------------------------------------------------------------------

# 7. Reading Individual Bits

The program uses:

``` cpp
bitRead(value, i);
```

to extract individual binary bits.

Conceptually:

``` text
Decimal value
     ↓
Convert to binary
     ↓
Extract each bit
     ↓
Send bits to LEDs
```

For example, consider the decimal value:

``` text
6
```

Its four-bit binary representation is:

``` text
0110
```

Therefore:

  Bit       Value LED State
  ------- ------- -----------
  Bit 3       `0` OFF
  Bit 2       `1` ON
  Bit 1       `1` ON
  Bit 0       `0` OFF

### Binary Visualization

``` text
6 = 0110

Bit:       3    2    1    0
Weight:    8    4    2    1
           │    │    │    │
State:     0    1    1    0
           ○    ●    ●    ○
          OFF  ON   ON  OFF
```

------------------------------------------------------------------------

# 8. Button Event Detection

A common beginner mistake is to check only whether a button is currently
LOW or HIGH.

Instead, the program compares:

``` text
Previous State
      ↓
Current State
```

A transition from:

``` text
HIGH → LOW
```

is treated as a **button press**.

### Edge Detection

``` mermaid
sequenceDiagram
    participant B as Button
    participant A as Arduino
    participant C as Counter

    B->>A: HIGH
    A->>A: Store previous state
    B->>A: LOW
    A->>A: Detect HIGH → LOW transition
    A->>C: Increment / decrement
    C-->>A: New counter value
```

This is called **edge detection**.

### Why Not Count While the Button Is Held?

If the program simply checked:

``` cpp
if (buttonState == LOW)
```

the counter could change repeatedly while the user held the button.

Instead, detecting the transition ensures that **one press produces one
logical event**.

------------------------------------------------------------------------

# 9. Button Debouncing

Mechanical switches do not always produce one clean electrical
transition.

When a button is pressed, the signal can briefly bounce between HIGH and
LOW:

``` text
HIGH → LOW → HIGH → LOW → HIGH
```

This may happen within a very short period.

The Arduino could mistakenly interpret these rapid transitions as
**multiple button presses**.

### Simplified Bounce Pattern

``` text
Ideal:

HIGH ────────────┐
                  └──────── LOW


Real switch:

HIGH ──────┐ ┌───┐ ┌────────
           └─┘   └─┘
             bouncing
```

The project uses a small **debounce delay** to reduce accidental
multiple counts.

> ⚠️ **Engineering note:** A fixed delay is simple and useful for
> learning, but production systems often use more robust debounce
> techniques such as timer-based filtering or state-machine debouncing.

------------------------------------------------------------------------

# 10. How the Complete System Works

The complete control loop can be summarized as:

``` mermaid
flowchart TD
    A[Start Arduino] --> B[Read Buttons]
    B --> C{UP Pressed?}
    C -- Yes --> D[Increment Counter]
    C -- No --> E{DOWN Pressed?}
    D --> F[Apply Limits]
    E -- Yes --> G[Decrement Counter]
    E -- No --> F
    G --> F
    F --> H[Convert Counter to Binary]
    H --> I[Update 4 LEDs]
    I --> J[Print Count to Serial Monitor]
    J --> B
```

------------------------------------------------------------------------

# 11. Experiments

## 🧪 Experiment 1 --- Change the Counter Range

Change the maximum value to `9`:

``` cpp
const int MIN_COUNT = 0;
const int MAX_COUNT = 9;
```

### Observe

-   What happens when the counter reaches `9`?
-   What happens when you press UP again?
-   What happens when the counter reaches `0`?
-   What happens when you press DOWN again?

### Think About

Why is the original maximum value `15` particularly convenient for a
four-bit display?

------------------------------------------------------------------------

## 🧪 Experiment 2 --- Add a Reset Button

Add a third button that resets the counter:

``` text
Counter → 0
```

### Suggested behavior

  Button   Action
  -------- --------------------
  UP       Increase counter
  DOWN     Decrease counter
  RESET    Set counter to `0`

### Student Task

Implement the reset functionality without changing the existing UP and
DOWN behavior.

------------------------------------------------------------------------

## 🧪 Experiment 3 --- Build an Automatic Counter

Remove the UP button and make the counter automatically increase every
second.

Instead of using a long `delay()`, investigate how:

``` cpp
millis()
```

can be used.

### Learning Goal

Understand **non-blocking timing** in Arduino programs.

------------------------------------------------------------------------

## 🧪 Experiment 4 --- Seven-Segment Display

Research how the four-bit binary output could be replaced with a
**seven-segment display**.

### Questions to Investigate

1.  How many LEDs are inside a typical seven-segment display?
2.  How are the segments named?
3.  How would you display `0–9`?
4.  What additional logic is required?
5.  How is this different from displaying raw binary?

> 🚀 This experiment prepares students for more advanced display and
> human-machine-interface systems.

------------------------------------------------------------------------

# 12. Level-Up Challenge --- Visitor Counter

Build a **visitor counter** using the same core concept.

### Requirements

-   **UP button** = person enters
-   **DOWN button** = person leaves
-   Counter cannot become negative
-   Display the current count
-   Print the count to the Serial Monitor
-   Maximum capacity = **15**
-   When capacity is reached, activate a **warning LED**

### System Concept

``` mermaid
flowchart LR
    A[Person Enters] --> B[UP Button]
    C[Person Leaves] --> D[DOWN Button]
    B --> E[Visitor Counter]
    D --> E
    E --> F[4-Bit LED Display]
    E --> G[Serial Monitor]
    E --> H{Count = 15?}
    H -- Yes --> I[Warning LED ON]
    H -- No --> J[Warning LED OFF]
```

### Challenge Specification

  Requirement        Expected Behavior
  ------------------ ----------------------------------
  Entry              Counter increases by 1
  Exit               Counter decreases by 1
  Minimum            Counter never goes below `0`
  Maximum            Counter never exceeds `15`
  Display            Current count shown using 4 LEDs
  Serial Monitor     Current count printed
  Capacity reached   Warning LED turns ON
  Below capacity     Warning LED turns OFF

------------------------------------------------------------------------

# 13. Real-World Connection

Counters are fundamental building blocks in many real-world embedded
systems.

  Application              What Is Being Counted?
  ------------------------ ------------------------
  👥 People counting       Visitors / occupants
  🏭 Production lines      Manufactured products
  🚗 Parking systems       Vehicles
  📦 Inventory systems     Items / stock
  ⚙️ Machine monitoring    Machine cycles
  🎟️ Event systems         Entries / tickets
  🔬 Digital instruments   Events / pulses

The counter in this project is intentionally simple, but the same
principles appear in much larger systems.

------------------------------------------------------------------------

# 14. Key Concepts Learned

  -----------------------------------------------------------------------
  Concept                             What You Learned
  ----------------------------------- -----------------------------------
  **State**                           A variable can represent the
                                      current condition of a system

  **Increment**                       `counter++` increases a value

  **Decrement**                       `counter--` decreases a value

  **Constraints**                     Minimum and maximum values prevent
                                      invalid states

  **Binary**                          Four bits represent values from 0
                                      to 15

  **Bit manipulation**                `bitRead()` extracts individual
                                      bits

  **Edge detection**                  Button transitions can represent
                                      events

  **Debouncing**                      Prevents mechanical switch noise
                                      from creating false events

  **Serial output**                   Provides a simple way to observe
                                      program state

  **System design**                   Input → logic → state → output
  -----------------------------------------------------------------------

------------------------------------------------------------------------

# 15. Quick Review Questions

1.  What does the variable `counter` represent?
2.  What is the difference between `counter++` and `counter--`?
3.  Why is the maximum value `15` when using four LEDs?
4.  How many combinations can four binary bits represent?
5.  What does `bitRead(value, i)` do?
6.  Why is `HIGH → LOW` transition useful for detecting a button press?
7.  What is switch bounce?
8.  Why can a button press sometimes be counted multiple times?
9.  Why are minimum and maximum limits important?
10. How could `millis()` improve the automatic counter experiment?

------------------------------------------------------------------------

# 16. Takeaway

> **A counter is more than a number---it is a simple example of state
> management in an embedded system.**

The project combines:

**Input → Event Detection → Logic → State → Output**

Once students understand this pattern, they can apply it to much more
complex systems such as:

-   visitor counters,
-   production counters,
-   parking systems,
-   inventory trackers,
-   machine-cycle counters,
-   pulse counters,
-   digital instruments, and
-   IoT monitoring systems.

------------------------------------------------------------------------

## 🧠 Remember

``` text
INPUT
  ↓
DETECT EVENT
  ↓
CHANGE STATE
  ↓
APPLY RULES
  ↓
DISPLAY / OUTPUT
```

