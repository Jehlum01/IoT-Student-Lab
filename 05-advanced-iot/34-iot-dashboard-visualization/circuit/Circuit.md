# ⚡ Project 34 — Circuit, Data Flow & Architecture

## 1. Complete System

```mermaid
flowchart TB
    D[🌡️ DHT22]
    E[📡 ESP32]
    B[☁️ MQTT Broker]
    P[🐍 Python MQTT Client]
    S[🧠 Application State]
    F[🌐 Flask]
    H[🖥️ Browser]
    V[📊 Dashboard]

    D --> E
    E -->|MQTT| B
    B -->|Telemetry| P
    P --> S
    S --> F
    F -->|HTTP JSON| H
    H --> V
```

## 2. End-to-End Sequence

```mermaid
sequenceDiagram
    participant D as DHT22
    participant E as ESP32
    participant B as MQTT Broker
    participant P as Python
    participant H as Browser

    D->>E: Temperature + Humidity
    E->>B: Publish telemetry JSON
    B->>P: Deliver message
    P->>P: Decode + parse JSON
    P->>P: Update latest_data
    H->>P: GET /api/data
    P-->>H: JSON response
    H->>H: Update dashboard
```

## 3. Data Transformation

```mermaid
flowchart LR
    A[Sensor measurement] --> B[MQTT payload]
    B --> C[JSON]
    C --> D[Python dictionary]
    D --> E[Application state]
    E --> F[HTTP JSON]
    F --> G[Browser cards]
```

## 4. Browser Polling

```mermaid
flowchart TD
    A[Browser] --> B[GET /api/data]
    B --> C[Flask]
    C --> D[latest_data]
    D --> E[JSON]
    E --> A
    A --> F[Update UI]
    F --> G[Wait 2 seconds]
    G --> B
```

## 5. Layered Architecture

```text
Presentation → Browser / HTML / CSS / JavaScript
Application  → Python / Flask
Messaging    → MQTT / Broker
Network      → Wi-Fi / IP / TCP
Device       → ESP32 / DHT22
```

## 6. Project Progression

```mermaid
flowchart LR
    P31[31 MQTT Fundamentals]
    P32[32 Sensor Publisher]
    P33[33 Remote Control]
    P34[34 Dashboard]
    P35[35 Persistence]

    P31 --> P32 --> P33 --> P34 --> P35
```

## 7. Live vs Historical

```text
Project 34:
ESP32 → MQTT → Python → Dashboard
                         └── latest value

Project 35:
ESP32 → MQTT → Python → Database → Dashboard
                         └── historical values
```
