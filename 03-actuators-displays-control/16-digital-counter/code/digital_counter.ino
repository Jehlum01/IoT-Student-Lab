/*
  IoT Student Lab
  Project 16: Digital Counter
  Platform: Arduino Uno
  Concept: State Variables + Button Events + Binary Output
*/

const int UP_BUTTON_PIN = 2;
const int DOWN_BUTTON_PIN = 3;

const int LED_COUNT = 4;
const int LED_PINS[LED_COUNT] = {8, 9, 10, 11};

const int MIN_COUNT = 0;
const int MAX_COUNT = 15;

const unsigned long DEBOUNCE_DELAY = 50;

int counter = 0;

bool lastUpButtonState = HIGH;
bool lastDownButtonState = HIGH;

void setup() {
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  displayCount(counter);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 16: Digital Counter");
  Serial.println("================================");
  Serial.println("UP button   → increase");
  Serial.println("DOWN button → decrease");
}

void loop() {
  bool currentUpButtonState = digitalRead(UP_BUTTON_PIN);
  bool currentDownButtonState = digitalRead(DOWN_BUTTON_PIN);

  // Detect UP button press.
  if (lastUpButtonState == HIGH && currentUpButtonState == LOW) {
    counter++;

    if (counter > MAX_COUNT) {
      counter = MAX_COUNT;
    }

    displayCount(counter);

    Serial.print("Counter: ");
    Serial.println(counter);

    delay(DEBOUNCE_DELAY);
  }

  // Detect DOWN button press.
  if (lastDownButtonState == HIGH && currentDownButtonState == LOW) {
    counter--;

    if (counter < MIN_COUNT) {
      counter = MIN_COUNT;
    }

    displayCount(counter);

    Serial.print("Counter: ");
    Serial.println(counter);

    delay(DEBOUNCE_DELAY);
  }

  lastUpButtonState = currentUpButtonState;
  lastDownButtonState = currentDownButtonState;
}

void displayCount(int value) {
  for (int i = 0; i < LED_COUNT; i++) {
    int bitValue = bitRead(value, i);
    digitalWrite(LED_PINS[i], bitValue);
  }
}
