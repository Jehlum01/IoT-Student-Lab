/*
  IoT Student Lab
  Project 18: Buzzer Alarm
  Platform: Arduino Uno
  Concept: Digital Input + Audible Output + Alarm Logic
*/

const int BUTTON_PIN = 2;
const int LED_PIN = 8;
const int BUZZER_PIN = 9;

bool alarmActive = false;
bool lastButtonState = HIGH;

const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 18: Buzzer Alarm");
  Serial.println("================================");
  Serial.println("Press the button to activate/deactivate alarm.");
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Detect a new button press.
  if (lastButtonState == HIGH && currentButtonState == LOW) {

    delay(DEBOUNCE_DELAY);

    alarmActive = !alarmActive;

    if (alarmActive) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);

      Serial.println("ALARM: ON");
    } else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

      Serial.println("ALARM: OFF");
    }
  }

  lastButtonState = currentButtonState;
}
