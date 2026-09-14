/*
  IoT Student Lab
  Project 14: Automatic Security Alarm
  Platform: Arduino Uno
  Sensor: PIR Motion Sensor
  Actuators: Buzzer + LED
  Concept: Sensor + State + Timing + Alarm Automation
*/

const int PIR_PIN = 2;
const int LED_PIN = 8;
const int BUZZER_PIN = 9;

const unsigned long ALARM_DURATION = 5000;

bool alarmActive = false;
unsigned long alarmStartTime = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 14: Automatic Security Alarm");
  Serial.println("================================");
  Serial.println("System armed.");
}

void loop() {
  int motionState = digitalRead(PIR_PIN);

  // Start alarm when motion is detected.
  if (motionState == HIGH && !alarmActive) {
    alarmActive = true;
    alarmStartTime = millis();

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("ALERT: Motion detected!");
    Serial.println("Alarm ON");
  }

  // Keep alarm active for the configured duration.
  if (alarmActive && millis() - alarmStartTime >= ALARM_DURATION) {
    alarmActive = false;

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("Alarm OFF");
    Serial.println("System armed.");
  }

  delay(50);
}
