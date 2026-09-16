# Project 26 — ESP32 Web Server Wiring

## Hardware

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 development board | 1 | Controller + Wi-Fi |
| LED | 1 | Physical output |
| 220Ω resistor | 1 | Current limiting |
| Breadboard | 1 | Circuit assembly |
| Jumper wires | As required | Connections |
| USB cable | 1 | Power/programming |

## LED Circuit

GPIO 5 is the output.

```text
                 ESP32
              ┌─────────┐
 GPIO 5 ──────┤         │
              │         │
 GND ─────────┤         │
              └─────────┘
                  │
                220Ω
                  │
                  ▼
              LED Anode
              LED Cathode
                  │
                  ▼
                 GND
```

### Connection table

| ESP32 Pin | Connection | Purpose |
|---|---|---|
| GPIO 5 | 220Ω → LED anode | Digital output |
| GND | LED cathode | Ground |
| USB | Computer | Power + programming + serial |

## LED Polarity

Typical through-hole LED:

```text
Longer leg  → Anode (+)
Shorter leg → Cathode (-)
```

A flat edge commonly indicates the cathode.

## Why the resistor?

The resistor limits current through the LED:

```text
GPIO HIGH → 220Ω → LED → GND
```

Never normally connect a bare LED directly to a GPIO.

## Network Arrangement

```text
              Wi-Fi Router / AP
                 /          \
                /            \
               ▼              ▼
            ESP32        Phone / Laptop
               │
             GPIO 5
               │
              LED
```

No physical wire is required between the ESP32 and router for Wi-Fi communication.

## Browser Test

Serial Monitor prints the current IP, for example:

```text
IP Address: 192.168.1.42
```

Open:

```text
http://192.168.1.42
```

## Routes

| Path | Effect |
|---|---|
| `/` | Webpage |
| `/on` | GPIO 5 HIGH → LED ON |
| `/off` | GPIO 5 LOW → LED OFF |
| Unknown path | 404 |

## Build Checklist

- [ ] GPIO 5 connected to resistor
- [ ] Resistor connected to LED anode
- [ ] LED cathode connected to GND
- [ ] Polarity verified
- [ ] No short circuit
- [ ] ESP32 powered by USB
- [ ] Browser device can reach ESP32

## Safety

ESP32 GPIO is generally 3.3V logic.

Do not:
- Apply 5V directly to GPIO 5.
- Short GPIO 5 to a power rail.
- Drive high-current loads directly.
- Connect mains voltage to the ESP32.

Use appropriate driver circuitry for larger loads.
