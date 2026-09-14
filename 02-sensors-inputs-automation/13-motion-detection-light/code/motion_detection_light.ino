/*
  IoT Student Lab
  Project 13: Motion Detection Light
  Platform: Arduino Uno
  Sensor: PIR Motion Sensor
  Actuator: LED
  Concept: Digital Sensor + Event Detection + Automation
*/

const int PIR_PIN = 2;
const int LED_PIN = 8;

const unsigned long LIGHT_ON_TIME = 5000;

unsigned long lastMotionTime = 0;
bool lightState = false;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 13: Motion Detection Light");
  Serial.println("================================");
}

void loop() {
  int motionState = digitalRead(PIR_PIN);

  if (motionState == HIGH) {
    lastMotionTime = millis();

    if (!lightState) {
      lightState = true;
      digitalWrite(LED_PIN, HIGH);

      Serial.println("Motion detected - Light ON");
    }
  }

  if (lightState && millis() - lastMotionTime >= LIGHT_ON_TIME) {
    lightState = false;
    digitalWrite(LED_PIN, LOW);

    Serial.println("No recent motion - Light OFF");
  }

  delay(50);
}
