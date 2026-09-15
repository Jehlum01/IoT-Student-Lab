# 🎲 Project 15 — Mini Electronic Dice

A digital 7-LED electronic dice circuit powered by an Arduino Uno. The system uses an active-low tactile push button to trigger a pseudo-random roll sequence and render standard pip patterns ($1\text{--}6$).

## 🧰 Components Required

| Component | Quantity | Notes / Specifications | 
 | ----- | ----- | ----- | 
| **Arduino Uno** | 1 | Microcontroller development board | 
| **LEDs** | 7 | Standard $5\text{ mm}$ (e.g., Red or Green) | 
| **Current-Limiting Resistors** | 7 | $220\ \Omega$ ($1/4\text{ W}$, $5\%$ tolerance) | 
| **Tactile Push Button** | 1 | Momentary 4-pin switch | 
| **Breadboard** | 1 | Full-size or half-size solderless board | 
| **Jumper Wires** | — | Male-to-Male (M-M) hookup leads | 

## 🔌 Circuit Wiring & Pin Mapping

### 1. Push Button (Active-Low Input)

The momentary tactile button uses the internal microcontroller pull-up resistor (`INPUT_PULLUP`). No external pull-up resistor is required.

| Switch Terminal | Arduino Uno Pin | State Logic | 
 | ----- | ----- | ----- | 
| **Terminal A** | `D2` | Button Released $\rightarrow$ `HIGH` ($5\text{ V}$) | 
| **Terminal B** | `GND` | Button Pressed $\rightarrow$ `LOW` ($0\text{ V}$) | 

```
// Firmware input configuration
pinMode(2, INPUT_PULLUP);

```

### 2. LED Matrix Pinout

Each LED channel must have its own dedicated series current-limiting resistor to protect the microcontroller output registers.

$$
\text{GPIO Pin} \;\longrightarrow\; 220\ \Omega\ \text{Resistor} \;\longrightarrow\; \text{Anode (+)} \;\longrightarrow\; [\text{LED}] \;\longrightarrow\; \text{Cathode (-)} \;\longrightarrow\; \text{GND}
$$

| LED Array Index | Arduino GPIO Pin | Role / Position on Die | 
 | ----- | ----- | ----- | 
| **Position 0** | `D3` | Top-Left Corner | 
| **Position 1** | `D4` | Top-Right Corner | 
| **Position 2** | `D5` | Center-Top / Upper Row | 
| **Position 3** | `D6` | True Center Pip | 
| **Position 4** | `D7` | Center-Bottom / Lower Row | 
| **Position 5** | `D8` | Bottom-Left Corner | 
| **Position 6** | `D9` | Bottom-Right Corner | 

## 📐 Physical Dice Layout

### Pin Alignment Guide

Arrange the 7 LEDs on your breadboard following this coordinate mapping:

```
          [ D3 ]              [ D4 ]
          (Pos 0)             (Pos 1)

                    [ D5 ]
                    (Pos 2)

                    [ D6 ]  ◄── (Center Pip)
                    (Pos 3)

                    [ D7 ]
                    (Pos 4)

          [ D8 ]              [ D9 ]
          (Pos 5)             (Pos 6)

```

> \[!TIP\]
> **Orientation Consistency:** Ensure all 7 LED cathodes (short legs / flat edges) connect to the common ground rail, and keep their pin positions aligned with the software indices.

## 🎯 Binary Pip Patterns ($1\text{ to }6$)

Legend: `●` = **LED ON (`HIGH`)** | `·` = **LED OFF (`LOW`)**

```
 ─── Value 1 ───       ─── Value 2 ───       ─── Value 3 ───
    ·       ·             ●       ·             ●       ·
        ·                     ·                     ·
        ●                     ·                     ●
        ·                     ·                     ·
    ·       ·             ·       ●             ·       ●

 ─── Value 4 ───       ─── Value 5 ───       ─── Value 6 ───
    ●       ●             ●       ●             ●       ●
        ·                     ·                     ●
        ·                     ●                     ·
        ·                     ·                     ●
    ●       ●             ●       ●             ●       ●

```

## 🧪 Testing & Verification Sequence

1. **Firmware Upload:** Connect the Arduino via USB and flash your sketch.

2. **Serial Telemetry:** Open the Serial Monitor set to **9600 baud**.

3. **Actuation:** Press and release the button wired to `D2`.

4. **Pattern Inspection:** Verify that the LEDs illuminate to form a valid die face from $1$ through $6$.

5. **Cycle Testing:** Depress the switch repeatedly to confirm dynamic pseudo-random outcome generation.

## 🔍 Troubleshooting Guide

```
                         Troubleshooting Flowchart
                                     │
                 ┌───────────────────┴───────────────────┐
                 ▼                                       ▼
        [Button Non-Responsive]                 [LED Malfunction]
                 │                                       │
      ┌──────────┴──────────┐                 ┌──────────┴──────────┐
      ▼                     ▼                 ▼                     ▼
Check Pin 2 / GND     Verify Firmware   One LED Dead:         Wrong Shape:
continuity across      uses correct     Inspect Polarity,      Check Pin Indices
switch diagonal.      `INPUT_PULLUP`.   Resistor & Rail.      (D3-D9 mapping).

```

| Symptom | Probable Cause | Corrective Action | 
 | ----- | ----- | ----- | 
| **Button does nothing** | • Loose breadboard connection  • Wrong switch pin pair used  • `pinMode` not set to `INPUT_PULLUP` | Reorient switch diagonally across the center trench. Ensure one pin lands on `D2` and the opposing pin on `GND`. | 
| **One LED never illuminates** | • Reversed LED polarity  • Burned-out LED or open resistor  • Misplaced jumper wire | Check that the anode (longer leg) connects through the $220\ \Omega$ resistor to the GPIO pin, and the cathode connects to `GND`. | 
| **LEDs display distorted patterns** | • Swapped digital output pins  • Misaligned breadboard layout | Verify each pin wire against the table: `D3` (Pos 0) through `D9` (Pos 6). | 
| **Same number appears repeatedly** | • Standard PRNG behavior  • Unseeded random generator | Microcontroller PRNGs are deterministic. Seed the generator using noise from an unconnected analog pin: `randomSeed(analogRead(A0));`. | 

## ⚠️ Circuit Safety

> **Current Limiting Required:**
>
> Never wire an LED directly between an Arduino GPIO pin and ground. Driving an LED without a series current-limiting resistor ($220\ \Omega\text{--}330\ \Omega$) draws excessive current, causing permanent damage to the microcontroller's ATmega328P output transistors.
