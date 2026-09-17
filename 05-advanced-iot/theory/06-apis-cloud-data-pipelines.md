# L5-T06 — APIs, Cloud & IoT Data Pipelines

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Understand:

- APIs
- REST
- Backend systems
- Databases
- IoT data pipelines
- Dashboards
- Data flow from device to application

---

# 1. IoT Is More Than the Device

A complete IoT system can contain:

```text
Device
Network
API
Backend
Database
Dashboard
````

---

# 2. Data Pipeline

A typical pipeline is:

```text
Sensor
  ↓
ESP32
  ↓
Network
  ↓
MQTT / HTTP
  ↓
Backend
  ↓
Database
  ↓
Dashboard
```

---

# 3. API

An API provides an interface through which software systems communicate.

For example:

```text
ESP32
  │
  │ POST
  ▼
API Server
```

The server receives data.

---

# 4. REST API

A REST-style API commonly uses HTTP methods such as:

```text
GET
POST
PUT
DELETE
```

Examples:

```text
GET /devices
GET /devices/01
POST /sensor-data
PUT /devices/01
DELETE /devices/01
```

---

# 5. GET

GET is commonly used to retrieve information.

Example:

```text
GET /temperature
```

Possible response:

```json
{
  "temperature": 26.4
}
```

---

# 6. POST

POST can be used to submit data.

Example:

```text
POST /sensor-data
```

Payload:

```json
{
  "device": "esp32-01",
  "temperature": 26.4,
  "humidity": 58
}
```

---

# 7. Backend

The backend performs application-level processing.

For example:

```text
MQTT Message
     ↓
Backend
     ↓
Validate
     ↓
Store
     ↓
Analyze
```

---

# 8. Database

A database stores information for later use.

Example:

```text
Time        Temperature
10:00       24.5
10:05       24.8
10:10       25.1
```

This allows historical analysis.

---

# 9. Dashboard

A dashboard presents information to humans.

```text
Database
   ↓
Backend/API
   ↓
Dashboard
```

Example:

```text
Temperature: 25.4 °C
Humidity:    61 %
Devices:     18 Online
Alerts:       2
```

---

# 10. Complete Architecture

```text
┌────────────┐
│   Sensor   │
└─────┬──────┘
      ↓
┌────────────┐
│   ESP32    │
└─────┬──────┘
      ↓
┌────────────┐
│ MQTT/HTTP  │
└─────┬──────┘
      ↓
┌────────────┐
│  Backend   │
└─────┬──────┘
      ↓
┌────────────┐
│  Database  │
└─────┬──────┘
      ↓
┌────────────┐
│ Dashboard  │
└────────────┘
```

---

# 11. Why Separate Components?

Separation provides modularity.

For example:

```text
ESP32
```

does not need to know how the dashboard stores information.

It only needs to publish valid data.

---

# 12. Reflection

1. What is an API?
2. What is REST?
3. What is a backend?
4. Why use a database?
5. What does a dashboard do?
6. Why separate device and application layers?

---

# Challenge

Design a temperature monitoring platform.

Specify:

```text
ESP32
 ↓
Communication
 ↓
API/Backend
 ↓
Database
 ↓
Dashboard
```

Define the data structure sent by the ESP32.

````


---
