# Project 29 — Wi-Fi Motion Alarm

## Hardware

| Component | ESP32 |
|---|---|
| PIR VCC | 5V |
| PIR OUT | GPIO 4 |
| PIR GND | GND |
| LED | GPIO 5 through 220Ω resistor |
| Buzzer | GPIO 18 |

## Circuit

```text
                  ESP32
             ┌─────────────┐
             │             │
        5V ──┤             │
             │     GPIO 4 ─┼──────── PIR OUT
       GND ──┤             │
             │             │
             │     GPIO 5 ─┼──220Ω──► LED ──► GND
             │             │
             │    GPIO 18 ─┼────────► Buzzer
             │             │
             └─────────────┘
````

## PIR Sensor

Typical HC-SR501 connections:

| PIR PinConnection |        |
| ----------------- | ------ |
| VCC               | 5V     |
| OUT               | GPIO 4 |
| GND               | GND    |

The PIR output is read as a digital signal.

```text
LOW  → No motion
HIGH → Motion detected
```

## LED

Use a current-limiting resistor.

```text
ESP32 GPIO 5
     │
    220Ω
     │
    LED
     │
    GND
```

## Buzzer

For a small low-current buzzer:

```text
GPIO 18 → Buzzer → GND
```

For a higher-current buzzer or other load, use an appropriate transistor/MOSFET driver instead of driving the load directly from the GPIO.

## Important

PIR modules can require a short warm-up period after power-up.

During this period, the output may behave unexpectedly.

Allow the sensor to stabilize before judging the circuit.

## Testing

1. Upload the program.
2. Open Serial Monitor.
3. Set baud rate to `115200`.
4. Wait for Wi-Fi connection.
5. Note the ESP32 IP address.
6. Open the IP address in a browser.
7. Move in front of the PIR.
8. Observe the LED and buzzer.
9. Observe the web dashboard.

Example:

```text
http://192.168.1.42
```

## Status API

Open:

```text
http://192.168.1.42/status
```

Example:

```json
{
  "motion": true,
  "alarm": true
}
```

## Safety

This project is intended for low-voltage educational experimentation.

Do not connect mains voltage loads directly to the ESP32.

Use proper driver circuitry and isolation for higher-power loads.

