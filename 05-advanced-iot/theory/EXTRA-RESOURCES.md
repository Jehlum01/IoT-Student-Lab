# Level 5 — Extra Resources & Further Learning

This resource sheet complements the eight theory lessons. It deliberately separates **core theory** from **external references** so students first understand the idea and then consult authoritative documentation.

## Recommended Learning Path

```text
ESP32 Networking
      ↓
HTTP & Client/Server
      ↓
APIs
      ↓
MQTT
      ↓
Topics & QoS
      ↓
Gateways & Edge Computing
      ↓
Backend & Data Pipelines
      ↓
Security & Reliability
      ↓
System Design
```

## 1. ESP32 Networking

### Arduino-ESP32 documentation
Official documentation for the Arduino framework on ESP32.

urlArduino-ESP32 Documentationhttps://docs.espressif.com/projects/arduino-esp32/en/latest/

Study:
- GPIO and peripherals
- Wi-Fi
- station mode
- access-point mode
- networking APIs

### Wi-Fi API

urlArduino-ESP32 Wi-Fi APIhttps://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html

Focus on the distinction between **STA mode** (ESP32 joins an existing Wi-Fi network) and **AP mode** (ESP32 provides a network for other devices). The official documentation describes both modes. citeturn0search10

---

## 2. HTTP and Web APIs

### HTTP Overview

urlMDN — HTTP Overviewhttps://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Overview

Use this to deepen:
- client/server
- requests and responses
- HTTP messages
- APIs
- application-layer communication

MDN describes HTTP as a client-server protocol in which clients send requests and servers return responses. citeturn0search2

### HTTP Methods

urlMDN — HTTP Request Methodshttps://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods

Study:
- GET
- POST
- PUT
- DELETE
- method semantics
- safe and idempotent operations

MDN's reference explains, for example, that GET is used to retrieve a representation while POST commonly submits data and can cause state changes. citeturn0search6

### Student exercise

Create this table after reading:

| Method | Typical purpose | IoT example |
|---|---|---|
| GET | Retrieve information | Read device status |
| POST | Submit data / trigger processing | Send sensor data |
| PUT | Replace/update a resource | Update configuration |
| DELETE | Remove a resource | Remove a registered device |

---

## 3. MQTT

### MQTT 5.0 — Primary Specification

urlOASIS MQTT Version 5.0 Specificationhttps://docs.oasis-open.org/mqtt/mqtt/v5.0/mqtt-v5.0.html

This is the primary technical reference for MQTT.

Study progressively:
1. Client
2. Broker
3. Publish
4. Subscribe
5. Topic
6. Payload
7. QoS
8. Retained messages
9. Will messages
10. MQTT control packets

The OASIS specification defines MQTT as a lightweight client/server publish-subscribe messaging transport protocol designed for contexts including IoT and constrained environments. citeturn0search5

**Do not try to memorize the entire specification.** Use it as a reference when exact protocol behavior matters.

### Eclipse Mosquitto

urlEclipse Mosquittohttps://mosquitto.org/

Mosquitto is useful for classroom MQTT experimentation.

Suggested architecture:

```text
ESP32 Publisher
       ↓
     Broker
       ↓
MQTT Subscriber
```

Then extend it:

```text
ESP32 Publisher
       ↓
     Broker
    ↙   ↓   ↘
Dashboard Logger Automation
```

---

## 4. MQTT Experiments

### Experiment A — One publisher, one subscriber

Publish:

```text
classroom/lab/temperature
```

Record:
- topic
- payload
- publishing device
- subscribing device
- observed message

### Experiment B — One publisher, multiple subscribers

```text
             ┌──► Dashboard
ESP32 → Broker├──► Logger
             └──► Automation
```

Explain why the publisher does not need separate application-specific knowledge of every consumer.

### Experiment C — Command vs state

Create:

```text
home/room1/light/set
home/room1/light/state
```

Trace:

```text
Dashboard
   ↓
SET = ON
   ↓
ESP32
   ↓
Relay
   ↓
STATE = ON
```

Explain why **desired state** and **reported state** are different concepts.

### Experiment D — QoS

Compare QoS 0, 1, and 2 in a controlled experiment.

Record:
- delivery behavior
- duplicate possibility
- overhead
- suitability for the message

### Experiment E — Retained state

Publish a retained state, disconnect the subscriber, reconnect, and observe what the new subscriber receives.

### Experiment F — Last Will

Create:

```text
device/esp32-01/status
```

Use:
```text
online
offline
```

Test unexpected disconnection.

---

## 5. Security and Reliability

### NIST SP 800-213

urlNIST — IoT Device Cybersecurity Guidancehttps://csrc.nist.gov/pubs/sp/800/213/final

Useful for understanding how IoT devices should be considered within a broader system and risk-management context. citeturn0search4

### NISTIR 8259A

urlNIST — IoT Device Cybersecurity Capability Core Baselinehttps://csrc.nist.gov/pubs/ir/8259/a/final

Use this to think about the technical cybersecurity capabilities a device may need.

### NISTIR 8259 Rev. 1

urlNIST — Foundational Cybersecurity Activities for IoT Product Manufacturershttps://csrc.nist.gov/pubs/ir/8259/r1/final

This 2026 revision is useful when students move from building prototypes toward thinking about the lifecycle and product-level security of IoT systems. citeturn0search9

---

## 6. Security Study Questions

After reading the NIST material, answer:

1. What are the assets in your IoT project?
2. What network interfaces exist?
3. How is a device identified?
4. How is a user authenticated?
5. How is authorization enforced?
6. How is communication protected?
7. Where are credentials stored?
8. What happens after a credential compromise?
9. What happens when the network disappears?
10. How is device failure detected?

---

## 7. Architecture Practice

For every Level 5 project, draw three diagrams.

### Physical architecture

```text
Sensor → ESP32 → Relay → Physical Device
```

### Communication architecture

```text
ESP32 → Wi-Fi → MQTT Broker → Backend
```

### Application architecture

```text
Device
  ↓
Broker / API
  ↓
Backend
  ↓
Database
  ↓
Dashboard
```

For each arrow, write one sentence explaining what crosses the boundary.

---

## 8. Student Portfolio Structure

For every advanced project, maintain:

```text
project/
├── README.md
├── theory.md
├── architecture.md
├── wiring.md
├── circuit.md
├── code/
├── experiments/
│   ├── experiment-01.md
│   ├── experiment-02.md
│   └── experiment-03.md
├── test-results.md
├── troubleshooting.md
└── security.md
```

This turns a project into an engineering case study rather than only a code exercise.

---

## 9. Further Topics After Level 5

### Networking
- TCP/IP
- DNS
- DHCP
- TLS
- IPv4/IPv6
- NAT
- VLANs

### IoT protocols
- MQTT
- HTTP
- CoAP
- WebSockets
- MQTT over WebSockets
- BLE
- ESP-NOW

### Backend
- REST APIs
- authentication
- JSON
- databases
- message queues
- event-driven architecture

### Data
- time-series databases
- validation
- timestamps
- aggregation
- anomaly detection

### Operations
- logging
- monitoring
- observability
- OTA updates
- device provisioning
- fleet management

### Security
- TLS
- certificates
- secure credential storage
- authorization
- network segmentation
- threat modeling

---

## 10. Resource Discipline

When using external material:

1. Start with official documentation.
2. Learn one concept.
3. Build a small experiment.
4. Change one variable.
5. Observe the result.
6. Record what happened.
7. Explain the result in your own words.
8. Only then move to a larger project.

The objective is not to collect links.

The objective is to turn information into engineering understanding.

---

## 11. Before Project 31

Students should be able to explain:

- [ ] Embedded system vs IoT system
- [ ] Local vs distributed architecture
- [ ] Client/server
- [ ] HTTP request/response
- [ ] API
- [ ] MQTT
- [ ] Broker
- [ ] Publisher
- [ ] Subscriber
- [ ] Topic
- [ ] Payload
- [ ] QoS
- [ ] Retained message
- [ ] Last Will
- [ ] Gateway
- [ ] Edge computing
- [ ] Backend
- [ ] Database
- [ ] Dashboard
- [ ] Authentication
- [ ] Authorization
- [ ] Confidentiality
- [ ] Integrity
- [ ] Availability
- [ ] Device identity
- [ ] Failure handling
- [ ] Observability
- [ ] Scalability
- [ ] Maintainability

Project 31 should therefore be the first hands-on MQTT laboratory:

```text
Theory
  ↓
Architecture
  ↓
Broker
  ↓
Publisher
  ↓
Subscriber
  ↓
ESP32
  ↓
Telemetry
  ↓
Commands
  ↓
Multiple Devices
  ↓
Integration
```
