/*
  IoT Student Lab
  Project 19: Ultrasonic Distance Meter
  Platform: Arduino Uno
  Sensor: HC-SR04
  Concept: Pulse Timing + Distance Calculation
*/

const int TRIG_PIN = 8;
const int ECHO_PIN = 9;

const unsigned long ECHO_TIMEOUT = 30000UL;

float measureDistanceCm() {
  // Ensure a clean trigger pulse.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send approximately 10 microsecond trigger pulse.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the returning echo.
  unsigned long duration =
    pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT);

  // No echo received.
  if (duration == 0) {
    return -1.0;
  }

  // Approximate speed of sound:
  // distance = time × speed / 2
  //
  // 0.0343 cm/µs is approximately the speed of sound.
  float distanceCm = duration * 0.0343 / 2.0;

  return distanceCm;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 19: Ultrasonic Distance Meter");
  Serial.println("================================");
}

void loop() {
  float distance = measureDistanceCm();

  if (distance < 0) {
    Serial.println("No echo detected.");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");
  }

  delay(250);
}
