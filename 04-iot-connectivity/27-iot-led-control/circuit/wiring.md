# Project 27 — Wiring Guide

## 1. ESP32 → Relay

| ESP32 | Relay Module |
|---|---|
| GPIO 5 | IN |
| GND | GND |
| Appropriate supply | VCC* |

*Verify the exact relay module's supply requirements.

## 2. Relay → Low-Voltage Load

The relay contacts switch the separate load circuit.

```text
External DC Supply
      │
      ▼
 Relay Contact
      │
      ▼
Low-Voltage Lamp
      │
      ▼
 Supply Return
```

The ESP32 controls the relay; it does not directly power the lamp.

## 3. Control-Side Diagram

```text
                 ESP32
          ┌────────────────┐
GPIO 5 ───┤                │
GND ──────┤                │
          └───────┬────────┘
                  │
                  ▼
           ┌─────────────┐
           │ Relay Module│
           │ IN VCC GND  │
           └──────┬──────┘
                  │
                  ▼
            Relay Contacts
                  │
                  ▼
          Low-Voltage Load
```

## 4. Relay Logic

For the assumed active-LOW module:

```text
GPIO LOW  → Relay ON  → Light ON
GPIO HIGH → Relay OFF → Light OFF
```

Different modules may use different trigger logic.

## 5. Network Path

```text
Phone / Laptop
      │ HTTP
      ▼
 Wi-Fi Router
      │ Wi-Fi
      ▼
    ESP32
      │ GPIO 5
      ▼
 Relay Module
      │
      ▼
Low-Voltage Light
```

## 6. Pre-Power Checklist

- [ ] Confirm relay pin labels.
- [ ] Confirm relay supply requirements.
- [ ] Confirm trigger logic.
- [ ] Verify ESP32 GND.
- [ ] Verify GPIO 5 → IN.
- [ ] Verify load-side wiring.
- [ ] Use only a low-voltage DC load.
- [ ] Keep mains voltage out of the prototype.

## 7. Relay Power Note

Do not power a relay coil directly from an ESP32 GPIO. Use a properly designed relay module/driver and suitable power arrangement.

## 8. Verification

Before connecting the load:

```text
ESP32
  ↓
Relay input
  ↓
Indicator/click
  ↓
Confirm ON/OFF
  ↓
Connect low-voltage load
```

This reduces troubleshooting variables.
