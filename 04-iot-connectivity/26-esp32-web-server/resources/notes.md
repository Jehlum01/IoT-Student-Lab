# Project 26 — ESP32 Web Server — Detailed Learning Notes

## 1. Why This Project Matters

A Wi-Fi connection becomes much more useful when the ESP32 can provide an application interface.

The progression is:

```text
Wi-Fi
  ↓
IP Address
  ↓
HTTP
  ↓
Web Server
  ↓
HTML
  ↓
GPIO
  ↓
Physical Output
```

This is the foundation of many local IoT systems.

## 2. Web Server

A web server listens for client requests and sends responses.

Here:

```text
Browser = Client
ESP32   = Server
```

```text
Browser ───── HTTP Request ─────► ESP32
Browser ◄──── HTTP Response ───── ESP32
```

The ESP32 combines embedded control and application-server functionality.

## 3. HTTP

HTTP means **HyperText Transfer Protocol**.

A browser can send a request such as:

```text
GET /on
```

The ESP32 interprets the route and performs the associated action.

## 4. URL Anatomy

Example:

```text
http://192.168.1.42/on
  │       │          │
  │       │          └─ path
  │       └──────────── host/IP
  └──────────────────── protocol
```

The IP identifies the ESP32 on the local network, while the path identifies the requested application resource/action.

## 5. Port 80

The server is created with:

```cpp
WebServer server(80);
```

Port 80 is the conventional HTTP port.

Therefore:

```text
http://192.168.1.42
```

normally targets port 80 automatically.

## 6. Routes

The project provides:

```text
/       → webpage
/on     → LED ON
/off    → LED OFF
```

This creates a simple API-like interface.

```text
External event
      ↓
HTTP route
      ↓
C++ handler
      ↓
Hardware action
```

## 7. Client-Server Model

### Browser
- Initiates requests.
- Displays HTML.
- Provides buttons.

### ESP32
- Receives requests.
- Selects a handler.
- Controls GPIO.
- Generates responses.

This pattern is also used in larger web applications.

## 8. HTML

HTML provides webpage structure.

Example:

```html
<h1>IoT Student Lab</h1>
```

The ESP32 sends HTML to the browser, which renders it as a webpage.

## 9. CSS

CSS controls presentation:

- Fonts
- Spacing
- Cards
- Buttons
- Alignment
- Backgrounds
- Text size

The project therefore combines:

```text
HTML → structure
CSS  → presentation
C++  → device logic
```

## 10. Dynamic Web Content

The page contains live device information:

```text
SSID
IP Address
RSSI
LED State
GPIO
```

The ESP32 inserts these values before sending the response.

```text
ESP32 state
    ↓
HTML template
    ↓
Dynamic values
    ↓
HTTP response
    ↓
Browser
```

## 11. Wi-Fi Information

The program can obtain:

```cpp
WiFi.SSID()
WiFi.localIP()
WiFi.RSSI()
```

These provide the connected network name, local IP and received signal strength.

## 12. GPIO Control

GPIO 5 is the output.

```text
GPIO HIGH → LED ON
GPIO LOW  → LED OFF
```

The code uses:

```cpp
digitalWrite(LED_PIN, HIGH);
```

and:

```cpp
digitalWrite(LED_PIN, LOW);
```

The network request therefore becomes a GPIO operation.

## 13. Software State

The project stores:

```cpp
bool ledState = false;
```

```text
false → OFF
true  → ON
```

The state is used both for control and for displaying the current condition on the webpage.

## 14. `server.handleClient()`

The main loop calls:

```cpp
server.handleClient();
```

Conceptually:

```text
Check for request
       ↓
Request?
 /          No          Yes
 |           |
 |        Find route
 |           |
 |       Run handler
 └─────┬─────┘
       ↓
     Repeat
```

This allows the server to process incoming browser requests.

## 15. 404 Handling

An unknown route such as:

```text
/test
```

does not match the defined routes.

The program calls:

```text
handleNotFound()
```

and returns:

```text
404 - Page Not Found
```

This teaches predictable handling of invalid input.

## 16. Testing

Follow this sequence:

```text
Program ESP32
      ↓
Open Serial Monitor
      ↓
Confirm Wi-Fi
      ↓
Record IP
      ↓
Open IP in browser
      ↓
Test /
      ↓
Test /on
      ↓
Test /off
      ↓
Test invalid route
```

## 17. Serial Debugging

Typical startup:

```text
Wi-Fi connected!

SSID: IoT-Lab
IP Address: 192.168.1.42
RSSI: -54 dBm

Web server started.
Open: http://192.168.1.42
```

ON:

```text
HTTP request: /on
LED → ON
```

OFF:

```text
HTTP request: /off
LED → OFF
```

This gives visibility into what the embedded system is receiving.

## 18. Troubleshooting Layers

Use this order:

```text
1. Hardware
   ↓
2. Wi-Fi
   ↓
3. IP
   ↓
4. HTTP server
   ↓
5. Route
   ↓
6. GPIO
   ↓
7. LED
```

### Hardware problem
Check power, wiring, resistor and LED polarity.

### Wi-Fi problem
Check credentials, connection and signal.

### IP problem
Check the current address printed by the ESP32.

### Network problem
Check local reachability, firewall and client isolation.

### HTTP problem
Check server startup and URL.

### Route problem
Check `/`, `/on`, `/off`.

### GPIO problem
Check GPIO 5 and `digitalWrite()` behaviour.

## 19. Network Failure vs Application Failure

### Network failure

```text
Browser
   X
ESP32
```

The request does not reach the application.

### Application failure

```text
Browser
   ↓
ESP32
   ↓
Wrong route / handler behaviour
```

### Hardware failure

```text
Browser
   ↓
ESP32
   ↓
GPIO
   X
LED
```

Separating these cases is an important engineering debugging skill.

## 20. Experiment — `/blink`

Create a route:

```text
/blink
```

Make the LED blink three times.

A more advanced version can use non-blocking timing so the server remains responsive during the sequence.

## 21. Experiment — `/status`

Create:

```text
/status
```

Return:

```text
LED: ON
```

or:

```text
LED: OFF
```

This introduces the difference between:

```text
/on      → command
/off     → command
/status  → information
```

## 22. Experiment — Uptime

Use:

```cpp
millis()
```

to calculate how long the ESP32 has been running.

Display:

```text
Seconds
Minutes
Hours
```

This introduces device telemetry.

## 23. Experiment — Second LED

Add a second output.

Possible routes:

```text
/led2/on
/led2/off
```

Display both states in the webpage.

## 24. Engineering Challenge

Build a dashboard:

```text
┌──────────────────────────────┐
│       ESP32 DASHBOARD        │
├──────────────────────────────┤
│ Wi-Fi: Connected             │
│ SSID: IoT-Lab                │
│ IP: 192.168.x.x              │
│ RSSI: -55 dBm                │
├──────────────────────────────┤
│ LED 1: ON                    │
│ [ ON ] [ OFF ]               │
│                              │
│ LED 2: OFF                   │
│ [ ON ] [ OFF ]               │
└──────────────────────────────┘
```

This combines networking, HTTP, HTML, CSS, state management and GPIO.

## 25. Security

The project is a local demonstration and does not provide:

- Authentication
- HTTPS
- User accounts
- Authorization
- Secure credential management

Therefore:

- Keep it on a controlled local network.
- Never publish real Wi-Fi passwords.
- Do not expose it directly to the public Internet.
- Do not use it for safety-critical systems.
- Do not connect mains voltage directly to GPIO.

## 26. Real-World Applications

The architecture can later control:

```text
Browser → ESP32 → LED
Browser → ESP32 → Relay driver
Browser → ESP32 → Servo
Browser → ESP32 → Buzzer
Browser → ESP32 → Motor controller
```

It can also be reversed for monitoring:

```text
Sensor → ESP32 → Wi-Fi → Browser
```

Eventually:

```text
Sensor
  ↓
ESP32
  ↓
Wi-Fi
  ↓
Server / Dashboard
  ↓
Decision
  ↓
Actuator
```

## 27. Reflection Questions

1. What is a web server?
2. What is the difference between client and server?
3. What is HTTP?
4. What is a URL?
5. What is a route?
6. Why is port 80 used?
7. Why does `/on` call a function?
8. What does `digitalWrite()` do?
9. Why is `ledState` useful?
10. Why does the browser need the ESP32 IP?
11. What does a 404 response mean?
12. Why is `server.handleClient()` needed?
13. Why can local IoT work without Internet access?
14. How would you add a second LED?
15. Why should this simple server not be exposed publicly?

## 28. Observation Table

| Test | Expected | Actual | Pass? |
|---|---|---|---|
| Startup | Serial banner | | |
| Wi-Fi | Connected | | |
| IP | Address shown | | |
| Server | Started | | |
| `/` | Webpage | | |
| `/on` | LED ON | | |
| `/off` | LED OFF | | |
| Invalid route | 404 | | |

## 29. Final Mental Model

```text
                 USER
                   ↓
                BROWSER
                   ↓
                HTTP GET
                   ↓
               Wi-Fi/LAN
                   ↓
             ESP32 SERVER
                   ↓
             ROUTE HANDLER
                   ↓
                 GPIO 5
                   ↓
                  LED
```

> **Key takeaway:** a web request can become a physical action when embedded software connects network events to hardware outputs.
