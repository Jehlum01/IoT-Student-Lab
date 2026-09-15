# Level 2 — Practice Questions

## A. Fundamentals

### 1. Digital Input

What does `digitalRead()` return when used to read a digital input?

---

### 2. INPUT_PULLUP

Why is `INPUT_PULLUP` useful when connecting a push button?

---

### 3. Active-Low Logic

When a button is configured with `INPUT_PULLUP` and connected between the input pin and GND, what state normally represents a pressed button?

---

### 4. Analog Input

What is the typical ADC reading range returned by `analogRead()` on an Arduino Uno?

---

### 5. Sensor Reading

Why does an LDR circuit commonly use a voltage divider?

---

## B. Programming Logic

### 6. Toggle

What is the purpose of a state variable in an LED toggle project?

---

### 7. Boolean Logic

What does this operation do?

```cpp
ledState = !ledState;


8. Edge Detection

Why is it useful to detect the transition from HIGH to LOW rather than simply checking whether a button is LOW?

9. Threshold

An LDR project uses:

if (lightLevel < DARK_THRESHOLD)

What does this condition represent?

10. Decision Making

Complete the basic automation model:

Sense → ______ → Act
C. Temperature
11. LM35

Approximately what voltage change corresponds to a 1°C temperature change for a commonly used LM35?

12. Conversion

If an LM35 produces approximately 0.30 V, what temperature does the basic LM35 conversion estimate?

13. Monitoring

Why is displaying both the raw ADC value and calculated temperature useful during development?

D. Automation
14. Actuator

What is the role of an actuator in an embedded automation system?

15. Fan Control

Why should a DC fan generally not be powered directly from an Arduino GPIO pin?

16. Hysteresis

A temperature-controlled fan turns ON at 30°C and OFF at 28°C.

What problem does this separation between thresholds help prevent?

17. PIR

What type of signal does a typical PIR module provide to the Arduino?

18. Motion Detection

Why might a PIR-based light remain ON longer than expected?

E. Timing
19. delay()

What is a major limitation of using a long delay() in an automation system?

20. millis()

Why can millis() be preferable to delay() for responsive embedded systems?
