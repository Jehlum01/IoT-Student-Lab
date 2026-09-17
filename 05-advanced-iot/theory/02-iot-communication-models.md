# L5-T02 — IoT Communication Models

> **Level 5 — Advanced IoT Theory**

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Understand:

- Direct communication
- Client/server architecture
- Request/response
- Publish/subscribe
- Why MQTT uses publish/subscribe
- When different communication models are useful

---

# 1. Why Communication Models Matter

An IoT device needs a way to exchange information.

Different applications require different communication architectures.

The three important models for this course are:

```text
Direct
Client/Server
Publish/Subscribe
````

---

# 2. Direct Communication

The simplest model is direct communication.

```text
Device A ─────────► Device B
```

Example:

```text
ESP32 ─────────► Servo
```

The ESP32 directly controls the actuator.

This is common in embedded systems.

---

# 3. Client/Server

A client requests something from a server.

```text
Client
   │
   │ Request
   ▼
Server
   │
   │ Response
   ▼
Client
```

Level 4 used this model.

For example:

```text
Browser
   │
   │ HTTP GET
   ▼
ESP32 Web Server
   │
   │ HTML
   ▼
Browser
```

---

# 4. Request/Response

HTTP commonly follows:

```text
REQUEST
   ↓
SERVER PROCESSING
   ↓
RESPONSE
```

Example:

```text
GET /temperature
```

Response:

```text
Temperature: 25.4 °C
```

The client initiates the interaction.

---

# 5. Publish/Subscribe

MQTT introduces another model.

```text
Publisher
     │
     │ Message
     ▼
   Broker
     │
     ├────────► Subscriber A
     │
     └────────► Subscriber B
```

The publisher does not need to directly communicate with each subscriber.

---

# 6. Why Is This Useful?

Imagine:

```text
ESP32
```

publishes:

```text
home/room1/temperature
```

Three systems can subscribe:

```text
Dashboard
Database
Automation Engine
```

The ESP32 does not need three separate connections.

```text
ESP32
  │
  ▼
Broker
 ├──► Dashboard
 ├──► Database
 └──► Automation
```

---

# 7. Comparison

| ModelMain Idea    |                                                |
| ----------------- | ---------------------------------------------- |
| Direct            | Device communicates directly                   |
| Client/Server     | Client requests, server responds               |
| Publish/Subscribe | Publisher sends to broker, subscribers receive |

---

# 8. HTTP vs MQTT

### HTTP

```text
Client → Request → Server
Client ← Response ← Server
```

### MQTT

```text
Publisher → Broker → Subscriber
```

MQTT is designed around messaging.

HTTP is commonly used for web/API request-response communication.

---

# 9. Example IoT System

Consider a temperature sensor.

### HTTP approach

```text
Browser
   ↓
Request
   ↓
ESP32
   ↓
Temperature
   ↓
Browser
```

### MQTT approach

```text
ESP32
   │
   │ publish
   ▼
Broker
   │
   ├──► Dashboard
   ├──► Database
   └──► Automation
```

---

# 10. Choosing a Model

Ask:

### Direct communication

Do I need simple local control?

### Client/server

Does one system need to request information or perform an operation?

### Publish/subscribe

Should multiple systems receive the same event or data stream?

---

# 11. Key Concept

The important difference is:

```text
HTTP

Who do I request?


MQTT

Who is interested in this message?
```

This change in thinking is fundamental to advanced IoT.

---

# Reflection

1. What is a client?
2. What is a server?
3. What is a publisher?
4. What is a subscriber?
5. What does the broker do?
6. Why can publish/subscribe scale differently from direct communication?

---

# Challenge

Design two architectures for a smart greenhouse:

1. One using HTTP
2. One using MQTT

Compare:

- Communication
- Number of connections
- Data flow
- Scalability

````


---
