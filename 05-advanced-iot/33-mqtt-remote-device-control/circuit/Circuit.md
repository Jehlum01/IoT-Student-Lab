# ⚡ Project 33 — MQTT Remote Device Control Circuit & Communication

## 1. Complete System

```mermaid
flowchart TB
    C[🧑‍💻 Controller]
    B[☁️ MQTT Broker]
    E[📡 ESP32]
    G[GPIO 5]
    R[220 Ω]
    L[💡 LED]

    C -->|PUBLISH command| B
    B -->|command topic| E
    E --> G --> R --> L
    E -->|PUBLISH state| B
    B -->|state topic| C
```

---

## 2. Two-Way Message Flow

```mermaid
sequenceDiagram
    participant C as Controller
    participant B as MQTT Broker
    participant E as ESP32
    participant L as LED

    C->>B: PUBLISH command = ON
    B->>E: DELIVER command
    E->>E: mqttCallback()
    E->>E: Validate ON
    E->>L: GPIO 5 HIGH
    E->>B: PUBLISH state = ON
    B->>C: DELIVER state
```

---

## 3. Command Processing

```mermaid
flowchart TD
    A[MQTT message arrives] --> B{Expected command topic?}
    B -->|No| C[Ignore]
    B -->|Yes| D[Convert payload]
    D --> E[Trim whitespace]
    E --> F[Uppercase]
    F --> G{Command}
    G -->|ON| H[ledState = true]
    G -->|OFF| I[ledState = false]
    G -->|Invalid| J[Reject]
    H --> K[GPIO HIGH]
    I --> L[GPIO LOW]
    K --> M[Publish state]
    L --> M
```

---

## 4. Connection Recovery

```mermaid
flowchart TD
    A[Main loop] --> B{Wi-Fi connected?}
    B -->|No| C[Reconnect Wi-Fi]
    C --> D{MQTT connected?}
    B -->|Yes| D
    D -->|No| E[Reconnect MQTT]
    E --> F[Subscribe command topic]
    F --> G[Publish current state]
    D -->|Yes| H[mqttClient.loop()]
    G --> H
    H --> A
```

---

## 5. Topic Architecture

```text
iot-student-lab
└── project33
    └── device
        ├── command
        │   ├── ON
        │   └── OFF
        │
        └── state
            ├── ON
            └── OFF
```

---

## 6. Project Progression

```mermaid
flowchart LR
    P31[31: MQTT Fundamentals]
    P32[32: Sensor Publisher]
    P33[33: Remote Control]
    P34[34: Dashboard]

    P31 --> P32 --> P33 --> P34
```

### Architectural evolution

```text
31: ESP32 → Broker → Subscriber

32: Sensor → ESP32 → Broker → Consumer

33: Controller ↔ Broker ↔ ESP32 → Actuator

34: MQTT → Data Consumer → Dashboard
```

---

## 7. Command vs State

```text
COMMAND
Controller
   │
   ▼
.../command
   │
   ▼
ESP32

STATE
ESP32
   │
   ▼
.../state
   │
   ▼
Controller
```

This separation allows the system to distinguish **requested action** from **reported device state**.
