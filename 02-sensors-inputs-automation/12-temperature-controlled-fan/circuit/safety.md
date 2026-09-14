Flyback Protection

For a brushed DC fan or other inductive load, use a suitable flyback diode across the fan terminals.

The diode protects the switching device from voltage spikes generated when the fan is switched OFF.

Common Ground

The Arduino ground and the external fan-supply ground should be connected together when using a typical low-side transistor/MOSFET driver.

Arduino GND ───────── External Supply GND
Important

Do NOT connect a motor/fan directly between an Arduino GPIO pin and GND.

A GPIO pin is intended to provide a control signal, not the current required by a motor.

Control Logic
Temperature >= 30°C
        ↓
     Fan ON

Temperature <= 28°C
        ↓
     Fan OFF

The gap between the ON and OFF temperatures provides hysteresis.

Testing
Connect the LM35.
Connect the fan driver.
Verify all grounds.
Upload the program.
Open Serial Monitor at 9600 baud.
Warm the sensor gently using your fingers.
Observe the temperature.
Verify that the fan turns ON after reaching the ON threshold.
Allow the sensor to cool.
Verify that the fan turns OFF after reaching the OFF threshold.
Safety
Use only a low-voltage DC fan for this student project.
Use an external supply appropriate for the fan.
Never connect mains AC directly to the Arduino circuit.
Never power a motor directly from an Arduino GPIO.
Verify transistor/MOSFET and diode orientation before powering the circuit.
