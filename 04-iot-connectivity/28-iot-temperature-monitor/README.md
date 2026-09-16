# Project 28 — Wi-Fi Temperature Monitor

> **ESP32 + DHT22 + Wi-Fi + Local Web Dashboard**

## 🎯 Goal
Build a local IoT monitoring system that reads temperature and humidity from a DHT22 and displays the measurements through a web dashboard hosted by the ESP32.

```text
DHT22 → ESP32 → Wi-Fi → HTTP → Browser
```

## 🧠 Learning Objectives
- Read temperature and humidity from a DHT22.
- Understand digital sensor communication.
- Connect an ESP32 to Wi-Fi.
- Host a local HTTP dashboard.
- Handle invalid sensor readings.
- Use `millis()` for periodic sampling.
- Create a `/data` endpoint.
- Apply fault isolation during debugging.

## 🧰 Components

| Component | Purpose |
|---|---|
| ESP32 | Controller, Wi-Fi and web server |
| DHT22 | Temperature/humidity sensor |
| Breadboard | Prototyping |
| Jumper wires | Connections |
| USB cable | Power/programming |

## 🔌 Wiring

| DHT22 | ESP32 |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |

For a bare DHT22, use the appropriate DATA pull-up resistor according to the sensor documentation. Many modules already include it.

The source specifies GPIO 4 and DHT22. 

## 🌐 Web Dashboard

The dashboard displays:
- Temperature
- Humidity
- Sensor status
- SSID
- IP address
- RSSI
- DHT22 GPIO

It refreshes approximately every 5 seconds.

### Routes

| Route | Function |
|---|---|
| `/` | HTML dashboard |
| `/data` | Plain-text sensor data |
| Other | HTTP 404 |

Example `/data` response:

```text
Temperature: 24.5 C
Humidity: 57.0 %
```

## ⏱️ Sampling
The DHT22 is read approximately every **2 seconds** using `millis()`. This allows the ESP32 to continue processing web clients rather than blocking the main loop with a long delay.

## 🛡️ Sensor Validation

```text
Read DHT22
    ↓
Valid?
 ┌──┴──┐
Yes    No
 ↓      ↓
Store  Error
data   state
```

Invalid readings are not presented as normal sensor data.

## 🖥️ Testing

- [ ] DHT22 VCC → 3.3V
- [ ] DATA → GPIO 4
- [ ] GND → GND
- [ ] Pull-up verified where required
- [ ] DHT library installed
- [ ] Wi-Fi connected
- [ ] IP address visible at 115200 baud
- [ ] Sensor values visible
- [ ] Dashboard loads
- [ ] `/data` works
- [ ] Error handling works

## 🛠️ Troubleshooting

```text
DHT22 → GPIO → Processing → Wi-Fi → HTTP → Browser
```

If the sensor fails, check wiring, sensor type, pull-up and library. If the sensor works but the webpage fails, investigate the network/server layer.

## 🔬 Experiments

### 1. Temperature Warning
Add a threshold such as `> 30 °C`.

### 2. Minimum / Maximum
Track minimum and maximum temperature from valid readings.

### 3. Uptime
Display ESP32 uptime using `millis()`.

### 4. JSON API
Change `/data` to:

```json
{"temperature":24.5,"humidity":57.0}
```

### 5. Multiple Sensors
Extend the dashboard with additional environmental measurements.

## 🏆 Engineering Challenge
Build a local environmental dashboard with DHT22 temperature/humidity, Wi-Fi information, error handling, automatic refresh and a `/data` endpoint.

## ⚠️ Safety
This is a low-voltage sensor project. Do not connect mains voltage to the ESP32, DHT22, breadboard or exposed prototype.

## 📈 Progression

```text
25 Wi-Fi Connection
       ↓
26 Web Server
       ↓
27 Smart Light
       ↓
28 Temperature Monitor
       ↓
29 Motion Alarm
       ↓
30 Smart Home Automation
```

Project 28 introduces **remote monitoring**, complementing the actuator control introduced previously.
