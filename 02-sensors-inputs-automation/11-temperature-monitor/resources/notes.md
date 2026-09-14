# Project 11 — Learning Notes

## What are we learning?

This project introduces a real-world sensor and teaches the complete measurement chain:

**Sense → Measure → Calculate → Display**

The Arduino does not directly receive a temperature value.

The sensor produces an electrical signal. The Arduino's ADC converts that signal into a numerical value.

## Key Concepts

### 1. Analog Input

Unlike a digital input that mainly represents:

```text
HIGH / LOW

##Important

The Arduino reads the sensor as an analog voltage.

For the commonly used LM35:

Approximately 10 mV represents 1°C.
0.25 V ≈ 25°C
0.30 V ≈ 30°C

The exact reading may vary slightly because of sensor tolerance, supply voltage, ADC reference, wiring, and environmental conditions.

##Testing
1. Connect the LM35 carefully.
2. Upload the program.
3. Open Arduino IDE Serial Monitor.
4. Set the baud rate to 9600.
5. Observe the temperature.
6. Hold the sensor carefully between your fingers.
7. Observe whether the temperature gradually increases.

##Troubleshooting
Temperature stays at 0°C

Check:

1. LM35 power connection
2. LM35 ground
3. A0 signal connection
4. Sensor orientation
5. Temperature is extremely high

Immediately disconnect power and check the sensor pin connections.

Temperature fluctuates

##Possible causes:

Loose jumper wires
Electrical noise
Sensor movement
Unstable power supply
Serial Monitor shows unreadable characters

##Make sure Serial Monitor is set to:

##9600 baud

##Safety

1. Do not expose the sensor or Arduino to water.

2. Do not connect the analog input directly to voltages above the Arduino's permitted input range.

## What is really happening?
an analog input provides a range of numerical values.

On a typical Arduino Uno:

analogRead(A0)

returns approximately:

0 → 1023

2. ADC
ADC means:
### Analog-to-Digital Converter

It converts the sensor's analog voltage into a digital number that the microcontroller can process.

3. Voltage Calculation

The program converts the ADC reading into voltage:

voltage = sensorValue * 5.0 / 1023.0;

4. Temperature Calculation

For the commonly used LM35:

10 mV ≈ 1°C

Therefore:

temperatureC = voltage * 100.0;

Example:

0.25 V × 100 = 25°C

#Why Serial Monitor?

The Serial Monitor gives us a simple way to observe sensor data while developing and debugging.

The program reports:

Raw ADC
Voltage
Temperature

This is useful because students can compare the raw measurement with the processed result.

Engineering Thinking

Ask: What?

We want to measure temperature.

Why?

Temperature is an important environmental parameter used in:

1. Weather stations
2. HVAC systems
3. Industrial monitoring
4. Data logging
5. Smart homes
6. Equipment protection

## How?

Sensor
  ↓
Analog signal
  ↓
ADC
  ↓
Calculation
  ↓
Temperature value
  ↓
Serial Monitor


###Experiments

## Experiment 1 — Touch the sensor

Observe the temperature before and after holding the sensor.

Question:

Why does the reading change?

## Experiment 2 — Change the update rate

Change:

delay(1000);

to:

delay(500);

Observe the difference.

## Experiment 3 — Display Fahrenheit

Add a Fahrenheit calculation:

float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

Display both Celsius and Fahrenheit.

## Experiment 4 — Temperature warning

Add an LED that turns ON when:

Temperature > 30°C

This prepares students for Project 12:

Temperature-Controlled Fan

Challenge

Modify the program so that the Serial Monitor displays:

Temperature: 27.4 °C
Status: NORMAL

and when the temperature exceeds a chosen threshold:

Temperature: 32.1 °C
Status: HIGH TEMPERATURE
