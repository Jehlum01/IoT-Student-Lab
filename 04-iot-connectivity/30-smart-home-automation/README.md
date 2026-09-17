# 🏠 Project 30 — Smart Home Automation

> **Final Level 4 Integration Project — ESP32 + Wi-Fi + Web Control + Multiple Devices + Relay Switching**

Project 30 is the culmination of the Level 4 IoT Connectivity sequence. Instead of controlling one output, students build a small **multi-device smart-home controller** in which an ESP32 connects to Wi-Fi, hosts a web dashboard, maintains the state of several devices, and controls them through relay interfaces.

The source curriculum explicitly positions this as the final Level 4 integration project and connects Wi-Fi, ESP32, web/remote control, multiple outputs, and smart-home automation. fileciteturn5file0L1-L14

---

# 1. The Big Idea

A conventional switch controls one device locally:

```text
Human
  ↓
Physical Switch
  ↓
Light
```

This project changes the control model:

```text
Human
  ↓
Phone / Laptop
  ↓
Browser
  ↓
Wi-Fi
  ↓
ESP32
  ↓
Relay
  ↓
Device
```

And because the ESP32 controls multiple outputs:

```text
                         ┌──► Light
                         │
Browser → Wi-Fi → ESP32 ─┼──► Fan
                         │
                         └──► Auxiliary Device
```

The student is no longer learning a single circuit in isolation.

The student is learning how to assemble **a small connected control system**.

---

# 2. Learning Objectives

By the end of this project, students should be able to:

- explain the architecture of a local smart-home system;
- connect an ESP32 to a Wi-Fi network;
- understand the role of an IP address;
- explain browser-to-ESP32 HTTP communication;
- control multiple GPIO outputs;
- represent individual device states using Boolean variables;
- understand active-LOW relay logic;
- distinguish a GPIO control signal from the power delivered to a load;
- implement safe startup states;
- create separate HTTP routes for multiple devices;
- implement a master/all-off function;
- build a dynamic browser dashboard;
- expose machine-readable JSON status;
- troubleshoot the system layer by layer;
- extend manual control into sensor-based automation.

---

# 3. Project Position in the Learning Path

```text
25 — ESP32 Wi-Fi Connection
          ↓
26 — ESP32 Web Server
          ↓
27 — Wi-Fi Smart Light
          ↓
28 — Wi-Fi Temperature Monitor
          ↓
29 — Wi-Fi Motion Alarm
          ↓
30 — Smart Home Automation
```

The progression is intentional:

```text
CONNECT
   ↓
SERVE
   ↓
CONTROL
   ↓
MONITOR
   ↓
RESPOND
   ↓
AUTOMATE
```

Project 30 combines these ideas into one multi-output system.

---

# 4. What Students Build

The implementation controls three device channels:

1. **Light**
2. **Fan**
3. **Auxiliary device**

The browser provides independent ON/OFF controls for each.

```text
                SMART HOME DASHBOARD

       ┌────────────┐
       │   LIGHT    │
       │  ON / OFF  │
       └────────────┘

       ┌────────────┐
       │    FAN     │
       │  ON / OFF  │
       └────────────┘

       ┌────────────┐
       │ AUXILIARY  │
       │  ON / OFF  │
       └────────────┘
```

The ESP32 remembers each device's current state.

---

# 5. Components

| Component | Role | Main concept |
|---|---|---|
| ESP32 development board | Controller + Wi-Fi | Embedded + networking |
| Relay module / relay channels | Switch interface | Actuation |
| Low-voltage demonstration load | Device being controlled | Physical output |
| Breadboard | Prototype assembly | Circuit organization |
| Jumper wires | Connections | Signal/power routing |
| USB cable | ESP32 power/programming | Development |

For early classroom testing, LEDs can be used as low-voltage demonstration loads before moving to any actual appliance interface.

---

# 6. GPIO Mapping

| Device | ESP32 GPIO |
|---|---:|
| Light relay | GPIO 5 |
| Fan relay | GPIO 18 |
| Auxiliary relay | GPIO 19 |

Conceptually:

```text
GPIO 5  → Light relay
GPIO 18 → Fan relay
GPIO 19 → Auxiliary relay
```

---

# 7. System Architecture

```text
                    USER
                      │
                      ▼
             ┌────────────────┐
             │ Phone / Laptop │
             │    Browser     │
             └───────┬────────┘
                     │
                   HTTP
                     │
                   Wi-Fi
                     │
                     ▼
             ┌────────────────┐
             │      ESP32     │
             │                │
             │ Web Server     │
             │ State Logic    │
             └───┬─────┬────┬─┘
                 │     │    │
              GPIO 5 GPIO18 GPIO19
                 │     │    │
                 ▼     ▼    ▼
              Relay  Relay Relay
                 │     │    │
                 ▼     ▼    ▼
               Light  Fan  Auxiliary
```

The system has three major layers:

```text
USER INTERFACE
      ↓
NETWORK + CONTROLLER
      ↓
PHYSICAL DEVICES
```

---

# 8. Relay: Why Is It Needed?

The ESP32 GPIO is primarily a **logic/control interface**.

A relay creates a switching interface between the controller and an appropriate external load:

```text
ESP32
  │
  │ Control signal
  ▼
Relay
  │
  │ Switching
  ▼
Load
```

This does not mean that every load can safely be connected to any relay.

The relay, wiring, power source, connector, enclosure, and load must all be appropriate for the application.

---

# 9. Active-LOW Relay Logic

The example assumes an active-LOW relay:

```text
GPIO LOW
   ↓
Relay ON
```

and:

```text
GPIO HIGH
   ↓
Relay OFF
```

Therefore the program defines:

```cpp
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;
```

This is a crucial lesson because students often assume:

```text
HIGH = ON
LOW  = OFF
```

That assumption is not universally correct for modules.

**Always verify the exact relay board being used.**

---

# 10. Device State Management

Each device has a Boolean state:

```cpp
bool lightState = false;
bool fanState = false;
bool auxState = false;
```

The states represent:

```text
true  → ON
false → OFF
```

Example:

```text
lightState = true
fanState   = false
auxState   = true
```

means:

```text
Light     → ON
Fan       → OFF
Auxiliary → ON
```

The state is important because the dashboard needs to know what the system currently believes each device's condition to be.

---

# 11. Applying the States to Hardware

The function:

```cpp
applyRelayStates()
```

maps software state to GPIO output.

Conceptually:

```text
lightState
     ↓
Light relay GPIO

fanState
     ↓
Fan relay GPIO

auxState
     ↓
Auxiliary relay GPIO
```

This separation is useful because it keeps the **device state model** distinct from the physical GPIO operation.

---

# 12. Safe Startup

The program deliberately starts with all devices OFF:

```text
Light     → OFF
Fan       → OFF
Auxiliary → OFF
```

This is a valuable embedded-systems design principle:

> **A system should have a known startup state.**

Without an intentional startup state, an unexpected GPIO level could cause an output to activate at boot.

---

# 13. Web Dashboard

The browser dashboard provides three independent device cards.

Each card contains:

```text
Device name
Current state
ON button
OFF button
```

For example:

```text
┌────────────────────┐
│       LIGHT        │
│                    │
│        ON          │
│                    │
│   [ ON ] [ OFF ]   │
└────────────────────┘
```

The same pattern is used for the fan and auxiliary device.

The page also displays network information:

- SSID
- IP address
- RSSI
- GPIO assignments

---

# 14. HTTP Routes

Each button corresponds to a web route.

| Route | Function |
|---|---|
| `/` | Dashboard |
| `/light/on` | Turn light ON |
| `/light/off` | Turn light OFF |
| `/fan/on` | Turn fan ON |
| `/fan/off` | Turn fan OFF |
| `/aux/on` | Turn auxiliary ON |
| `/aux/off` | Turn auxiliary OFF |
| `/all/off` | Turn everything OFF |
| `/status` | Return JSON status |

This demonstrates how a single ESP32 can expose multiple control endpoints.

---

# 15. Browser Request Flow

When the user presses Light → ON:

```text
User
 ↓
Clicks ON
 ↓
Browser
 ↓
GET /light/on
 ↓
Wi-Fi
 ↓
ESP32
 ↓
handleLightOn()
 ↓
lightState = true
 ↓
Relay ON
 ↓
Updated dashboard
```

The same pattern is repeated for the fan and auxiliary device.

---

# 16. Master OFF

The project includes:

```text
/all/off
```

This sets:

```text
Light     → OFF
Fan       → OFF
Auxiliary → OFF
```

The concept is important because larger automation systems often require an overarching control mode:

```text
Individual control
        +
System-level control
```

In the classroom prototype, `/all/off` also provides a convenient master shutdown function.

---

# 17. Status API

The project provides:

```text
/status
```

Example:

```json
{
  "light": true,
  "fan": false,
  "auxiliary": true
}
```

This creates two interfaces:

```text
HTML
 ↓
Human interface

JSON
 ↓
Machine interface
```

A future application could consume this JSON without needing to understand the HTML page.

---

# 18. Local Network Model

This implementation is intentionally local:

```text
Phone / Laptop
      │
      ▼
Wi-Fi Router
      │
      ▼
ESP32
```

The browser and ESP32 need to be reachable on the same local network for the basic demonstration.

The source curriculum intentionally establishes this local ESP32 foundation rather than requiring a third-party cloud platform. fileciteturn5file0L31-L31

---

# 19. Testing Strategy

Test progressively.

```text
1. ESP32 startup
       ↓
2. Relay logic
       ↓
3. One device
       ↓
4. All three devices
       ↓
5. Web dashboard
       ↓
6. Individual routes
       ↓
7. Master OFF
       ↓
8. JSON API
```

This makes debugging much easier than testing the entire system simultaneously.

---

# 20. Observation Table

| Test | Expected result | Actual result | Pass? |
|---|---|---|---|
| ESP32 startup | All outputs OFF | | |
| Wi-Fi | Connected | | |
| Dashboard | Opens | | |
| Light ON | Light relay activates | | |
| Light OFF | Light relay deactivates | | |
| Fan ON | Fan relay activates | | |
| Fan OFF | Fan relay deactivates | | |
| Auxiliary ON | Auxiliary relay activates | | |
| Auxiliary OFF | Auxiliary relay deactivates | | |
| `/all/off` | All OFF | | |
| `/status` | JSON returned | | |

---

# 21. Troubleshooting

## ESP32 does not connect to Wi-Fi

Check:

- SSID;
- password;
- network availability;
- ESP32 startup messages;
- compatible local network.

## Dashboard does not open

Check:

```text
Wi-Fi connected?
      ↓
IP address received?
      ↓
Correct IP entered?
      ↓
Browser device on same network?
      ↓
Web server started?
```

## Relay works backwards

Your module may use different logic.

Verify the module and adjust the ON/OFF logic accordingly.

## Relay clicks but device does not operate

Separate the control-side problem from the load-side problem:

```text
Browser
 ↓
HTTP route
 ↓
ESP32 GPIO
 ↓
Relay
 ↓
Load-side wiring
 ↓
Device
```

If the relay responds but the load does not, investigate the load-side circuit separately.

---

# 22. Safety

For student laboratory work:

> **Use low-voltage demonstration loads.**

Do not connect household AC mains directly to a breadboard or ESP32 circuit.

Real mains switching requires appropriate:

- isolation;
- relay/contact ratings;
- wiring;
- enclosure;
- protection;
- load calculations;
- supervision.

A safe learning progression is:

```text
ESP32
  ↓
Relay module
  ↓
LED / low-voltage load
```

before studying professional mains-control implementations.

---

# 23. Experiments

### Experiment 1 — Add a Fourth Device

Add another output and create a new state variable.

Students must design:

```text
New GPIO
   ↓
New relay
   ↓
New device state
   ↓
ON route
   ↓
OFF route
   ↓
Dashboard card
```

### Experiment 2 — Master Dashboard

Create a clearly visible:

```text
ALL DEVICES OFF
```

control using:

```text
/all/off
```

Discuss why system-level controls can be useful.

### Experiment 3 — Dashboard Design

Improve the interface with:

- device icons;
- clearer status indicators;
- responsive layout;
- device descriptions;
- network information.

### Experiment 4 — Add Sensors

Bring concepts from earlier projects into this system:

```text
PIR
 ↓
ESP32
 ↓
Light
```

or:

```text
Temperature
 ↓
ESP32
 ↓
Fan
```

This is the transition from **manual remote control** to **automatic control**.

### Experiment 5 — Manual + Automatic Modes

Create:

```text
MANUAL
AUTO
```

Manual:

```text
Browser → ESP32 → Device
```

Automatic:

```text
Sensor → Decision → ESP32 → Device
```

This is one of the most important conceptual extensions.

---

# 24. Engineering Challenge

## Build a Smart Room

Design a low-voltage smart-room prototype containing at least:

- three controllable outputs;
- Wi-Fi;
- browser dashboard;
- individual device controls;
- master OFF;
- status API;
- known startup state;
- fault-isolation plan.

Then add at least one sensor.

Possible architecture:

```text
                 ┌──────────────┐
                 │    SENSORS   │
                 └──────┬───────┘
                        ↓
                 ┌──────────────┐
                 │    ESP32     │
                 │              │
                 │ Decision     │
                 │ State        │
                 │ Web Server   │
                 └──────┬───────┘
                        │
             ┌──────────┼──────────┐
             ↓          ↓          ↓
           Light       Fan      Auxiliary
```

---

# 25. Design Questions

Before building an extension, answer:

1. What problem is the system solving?
2. What devices need control?
3. What sensors are required?
4. What should happen when Wi-Fi fails?
5. What should the startup state be?
6. Should automatic mode override manual mode?
7. What happens if a sensor gives an invalid reading?
8. How will you detect a failed relay?
9. How will another application obtain device states?
10. How can the system be expanded without rewriting everything?

---

# 26. Real-World Connection

A production smart-home architecture may contain:

```text
Sensors
   ↓
Edge Controller
   ↓
Decision / Automation
   ↓
Actuators
   ↓
Network
   ↓
App / Dashboard
   ↓
Data / Automation Services
```

The student project is a simplified local version of this architecture.

The important learning outcome is not merely switching three outputs.

It is understanding the architecture behind connected automation.

---

# 27. Key Takeaways

Students should be able to explain:

```text
Browser
   ↓
HTTP
   ↓
Wi-Fi
   ↓
ESP32
   ↓
State
   ↓
GPIO
   ↓
Relay
   ↓
Physical Device
```

And they should understand that:

> **Smart automation is the combination of sensing, decision-making, communication, state, and actuation.**

---

# 28. Completion Checklist

- [ ] ESP32 powered
- [ ] Relay channels connected correctly
- [ ] Low-voltage loads selected
- [ ] Startup state verified OFF
- [ ] Wi-Fi connected
- [ ] IP address identified
- [ ] Dashboard opens
- [ ] Light ON/OFF works
- [ ] Fan ON/OFF works
- [ ] Auxiliary ON/OFF works
- [ ] `/all/off` works
- [ ] `/status` returns JSON
- [ ] At least one experiment completed
- [ ] Fault-isolation process documented
- [ ] Smart-room extension designed

---

# 29. Final Level 4 Challenge

Do not stop at reproducing the supplied circuit.

Redesign the system.

Your final project proposal should answer:

```text
WHAT problem am I solving?
        ↓
WHAT should I sense?
        ↓
WHAT decision should the ESP32 make?
        ↓
WHAT should it control?
        ↓
HOW should the user interact with it?
        ↓
HOW should another application access its data?
        ↓
WHAT happens when something fails?
```

The objective has now changed from:

> **Make the code work.**

to:

> **Design a connected system that solves a problem.**
