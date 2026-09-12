# Project 01 — Learning Notes

## 1. What is a GPIO?

GPIO means General Purpose Input/Output.

A digital GPIO can be configured by the microcontroller as an input or output.

In this project, Arduino digital pin 8 is configured as an OUTPUT.

---

## 2. What does HIGH mean?

For this project, setting the output HIGH makes the GPIO output a high digital logic level.

This drives the LED circuit into its ON state.

---

## 3. What does LOW mean?

Setting the output LOW makes the GPIO output a low digital logic level.

This turns the LED OFF in our circuit.

---

## 4. setup()

`setup()` runs once when the Arduino starts or resets.

We use it to configure the LED pin:

```cpp
pinMode(LED_PIN, OUTPUT);

##5. loop()

loop() runs repeatedly.

The Arduino continuously executes the instructions inside it.

##6. digitalWrite()
digitalWrite(LED_PIN, HIGH);

sets the selected digital output HIGH.

digitalWrite(LED_PIN, LOW);

sets it LOW.

##7. delay()
delay(1000);

pauses program execution for approximately 1000 milliseconds.

1000 milliseconds = 1 second.

## Experiment

Change:

```cpp
delay(1000); to: delay(250);

Observe the difference.

Then try:

```cpp
delay(2000);

Observe again.

##Question

How does changing the delay value affect the blinking frequency?
