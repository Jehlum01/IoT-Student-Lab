# L5-T05 — IoT Gateways & Edge Computing

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Understand:

- IoT gateways
- Edge computing
- Local processing
- Cloud processing
- Why data may be processed before transmission

---

# 1. Basic IoT

A simple architecture:

```text
Sensor
  ↓
ESP32
  ↓
Cloud
````

But this is not always the best architecture.

---

# 2. Gateway

A gateway acts as an intermediary between devices and other networks or services.

```text
Sensors
  ↓
ESP32 Devices
  ↓
Gateway
  ↓
Internet
  ↓
Cloud
```

---

# 3. Why Use a Gateway?

A gateway may provide:

- Protocol translation
- Local processing
- Data filtering
- Aggregation
- Security controls
- Local storage
- Connectivity management

---

# 4. Edge Computing

Edge computing means processing data closer to where it is generated.

Instead of:

```text
Sensor
  ↓
Internet
  ↓
Cloud
```

we can have:

```text
Sensor
  ↓
Edge Device
  ↓
Processing
  ↓
Cloud
```

---

# 5. Example

Imagine 100 sensors measuring temperature every second.

Raw data:

```text
100 sensors × 1 reading/second
```

The edge system could calculate:

```text
Average temperature
Maximum temperature
Minimum temperature
Abnormal readings
```

and send only important information to the backend.

---

# 6. Edge Decision

Consider an industrial temperature sensor.

```text
Temperature
     ↓
Edge Device
     ↓
Temperature > limit?
    /        \
  NO          YES
  ↓            ↓
Continue      Alarm
```

The local decision does not necessarily need to wait for cloud processing.

---

# 7. Cloud Processing

Cloud systems are useful for:

- Large-scale storage
- Analytics
- Dashboards
- Remote access
- Machine learning
- Long-term data analysis

---

# 8. Edge + Cloud

A realistic architecture can combine both:

```text
                 CLOUD
                   ▲
                   │
                Internet
                   │
                   ▼
             ┌───────────┐
             │   EDGE    │
             │  GATEWAY  │
             └─────┬─────┘
                   │
          ┌────────┼────────┐
          ▼        ▼        ▼
        ESP32    ESP32    ESP32
```

---

# 9. Local vs Cloud

| ProcessingLocal/EdgeCloud |                |                   |
| ------------------------- | -------------- | ----------------- |
| Response time             | Usually lower  | Network dependent |
| Internet dependency       | Can be reduced | Usually required  |
| Large-scale storage       | Limited        | Strong            |
| Local automation          | Strong         | Possible          |
| Centralized analytics     | Limited        | Strong            |

---

# 10. Important Principle

Do not send everything to the cloud simply because you can.

Ask:

```text
What data?
Why?
How often?
Where should it be processed?
Who needs it?
```

---

# Reflection

1. What is an IoT gateway?
2. What is edge computing?
3. Why process data locally?
4. What is cloud processing useful for?
5. Why might a system combine edge and cloud?

---

# Challenge

Design an agricultural IoT system using:

- 20 ESP32 nodes
- One gateway
- Cloud backend
- Dashboard

Identify which processing should happen:

- On ESP32
- At gateway
- In cloud

````


---
