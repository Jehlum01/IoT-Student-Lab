/*
  IoT Student Lab
  Project 15: Mini Electronic Dice
  Platform: Arduino Uno
  Concept: Digital Input + Randomness + Multiple Outputs
*/

const int BUTTON_PIN = 2;

const int LED_COUNT = 7;

const int LED_PINS[LED_COUNT] = {
  3, 4, 5, 6, 7, 8, 9
};

const int DEBOUNCE_DELAY = 50;

bool lastButtonState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  allLedsOff();

  randomSeed(analogRead(A0));

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 15: Mini Electronic Dice");
  Serial.println("================================");
  Serial.println("Press the button to roll.");
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Detect a button press.
  if (lastButtonState == HIGH && currentButtonState == LOW) {

    delay(DEBOUNCE_DELAY);

    int diceValue = random(1, 7);

    displayDice(diceValue);

    Serial.print("Dice roll: ");
    Serial.println(diceValue);
  }

  lastButtonState = currentButtonState;
}

void displayDice(int value) {
  allLedsOff();

  /*
    Seven LEDs represent the standard dice positions:

        0   1

        2

        3

        4

        5   6
  */

  switch (value) {

    case 1:
      digitalWrite(LED_PINS[3], HIGH);
      break;

    case 2:
      digitalWrite(LED_PINS[0], HIGH);
      digitalWrite(LED_PINS[6], HIGH);
      break;

    case 3:
      digitalWrite(LED_PINS[0], HIGH);
      digitalWrite(LED_PINS[3], HIGH);
      digitalWrite(LED_PINS[6], HIGH);
      break;

    case 4:
      digitalWrite(LED_PINS[0], HIGH);
      digitalWrite(LED_PINS[1], HIGH);
      digitalWrite(LED_PINS[5], HIGH);
      digitalWrite(LED_PINS[6], HIGH);
      break;

    case 5:
      digitalWrite(LED_PINS[0], HIGH);
      digitalWrite(LED_PINS[1], HIGH);
      digitalWrite(LED_PINS[3], HIGH);
      digitalWrite(LED_PINS[5], HIGH);
      digitalWrite(LED_PINS[6], HIGH);
      break;

    case 6:
      digitalWrite(LED_PINS[0], HIGH);
      digitalWrite(LED_PINS[1], HIGH);
      digitalWrite(LED_PINS[2], HIGH);
      digitalWrite(LED_PINS[4], HIGH);
      digitalWrite(LED_PINS[5], HIGH);
      digitalWrite(LED_PINS[6], HIGH);
      break;
  }
}

void allLedsOff() {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}
