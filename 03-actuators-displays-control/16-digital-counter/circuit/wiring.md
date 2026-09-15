# 4-Bit Digital Counter with Arduino Uno

![Arduino](https://img.shields.io/badge/Platform-Arduino%20Uno-**00979C**?logo=arduino&logoColor=white) ![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?logo=c%2B%2B) A simple hardware implementation of a 4-bit binary digital up/down counter using an Arduino Uno, two momentary tactile buttons, and four LEDs. The counter supports values from **0 to 15** (`**0000**` to `**1111**` in binary) with integrated upper and lower limit clamping.

---

## Table of Contents

- [Overview](#overview)
- [Bill of Materials](#bill-of-materials)
- [Pin Configuration](#pin-configuration)
- [Circuit Diagram](#circuit-diagram)
- [Binary Truth Table](#binary-truth-table)
- [Firmware Implementation](#firmware-implementation)
- [Testing & Verification](#testing--verification)
- [Troubleshooting](#troubleshooting)
- [Safety Guidelines](#safety-guidelines)
- [License](#license)

---

## Overview

This project demonstrates binary counting and digital I/O handling on an embedded microcontroller:
- **Button Inputs**: Uses internal pull-up resistors (`INPUT_PULLUP`), eliminating the need for external pull-up/pull-down resistors.
- **Active-Low Logic**: Buttons read `**LOW**` when pressed and `**HIGH**` when idle.
- **Output Display**: 4 individual LEDs represent bit weights $2^0$, $2^1$, $2^2$, and $2^3$.
- **Boundary Clamping**: The value is constrained strictly between `0` and `15`.

---

## Bill of Materials

| Item | Quantity | Description |
|---|---|---|
| **Arduino Uno** | 1 | Microcontroller board (or compatible equivalent) |
| **LEDs** | 4 | Standard 5mm LEDs (Red, Green, Blue, or Yellow) |
| **Resistors** | 4 | 220 Ω (1/4 W, current limiting) |
| **Push Buttons** | 2 | Momentary tactile push buttons |
| **Breadboard** | 1 | Standard half-size or full-size solderless board |
| **Jumper Wires** | — | Male-to-Male jumper cables |

---

## Pin Configuration

### Push Buttons (Inputs)

Both buttons are configured using `INPUT_PULLUP`. Connect one terminal of each switch to the specified digital pin and the opposing terminal to `**GND**`.

| Function | Arduino Pin | Normal State | Pressed State |
|---|---|---|---|
| **UP** (Increment) | `D2` | `HIGH` (5V via internal pull-up) | `LOW` (GND) |
| **DOWN** (Decrement) | `D3` | `HIGH` (5V via internal pull-up) | `LOW` (GND) |

### LED Outputs (Binary Representation)

Each **LED** represents one binary bit. Anode connects through a **220** Ω current-limiting resistor to the pin; cathode connects to common `**GND**`.

| Bit Position | Bit Weight | Arduino Pin | Resistor |
|---|---|---|---|
| **Bit 0 (LSB)** | $2^0 = 1$ | `D8` | 220 Ω |
| **Bit 1** | $2^1 = 2$ | `D9` | 220 Ω |
| **Bit 2** | $2^2 = 4$ | `D10` | 220 Ω |
| **Bit 3 (MSB)** | $2^3 = 8$ | `D11` | 220 Ω |

---

## Circuit Diagram

```text
    **ARDUINO** **UNO**
    ┌─────────────────┐
    │                 │
    D2 ──────┤ UP **BUTTON**       │
    D3 ──────┤ **DOWN** **BUTTON**     │
    │                 │
    D8 ──────┤ **BIT** 0 (**LSB**)     │
    D9 ──────┤ **BIT** 1           │
    **D10** ──────┤ **BIT** 2           │
    **D11** ──────┤ **BIT** 3 (**MSB**)     │
    │                 │
    **GND** ──────┤ **GND**             │
    └─────────────────┘

**WIRING** **CONNECTIONS**:

Buttons (Active-Low):
    D2 ───────── [ **PUSH** **BUTTON**: UP ]   ───────── **GND**
    D3 ───────── [ **PUSH** **BUTTON**: **DOWN** ] ───────── **GND**

**LED** Outputs:
    D8  (Bit 0) ─── [ **220**Ω ] ─── (Anode) [ **LED** 0 ] (Cathode) ─── **GND**
    D9  (Bit 1) ─── [ **220**Ω ] ─── (Anode) [ **LED** 1 ] (Cathode) ─── **GND**
    **D10** (Bit 2) ─── [ **220**Ω ] ─── (Anode) [ **LED** 2 ] (Cathode) ─── **GND**
    **D11** (Bit 3) ─── [ **220**Ω ] ─── (Anode) [ **LED** 3 ] (Cathode) ─── **GND**
