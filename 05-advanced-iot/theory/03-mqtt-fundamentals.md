# L5-T03 — MQTT Fundamentals

> **Level 5 — Advanced IoT Theory**

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Understand:

- MQTT
- MQTT clients
- Broker
- Publisher
- Subscriber
- Messages
- Topics
- Basic MQTT architecture

---

# 1. What Is MQTT?

MQTT is a lightweight messaging protocol commonly used for IoT communication.

It uses a publish/subscribe architecture.

The three major roles are:

```text
Publisher
Subscriber
Broker
````

---

# 2. MQTT Architecture

```text
             ┌─────────────┐
             │   BROKER    │
             └──────┬──────┘
                    ▲
             Publish│
                    │
             ┌──────┴──────┐
             │    ESP32    │
             │  Publisher  │
             └─────────────┘

                    │
               Distribute
                    │
             ┌──────┴──────┐
             ▼             ▼
        Subscriber     Subscriber
```

---

# 3. MQTT Client

An MQTT client is a device or application that connects to an MQTT broker.

Examples:

- ESP32
- Laptop
- Server
- Dashboard
- Mobile application

A client can publish, subscribe, or do both.

---

# 4. Broker

The broker is the central message-handling component.

It receives messages from publishers and forwards them to matching subscribers.

```text
Publisher
    ↓
Broker
    ↓
Subscribers
```

The publisher does not need to know every subscriber.

---

# 5. Publisher

A publisher sends messages.

Example:

```text
ESP32
```

publishes:

```text
Temperature = 27.4
```

to:

```text
home/room1/temperature
```

---

# 6. Subscriber

A subscriber listens to a topic.

Example:

```text
Dashboard
```

subscribes to:

```text
home/room1/temperature
```

Whenever a matching message arrives, the dashboard receives it.

---

# 7. Topic

A topic identifies the logical destination of a message.

Examples:

```text
home/livingroom/temperature
home/livingroom/humidity
home/bedroom/light
farm/field1/soil
factory/motor1/status
```

Topics should be designed consistently.

---

# 8. Message

A message contains a payload.

Example:

```text
Topic:
home/livingroom/temperature

Payload:
27.4
```

Another payload could be:

```json
{
  "temperature": 27.4,
  "humidity": 61
}
```

---

# 9. Complete Example

```text
DHT22
  ↓
ESP32
  ↓
Publish
  ↓
home/room1/temperature
  ↓
MQTT Broker
  ↓
┌───────────────┬───────────────┐
▼               ▼
Dashboard       Database
```

---

# 10. Why MQTT Fits IoT

IoT systems often have:

- Limited processing resources
- Limited bandwidth
- Many devices
- Intermittent connectivity
- Event-driven data

MQTT's messaging model can fit these requirements well.

---

# 11. MQTT Connection

Conceptually:

```text
ESP32
  │
  │ CONNECT
  ▼
Broker
  │
  │ CONNACK
  ▼
ESP32 connected
```

The client then publishes and/or subscribes.

---

# 12. Publish Flow

```text
ESP32
  │
  │ PUBLISH
  ▼
Broker
  │
  ▼
Subscriber
```

---

# 13. Subscribe Flow

```text
Client
  │
  │ SUBSCRIBE
  ▼
Broker
```

The broker records the subscription.

Later, matching publications can be delivered to that client.

---

# 14. MQTT vs HTTP

```text
HTTP

Client
  ↓
Request
  ↓
Server
  ↓
Response
```

```text
MQTT

Publisher
  ↓
Broker
  ↓
Subscriber
```

They solve different communication problems.

---

# 15. Key Takeaways

Remember:

```text
CLIENT
   ↓
connects to
   ↓
BROKER

PUBLISHER
   ↓
publishes
   ↓
TOPIC

SUBSCRIBER
   ↓
subscribes to
   ↓
TOPIC
```

---

# Reflection

1. What is MQTT?
2. What is an MQTT broker?
3. What is a client?
4. What is a publisher?
5. What is a subscriber?
6. What is a topic?
7. What is a payload?

---

# Challenge

Design an MQTT system for a smart classroom.

Create topics for:

- Temperature
- Humidity
- Light
- Motion
- Door status

Draw the message flow before writing code.

````


---
