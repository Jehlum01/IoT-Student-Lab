/*
  IoT Student Lab
  Project 02: Random LED Glow & Variable Timing

  Platform: Arduino Uno
  Concept: Variables + Randomness + Variable Timing

  Learning:
  - Variables
  - random()
  - Using variables with delay()
  - Creating unpredictable behaviour
*/

const int LED_PIN = 8;

// Minimum and maximum delay in milliseconds.
const int MIN_DELAY = 200;
const int MAX_DELAY = 2000;

void setup() {
  // Configure the LED pin as a digital output.
  pinMode(LED_PIN, OUTPUT);

  // Start the random number generator.
  randomSeed(analogRead(A0));
}

void loop() {

  // Generate a random ON duration.
  int onTime = random(MIN_DELAY, MAX_DELAY);

  // Turn the LED ON.
  digitalWrite(LED_PIN, HIGH);

  // Keep it ON for the randomly selected time.
  delay(onTime);

  // Generate a random OFF duration.
  int offTime = random(MIN_DELAY, MAX_DELAY);

  // Turn the LED OFF.
  digitalWrite(LED_PIN, LOW);

  // Keep it OFF for the randomly selected time.
  delay(offTime);
}
