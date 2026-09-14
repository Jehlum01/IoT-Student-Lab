/*
  IoT Student Lab
  Project 12: Temperature-Controlled Fan
  Platform: Arduino Uno
  Sensor: LM35
  Actuator: DC Fan through transistor driver
  Concept: Sensor + Decision + Actuator + Automation
*/

const int TEMP_SENSOR_PIN = A0;
const int FAN_PIN = 8;

const float ADC_REFERENCE = 5.0;
const int ADC_RESOLUTION = 1023;

const float FAN_ON_TEMP = 30.0;
const float FAN_OFF_TEMP = 28.0;

bool fanState = false;

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 12: Temperature-Controlled Fan");
  Serial.println("================================");
}

void loop() {
  int sensorValue = analogRead(TEMP_SENSOR_PIN);

  float voltage = sensorValue * ADC_REFERENCE / ADC_RESOLUTION;
  float temperatureC = voltage * 100.0;

  /*
    Hysteresis prevents the fan from rapidly switching
    ON and OFF when the temperature is close to the threshold.
  */

  if (!fanState && temperatureC >= FAN_ON_TEMP) {
    fanState = true;
    digitalWrite(FAN_PIN, HIGH);
  }

  if (fanState && temperatureC <= FAN_OFF_TEMP) {
    fanState = false;
    digitalWrite(FAN_PIN, LOW);
  }

  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print(" °C | Fan: ");

  if (fanState) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  delay(1000);
}
