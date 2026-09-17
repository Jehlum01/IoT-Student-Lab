# 📚 Project 30 — Smart Home Automation: Master Learning Notes

> **Maximum-detail classroom notes for the final Level 4 integration project**

---

# 1. What Are We Actually Building?

A smart home is not simply a collection of remote-controlled switches.

A useful mental model is:

```text
PHYSICAL WORLD
      ↓
Sensors / Devices
      ↓
Controller
      ↓
Decision + State
      ↓
Actuators
      ↓
Network
      ↓
Human / Software Interface
```

Project 30 implements a simplified version of this model using an ESP32.

The project has three controllable channels:

```text
GPIO 5  → Light
GPIO 18 → Fan
GPIO 19 → Auxiliary device
```

The browser communicates with the ESP32 through the local Wi-Fi network.

---

# 2. Why This Is the Final Level 4 Project

Projects 25–29 progressively introduced:

```text
Wi-Fi
 ↓
Web server
 ↓
Remote GPIO control
 ↓
Sensor monitoring
 ↓
Event-driven alarm
```

Project 30 combines these ideas:

```text
Wi-Fi
  +
Web Server
  +
Multiple Outputs
  +
State Management
  +
Relay Control
  +
API
  +
System-Level Control
  =
Smart Home Automation
```

This is why the project should be taught as an **integration exercise**, not just another relay demonstration.

---

# 3. Project Architecture

The complete learning architecture is:

```text
                    USER
                     │
                     ▼
             ┌───────────────┐
             │ Browser       │
             │ Phone/Laptop  │
             └───────┬───────┘
                     │
                    HTTP
                     │
                    Wi-Fi
                     │
                     ▼
             ┌───────────────┐
             │     ESP32     │
             │               │
             │ Web Server    │
             │ State Logic   │
             │ GPIO Control  │
             └───┬─────┬───┬─┘
                 │     │   │
                 ▼     ▼   ▼
              Relay  Relay Relay
                 │     │   │
                 ▼     ▼   ▼
               Light  Fan  Aux
```

The ESP32 is the **bridge between the digital/network world and the physical world**.

---

# 4. Smart Home vs Remote Control

These terms are related but not identical.

## Remote control

A user directly commands a device:

```text
User
 ↓
Browser
 ↓
ESP32
 ↓
Light ON
```

## Automation

The system can make decisions based on conditions:

```text
Sensor
 ↓
ESP32
 ↓
Decision
 ↓
Light ON
```

A smart-home platform can support both.

Project 30 begins with reliable remote control and then challenges students to extend it into automatic behavior.

---

# 5. The Three Device States

The program defines:

```cpp
bool lightState = false;
bool fanState = false;
bool auxState = false;
```

Each is a Boolean.

A Boolean has two logical values:

```text
true
false
```

In this project:

```text
true  → ON
false → OFF
```

Example:

```text
lightState = true
fanState = false
auxState = true
```

means:

```text
Light     ON
Fan       OFF
Auxiliary ON
```

---

# 6. Why Store State?

Suppose the browser sends:

```text
/light/on
```

The ESP32 turns the relay on.

But the dashboard also needs to know:

> What is the current state of the light?

The program therefore stores:

```cpp
lightState = true;
```

The stored state becomes a source of truth for the dashboard.

```text
Command
  ↓
State changes
  ↓
Hardware changes
  ↓
Dashboard reflects state
```

This pattern appears throughout embedded and distributed systems.

---

# 7. State Is Different from an Output Pin

Students often think:

```text
GPIO HIGH = State
```

But the concepts should be separated.

For an active-LOW relay:

```text
Software:
lightState = true

Physical control:
GPIO = LOW

Physical meaning:
Relay = ON
```

So:

```text
Software state
      ↓
Control logic
      ↓
Electrical signal
      ↓
Physical device
```

This is why the `RELAY_ON` and `RELAY_OFF` constants are useful.

---

# 8. Active-LOW Relay Logic

The source assumes:

```cpp
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;
```

Therefore:

```text
Software intention       GPIO       Relay
------------------------------------------
ON                         LOW       ON
OFF                        HIGH      OFF
```

This may initially feel backwards.

Students should remember:

> **The electrical logic of a module is part of the hardware interface.**

Do not blindly assume HIGH means ON.

---

# 9. Why Relay Modules Are Used

A GPIO pin is a logic interface.

A load may require a different voltage/current arrangement.

The relay provides switching functionality:

```text
ESP32
  │
  │ low-power control
  ▼
Relay
  │
  │ switching contacts
  ▼
Load
```

The important distinction is:

```text
CONTROL SIDE
ESP32 → relay input

LOAD SIDE
Power source → relay contacts → load
```

These should be treated as separate parts of the system.

---

# 10. Relay Contact Concept

A relay contains a controllable switching mechanism.

Conceptually:

```text
Control signal
     ↓
[ Relay ]
     ↓
Switching path
     ↓
Load
```

The relay allows the controller to command a switching action without the ESP32 GPIO being the load's power source.

However, the relay itself does not automatically make an unsafe circuit safe. The load, voltage, current, wiring, insulation, enclosure, and relay rating all matter.

---

# 11. Safe Classroom Load

For student experimentation, prefer:

```text
ESP32
 ↓
Relay
 ↓
Low-voltage lamp / LED / suitable DC load
```

Avoid using exposed household mains wiring as a classroom breadboard exercise.

The learning objective is the **control architecture**, not practicing dangerous electrical work.

---

# 12. GPIO Allocation

The source uses:

```text
GPIO 5  → Light
GPIO 18 → Fan
GPIO 19 → Auxiliary
```

Think of the GPIO map as the software/hardware contract:

```text
GPIO 5
  ↕
Light channel

GPIO 18
  ↕
Fan channel

GPIO 19
  ↕
Auxiliary channel
```

Changing the physical pin without changing the program breaks that contract.

---

# 13. The `applyRelayStates()` Function

The function centralizes output control.

Conceptually:

```text
lightState ──► Light GPIO
fanState   ──► Fan GPIO
auxState   ──► Auxiliary GPIO
```

Why is centralization useful?

Imagine ten devices.

If GPIO control is scattered everywhere, the program becomes difficult to reason about.

A centralized function creates a clean boundary:

```text
DEVICE STATE
     ↓
applyRelayStates()
     ↓
GPIO OUTPUT
```

---

# 14. Safe Startup

The program starts with:

```text
lightState = false;
fanState = false;
auxState = false;
```

Then applies those states.

The intended physical result is:

```text
Light     OFF
Fan       OFF
Auxiliary OFF
```

This is called a **known startup state**.

In real embedded systems, startup behavior is extremely important because users may not be standing next to the device when it boots.

---

# 15. Why Startup Safety Matters

Imagine a controller powering up after a reset.

If the fan accidentally starts:

```text
Unexpected startup
       ↓
Physical consequence
```

That may be inconvenient.

For a motor, heater, pump, or industrial actuator, it could be much more serious.

Therefore:

> **Define the startup behavior deliberately.**

Project 30 introduces this principle through an all-OFF startup.

---

# 16. Wi-Fi as the Communication Layer

The ESP32 connects to Wi-Fi in station mode.

Conceptually:

```text
ESP32
  ↓
Wi-Fi station
  ↓
Router
  ↓
Local network
```

The ESP32 receives an IP address.

For example:

```text
192.168.1.42
```

The user then opens:

```text
http://192.168.1.42
```

The actual address comes from the ESP32's Serial Monitor.

---

# 17. Client and Server

The browser is the client.

The ESP32 is the server.

```text
CLIENT                       SERVER
Browser ───── request ─────► ESP32
Browser ◄──── response ───── ESP32
```

This is the foundation of the project's remote-control mechanism.

---

# 18. HTTP Routes

The ESP32 creates multiple routes.

### Main page

```text
/
```

### Light

```text
/light/on
/light/off
```

### Fan

```text
/fan/on
/fan/off
```

### Auxiliary

```text
/aux/on
/aux/off
```

### Master control

```text
/all/off
```

### Status

```text
/status
```

Each route represents a specific operation or data interface.

---

# 19. What Happens When Light ON Is Pressed?

Follow the entire chain:

```text
User clicks ON
       ↓
Browser creates HTTP request
       ↓
GET /light/on
       ↓
Wi-Fi network
       ↓
ESP32 WebServer
       ↓
handleLightOn()
       ↓
lightState = true
       ↓
Relay command = ON
       ↓
GPIO 5 changes
       ↓
Light relay activates
       ↓
ESP32 generates dashboard
       ↓
Browser receives updated page
```

This is a complete digital-to-physical control pipeline.

---

# 20. Why the Dashboard Is Dynamic

The webpage contains values generated from the current state.

For example:

```cpp
page += lightState ? "ON" : "OFF";
```

The program asks:

```text
Is lightState true?
       /       \
     YES        NO
      ↓          ↓
     ON         OFF
```

The browser therefore receives a page representing the ESP32's current state.

---

# 21. Ternary Operator

This expression:

```cpp
lightState ? "ON" : "OFF"
```

is a compact conditional expression.

It means:

```text
condition ? value_if_true : value_if_false
```

So:

```cpp
lightState ? "ON" : "OFF"
```

means:

```text
If lightState is true → "ON"
Otherwise              → "OFF"
```

The same pattern is used for the fan and auxiliary device.

---

# 22. HTML + Embedded C++

The webpage is generated inside the ESP32 program.

Conceptually:

```text
C++ Program
     ↓
Current device states
     ↓
HTML generation
     ↓
HTTP response
     ↓
Browser
```

This demonstrates that an embedded device can act as both:

```text
Controller
+
Web server
```

---

# 23. Responsive Dashboard

The HTML includes a viewport setting so the dashboard can adapt better to mobile screens.

The layout uses multiple cards:

```text
┌───────────┐ ┌───────────┐ ┌───────────┐
│   LIGHT   │ │    FAN    │ │    AUX    │
│           │ │           │ │           │
│ ON / OFF  │ │ ON / OFF  │ │ ON / OFF  │
└───────────┘ └───────────┘ └───────────┘
```

This is a useful opportunity to connect embedded programming with basic web development.

---

# 24. Automatic Page Refresh

The dashboard refreshes approximately every 3 seconds.

Conceptually:

```text
Load page
   ↓
Show states
   ↓
Wait
   ↓
Reload
   ↓
Show latest states
```

This is a simple polling strategy.

It is easy to understand, but not the only way to build real-time interfaces.

---

# 25. The `/status` API

The status route produces:

```json
{
  "light": true,
  "fan": false,
  "auxiliary": true
}
```

This is not primarily designed for a human to read.

It is designed for another software component.

For example:

```text
Mobile App
     ↓
GET /status
     ↓
ESP32
     ↓
JSON
```

---

# 26. Why APIs Matter

Imagine a mobile app wants to know:

```text
Is the fan ON?
```

It should not need to scrape the visual HTML dashboard.

Instead, it can request:

```text
/status
```

and parse:

```json
"fan": true
```

This is the beginning of **API-driven system integration**.

---

# 27. Human Interface vs Machine Interface

Keep this distinction clear:

```text
             ESP32
            /     \
           /       \
        HTML       JSON
          ↓          ↓
       Human      Software
```

HTML:

```text
/
```

JSON:

```text
/status
```

This pattern becomes important when connecting embedded devices to larger software systems.

---

# 28. The Master OFF Function

The route:

```text
/all/off
```

sets all states to false.

Conceptually:

```text
/all/off
   ↓
Light = OFF
Fan = OFF
Auxiliary = OFF
   ↓
applyRelayStates()
   ↓
All outputs OFF
```

This is an example of a **system-level command**.

---

# 29. Individual vs Global Commands

The project therefore has two levels of control.

### Individual

```text
/light/on
/fan/off
/aux/on
```

### Global

```text
/all/off
```

This distinction is useful in larger systems.

For example:

```text
Room-level control
      +
Building-level control
```

can coexist.

---

# 30. Error Handling

The project includes a 404 handler.

If the browser requests:

```text
/unknown
```

the ESP32 returns:

```text
404 - Page Not Found
```

This demonstrates that web applications need to handle invalid requests as well as valid ones.

---

# 31. Network Information

The dashboard shows:

```text
SSID
IP address
RSSI
```

### SSID

The name of the connected Wi-Fi network.

### IP address

The local network address of the ESP32.

### RSSI

A measurement associated with received Wi-Fi signal strength.

These values are useful during testing and troubleshooting.

---

# 32. Understanding the Complete Control Path

A student should be able to trace this:

```text
Button
 ↓
Browser
 ↓
HTTP
 ↓
Wi-Fi
 ↓
ESP32 route
 ↓
State variable
 ↓
Relay logic
 ↓
GPIO
 ↓
Relay
 ↓
Physical device
```

If the device fails, each stage becomes a possible diagnostic layer.

---

# 33. Fault Isolation

Use:

```text
Browser
   ↓
HTTP route
   ↓
ESP32 handler
   ↓
State variable
   ↓
GPIO
   ↓
Relay
   ↓
Load
```

Do not replace components randomly.

Find the first point at which expected behavior stops.

---

# 34. Example Fault

Suppose:

```text
Browser button works
      ↓
Serial message appears
      ↓
Relay clicks
      ↓
Lamp remains OFF
```

The problem is probably not:

```text
Wi-Fi
```

because the request reached the ESP32.

It is also less likely to be:

```text
HTTP route
```

because the handler executed.

The investigation should move toward:

```text
Relay contact side
Load power
Load wiring
Relay rating
```

This is the value of layered debugging.

---

# 35. Experiment 1 — Add a Fourth Device

Students should not simply copy the three-device pattern.

Design a fourth channel.

For example:

```text
New GPIO
   ↓
New relay
   ↓
newDeviceState
   ↓
ON handler
   ↓
OFF handler
   ↓
Dashboard card
   ↓
Status API
```

### Questions

- Which GPIO will you use?
- What device will it represent?
- What should its startup state be?
- What route naming convention will you use?

---

# 36. Experiment 2 — Master Dashboard

Improve the dashboard with a prominent global control:

```text
┌─────────────────────────┐
│     ALL DEVICES OFF     │
└─────────────────────────┘
```

The button should request:

```text
/all/off
```

### Discussion

Why might a user want a master OFF control?

Possible contexts include:

```text
Leaving a room
End of classroom demonstration
Emergency shutdown concept
Night mode preparation
```

---

# 37. Experiment 3 — Dashboard UX

Modify the interface.

Students can add:

```text
Device icons
Current state
GPIO information
Network information
Better spacing
Mobile-friendly controls
```

The important lesson:

> A working system is not automatically a good user interface.

---

# 38. Experiment 4 — Add a PIR Sensor

Project 29 introduced motion sensing.

Combine it with Project 30:

```text
PIR
 ↓
ESP32
 ↓
Decision
 ↓
Light
```

Possible behavior:

```text
Motion detected
      ↓
Light ON
```

Now the system is no longer purely manual.

---

# 39. Experiment 5 — Temperature Controls Fan

Use the temperature-monitoring concepts from Project 28.

Architecture:

```text
Temperature Sensor
       ↓
      ESP32
       ↓
Temperature decision
       ↓
Fan relay
```

Example conceptual rule:

```text
Temperature high
      ↓
Fan ON
```

This is the beginning of **closed-loop automation**.

---

# 40. Manual Mode vs Automatic Mode

A stronger smart-home design supports:

```text
MANUAL
AUTO
```

### Manual

```text
Browser
   ↓
Command
   ↓
Device
```

### Automatic

```text
Sensor
   ↓
Decision
   ↓
Device
```

The ESP32 becomes a decision-making controller rather than simply a remote switch.

---

# 41. Why Modes Matter

Suppose the temperature is high and automatic mode turns the fan ON.

What if the user wants the fan OFF temporarily?

The system needs a clear rule.

For example:

```text
MANUAL mode
→ user controls the device

AUTO mode
→ system controls the device
```

This introduces the concept of **control authority**.

---

# 42. Experiment 6 — Build a Smart Room

Combine:

```text
PIR
LDR
Temperature sensor
```

with:

```text
Light
Fan
Auxiliary device
```

Possible architecture:

```text
             ┌──────────┐
             │   PIR    │
             └────┬─────┘
                  │
             ┌────▼─────┐
             │   LDR    │
             └────┬─────┘
                  │
        ┌─────────▼─────────┐
        │       ESP32       │
        │ Decision + State  │
        └───────┬───────────┘
                │
       ┌────────┼────────┐
       ▼        ▼        ▼
     Light     Fan      Aux
```

Now students are designing a small automation system rather than reproducing a demonstration.

---

# 43. Experiment 7 — Sensor + Manual Override

Design:

```text
AUTO mode
   ↓
Sensor controls device
```

and:

```text
MANUAL mode
   ↓
Browser controls device
```

The dashboard should clearly show which mode is active.

This introduces a more realistic automation pattern.

---

# 44. Experiment 8 — Expand the JSON API

The current API provides:

```json
{
  "light": true,
  "fan": false,
  "auxiliary": true
}
```

Students can think about extending it with:

```text
mode
uptime
sensor readings
Wi-Fi signal
device count
```

For example conceptually:

```json
{
  "light": true,
  "fan": false,
  "auxiliary": true,
  "mode": "auto"
}
```

The exact extension is a student design exercise.

---

# 45. Engineering Challenge — Smart Room

Build a complete low-voltage smart-room prototype.

### Minimum requirements

```text
✓ ESP32
✓ Wi-Fi
✓ 3 outputs
✓ Relay interface
✓ Browser dashboard
✓ Individual controls
✓ Master OFF
✓ State management
✓ JSON API
✓ Known startup state
```

### Add at least one:

```text
✓ PIR
or
✓ LDR
or
✓ Temperature sensor
```

### Then implement one automatic behavior.

---

# 46. Engineering Design Process

Students should follow:

```text
1. Define problem
       ↓
2. Define inputs
       ↓
3. Define outputs
       ↓
4. Define states
       ↓
5. Define decisions
       ↓
6. Design wiring
       ↓
7. Implement control
       ↓
8. Implement dashboard
       ↓
9. Test each layer
       ↓
10. Integrate
```

This is much closer to engineering practice than simply writing code until the project works.

---

# 47. Failure Scenarios to Discuss

### Wi-Fi failure

What should happen?

The physical system should have a defined local behavior rather than assuming the network is always available.

### ESP32 restart

What should the outputs become?

The project chooses:

```text
All OFF
```

### Sensor failure

What should automation do?

Possible design questions:

```text
Stop?
Use previous value?
Switch to manual?
Show an error?
```

### Relay failure

How could the software know?

The current project does not provide load feedback.

That is an important limitation.

---

# 48. Open-Loop vs Closed-Loop

The basic Project 30 system is largely **open-loop**:

```text
User command
   ↓
ESP32
   ↓
Relay
   ↓
Device
```

The controller sends a command but does not necessarily measure whether the physical device actually achieved the desired condition.

A closed-loop extension might be:

```text
Command
   ↓
Device
   ↓
Sensor / feedback
   ↓
ESP32
   ↓
Verify result
```

This is a major engineering concept.

---

# 49. Example of Feedback

Imagine the user requests:

```text
Light ON
```

Open-loop:

```text
ESP32 assumes ON
```

Closed-loop:

```text
ESP32 requests ON
       ↓
Sensor measures actual condition
       ↓
ESP32 verifies
```

Now the system can distinguish:

```text
Commanded ON
```

from:

```text
Actually ON
```

This is a valuable future extension.

---

# 50. Scalability

Three devices are easy to understand:

```text
Light
Fan
Aux
```

But imagine:

```text
20 lights
8 fans
10 sensors
4 doors
```

The program becomes difficult if every device is handled as completely independent custom code.

This motivates future concepts such as:

```text
Device abstraction
Data structures
Reusable handlers
Configuration tables
MQTT topics
REST APIs
Databases
Cloud dashboards
```

Project 30 is therefore a bridge toward advanced IoT architecture.

---

# 51. Security Discussion

The local demonstration is intentionally simple.

The web server does not implement a complete production authentication/security architecture.

Students should understand:

```text
Local classroom demo
        ≠
Production smart-home platform
```

A production system may require:

- authentication;
- authorization;
- encrypted communication;
- secure credentials;
- network segmentation;
- secure firmware;
- audit logging;
- safe remote access.

The current project should remain a controlled educational prototype.

---

# 52. Safety Discussion

This project controls relay interfaces, so electrical safety becomes more important than in LED-only projects.

Use:

```text
ESP32
 ↓
Relay
 ↓
Low-voltage demonstration load
```

for classroom work.

Do not place household mains voltage on an exposed breadboard.

For real electrical installations, the relevant equipment, wiring, isolation, enclosure, protection, and professional procedures must be appropriate to the installation.

---

# 53. Testing Matrix

| Layer | Test | Expected result |
|---|---|---|
| Power | ESP32 startup | Controller starts |
| Startup | Relay state | All outputs OFF |
| Network | Wi-Fi | Connected |
| Network | IP | Address displayed |
| Web | `/` | Dashboard loads |
| Light | `/light/on` | Relay ON |
| Light | `/light/off` | Relay OFF |
| Fan | `/fan/on` | Relay ON |
| Fan | `/fan/off` | Relay OFF |
| Auxiliary | `/aux/on` | Relay ON |
| Auxiliary | `/aux/off` | Relay OFF |
| Master | `/all/off` | All OFF |
| API | `/status` | Valid JSON |
| Error | Invalid route | 404 |

---

# 54. Debugging Questions

When something fails, ask:

```text
Did the user action occur?
        ↓
Did the browser send the request?
        ↓
Did the ESP32 receive the route?
        ↓
Did the handler execute?
        ↓
Did the state variable change?
        ↓
Did the GPIO change?
        ↓
Did the relay respond?
        ↓
Did the load respond?
```

This transforms debugging from guessing into a structured investigation.

---

# 55. Student Knowledge Check

1. Why is the ESP32 used instead of a normal physical switch?
2. What is the purpose of Wi-Fi in this project?
3. What is an IP address?
4. What is the role of the web server?
5. What is a route?
6. Why are device states stored as variables?
7. What does active-LOW mean?
8. Why is `RELAY_ON` defined separately?
9. Why should the startup state be known?
10. What does `/all/off` do?
11. What is the purpose of `/status`?
12. Why is JSON useful?
13. What is the difference between manual and automatic control?
14. What is open-loop control?
15. What would feedback add?
16. What happens if Wi-Fi fails?
17. Why should mains voltage not be used on the classroom breadboard?
18. How would you add a fourth device?
19. How would you add a PIR sensor?
20. How would you design a smart-room system?

---

# 56. Student Reflection

Ask students to write short answers:

### Before building

```text
What problem will this system solve?
```

### During building

```text
Which layer failed first?
How did you isolate it?
```

### After building

```text
What works?
What does not?
What would you improve?
```

### Engineering reflection

```text
What would happen if this system had to control
100 devices instead of 3?
```

---

# 57. Final Project Challenge

The final challenge is not to add random features.

It is to design a coherent system.

Students should submit:

```text
1. Problem statement
2. System architecture
3. Component list
4. GPIO map
5. State model
6. Control flow
7. Wiring diagram
8. Web interface
9. Testing table
10. Troubleshooting record
11. One automation rule
12. Future expansion plan
```

---

# 58. Final Mental Model

Everything learned in Level 4 can now be represented as:

```text
             ┌──────────────────┐
             │   PHYSICAL WORLD │
             └────────┬─────────┘
                      │
                   Sensors
                      │
                      ▼
             ┌──────────────────┐
             │      ESP32       │
             │                  │
             │ Read             │
             │ Process          │
             │ Decide           │
             │ Store State      │
             └───────┬──────────┘
                     │
          ┌──────────┼──────────┐
          ▼          ▼          ▼
       Light        Fan        Aux
          │          │          │
          └──────────┼──────────┘
                     │
                  Actuation
                     │
                     ▼
                  Wi-Fi
                     │
                     ▼
             ┌──────────────────┐
             │ Browser / API    │
             └──────────────────┘
```

The complete conceptual chain is:

```text
SENSE
  ↓
PROCESS
  ↓
DECIDE
  ↓
STORE STATE
  ↓
ACT
  ↓
CONNECT
  ↓
DISPLAY
  ↓
MONITOR
  ↓
AUTOMATE
```

---

# 59. Level 4 Completion

The sequence now tells a coherent story:

```text
25
ESP32 + Wi-Fi
     ↓
26
Web Server
     ↓
27
Remote Light Control
     ↓
28
Remote Sensor Monitoring
     ↓
29
Networked Event Alarm
     ↓
30
Multi-Device Smart Automation
```

Students have moved from asking:

> **How do I connect the ESP32 to Wi-Fi?**

to:

> **How can I build a connected system that interacts with the physical world?**

That is the central learning outcome of this level.

---

# 60. Beyond Project 30

The next stage can move toward:

```text
MQTT
  ↓
IoT messaging
  ↓
Cloud / backend concepts
  ↓
Databases
  ↓
Advanced dashboards
  ↓
Automation engines
  ↓
Authentication
  ↓
Security
  ↓
Production-style IoT architecture
```

Project 30 is therefore the bridge from **IoT demonstrations** to **IoT systems engineering**.
