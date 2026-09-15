/*
  IoT Student Lab
  Project 22: Automatic Door System
  Platform: Arduino Uno
  Sensor: HC-SR04 Ultrasonic Sensor
  Actuator: SG90 Servo Motor

  Concept:
  Sensor → Decision → Servo → Automatic Door
*/

#include <Servo.h>

const int TRIG_PIN = 8;
const int ECHO_PIN = 9;
const int SERVO_PIN = 10;

const int DOOR_CLOSED_ANGLE = 0;
const int DOOR_OPEN_ANGLE = 90;

// Open when an object is within this distance
const float DETECTION_DISTANCE = 30.0;

// Keep door open for this long after the last detection
const unsigned long CLOSE_DELAY = 3000;

// HC-SR04 timeout
const unsigned long ECHO_TIMEOUT = 30000UL;

Servo doorServo;

bool doorOpen = false;
unsigned long lastDetectionTime = 0;

float measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration =
    pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT);

  if (duration == 0) {
    return -1.0;
  }

  return duration * 0.0343 / 2.0;
}

void openDoor() {
  if (!doorOpen) {
    doorOpen = true;
    doorServo.write(DOOR_OPEN_ANGLE);

    Serial.println("Door: OPEN");
  }

  lastDetectionTime = millis();
}

void closeDoor() {
  if (doorOpen) {
    doorOpen = false;
    doorServo.write(DOOR_CLOSED_ANGLE);

    Serial.println("Door: CLOSED");
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  doorServo.attach(SERVO_PIN);
  doorServo.write(DOOR_CLOSED_ANGLE);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 22: Automatic Door");
  Serial.println("================================");
  Serial.println("Detection distance: 30 cm");
  Serial.println("Door initially CLOSED");
}

void loop() {
  float distance = measureDistanceCm();

  Serial.print("Distance: ");

  if (distance < 0) {
    Serial.println("No echo");
  }
  else {
    Serial.print(distance, 1);
    Serial.println(" cm");
  }

  // Object detected
  if (distance > 0 && distance <= DETECTION_DISTANCE) {
    openDoor();
  }

  // Close only after the object has left
  // and the configured delay has elapsed.
  if (doorOpen &&
      millis() - lastDetectionTime >= CLOSE_DELAY) {
    closeDoor();
  }

  delay(100);
}
