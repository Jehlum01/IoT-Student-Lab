# Project 27 — Student Learning Notes

## 1. From Web Server to Actuator

Project 26 introduced the ESP32 web server. Project 27 connects it to an actuator:

```text
Browser → Wi-Fi → ESP32 → Relay → Light
```

This is a basic IoT actuator system. fileciteturn3file0L655-L676

## 2. Relay Fundamentals

A relay is an electrically controlled switch.

```text
ESP32
  ↓
Relay Driver / Coil
  ↓
Switching Mechanism
  ↓
Load Circuit
```

The control side and switched load side are functionally separated by the relay's switching mechanism; exact isolation depends on the module.

## 3. Why Not Drive the Light Directly?

Do not treat an ESP32 GPIO as a power output for a lamp or substantial load.

```text
ESP32 GPIO
    ↓
Relay / Driver
    ↓
Suitable Load Supply
    ↓
Light
```

## 4. Active-LOW Logic

For the relay assumed by the source:

```text
LOW  → ON
HIGH → OFF
```

The code defines:

```cpp
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;
```

Always verify your actual module.

## 5. HTTP Routes

The browser uses:

```text
GET /
GET /on
GET /off
```

The ESP32 maps these routes to handler functions.

```text
/on  → handleLightOn()
/off → handleLightOff()
/    → handleRoot()
```

Unknown routes are handled by a 404 response.

## 6. Software State

```cpp
bool lightState = false;
```

This variable represents the intended light state for the webpage.

Important engineering point: software state can differ from physical state if the relay, wiring, power, or load fails.

## 7. Dynamic Webpage

The webpage reports:

- Light ON/OFF state
- Wi-Fi SSID
- IP address
- RSSI
- Relay GPIO

The source uses `WiFi.SSID()`, `WiFi.localIP()`, and `WiFi.RSSI()` for this information. fileciteturn3file0L181-L205

## 8. Fault Isolation

Debug from the outside toward the physical system:

```text
Browser
   ↓
Network
   ↓
HTTP
   ↓
ESP32
   ↓
GPIO
   ↓
Relay
   ↓
Load
```

Ask one question at each layer. This is **fault isolation**. fileciteturn3file0L1042-L1074

## 9. Relay-First Testing

Before attaching the load:

1. Power the ESP32.
2. Confirm Wi-Fi.
3. Open the webpage.
4. Test ON/OFF.
5. Observe the relay indicator if available.
6. Listen for relay switching if applicable.
7. Confirm operation.
8. Connect the low-voltage load.

The source recommends this staged approach to reduce troubleshooting complexity. fileciteturn3file0L962-L970

## 10. Troubleshooting

| Problem | Investigate |
|---|---|
| Relay always ON | Trigger logic, startup state, wiring |
| Relay never ON | GPIO, VCC, GND, IN, power |
| ESP32 resets | Supply capacity, relay noise, wiring |
| Webpage unavailable | Wi-Fi and IP address |
| `/on` does nothing | HTTP route, GPIO, relay input |
| Relay switches but lamp does not | Load-side circuit |

## 11. Experiment — Physical Button

```text
Button ────────┐
               ├── ESP32 ── Relay ── Light
Browser ───────┘
```

Compare local control with network control.

## 12. Experiment — Two Lights

Add another relay output and independently control two low-voltage lights.

## 13. Experiment — Automatic Light

Add an LDR:

```text
LDR
 ↓
ESP32
 ↓
Decision
 ↓
Relay
 ↓
Light
```

This combines:

```text
SENSE → DECIDE → ACT
```

with remote control.

## 14. Engineering Challenge

Build a two-channel controller with:

- Two relay outputs
- Two low-voltage loads
- Independent browser controls
- Individual status
- Wi-Fi information
- Clear webpage layout

## 15. Safety

**Low-voltage DC loads only.**

Do not connect household AC/mains voltage to breadboards or exposed student circuits. A relay module does not automatically make mains experimentation safe. fileciteturn3file0L1199-L1209

## 16. Key Takeaways

```text
Wi-Fi
  ↓
HTTP
  ↓
ESP32
  ↓
GPIO
  ↓
Relay
  ↓
Electrical Load
```

The curriculum progression is:

```text
Project 25 — Networking
       ↓
Project 26 — Web Server
       ↓
Project 27 — Actuator Control
```

The next step introduces sensor-based remote monitoring. fileciteturn3file0L1235-L1267
