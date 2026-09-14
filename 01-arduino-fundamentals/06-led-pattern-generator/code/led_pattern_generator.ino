/*
  IoT Student Lab
  Project 06: LED Pattern Generator

  Platform: Arduino Uno
  Concept: Arrays + Binary Patterns + Loops

  Learning:
  - Using arrays for hardware pins
  - Representing patterns as binary values
  - Bitwise operations
  - Using loops to display patterns
*/

const int LED_COUNT = 8;

const int LED_PINS[LED_COUNT] = {
  2, 3, 4, 5, 6, 7, 8, 9
};

const int PATTERN_DELAY = 500;

void setup() {

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  allLedsOff();
}

void loop() {

  // Display every 8-bit binary pattern.
  for (int pattern = 0; pattern <= 255; pattern++) {

    displayPattern(pattern);

    delay(PATTERN_DELAY);
  }
}

void displayPattern(int pattern) {

  for (int i = 0; i < LED_COUNT; i++) {

    // Extract one bit from the pattern.
    int bitValue = bitRead(pattern, i);

    digitalWrite(LED_PINS[i], bitValue);
  }
}

void allLedsOff() {

  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}
