/*
  IoT Student Lab
  Project 04: Pedestrian Traffic Light

  Platform: Arduino Uno
  Concept: Digital Input + Conditions + Decision Making

  Learning:
  - Reading a push button
  - Using digitalRead()
  - Using INPUT_PULLUP
  - Using if conditions
  - Responding to user input
  - Combining inputs and outputs
*/

const int RED_LED = 8;
const int YELLOW_LED = 9;
const int GREEN_LED = 10;

const int BUTTON_PIN = 2;

// Normal traffic timing.
const unsigned long RED_TIME = 5000;
const unsigned long GREEN_TIME = 5000;
const unsigned long YELLOW_TIME = 2000;

// Extra red time after a pedestrian request.
const unsigned long PEDESTRIAN_TIME = 5000;

void setup() {

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Button is connected between D2 and GND.
  // INPUT_PULLUP keeps the input HIGH normally
  // and LOW when the button is pressed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  allLightsOff();
}

void loop() {

  // RED state
  setLights(HIGH, LOW, LOW);
  delay(RED_TIME);

  // GREEN state
  setLights(LOW, LOW, HIGH);

  unsigned long greenStart = millis();

  while (millis() - greenStart < GREEN_TIME) {

    // Button pressed?
    if (digitalRead(BUTTON_PIN) == LOW) {

      // Give the system a short yellow transition.
      setLights(LOW, HIGH, LOW);
      delay(YELLOW_TIME);

      // Stop traffic for the pedestrian crossing.
      setLights(HIGH, LOW, LOW);
      delay(PEDESTRIAN_TIME);

      return;
    }
  }

  // Normal transition to yellow.
  setLights(LOW, HIGH, LOW);
  delay(YELLOW_TIME);
}

void setLights(int redState, int yellowState, int greenState) {

  digitalWrite(RED_LED, redState);
  digitalWrite(YELLOW_LED, yellowState);
  digitalWrite(GREEN_LED, greenState);
}

void allLightsOff() {

  setLights(LOW, LOW, LOW);
}
