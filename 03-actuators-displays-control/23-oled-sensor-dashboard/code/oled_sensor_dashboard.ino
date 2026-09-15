/*
  IoT Student Lab
  Project 23: OLED Sensor Dashboard
  Platform: Arduino Uno

  Sensors:
  - LDR
  - LM35

  Display:
  - 0.96" SSD1306 OLED, I2C

  Concept:
  Sensor Data + I2C + OLED Visualization
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

const int OLED_RESET = -1;
const int OLED_ADDRESS = 0x3C;

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

const int LDR_PIN = A0;
const int TEMP_SENSOR_PIN = A1;

const float ADC_REFERENCE = 5.0;
const int ADC_RESOLUTION = 1023;

const unsigned long UPDATE_INTERVAL = 500;

unsigned long lastUpdateTime = 0;

float readTemperatureC() {
  int sensorValue = analogRead(TEMP_SENSOR_PIN);

  float voltage =
    sensorValue * ADC_REFERENCE / ADC_RESOLUTION;

  // LM35 produces approximately 10 mV per °C.
  return voltage * 100.0;
}

void showDashboard(int lightLevel, float temperatureC) {
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  // Header
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("IoT SENSOR DASHBOARD");

  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  // Temperature
  display.setTextSize(1);
  display.setCursor(0, 18);
  display.print("Temperature");

  display.setTextSize(2);
  display.setCursor(0, 29);
  display.print(temperatureC, 1);
  display.print(" C");

  // Light
  display.setTextSize(1);
  display.setCursor(0, 51);
  display.print("Light: ");

  display.setTextSize(1);
  display.print(lightLevel);

  display.display();
}

void setup() {
  Serial.begin(9600);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {

    Serial.println("OLED initialization failed.");

    while (true) {
      // Stop here if the OLED cannot initialize.
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("IoT Student Lab");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println("Dashboard");

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.println("Starting...");

  display.display();

  delay(1500);
}

void loop() {
  if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
    lastUpdateTime = millis();

    int lightLevel = analogRead(LDR_PIN);
    float temperatureC = readTemperatureC();

    showDashboard(lightLevel, temperatureC);

    Serial.print("Temperature: ");
    Serial.print(temperatureC, 1);
    Serial.print(" C | Light: ");
    Serial.println(lightLevel);
  }
}
