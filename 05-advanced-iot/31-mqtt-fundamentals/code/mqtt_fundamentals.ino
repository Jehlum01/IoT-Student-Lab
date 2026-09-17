/*
  IoT Student Lab
  Project 31: MQTT Fundamentals

  Platform: ESP32
  Concept: MQTT Publish / Subscribe

  Flow:
    ESP32
      ↓
    Wi-Fi
      ↓
    MQTT Broker
      ↓
    MQTT Subscriber
*/

#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi Configuration
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// MQTT Configuration
const char* MQTT_BROKER = "YOUR_MQTT_BROKER";
const int MQTT_PORT = 1883;

const char* MQTT_CLIENT_ID = "iot-student-esp32-31";
const char* MQTT_TOPIC = "iot-student-lab/project31/message";

// Network / MQTT objects
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Timing
const unsigned long PUBLISH_INTERVAL = 5000;
unsigned long lastPublishTime = 0;
unsigned long messageNumber = 0;

void connectToWiFi() {
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

      Serial.print("Topic: ");
      Serial.println(MQTT_TOPIC);
    } else {
      Serial.print("failed, state=");
      Serial.println(mqttClient.state());

      Serial.println("Retrying in 3 seconds...");
      delay(3000);
    }
  }
}

void publishMessage() {
  messageNumber++;

  String message = "Hello from ESP32 | Message #";
  message += messageNumber;

  bool success = mqttClient.publish(
    MQTT_TOPIC,
    message.c_str()
  );

  if (success) {
    Serial.print("Published → ");
    Serial.print(MQTT_TOPIC);
    Serial.print(" : ");
    Serial.println(message);
  } else {
    Serial.println("MQTT publish failed.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("       IoT Student Lab");
  Serial.println("       Project 31: MQTT Fundamentals");
  Serial.println("========================================");

  connectToWiFi();

  mqttClient.setServer(
    MQTT_BROKER,
    MQTT_PORT
  );

  connectToMQTT();
}

void loop() {
  // Maintain MQTT connection.
  if (!mqttClient.connected()) {
    connectToMQTT();
  }

  // Process MQTT communication.
  mqttClient.loop();

  // Publish a message every PUBLISH_INTERVAL.
  unsigned long currentTime = millis();

  if (currentTime - lastPublishTime >= PUBLISH_INTERVAL) {
    lastPublishTime = currentTime;
    publishMessage();
  }
}
