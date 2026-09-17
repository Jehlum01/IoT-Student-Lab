# 🔌 Project 30 — Smart Home Automation Wiring

## 1. Important Scope

This student version is designed around **low-voltage demonstration loads**.

Recommended classroom progression:

```text
ESP32
  ↓
Relay Module
  ↓
LED / Low-Voltage Demonstration Load
```

Do **not** place household AC mains voltage on an exposed classroom breadboard.

---

# 2. ESP32 Pin Mapping

| Device | Relay Input | ESP32 GPIO |
|---|---|---:|
| Light | Relay 1 IN | GPIO 5 |
| Fan | Relay 2 IN | GPIO 18 |
| Auxiliary | Relay 3 IN | GPIO 19 |

---

# 3. Basic Control Wiring

```text
                     ESP32
                  ┌───────────┐
                  │           │
       GPIO 5 ────┼──────────►│ Relay 1 IN
                  │           │
      GPIO 18 ────┼──────────►│ Relay 2 IN
                  │           │
      GPIO 19 ────┼──────────►│ Relay 3 IN
                  │           │
           GND ───┼──────────►│ Relay GND
                  │           │
                  └───────────┘
```

Relay VCC must be connected according to the exact relay module specification.

---

# 4. Device Architecture

```text
GPIO 5
  ↓
Relay 1
  ↓
Light

GPIO 18
  ↓
Relay 2
  ↓
Fan

GPIO 19
  ↓
Relay 3
  ↓
Auxiliary
```

---

# 5. Relay Logic

The source implementation assumes active-LOW relay inputs:

```text
LOW  → Relay ON
HIGH → Relay OFF
```

Always verify your specific relay module.

If the module behaves in the opposite way, the software's relay constants must match the actual hardware logic.

---

# 6. Recommended Classroom Test

Before using any real load, replace the load with simple low-voltage indicators where practical.

For example:

```text
ESP32
  ↓
Relay
  ↓
Low-voltage LED / indicator
```

This allows students to verify:

- Wi-Fi;
- HTTP;
- state logic;
- GPIO;
- relay behavior;

without introducing mains-voltage hazards.

---

# 7. Testing Sequence

### Step 1 — Startup

Confirm:

```text
All devices initialized OFF.
```

### Step 2 — Wi-Fi

Confirm:

```text
Wi-Fi connected!
```

### Step 3 — IP address

Record the ESP32 IP.

### Step 4 — Dashboard

Open:

```text
http://<ESP32-IP>
```

### Step 5 — Test individually

```text
/light/on
/light/off

/fan/on
/fan/off

/aux/on
/aux/off
```

### Step 6 — Test master OFF

```text
/all/off
```

### Step 7 — Test API

```text
/status
```

---

# 8. Wiring Verification Checklist

- [ ] ESP32 powered correctly
- [ ] Relay module powered according to its specification
- [ ] ESP32 ground/reference connected appropriately
- [ ] Light relay IN → GPIO 5
- [ ] Fan relay IN → GPIO 18
- [ ] Auxiliary relay IN → GPIO 19
- [ ] No GPIO is accidentally connected to a load power path
- [ ] Low-voltage test loads used for classroom work
- [ ] No mains voltage on breadboard
- [ ] Wiring checked before power is applied

---

# 9. Fault Isolation

Use:

```text
Browser
   ↓
HTTP
   ↓
ESP32
   ↓
GPIO
   ↓
Relay
   ↓
Load
```

For example:

```text
Browser works
     ↓
Relay clicks
     ↓
Load does not operate
```

Then investigate the load-side circuit rather than changing the Wi-Fi code.

---

# 10. Safety

For real electrical loads, the relay must be appropriately rated and installed with suitable protection and isolation.

For student laboratory work:

> **Stay with low-voltage demonstration loads.**

Disconnect power before changing physical wiring.
