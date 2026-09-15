/*
  IoT Student Lab
  Project 17: Reaction Timer
  Platform: Arduino Uno
  Concept: millis() + Random Delay + Event Timing
*/

const int BUTTON_PIN = 2;
const int LED_PIN = 8;
const int BUZZER_PIN = 9;

const unsigned long MIN_WAIT_TIME = 2000;
const unsigned long MAX_WAIT_TIME = 5000;

bool waitingForReaction = false;
bool measuringReaction = false;

unsigned long signalTime = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  randomSeed(analogRead(A0));

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 17: Reaction Timer");
  Serial.println("================================");
  Serial.println("Press the button to start.");
}

void loop() {

  bool buttonState = digitalRead(BUTTON_PIN);

  // Start a new reaction test.
  if (!waitingForReaction && !measuringReaction &&
      buttonState == LOW) {

    delay(50);

    Serial.println();
    Serial.println("Get ready...");

    unsigned long waitTime =
      random(MIN_WAIT_TIME, MAX_WAIT_TIME + 1);

    delay(waitTime);

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    delay(100);

    digitalWrite(BUZZER_PIN, LOW);

    signalTime = millis();

    waitingForReaction = false;
    measuringReaction = true;

    Serial.println("GO!");
  }

  // Measure reaction after the signal.
  if (measuringReaction && buttonState == LOW) {

    unsigned long reactionTime =
      millis() - signalTime;

    digitalWrite(LED_PIN, LOW);

    Serial.print("Reaction time: ");
    Serial.print(reactionTime);
    Serial.println(" ms");

    measuringReaction = false;

    Serial.println("Press the button to try again.");

    delay(300);
  }
}
