# 🎯 Level 2 — Practical Assessment: Sensors, Inputs & Automation

> **Assessment Objective:** > > Independently construct, program, debug, and defend a complete automated embedded system synthesizing the core principles of Level 2.

## 🧭 System Pipeline Overview

Every practical evaluation submission must follow the deterministic closed-loop pipeline:

```
┌──────────────┐      ┌──────────────┐      ┌──────────────┐      ┌──────────────┐
│ 1. Sense     │ ──►  │ 2. Process   │ ──►  │ 3. Decide    │ ──►  │ 4. Actuate   │
│ (Raw Input)  │      │ (**ADC** / State)│      │ (Logic / **FSM**)│      │ (Actuators)  │
└──────────────┘      └──────────────┘      └──────────────┘      └──────────────┘
    ▲                                                                 │
    └──────────────────── 5. Continuous Loop ─────────────────────────┘

```

## 📋 Evaluation Sections

### Part A — Hardware Assembly & Safety

Students must construct a physical breadboard implementation meeting **IPC**/circuit safety standards:

- \[ \] **Component Identification:** Correctly identify resistor color codes, active vs. passive sensors, transistor leads, and actuator polarities.

- \[ \] **Safe Circuit Design:** Current-limiting resistors installed for all LEDs ($**220**\ \Omega\text{--}**330**\ \Omega$) and pull-up/pull-down dividers where applicable.

- \[ \] **Sensor Interfacing:** Correct pinout matching for analog sensors (e.g., **TMP36**, **LDR** dividers) and digital modules (e.g., **PIR** motion detectors).

- \[ \] **Actuator Isolation:** Transistor/**MOSFET**/Relay driver circuitry wired for high-draw loads.

> \[!**CAUTION**\] > **Actuator Current Limits:** > > Never drive inductive loads or DC motors directly from microcontroller **GPIO** pins. Students must interface motors via switching transistors with reverse-biased flyback diodes.

### Part B — Firmware & Architecture

The written sketch must avoid blocking routines and exhibit robust embedded firmware design patterns:

| Criterion | Implementation Expectation | 
 | ----- | ----- | 
| **Digital Input** | Active-low button logic using `INPUT_PULLUP` or debounce routines. | 
| **Analog Input** | Stable ADC acquisition with voltage conversion math. | 
| **Conditional Logic** | Deterministic relational operators (`<`, `>`, `!=`, `&&`, `||`). | 
| **State Tracking** | Finite state management using state variables (`enum` or integer states). | 
| **Thresholding** | Noise-tolerant boundaries or hysteresis windows. | 
| **Non-blocking Timing** | Timestamp differential tracking via `millis()` (zero blocking `delay()`). | 
| **Serial Telemetry** | Structured, human-readable telemetry logs output to the Serial Monitor. |

### Part C — Closed-Loop System Behavior

The complete system must maintain continuous operation across a five-phase functional loop:

1. **Sense:** Continuously sample analog and digital telemetry.

2. **Process:** Filter noise, map **ADC** values to physical units ($^\circ\text{C}$, $\text{Lux}$), and compute delta intervals.

3. **Decide:** Compare processed parameters against target thresholds and state machine modes.

4. **Control:** Drive output pins, modulate **PWM** channels, or trip alert indicators.

5. **Monitor:** Remain responsive to concurrent asynchronous events without system stalls.

### Part D — Guided Fault Diagnosis (Troubleshooting)

The instructor will inject **one controlled fault** into the working setup.

#### Potential Fault Injections

- ⚡ Reversed **LED** polarity or missing current-limiting resistor.

- ⚡ Loose, floating, or shorted sensor signal wire.

- ⚡ Misconfigured **GPIO** pin mapping in firmware (`#define` or `const int`).

- ⚡ Threshold logic inversion (e.g., `<` swapped with `>`).

- ⚡ Button input configured as `**INPUT**` instead of `INPUT_PULLUP`.

#### Required Diagnostic Workflow

Students must document their resolution using the structured troubleshooting loop:

```
[1. Observe Symptom] ──► [2. Form Hypothesis] ──► [3. Perform Test]
    │
    ▼
[6. Verify Stability] ◄── [5. Apply Correction] ◄── [4. Identify Defect]

```

### Part E — Dynamic Engineering Modification

Upon restoring the system to nominal operation, the student receives one immediate engineering change order (**ECO**):

- 🔹 **Threshold Re-calibration:** Adjust activation points to suit a different environment.

- 🔹 **Timing Re-specification:** Modify inactivity timeout or hold duration.

- 🔹 **Hardware Expansion:** Add an auxiliary indicator **LED**, alert buzzer, or secondary sensor.

- 🔹 **Override Feature:** Implement an asynchronous manual button toggle to override automatic rules.

- 🔹 **State Expansion:** Add a distinct operational state (e.g., `**STANDBY**`, `**ARMED**`, `**MAINTENANCE**`).

## 📊 Evaluation Rubric

```
                     Evaluation Weight Distribution
 ┌──────────────────────┬──────────────────────┬─────────────┐
 │ Circuit Assembly     │ Programming          │ Sensors     │
 │ 20%                  │ 25%                  │ 15%         │
 ├──────────────────────┼──────────────────────┼─────────────┤
 │ Automation Logic     │ Troubleshooting      │ Oral Defense│
 │ 15%                  │ 15%                  │ 10%         │
 └──────────────────────┴──────────────────────┴─────────────┘

```

| Area | Weight | Exemplary (Full Marks) | Needs Remediation (0 Marks) | 
 | ----- | ----- | ----- | ----- | 
| **Circuit Assembly** | **20%** | Neat, color-coded, safe resistor choices, isolated motor driver. | Messy, short circuits present, motor driven directly off GPIO. | 
| **Programming** | **25%** | Modular, readable, non-blocking timing, debounced inputs. | Blocking `delay()`, unorganized global logic, no comments. | 
| **Sensor Integration** | **15%** | Accurate conversions, scaled analog readings, stable triggers. | Inaccurate math, floating pins, unstable readings. | 
| **Automation Logic** | **15%** | Clear deterministic state transitions, arbitration of edge cases. | Erratic oscillation, race conditions, unhandled states. | 
| **Troubleshooting** | **15%** | Systematic diagnostic methodology; identifies fault without guessing. | Random guesswork, rewrites code instead of checking hardware. | 
| **Oral Defense** | **10%** | Clearly articulates physics, logic flow, and trade-offs. | Cannot explain how the code or circuit functions. | 
| **Total** | **100%** | **Passing Score:**  75\% |  |

## 🎓 Engineering Mindset

To receive full credit, the student must pass an oral technical defense, answering five core engineering questions:

> 1. **What is happening?**

>    *Describe the current state and electrical activity of the hardware.*

> 2. **Why is it happening?**

>    *Explain which environmental stimulus or register state triggered this condition.*

> 3. **How does the program respond?**

>    *Walk through the specific lines of logic and variables handling the transition.*

> 4. **How did you test it?**

>    *Describe the measurement method (multimeter, Serial logs, stimulus test).*

> 5. **What would you improve?**

>    *Identify efficiency limits, noise vulnerabilities, or scalability constraints in the design.*
