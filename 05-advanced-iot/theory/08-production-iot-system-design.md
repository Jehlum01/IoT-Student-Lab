# L5-T08 — Production-Style IoT System Design

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Learn how to design an IoT system before writing code.

---

# 1. Prototype vs System

A prototype asks:

> Can this work?

A production-style design asks:

> Can this continue working reliably, securely and maintainably?

---

# 2. Layered Architecture

A useful architecture is:

```text
┌────────────────────────────┐
│        APPLICATION         │
│ Dashboard / Mobile App     │
├────────────────────────────┤
│            API             │
│ REST / MQTT Interface      │
├────────────────────────────┤
│          BACKEND           │
│ Logic / Processing         │
├────────────────────────────┤
│           DATA             │
│ Database / Storage         │
├────────────────────────────┤
│         NETWORK            │
│ Wi-Fi / Ethernet / MQTT    │
├────────────────────────────┤
│          DEVICE            │
│ ESP32 / Sensors / Outputs  │
├────────────────────────────┤
│         PHYSICAL           │
│ Environment / Machine      │
└────────────────────────────┘
````

---

# 3. Start With the Problem

Do not start with:

> Which sensor should I use?

Start with:

> What problem am I solving?

Example:

```text
Problem:
Water tanks are overflowing.
```

Then determine:

```text
Measurement
 ↓
Sensor
 ↓
Decision
 ↓
Actuator
 ↓
Communication
 ↓
Monitoring
```

---

# 4. Requirements

Define:

### Functional requirements

What must the system do?

### Non-functional requirements

How well must it operate?

Examples:

- Reliability
- Response time
- Security
- Scalability
- Maintainability

---

# 5. Device Design

Ask:

```text
Which microcontroller?
Which sensors?
Which actuators?
Which power supply?
Which communication method?
```

---

# 6. Communication Design

Choose:

```text
HTTP
MQTT
BLE
ESP-NOW
Wi-Fi
Ethernet
```

The choice should follow the requirements.

---

# 7. Data Design

Define:

```text
What data?
Format?
Frequency?
Units?
Timestamp?
Device ID?
```

Example:

```json
{
  "device_id": "esp32-01",
  "temperature": 25.4,
  "humidity": 61,
  "timestamp": 123456
}
```

---

# 8. Failure Design

Always ask:

```text
What happens if...
```

### Sensor fails?

### Wi-Fi fails?

### Broker fails?

### Database fails?

### Power fails?

### Device restarts?

A good system has deliberate answers.

---

# 9. Scalability

One device:

```text
ESP32 → Broker
```

Ten devices:

```text
ESP32 × 10 → Broker
```

A thousand devices:

```text
ESP32 × 1000
      ↓
Network
      ↓
Broker Cluster / Backend
```

Architecture must evolve with scale.

---

# 10. Observability

Advanced systems need visibility.

Monitor:

- Device status
- Network status
- Sensor errors
- Message rates
- CPU/memory where relevant
- Connectivity
- Alerts

If you cannot observe a system, troubleshooting becomes difficult.

---

# 11. Maintainability

Good systems should be understandable by someone other than the original developer.

Use:

- Clear naming
- Documentation
- Modular code
- Version control
- Configuration separation
- Consistent interfaces

---

# 12. Testing Strategy

Test at multiple levels.

```text
Component Test
      ↓
Device Test
      ↓
Communication Test
      ↓
Integration Test
      ↓
System Test
```

---

# 13. Engineering Design Template

Before building an advanced IoT project, document:

```text
1. Problem
2. Requirements
3. Architecture
4. Components
5. Communication
6. Data model
7. Security
8. Failure handling
9. Testing
10. Deployment
11. Maintenance
```

---

# 14. Example

Smart greenhouse:

```text
Temperature ─┐
Humidity ────┤
Soil ────────┤
Light ───────┘
       ↓
     ESP32
       ↓
     MQTT
       ↓
    Broker
       ↓
    Backend
       ↓
   Database
       ↓
   Dashboard
       ↓
 Automation
       ↓
     Pump
```

This is no longer just a circuit.

It is a system.

---

# 15. The Advanced IoT Mindset

The progression is:

```text
Build
 ↓
Connect
 ↓
Communicate
 ↓
Monitor
 ↓
Automate
 ↓
Secure
 ↓
Scale
 ↓
Maintain
```

---

# Final Challenge

Design your own IoT system.

Do not write code.

Produce:

### 1. Problem statement

What problem are you solving?

### 2. Architecture

Draw the complete system.

### 3. Hardware

List the devices.

### 4. Communication

Explain the protocol.

### 5. Data

Define your messages.

### 6. Backend

Explain where processing happens.

### 7. Security

Explain how access is controlled.

### 8. Reliability

Explain failure behavior.

### 9. Testing

Explain how you will prove it works.

### 10. Scaling

Explain what changes when the number of devices increases.

---

# Level 5 Principle

> **Do not build a connected gadget. Design an IoT system.**

````


---
