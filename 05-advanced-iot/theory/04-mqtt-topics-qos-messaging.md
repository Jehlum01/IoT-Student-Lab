# L5-T04 — MQTT Topics, QoS & Messaging

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Understand:

- MQTT topic design
- Payloads
- QoS
- Retained messages
- Last Will and Testament
- Message reliability concepts

---

# 1. Topic Design

A topic should clearly describe the data.

Example:

```text
home/livingroom/temperature
````

Breakdown:

```text
home
 ↓
livingroom
 ↓
temperature
```

---

# 2. Topic Hierarchy

A larger system might use:

```text
home/
├── livingroom/
│   ├── temperature
│   ├── humidity
│   └── light
│
├── bedroom/
│   ├── temperature
│   └── light
│
└── kitchen/
    ├── temperature
    └── smoke
```

Consistent naming becomes important as the system grows.

---

# 3. Payload

The payload is the actual message data.

Simple payload:

```text
27.5
```

Structured payload:

```json
{
  "temperature": 27.5,
  "humidity": 62
}
```

---

# 4. QoS

MQTT defines three Quality of Service levels.

## QoS 0

```text
At most once
```

The message is delivered with minimal overhead.

---

## QoS 1

```text
At least once
```

Delivery is acknowledged, but duplicates can occur.

---

## QoS 2

```text
Exactly once
```

Provides the strongest delivery guarantee among the MQTT QoS levels, with additional protocol overhead.

---

# 5. Engineering Trade-off

Higher delivery guarantees can involve additional communication and processing.

Think about:

```text
Reliability
     ↕
Traffic
     ↕
Latency
     ↕
Resource Usage
```

The correct QoS depends on the application.

---

# 6. Retained Messages

A retained message allows a broker to retain the latest message for a topic.

Conceptually:

```text
Publisher
   ↓
Broker
   ↓
Retained value
```

A new subscriber can receive the retained value when subscribing.

Example:

```text
home/room1/light = ON
```

A newly connected dashboard can learn the current state without waiting for the next publication.

---

# 7. Last Will and Testament

An MQTT client can provide a Last Will and Testament message.

Concept:

```text
ESP32
  ↓
connects
  ↓
Broker
```

If the client disconnects unexpectedly, the broker can publish the configured will message.

Example:

```text
device/esp32-01/status
```

Payload:

```text
offline
```

This can help monitoring systems detect unexpected device loss.

---

# 8. Online / Offline State

A common design is:

```text
online
offline
```

Example:

```text
device/room1/status
```

Possible values:

```text
online
offline
```

A dashboard can then display device availability.

---

# 9. Message Flow

```text
ESP32
 │
 │ temperature = 25.4
 ▼
Broker
 │
 ├──► Dashboard
 │
 ├──► Database
 │
 └──► Automation Engine
```

---

# 10. Designing Topics

Avoid random topic names such as:

```text
abc123
data
sensor1
```

Prefer meaningful structures:

```text
home/livingroom/temperature
```

or:

```text
iot/device01/temperature
```

---

# 11. Reflection

1. What is QoS?
2. What is the difference between QoS 0 and QoS 1?
3. Why might duplicate messages occur?
4. What does retained messaging solve?
5. Why is device online/offline status useful?

---

# Challenge

Design a topic hierarchy for:

```text
School
 ├── Building A
 ├── Building B
 └── Laboratory
```

Each location has:

- Temperature
- Humidity
- Motion
- Light

Create a logical MQTT topic structure.

````


---
