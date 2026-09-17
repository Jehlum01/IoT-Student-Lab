/*
  IoT Student Lab
  Project 32: ESP32 MQTT Sensor Publisher

  Platform: ESP32
  Sensor: DHT22

  Flow:
    DHT22 → ESP32 → Wi-Fi → MQTT Broker → Subscriber
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* MQTT_BROKER = "YOUR_MQTT_BROKER";
const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "iot-student-esp32-32";

const char* MQTT_TOPIC_TEMPERATURE =
  "iot-student-lab/project32/temperature";

const char* MQTT_TOPIC_HUMIDITY =
  "iot-student-lab/project32/humidity";

const char* MQTT_TOPIC_TELEMETRY =
  "iot-student-lab/project32/telemetry";

#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

WiFiClient espClient;
PubSubClient mqttClient(espClient);

const unsigned long SENSOR_INTERVAL = 2000;

unsigned long lastSensorRead = 0;
unsigned long readingNumber = 0;

void connectToWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected.");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void connectToMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");

    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Serial.println("connected.");
      Serial.print("Broker: ");
      Serial.println(MQTT_BROKER);
    } else {
      Serial.print("failed, state=");
      Serial.println(mqttClient.state());
      Serial.println("Retrying in 3 seconds...");
      delay(3000);
    }
  }
}

void publishSensorData(float temperature, float humidity) {
  readingNumber++;

  char temperaturePayload[16];
  snprintf(
    temperaturePayload,
    sizeof(temperaturePayload),
    "%.2f",
    temperature
  );

  bool temperatureSuccess = mqttClient.publish(
    MQTT_TOPIC_TEMPERATURE,
    temperaturePayload
  );

  char humidityPayload[16];
  snprintf(
    humidityPayload,
    sizeof(humidityPayload),
    "%.2f",
    humidity
  );

  bool humiditySuccess = mqttClient.publish(
    MQTT_TOPIC_HUMIDITY,
    humidityPayload
  );

  char telemetryPayload[120];
  snprintf(
    telemetryPayload,
    sizeof(telemetryPayload),
    "{\"reading\":%lu,\"temperature\":%.2f,\"humidity\":%.2f}",
    readingNumber,
    temperature,
    humidity
  );

  bool telemetrySuccess = mqttClient.publish(
    MQTT_TOPIC_TELEMETRY,
    telemetryPayload
  );

  Serial.println();
  Serial.println("========== SENSOR READING ==========");

  Serial.print("Reading #: ");
  Serial.println(readingNumber);

  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  Serial.println(" %");

  Serial.println();

  Serial.print("Temperature MQTT: ");
  Serial.println(temperatureSuccess ? "OK" : "FAILED");

  Serial.print("Humidity MQTT: ");
  Serial.println(humiditySuccess ? "OK" : "FAILED");

  Serial.print("Telemetry MQTT: ");
  Serial.println(telemetrySuccess ? "OK" : "FAILED");

  Serial.println("=====================================");
}

void readAndPublishSensor() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println();
    Serial.println("ERROR: DHT22 reading failed.");
    Serial.println("Check sensor wiring and power.");
    return;
  }

  publishSensorData(temperature, humidity);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("          IoT Student Lab");
  Serial.println(" Project 32: MQTT Sensor Publisher");
  Serial.println("========================================");

  dht.begin();
  connectToWiFi();

  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  connectToMQTT();

  Serial.println();
  Serial.println("System ready.");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi connection lost.");
    connectToWiFi();
  }

  if (!mqttClient.connected()) {
    Serial.println("MQTT connection lost.");
    connectToMQTT();
  }

  mqttClient.loop();

  unsigned long currentTime = millis();

  if (currentTime - lastSensorRead >= SENSOR_INTERVAL) {
    lastSensorRead = currentTime;
    readAndPublishSensor();
  }
}
