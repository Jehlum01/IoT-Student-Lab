/*
  IoT Student Lab
  Project 20: Parking Sensor
  Platform: Arduino Uno
  Sensor: HC-SR04 Ultrasonic Sensor
  Actuators: Buzzer + LEDs
  Concept: Distance Measurement + Thresholds + millis() Timing
*/

const int TRIG_PIN = 8;
const int ECHO_PIN = 9;

const int BUZZER_PIN = 10;

const int GREEN_LED = 11;
const int YELLOW_LED = 12;
const int RED_LED = 13;

// Distance thresholds in centimetres
const float SAFE_DISTANCE = 50.0;
const float STOP_DISTANCE = 20.0;

// HC-SR04 timeout
const unsigned long ECHO_TIMEOUT = 30000UL;

// Buzzer timing
const unsigned long CAUTION_INTERVAL = 700;
const unsigned long STOP_INTERVAL = 180;

enum Zone {
  SAFE,
  CAUTION,
  STOP
};

Zone currentZone = SAFE;
Zone previousZone = SAFE;

unsigned long lastBeepTime = 0;
bool buzzerState = false;

float measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT);

  if (duration == 0) {
    return -1.0;
  }

  return duration * 0.0343 / 2.0;
}

Zone determineZone(float distance) {
  if (distance < 0) {
    return SAFE;
  }

  if (distance <= STOP_DISTANCE) {
    return STOP;
  }

  if (distance <= SAFE_DISTANCE) {
    return CAUTION;
  }

  return SAFE;
}

void setIndicators(Zone zone) {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (zone == SAFE) {
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (zone == CAUTION) {
    digitalWrite(YELLOW_LED, HIGH);
  }
  else if (zone == STOP) {
    digitalWrite(RED_LED, HIGH);
  }
}

void updateBuzzer(Zone zone) {
  unsigned long interval = 0;

  if (zone == CAUTION) {
    interval = CAUTION_INTERVAL;
  }
  else if (zone == STOP) {
    interval = STOP_INTERVAL;
  }

  // Safe zone: buzzer remains OFF
  if (interval == 0) {
    buzzerState = false;
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  if (millis() - lastBeepTime >= interval) {
    lastBeepTime = millis();

    buzzerState = !buzzerState;
    digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);
  }
}

void printZone(Zone zone) {
  if (zone == SAFE) {
    Serial.println("Status: SAFE");
  }
  else if (zone == CAUTION) {
    Serial.println("Status: CAUTION - Slow down");
  }
  else if (zone == STOP) {
    Serial.println("Status: STOP - Very close");
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  setIndicators(SAFE);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 20: Parking Sensor");
  Serial.println("================================");
  Serial.println("SAFE    : > 50 cm");
  Serial.println("CAUTION : 20 - 50 cm");
  Serial.println("STOP    : <= 20 cm");
  Serial.println();
}

void loop() {
  float distance = measureDistanceCm();

  currentZone = determineZone(distance);

  // Update LEDs when the zone changes
  if (currentZone != previousZone) {
    setIndicators(currentZone);

    buzzerState = false;
    digitalWrite(BUZZER_PIN, LOW);
    lastBeepTime = millis();

    printZone(currentZone);

    previousZone = currentZone;
  }

  // Display distance
  Serial.print("Distance: ");

  if (distance < 0) {
    Serial.println("No echo detected");
  }
  else {
    Serial.print(distance, 1);
    Serial.println(" cm");
  }

  updateBuzzer(currentZone);

  delay(100);
}
