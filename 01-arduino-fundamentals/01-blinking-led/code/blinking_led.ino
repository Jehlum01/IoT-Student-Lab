/*
  IoT Student Lab
  Project 01: Blinking LED

  Platform: Arduino IDE
  Concept: Digital Output

  Learning:
  - GPIO / digital pins
  - pinMode()
  - digitalWrite()
  - delay()
  - setup()
  - loop()
*/

const int LED_PIN = 8; //define the pin connection

void setup() {
  // Configure the LED pin as a digital output.
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED ON.
  digitalWrite(LED_PIN, HIGH);

  // Keep it ON for 1 second.
  delay(1000);

  // Turn the LED OFF.
  digitalWrite(LED_PIN, LOW);

  // Keep it OFF for 1 second.
  delay(1000);
}
