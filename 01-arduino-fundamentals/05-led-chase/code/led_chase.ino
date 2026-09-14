/*
  IoT Student Lab
  Project 05: LED Chase / Running LEDs

  Platform: Arduino Uno
  Concept: Loops + Multiple GPIOs

  Learning:
  - Using arrays to store pin numbers
  - Using for loops
  - Controlling multiple outputs
  - Repeating a sequence
*/

const int LED_COUNT = 6;

const int LED_PINS[LED_COUNT] = {
  8, 9, 10, 11, 12, 13
};

const int STEP_DELAY = 120;

void setup() {

  // Configure all LED pins as outputs.
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  allLedsOff();
}

void loop() {

  // Move from left to right.
  for (int i = 0; i < LED_COUNT; i++) {

    allLedsOff();

    digitalWrite(LED_PINS[i], HIGH);

    delay(STEP_DELAY);
  }

  // Move from right to left.
  for (int i = LED_COUNT - 2; i > 0; i--) {

    allLedsOff();

    digitalWrite(LED_PINS[i], HIGH);

    delay(STEP_DELAY);
  }
}

void allLedsOff() {

  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}
