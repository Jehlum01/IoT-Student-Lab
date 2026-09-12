# 21 — Servo-Based Smart Gate

> **IoT Student Lab · Learning Project**

## 🎯 Project Overview

Use a servo motor to represent controlled gate movement.

This project is part of **Level 3 — Actuators, Displays & Real-World Control** and is designed around a hands-on engineering workflow:

**Understand → Build → Program → Test → Troubleshoot → Improve**

### Core focus

**Servo control**

---

## 🧠 Learning Objectives

By completing this project, students should be able to:

- Explain the purpose of the project and its components.
- Identify the inputs, processing logic and outputs.
- Build the circuit using the provided wiring information.
- Understand the important parts of the program.
- Test the system systematically.
- Identify common hardware and software faults.
- Suggest at least one improvement or extension.

---

## 📊 Project Information

| Item | Details |
|---|---|
| Difficulty | Beginner / Intermediate |
| Platform | Arduino Uno / Nano or the board specified by the instructor |
| Main concept | Servo control |
| Estimated time | Instructor-defined |
| Project type | Hands-on learning project |

---

## 🔧 Components

The exact bill of materials, component variants and quantities should be recorded here before the classroom build.

Typical components may include:

- Microcontroller board
- Breadboard
- Jumper wires
- Resistors
- LEDs / indicators
- Required sensor(s)
- Required actuator(s)
- Power supply appropriate for the circuit

> **Important:** Do not assume a pinout from a different board or module. Use the wiring table supplied for the exact hardware version used in class.

---

## 🔌 Wiring & Pin Configuration

Create a project-specific wiring table here.

| Component | Pin / Signal | Controller Pin | Purpose |
|---|---|---|---|
| Input / Sensor | Signal | TBD | Read system information |
| Output / Actuator | Control | TBD | Control physical output |
| Indicator | Signal | TBD | Show system state |
| Power | VCC / GND | Appropriate supply | Power the module |

**Before powering the circuit:** verify VCC, GND, signal wiring and voltage compatibility.

---

## ⚙️ How It Works

The system should be understood as a chain:

```text
INPUT / SENSOR
      ↓
MICROCONTROLLER
      ↓
DECISION / PROGRAM LOGIC
      ↓
OUTPUT / ACTUATOR
      ↓
USER / ENVIRONMENT
```

Students should be able to explain what happens at every stage rather than treating the code as a black box.

---

## 💻 Code

The source code for this project belongs in the project `code/` directory.

Before uploading:

1. Select the correct board.
2. Select the correct port.
3. Install the required libraries.
4. Verify the pin configuration.
5. Read the code before uploading it.
6. Upload and observe the result.

---

## 🧪 Testing Procedure

Use a controlled test sequence:

1. Inspect the circuit with power disconnected.
2. Check all connections.
3. Power the board.
4. Open Serial Monitor if the project uses serial output.
5. Test each input independently.
6. Test each output independently.
7. Test the complete system.
8. Record unexpected behaviour.
9. Troubleshoot one variable at a time.

---

## ✅ Expected Result

The completed system should respond to its defined inputs and produce the expected outputs.

Record actual observations during the classroom test rather than assuming that a successful upload means the project is correct.

---

## ❌ Troubleshooting

| Symptom | Possible Cause | What to Check |
|---|---|---|
| Nothing works | Power / GND problem | Supply, GND and wiring |
| Output does not respond | Incorrect pin | Pin definitions and physical wiring |
| Sensor value looks wrong | Wiring / calibration | Sensor supply, signal and expected range |
| Program does not compile | Library / syntax issue | Board package and required libraries |
| Behaviour is reversed | Active-high / active-low logic | Output logic and module type |
| Works intermittently | Loose connection / power issue | Breadboard and power supply |

---

## 🧩 Student Exercises

### Exercise 1 — Explain

Explain the purpose of every component used in the circuit.

### Exercise 2 — Predict

Before running the program, predict what should happen for different input conditions.

### Exercise 3 — Debug

Introduce one controlled wiring or software mistake and diagnose it.

### Exercise 4 — Modify

Change one parameter, threshold, timing value or output behaviour and observe the result.

---

## 🚀 Challenge

Extend the project without changing its fundamental purpose.

Possible directions:

- Add another indicator.
- Add a display.
- Add a manual override.
- Improve the user interface.
- Add data logging.
- Add another sensor.
- Add an error state.
- Convert the system into an IoT version where appropriate.

---

## 📝 Reflection

After completing the project, answer:

1. What did I build?
2. What was the most important concept?
3. What component was hardest to understand?
4. What problem did I encounter?
5. How did I troubleshoot it?
6. What would I improve?
7. What real-world system is similar to this project?

---

## 🏁 Learning Outcome

A successful student should be able to **build, explain, test and modify** the system—not merely upload the program.

---

## ⚠️ Safety

- Disconnect power before changing wiring.
- Check polarity before powering components.
- Avoid short circuits.
- Use suitable power supplies.
- Do not connect high-voltage mains directly to microcontroller circuits.
- Use instructor supervision for motors, pumps and relay-based systems.
- Follow the safety guidance for the exact hardware used.

---

## 📁 Recommended Project Structure

```text
21-project/
├── README.md
├── code/
├── circuit/
├── images/
└── resources/
```

---

## 🔗 Continue Learning

After completing this project, continue to the next project in the course sequence.

**Learn → Build → Experiment → Troubleshoot → Improve → Create**
