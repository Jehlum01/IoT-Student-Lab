/*
  IoT Student Lab
  Project 10: Smart Street Light

  Platform: Arduino Uno
  Concept: LDR + Thresholds + Multiple Outputs + Automation

  Learning:
  - Reading an analog sensor
  - Using thresholds
  - Controlling multiple outputs
  - Automatic decision making
*/

const int LDR_PIN = A0;

const int STREET_LIGHT_1 = 8;
const int STREET_LIGHT_2 = 9;
const int STREET_LIGHT_3 = 10;

// Adjust after observing the LDR readings.
const int DARK_THRESHOLD = 500;

void setup() {

  pinMode(STREET_LIGHT_1, OUTPUT);
  pinMode(STREET_LIGHT_2, OUTPUT);
  pinMode(STREET_LIGHT_3, OUTPUT);

  Serial.begin(9600);

  allLightsOff();
}

void loop() {

  int lightLevel = analogRead(LDR_PIN);

  Serial.print("Light level: ");
  Serial.println(lightLevel);

  /*
    Dark environment:
    Turn ON all street lights.
  */

  if (lightLevel < DARK_THRESHOLD) {

    digitalWrite(STREET_LIGHT_1, HIGH);
    digitalWrite(STREET_LIGHT_2, HIGH);
    digitalWrite(STREET_LIGHT_3, HIGH);

    Serial.println("DARK - Street lights ON");
  }

  /*
    Bright environment:
    Turn OFF all street lights.
  */

  else {

    allLightsOff();

    Serial.println("BRIGHT - Street lights OFF");
  }

  delay(500);
}

void allLightsOff() {

  digitalWrite(STREET_LIGHT_1, LOW);
  digitalWrite(STREET_LIGHT_2, LOW);
  digitalWrite(STREET_LIGHT_3, LOW);
}
