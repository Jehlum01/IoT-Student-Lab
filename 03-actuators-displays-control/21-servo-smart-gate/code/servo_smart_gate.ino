/*
  IoT Student Lab
  Project 21: Servo Smart Gate
  Platform: Arduino Uno
  Input: Push Button
  Actuator: Servo Motor
  Concept: Digital Input + Servo Control + State Logic
*/

#include <Servo.h>

const int BUTTON_PIN = 2;
const int SERVO_PIN = 9;

const int GATE_CLOSED_ANGLE = 0;
const int GATE_OPEN_ANGLE = 90;

const unsigned long OPEN_TIME = 5000;
const unsigned long DEBOUNCE_DELAY = 50;

Servo gateServo;

bool gateOpen = false;
bool lastButtonState = HIGH;
unsigned long gateOpenTime = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSED_ANGLE);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 21: Servo Smart Gate");
  Serial.println("================================");
  Serial.println("Gate: CLOSED");
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Detect button press
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(DEBOUNCE_DELAY);

    if (digitalRead(BUTTON_PIN) == LOW) {
      openGate();
    }
  }

  lastButtonState = currentButtonState;

  // Automatically close the gate after the open period
  if (gateOpen && millis() - gateOpenTime >= OPEN_TIME) {
    closeGate();
  }
}

void openGate() {
  if (gateOpen) {
    return;
  }

  gateOpen = true;
  gateOpenTime = millis();

  gateServo.write(GATE_OPEN_ANGLE);

  Serial.println("Gate: OPEN");
}

void closeGate() {
  gateOpen = false;

  gateServo.write(GATE_CLOSED_ANGLE);

  Serial.println("Gate: CLOSED");
}
