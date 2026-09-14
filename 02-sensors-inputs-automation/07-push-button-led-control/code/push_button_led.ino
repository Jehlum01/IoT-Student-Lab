/*
  IoT Student Lab
  Project 07: Push Button LED Control

  Platform: Arduino Uno
  Concept: Digital Input → Processing → Output

  Learning:
  - Digital input
  - digitalRead()
  - INPUT_PULLUP
  - if statements
  - Input/output relationship
*/

const int BUTTON_PIN = 2;
const int LED_PIN = 8;

void setup() {

  // LED is an output.
  pinMode(LED_PIN, OUTPUT);

  // Button uses Arduino's internal pull-up resistor.
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Start with LED OFF.
  digitalWrite(LED_PIN, LOW);
}

void loop() {

  // Read the button.
  int buttonState = digitalRead(BUTTON_PIN);

  // With INPUT_PULLUP:
  // HIGH = button released
  // LOW  = button pressed

  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}
