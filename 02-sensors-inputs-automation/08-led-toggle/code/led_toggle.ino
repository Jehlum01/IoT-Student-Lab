/*
  IoT Student Lab
  Project 08: LED Toggle / Electronic Switch

  Platform: Arduino Uno
  Concept: State Variables + Button Events + Toggle Logic
*/

const int BUTTON_PIN = 2;
const int LED_PIN = 8;

bool ledState = false;

// Stores the previous button state.
bool lastButtonState = HIGH;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
}

void loop() {

  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Detect a new button press.
  if (lastButtonState == HIGH && currentButtonState == LOW) {

    // Change the LED state.
    ledState = !ledState;

    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    // Simple debounce delay.
    delay(50);
  }

  // Store current state for the next loop.
  lastButtonState = currentButtonState;
}
