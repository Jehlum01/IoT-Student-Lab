# 🔍 Level 2: Embedded Systems Troubleshooting Guide

 **Core Debugging Principle:**  
Never assume the code is broken first. Good engineering follows a disciplined, step-by-step diagnostic workflow rather than guesswork.

---

## 🧭 Systematic Triage Pipeline

When diagnosing embedded hardware or firmware anomalies, isolate failure modes in this exact sequence:

```
[1. Power Rail] ──► [2. Ground Reference] ──► [3. Hardware Wiring]
                                                      │
                                                      ▼
[6. Program Logic] ◄── [5. Serial Diagnostics] ◄── [4. Pin & IO Mapping]
        │
        ▼
[7. Timing & Race Conditions]
```

---

## 🛠️ Root-Cause Analysis Framework

For each challenge, students must document their diagnostic findings using the **C-T-F-V** framework:

| Phase | Description | Goal |
| :--- | :--- | :--- |
| **Cause** | Identify the underlying physical or logical defect. | Pinpoint the exact failure mechanism. |
| **Test** | Formulate an experiment or measurement. | Confirm or invalidate the hypothesis. |
| **Fix** | Apply the targeted correction (hardware or code). | Resolve the root defect without side effects. |
| **Verification** | Re-run test conditions to ensure stability. | Validate normal operation under all states. |

---

## 📋 Diagnostic Cases

### Case 01 — Button Always LOW

#### Symptoms
* Input configured with internal pull-up: `pinMode(pin, INPUT_PULLUP);`
* **Serial Monitor Output:** Continuously reports `LOW` (0), even when the push button is physically released.

#### Diagnostic Checklist
- [ ] Button switch terminal orientation (bridging row connections incorrectly across the breadboard center trench).
- [ ] Short-circuit between digital input line and `GND`.
- [ ] Mechanical failure of momentary tactile switch.

```
       Incorrect Pinout (Internal Short)          Correct Bridged Layout
             ┌───────────┐                             ┌───────────┐
      Pin ───┤ 1       2 ├─── GND               Pin ───┤ 1       3 ├─── GND
             │   [   ]   │                             │   [   ]   │
             │ 3       4 │                             │ 2       4 │
             └───────────┘                             └───────────┘
```

#### Investigation Matrix
* **Cause:** Pin permanently connected to ground due to wrong leg pair usage on 4-pin switch, solder bridge, or misplaced jumper.
* **Test:** Disconnect the wire going to the button entirely; verify if the pin floats back to `HIGH` via `INPUT_PULLUP`.
* **Fix:** Reorient button diagonally across the breadboard divide or wire to normally-open contacts.
* **Verification:** Confirm Serial prints `HIGH` when idle, and changes to `LOW` *only* during active press.

---

### Case 02 — LED Always ON

#### Symptoms
* Automatic night-lamp using an LDR configured in a voltage divider connected to analog pin `A0`.
* The output illumination LED stays continuously `ON`, even when direct, bright light shines on the LDR.

#### Diagnostic Matrix
* **Investigate:**
  * Sensor circuit topology (Pull-up vs. Pull-down divider).
  * Voltage divider resistor values (e.g., using $100\ \Omega$ instead of $10\text{ k}\Omega$).
  * Software comparator operator (`>` vs. `<`) relative to ambient ADC counts.
  * Live ADC readings printed to Serial Monitor.

> [!TIP]
> **Voltage Divider Formula:**
> $$V_{\text{out}} = V_{\text{cc}} \times \frac{R_2}{R_1 + R_2}$$
> Always print raw analog counts ($0\text{--}1023$) to Serial before establishing a hardcoded threshold.

---

### Case 03 — Impossible Temperature Readings

#### Symptoms
* Analog temperature telemetry stream reports wild or extreme values:
  ```text
  [TELEMETRY] Sensor: TMP36 | Temperature: 480.0 °C | Status: FAULT
  ```

#### Diagnostic Flowchart
```
                      Read Raw ADC Value
                              │
               ┌──────────────┴──────────────┐
               ▼                             ▼
        ADC near 1023                  ADC Plausibility
    (Pin tied to VCC /                 (Pin is reading
   Sensor reversed / Hot)            standard millivolts)
               │                             │
               ▼                             ▼
     Check sensor pinout!           Inspect conversion math:
    TMP36 flat side pinout:          V = ADC * (5.0 / 1023.0)
     Pin 1: VCC                      T = (V - 0.5) * 100.0
     Pin 2: VOUT (Analog)
     Pin 3: GND
```

#### Diagnostic Action Items
- [ ] Inspect sensor orientation immediately (reverse polarity makes ICs blisteringly hot).
- [ ] Verify ADC conversion factor matches actual microcontroller rail voltage ($5.0\text{ V}$ vs. $3.3\text{ V}$).
- [ ] Confirm sensor transfer function (e.g., TMP36 vs. LM35 vs. Thermistor equation).

---

### Case 04 — Fan Rapidly Switches (Chatter / Oscillation)

#### Symptoms
* When temperature hovers near the switching boundary (e.g., $28.0\ ^\circ\text{C}$), the motor rapidly turns `ON` and `OFF` several times per second.

```
 Temp (°C)
   │                  Noisy Analog Signal
28 ┼───/\──/\──/\──/\──/\── Threshold Level (Motor switches constantly!)
   │  /  \/  \/  \/  \/  \
   └──────────────────────── Time
```

#### Engineering Solution: Hysteresis Band
* **Root Cause:** Signal noise and ADC jitter around a single scalar threshold.
* **Control Strategy:** Implement a dual-threshold hysteresis window or low-pass digital smoothing filter.

```c
// Example: Hysteresis Control Logic
const float TEMP_HIGH_TURN_ON  = 28.5; // Turn ON when too hot
const float TEMP_LOW_TURN_OFF  = 26.5; // Turn OFF only when cooled down

if (currentTemp >= TEMP_HIGH_TURN_ON) {
  setFanState(true);
} else if (currentTemp <= TEMP_LOW_TURN_OFF) {
  setFanState(false);
}
```

---

### Case 05 — PIR Light Turns OFF Too Early

#### Symptoms
* Room occupancy light is configured to remain illuminated for 5 seconds after motion stops, but shuts off abruptly or toggles unpredictably during active occupancy.

#### Critical Hardware & Firmware Checks

| Check | Focus Area | Correct Configuration |
| :--- | :--- | :--- |
| **PIR Retrigger Jumper** | Hardware mode switch on PIR board | Set to **'H' (Repeat Trigger)**, not 'L' (Single Trigger). |
| **Hardware Hold Potentiometer** | Onboard potentiometer on HC-SR501 | Set to minimum before relying on software timers. |
| **Non-blocking Timestamp** | Firmware timing architecture | Verify `millis()` reset condition captures active triggers. |

```c
// Correct re-triggerable non-blocking timing pattern
if (digitalRead(PIR_PIN) == HIGH) {
  lastMotionTime = millis(); // Refresh timestamp continuously while motion persists
  digitalWrite(LIGHT_PIN, HIGH);
}

if (millis() - lastMotionTime >= HOLD_DURATION_MS) {
  digitalWrite(LIGHT_PIN, LOW);
}
```

---

### Case 06 — PIR Never Detects Motion

#### Symptoms
* Sensor board receives $5\text{ V}$ power, but output pin never toggles to logic `HIGH` upon movement.

#### Investigation Checklist
- [ ] **Warm-up Stabilization:** Did you wait $30\text{--}60$ seconds after boot? (PIR sensors require thermal settling time).
- [ ] **Pinout Verification:** Do not assume header pin order. Many HC-SR501 boards use `GND-OUT-VCC` or `VCC-OUT-GND`.
- [ ] **Fresnel Lens Orientation:** Ensure sensor dome points outward into the field of detection.
- [ ] **Output Voltage Compatibility:** Some PIR modules output $3.3\text{ V}$ logic; verify that the Arduino digital pin registers this as logic `HIGH`.

---

### Case 07 — Buzzer Does Not Sound

#### Symptoms
* Security alarm trips, visual status LED activates as designed, but piezo buzzer emits zero audible output.

#### Diagnostic Decision Tree

```
                      Buzzer Hardware Type
                               │
               ┌───────────────┴───────────────┐
               ▼                               ▼
         Active Buzzer                  Passive Buzzer
   (Internal oscillator IC)          (Requires AC waveform)
               │                               │
       Digital Write Test:              Tone Function Test:
    digitalWrite(PIN, HIGH);            tone(PIN, 1000); // 1 kHz
               │                               │
               ├─► No sound?                   ├─► No sound?
               │   Check polarity (+ / -)      │   Check drive current /
               │   Check GPIO pin mapping      │   Check flyback / pin mapping
```

---

### Case 08 — Arduino Resets When Fan Starts

#### Symptoms
* Microcontroller runs fine through initial sensor checks. The moment temperature triggers the motor driver, the Arduino spontaneously reboots or halts.

> [!WARNING]
> **Do not modify program code.** This is fundamentally an electromechanical and power delivery fault.

#### Investigation Focus Areas
1. **Inrush Current & Voltage Sag (Brownout):**
   * Motor starting current draw pulls the system rail below the microcontroller's brownout detection threshold ($V_{\text{BOD}}$).
2. **Inductive Kickback (Back-EMF):**
   * Motor windings discharge high-voltage inductive spikes back into common rails when switching.
3. **Absence of a Flyback Diode:**
   * Ensure a rectifier diode (e.g., 1N4001 or 1N4148) is reverse-biased across inductive motor terminals.
4. **Shared Power Rails:**
   * Motor and logic components must not draw from the same unregulated Arduino $5\text{ V}$ header pin. Use an external supply with a **common ground**.

```
             Correct Inductive Load Drive Configuration

             +External Motor Power (e.g., 9V-12V)
                       │
                       ├───┐
                       │   │
                     ┌─┴───┴─┐
                     │ Motor │
                     └─┬───┬─┘
                       │   │   Flyback Diode (1N4001)
                       ├───◄─── [Cathode to +Rail]
                       │
                 ┌─────┴─────┐
   Arduino ──────┤ Base / Gate
    Digital Pin  │ Transistor│
                 └─────┬─────┘
                       │
                     Common Ground (Arduino GND + External GND)
```
#Keep Learning
