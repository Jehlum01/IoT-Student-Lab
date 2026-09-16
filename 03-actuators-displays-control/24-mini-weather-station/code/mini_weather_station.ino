/*
  IoT Student Lab
  Project 24: Mini Weather Station
  Platform: Arduino Uno

  Sensor:
  - DHT11 Temperature + Humidity

  Display:
  - SSD1306 OLED I2C

  Concept:
  Multiple Sensor Values + I2C + Data Visualization
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;
const int OLED_ADDRESS = 0x3C;

const int DHT_PIN = 2;
const int DHT_TYPE = DHT11;

const unsigned long UPDATE_INTERVAL = 2000;

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

DHT dht(DHT_PIN, DHT_TYPE);

unsigned long lastUpdateTime = 0;

void showStartupScreen() {
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("IoT Student Lab");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println("Weather");

  display.setCursor(0, 42);
  display.println("Station");

  display.display();

  delay(1500);
}

void showWeatherData(float temperature, float humidity) {
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("MINI WEATHER STATION");

  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  display.setCursor(0, 18);
  display.print("Temperature:");

  display.setTextSize(2);
  display.setCursor(0, 29);
  display.print(temperature, 1);
  display.print(" C");

  display.setTextSize(1);
  display.setCursor(0, 51);
  display.print("Humidity: ");

  display.print(humidity, 1);
  display.print(" %");

  display.display();
}

void setup() {
  Serial.begin(9600);

  dht.begin();

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {

    Serial.println("OLED initialization failed.");

    while (true) {
      // Stop if OLED initialization fails.
    }
  }

  showStartupScreen();

  Serial.println("================================");
  Serial.println("   IoT Student Lab");
  Serial.println("   Project 24: Mini Weather Station");
  Serial.println("================================");
  Serial.println("Starting sensor measurements...");
}

void loop() {
  if (millis() - lastUpdateTime < UPDATE_INTERVAL) {
    return;
  }

  lastUpdateTime = millis();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT11 reading failed.");

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("WEATHER STATION");

    display.setCursor(0, 25);
    display.println("Sensor read error!");

    display.setCursor(0, 45);
    display.println("Check DHT wiring.");

    display.display();

    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  showWeatherData(temperature, humidity);
}
