# Project 28 — Student Learning Notes

## 1. Remote Monitoring

Project 28 introduces the monitoring side of IoT:

```text
Sensor → ESP32 → Wi-Fi → Browser
```

The DHT22 supplies temperature and humidity; the ESP32 processes the measurements and serves them locally.

## 2. DHT22

The DHT22 is a digital temperature and humidity sensor.

```text
Temperature
Humidity
```

The project connects its DATA line to GPIO 4.

## 3. DHT Library

The program uses:

```cpp
#include <DHT.h>
DHT dht(DHT_PIN, DHT_TYPE);
dht.begin();
```

Measurements are obtained with:

```cpp
dht.readTemperature();
dht.readHumidity();
```

## 4. Why Validate Readings?

External sensors can fail to communicate.

```text
Read sensor
    ↓
Valid?
 ┌──┴──┐
Yes    No
 ↓      ↓
Store  Error
data   state
```

The program uses `isnan()` to detect invalid results and `sensorValid` to control dashboard behaviour.

## 5. Periodic Sampling

The sensor interval is approximately:

```text
2000 ms = 2 seconds
```

The project uses `millis()` so the main loop can continue serving web clients.

```text
Sensor timing
     +
Web server
     +
Other processing
```

## 6. Web Dashboard

The dashboard displays:

```text
Temperature
Humidity
Sensor Status
SSID
IP Address
RSSI
DHT22 GPIO
```

The browser refreshes approximately every 5 seconds.

## 7. `/data` Endpoint

The endpoint:

```text
/data
```

returns:

```text
Temperature: 24.5 C
Humidity: 57.0 %
```

This introduces the distinction between a human interface and a data interface.

## 8. Local IoT

```text
DHT22
  ↓
ESP32
  ↓
Wi-Fi
  ↓
Local Router
  ↓
Browser
```

The basic project does not require a cloud platform.

## 9. Testing

1. Verify VCC, DATA and GND.
2. Verify GPIO 4.
3. Open Serial Monitor at 115200 baud.
4. Confirm Wi-Fi connection.
5. Record the IP address.
6. Confirm valid sensor readings.
7. Open the IP address in a browser.
8. Test `/data`.

## 10. Fault Isolation

```text
DHT22
  ↓
GPIO 4
  ↓
Sensor Processing
  ↓
Wi-Fi
  ↓
HTTP Server
  ↓
Browser
```

Find the first layer where expected behaviour stops rather than changing everything simultaneously.

## 11. Troubleshooting

| Symptom | Investigate |
|---|---|
| DHT22 reading failed | Wiring, pull-up, sensor type, library |
| `nan` values | Sensor communication |
| Unrealistic values | Wiring, configuration, placement |
| Wi-Fi unavailable | Credentials/network |
| Dashboard unavailable | IP/network/server |
| `/data` unavailable | Route or sensor-validity state |

## 12. Experiments

### Temperature Warning
Create a threshold such as `>30 °C`.

### Minimum / Maximum
Track extrema from valid readings only.

### Uptime
Display seconds, minutes and hours using `millis()`.

### JSON API
Return:

```json
{
  "temperature": 24.5,
  "humidity": 57.0
}
```

### Multiple Sensors
Extend the dashboard with additional environmental measurements.

## 13. Engineering Challenge

Build a local environmental monitoring dashboard containing:

- DHT22 temperature
- DHT22 humidity
- Wi-Fi status
- IP address
- RSSI
- Error handling
- Automatic refresh
- `/data` endpoint

## 14. Key Takeaways

```text
READ
 ↓
PROCESS
 ↓
CONNECT
 ↓
SERVE
 ↓
MONITOR
```

## 15. Curriculum Progression

```text
25 — Wi-Fi Connection
        ↓
26 — Web Server
        ↓
27 — Smart Light
        ↓
28 — Temperature Monitor
        ↓
29 — Motion Alarm
        ↓
30 — Smart Home Automation
```

Project 28 moves the curriculum from networked actuation toward networked sensing and monitoring.
