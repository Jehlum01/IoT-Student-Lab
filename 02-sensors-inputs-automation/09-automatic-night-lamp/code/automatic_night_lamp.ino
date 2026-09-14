/*
  IoT Student Lab
  Project 09: Automatic Night Lamp

  Platform: Arduino Uno
  Concept: LDR + Analog Input + Threshold

  Learning:
  - Analog sensor input
  - analogRead()
  - Sensor values
  - Threshold-based decisions
  - Automatic control
*/

const int LDR_PIN = A0;
const int LED_PIN = 8;

// Adjust this value after observing your LDR readings.
const int DARK_THRESHOLD = 500;

void setup() {

  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Read the LDR value.
  int lightLevel = analogRead(LDR_PIN);

  // Display the sensor value.
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  // Decide whether it is dark.
  if (lightLevel < DARK_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(300);
}
