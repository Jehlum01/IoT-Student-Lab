/*
  IoT Student Lab
  Project 03: Traffic Light System

  Platform: Arduino Uno
  Concept: Multiple Outputs + Sequencing + State Logic

  Learning:
  - Controlling multiple GPIO pins
  - Executing instructions in sequence
  - Managing timed states
  - Coordinating multiple outputs
*/

const int RED_LED = 8;
const int YELLOW_LED = 9;
const int GREEN_LED = 10;

// Timing values in milliseconds.
const unsigned long RED_TIME = 5000;
const unsigned long YELLOW_TIME = 2000;
const unsigned long GREEN_TIME = 5000;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Start in a safe state.
  allLightsOff();
}

void loop() {

  // State 1: RED
  setLights(HIGH, LOW, LOW);
  delay(RED_TIME);

  // State 2: GREEN
  setLights(LOW, LOW, HIGH);
  delay(GREEN_TIME);

  // State 3: YELLOW
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
