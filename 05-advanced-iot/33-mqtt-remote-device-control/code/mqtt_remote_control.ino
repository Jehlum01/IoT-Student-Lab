/*
  IoT Student Lab
  Project 33: MQTT Remote Device Control

  Platform: ESP32
  Actuator: LED

  Concepts:
    - MQTT Publish
    - MQTT Subscribe
    - MQTT Commands
    - MQTT State Reporting
    - Callback Functions
    - Two-Way IoT Communication
*/

#include <WiFi.h>
#include <PubSubClient.h>

// ============================================================
// Wi-Fi Configuration
// ============================================================

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// ============================================================
// MQTT Configuration
// ============================================================

const char* MQTT_BROKER = "YOUR_MQTT_BROKER";
const int MQTT_PORT = 1883;

const char* MQTT_CLIENT_ID = "iot-student-esp32-33";

const char* MQTT_COMMAND_TOPIC =
  "iot-student-lab/project33/device/command";

const char* MQTT_STATE_TOPIC =
  "iot-student-lab/project33/device/state";

// ============================================================
// Hardware
// ============================================================

const int LED_PIN = 5;

// ============================================================
// MQTT Client
// ============================================================

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// ============================================================
// Device State
// ============================================================

bool ledState = false;

// Forward declaration
void publishDeviceState();

// ============================================================
// MQTT Callback
// ============================================================

void mqttCallback(char* topic, byte* payload, unsigned int length) {

  String command = "";

  for (unsigned int i = 0; i < length; i++) {
    command += (char)payload[i];
  }

  command.trim();
  command.toUpperCase();

  Serial.println();
  Serial.println("========== MQTT MESSAGE ==========");

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  Serial.println(command);

  Serial.println("===================================");

  // Accept commands only from the expected topic.
  if (String(topic) != MQTT_COMMAND_TOPIC) {
    Serial.println("Ignored: unexpected topic.");
    return;
  }

  // ON command
  if (command == "ON") {

    ledState = true;
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Command accepted: LED ON");
  }

  // OFF command
  else if (command == "OFF") {

    ledState = false;
    digitalWrite(LED_PIN, LOW);

    Serial.println("Command accepted: LED OFF");
  }

  // Unknown command
  else {

    Serial.println("Unknown command.");
    Serial.println("Use only: ON or OFF");

    return;
  }

  // Report the resulting state.
  publishDeviceState();
}

// ============================================================
// Publish Device State
// ============================================================

void publishDeviceState() {

  const char* state;

  if (ledState) {
    state = "ON";
  } else {
    state = "OFF";
  }

  bool success = mqttClient.publish(
    MQTT_STATE_TOPIC,
    state,
    true
  );

  Serial.print("State publish: ");

  if (success) {

    Serial.println("OK");

    Serial.print("Topic: ");
    Serial.println(MQTT_STATE_TOPIC);

    Serial.print("State: ");
    Serial.println(state);

  } else {

    Serial.println("FAILED");
  }
}

// ============================================================
// Connect to Wi-Fi
// ============================================================

void connectToWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  WiFi.mode(WIFI_STA);

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

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

// ============================================================
// Connect to MQTT Broker
// ============================================================

void connectToMQTT() {

  while (!mqttClient.connected()) {

    Serial.print("Connecting to MQTT broker...");

    if (mqttClient.connect(MQTT_CLIENT_ID)) {

      Serial.println("connected.");

      bool subscribed =
        mqttClient.subscribe(MQTT_COMMAND_TOPIC);

      if (subscribed) {

        Serial.println(
          "Subscribed to command topic."
        );

      } else {

        Serial.println(
          "ERROR: MQTT subscription failed."
        );
      }

      // Publish the current state after connecting.
      publishDeviceState();

    } else {

      Serial.print("failed, state=");
      Serial.println(mqttClient.state());

      Serial.println("Retrying in 3 seconds...");

      delay(3000);
    }
  }
}

// ============================================================
// Setup
// ============================================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("          IoT Student Lab");
  Serial.println(" Project 33: MQTT Remote Device Control");
  Serial.println("========================================");

  // Safe startup: LED OFF.
  pinMode(LED_PIN, OUTPUT);

  ledState = false;
  digitalWrite(LED_PIN, LOW);

  // Connect to Wi-Fi.
  connectToWiFi();

  // Configure MQTT.
  mqttClient.setServer(
    MQTT_BROKER,
    MQTT_PORT
  );

  mqttClient.setCallback(
    mqttCallback
  );

  // Connect to MQTT broker.
  connectToMQTT();

  Serial.println();
  Serial.println("System ready.");
}

// ============================================================
// Main Loop
// ============================================================

void loop() {

  // Maintain Wi-Fi.
  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("Wi-Fi connection lost.");
    connectToWiFi();
  }

  // Maintain MQTT.
  if (!mqttClient.connected()) {

    Serial.println("MQTT connection lost.");
    connectToMQTT();
  }

  // Process MQTT traffic and callbacks.
  mqttClient.loop();
}
