/*
  IoT Student Lab
  Project 11: Temperature Monitor
  Platform: Arduino Uno
  Sensor: LM35
  Concept: Analog Input + Sensor Reading + Calculation + Serial Monitor
*/

const int TEMP_SENSOR_PIN = A0;

const float ADC_REFERENCE = 5.0;
const int ADC_RESOLUTION = 1023;

void setup() {
  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 11: Temperature Monitor");
  Serial.println("================================");
}

void loop() {
  int sensorValue = analogRead(TEMP_SENSOR_PIN);

  float voltage = sensorValue * ADC_REFERENCE / ADC_RESOLUTION;

  // LM35 produces approximately 10 mV per degree Celsius.
  float temperatureC = voltage * 100.0;

  Serial.print("Raw ADC: ");
  Serial.print(sensorValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V");

  Serial.print(" | Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.println(" °C");

  delay(1000);
}
