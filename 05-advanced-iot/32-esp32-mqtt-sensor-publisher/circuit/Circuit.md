# 🧩 Project 32 — Circuit & Communication Architecture

## 1. Complete System

```mermaid
flowchart LR
    ENV[🌍 Environment]
    DHT[🌡️ DHT22]
    ESP[🧠 ESP32]
    WIFI[📡 Wi-Fi]
    MQTT[📨 MQTT]
    B[🗄️ Broker]
    S[💻 Subscriber]

    ENV --> DHT
    DHT --> ESP
    ESP --> WIFI
    WIFI --> MQTT
    MQTT --> B
    B --> S
```

## 2. Telemetry Pipeline

```mermaid
flowchart TD
    A[Sense] --> B[Validate]
    B --> C[Structure]
    C --> D[Connect]
    D --> E[Publish]
    E --> F[Broker]
    F --> G[Consume]
```

## 3. Validity Decision

```mermaid
flowchart TD
    A[Read DHT22] --> B{Valid reading?}
    B -- Yes --> C[Format payload]
    C --> D[Publish MQTT]
    B -- No --> E[Report error]
```

## 4. Timing

```mermaid
flowchart TD
    A[loop()] --> B[Maintain Wi-Fi]
    B --> C[Maintain MQTT]
    C --> D[mqttClient.loop()]
    D --> E[Check millis()]
    E --> F{2 seconds?}
    F -- No --> A
    F -- Yes --> G[Read + publish]
    G --> A
```

## 5. Topic Architecture

```mermaid
flowchart TD
    R[iot-student-lab] --> P[project32]
    P --> T[temperature]
    P --> H[humidity]
    P --> C[telemetry]
```

## 6. Multiple Devices

```mermaid
flowchart LR
    E1[ESP32-01] --> B[MQTT Broker]
    E2[ESP32-02] --> B
    E3[ESP32-03] --> B
    B --> S[Telemetry Consumer]
```

Possible pattern:

```text
iot-student-lab/devices/esp32-01/temperature
iot-student-lab/devices/esp32-02/temperature
iot-student-lab/devices/esp32-03/temperature
```

## 7. Project 31 → 32 → 33

```mermaid
flowchart LR
    A[31<br/>MQTT message] --> B[32<br/>Sensor telemetry] --> C[33<br/>Subscribe + control]
```

Project 32 is the bridge from MQTT theory to real physical-world telemetry.
