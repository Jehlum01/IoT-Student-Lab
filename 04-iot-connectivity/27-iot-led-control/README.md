# Project 27 — Wi-Fi Smart Light

> **ESP32 + Wi-Fi + Web Server + Relay + Low-Voltage DC Load**

## 🎯 Project Goal

Build a basic IoT actuator system in which a browser controls a low-voltage DC light through an ESP32 and relay.

```text
Browser
   │ HTTP
   ▼
Wi-Fi Router
   │ Wi-Fi
   ▼
ESP32 Web Server
   │ GPIO 5
   ▼
Relay Module
   │
   ▼
Low-Voltage DC Light
```

This project extends the web-server concepts introduced in Project 26 by connecting the web interface to a real actuator. fileciteturn3file0L1-L5

## 🧠 Learning Objectives

- Explain the role of a relay in an IoT actuator system.
- Control a relay from an ESP32 GPIO.
- Understand active-LOW relay logic.
- Use HTTP routes such as `/`, `/on`, and `/off`.
- Trace a command from a browser to a physical load.
- Display network information on a web page.
- Apply fault-isolation techniques.
- Distinguish low-voltage classroom experiments from mains electrical systems.

## 🧰 Components

| Component | Purpose |
|---|---|
| ESP32 development board | Wi-Fi controller and web server |
| 1-channel relay module | Electrically controlled switching |
| Low-voltage DC lamp/load | Physical output |
| Suitable external DC supply | Powers the load |
| Breadboard & jumper wires | Prototyping |
| USB cable | ESP32 power/programming |

## 🔌 Pin Assignment

| ESP32 | Relay |
|---|---|
| GPIO 5 | IN |
| GND | GND |
| Appropriate supply | VCC* |

*Follow the exact relay module specifications.*

The source assumes an active-LOW relay: `LOW = ON`, `HIGH = OFF`. fileciteturn3file0L48-L55

## 🌐 Web Interface

| Route | Function |
|---|---|
| `/` | Display the control page |
| `/on` | Turn the light ON |
| `/off` | Turn the light OFF |
| Other route | Return HTTP 404 |

The page displays light state, SSID, IP address, RSSI, and relay GPIO.

## 🔄 Turn ON

```text
ON button
   ↓
GET /on
   ↓
ESP32
   ↓
lightState = true
   ↓
GPIO 5 = LOW
   ↓
Relay ON
   ↓
Light ON
```

## 🔄 Turn OFF

```text
OFF button
   ↓
GET /off
   ↓
ESP32
   ↓
lightState = false
   ↓
GPIO 5 = HIGH
   ↓
Relay OFF
   ↓
Light OFF
```

## 💻 Program Structure

```text
setup()
 ├─ Configure relay GPIO
 ├─ Keep relay OFF during startup
 ├─ Start Serial Monitor
 ├─ Connect to Wi-Fi
 ├─ Register routes
 └─ Start web server

loop()
 └─ server.handleClient()
```

The project registers `/`, `/on`, `/off`, and a not-found handler. fileciteturn3file0L343-L403

## 🧪 Testing Checklist

- [ ] Relay wiring verified
- [ ] Low-voltage DC load only
- [ ] Relay starts OFF
- [ ] Wi-Fi connects
- [ ] IP address appears
- [ ] Webpage loads
- [ ] ON command activates relay
- [ ] OFF command deactivates relay
- [ ] Light follows relay state

## 🛠️ Troubleshooting

| Symptom | Check |
|---|---|
| Relay always ON | Active-LOW logic, startup state, wiring |
| Relay never activates | GPIO 5, VCC, GND, IN, trigger logic |
| ESP32 resets | Power supply, relay noise, wiring |
| Webpage unavailable | Wi-Fi connection and IP |
| Relay works but light does not | Load-side wiring and supply |

Use layered fault isolation:

```text
Browser → Network → HTTP → ESP32 → GPIO → Relay → Load
```

## 🔬 Experiments

### 1. Physical Button

```text
Physical Button ──┐
                  ├── ESP32 ── Relay ── Light
Browser ──────────┘
```

Compare local and network control.

### 2. Two Lights

Add a second relay channel and independently control two low-voltage loads.

### 3. Automatic Light

Add an LDR:

```text
LDR → ESP32 → Decision → Relay → Light
```

This introduces **SENSE → DECIDE → ACT** alongside remote control.

### 4. Manual + Wi-Fi Control

Combine a physical button with browser control and define how both inputs update the light state.

## 🏆 Engineering Challenge

Build a two-channel Wi-Fi smart-light controller with two relay outputs, two low-voltage loads, independent browser controls, status display, Wi-Fi information, and a clear webpage.

## ⚠️ Safety

**Use low-voltage DC loads only.**

Do not connect household AC/mains voltage to a breadboard or exposed classroom circuit. A relay module does not automatically make mains experimentation safe. fileciteturn3file0L1199-L1209

## 📈 Curriculum Progression

```text
Project 25 — Wi-Fi Connection
          ↓
Project 26 — Web Server
          ↓
Project 27 — Actuator Control
          ↓
Project 28 — Sensor Monitoring
          ↓
Project 29 — Network Alerts
          ↓
Project 30 — Multi-Device Automation
```

**Key distinction:** Project 26 teaches the web-server mechanism; Project 27 applies it to a real IoT actuator. fileciteturn3file0L1275-L1311
