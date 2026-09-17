/*
  IoT Student Lab
  Project 29: Wi-Fi Motion Alarm

  Platform: ESP32
  Sensor: PIR Motion Sensor
  Actuators: LED + Buzzer

  Concept:
  Digital Sensor + State Machine + Wi-Fi + Web Monitoring

  Learning Flow:
  PIR → ESP32 → Decision → Alarm → Wi-Fi → Browser
*/

#include <WiFi.h>
#include <WebServer.h>

// --------------------------------------------------
// Wi-Fi Configuration
// --------------------------------------------------

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// --------------------------------------------------
// Hardware
// --------------------------------------------------

const int PIR_PIN = 4;
const int LED_PIN = 5;
const int BUZZER_PIN = 18;

// --------------------------------------------------
// Alarm Configuration
// --------------------------------------------------

const unsigned long ALARM_DURATION = 5000;

// --------------------------------------------------
// Web Server
// --------------------------------------------------

WebServer server(80);

// --------------------------------------------------
// System State
// --------------------------------------------------

bool motionDetected = false;
bool alarmActive = false;

unsigned long alarmStartTime = 0;
unsigned long lastMotionTime = 0;

// --------------------------------------------------
// Read PIR Sensor
// --------------------------------------------------

void updateMotionState() {

  motionDetected = digitalRead(PIR_PIN) == HIGH;

  if (motionDetected) {

    lastMotionTime = millis();

    if (!alarmActive) {

      alarmActive = true;
      alarmStartTime = millis();

      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);

      Serial.println("ALERT: Motion detected!");
      Serial.println("Alarm: ON");
    }
  }

  // Turn alarm off after the configured duration.
  if (
    alarmActive &&
    millis() - alarmStartTime >= ALARM_DURATION
  ) {

    alarmActive = false;

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("Alarm: OFF");
  }
}

// --------------------------------------------------
// Build Web Dashboard
// --------------------------------------------------

String buildWebPage() {

  String page = R"rawliteral(
<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<meta http-equiv="refresh"
      content="2">

<title>ESP32 Wi-Fi Motion Alarm</title>

<style>

body {
  font-family: Arial, sans-serif;
  background: #f4f4f4;
  text-align: center;
  margin: 0;
  padding: 30px 15px;
}

.container {
  max-width: 700px;
  margin: auto;
  background: white;
  padding: 30px;
  border-radius: 14px;
}

h1 {
  margin-bottom: 5px;
}

.card {
  background: #eeeeee;
  padding: 25px;
  margin: 20px 0;
  border-radius: 12px;
}

.status {
  font-size: 30px;
  font-weight: bold;
  margin: 15px;
}

.motion {
  font-size: 24px;
  font-weight: bold;
}

.info {
  text-align: left;
  line-height: 1.9;
}

.warning {
  font-size: 14px;
  margin-top: 25px;
}

</style>

</head>

<body>

<div class="container">

<h1>IoT Student Lab</h1>

<p>
Project 29 — Wi-Fi Motion Alarm
</p>
)rawliteral";

  // ------------------------------------------------
  // Alarm Status
  // ------------------------------------------------

  page += R"rawliteral(

<div class="card">

<h2>Alarm Status</h2>

<div class="status">
)rawliteral";

  if (alarmActive) {

    page += "ALARM ACTIVE";

  } else {

    page += "SYSTEM ARMED";
  }

  page += R"rawliteral(
</div>

)rawliteral";

  if (alarmActive) {

    page += R"rawliteral(
<div class="motion">
Motion Detected
</div>
)rawliteral";

  } else {

    page += R"rawliteral(
<div class="motion">
No Active Alarm
</div>
)rawliteral";
  }

  page += R"rawliteral(

</div>

<div class="card info">

<h2>System Information</h2>

<strong>Motion Sensor:</strong> )rawliteral";

  page += motionDetected ? "DETECTED" : "CLEAR";

  page += R"rawliteral(<br>

<strong>Alarm:</strong> )rawliteral";

  page += alarmActive ? "ACTIVE" : "OFF";

  page += R"rawliteral(<br>

<strong>PIR GPIO:</strong> 4<br>

<strong>LED GPIO:</strong> 5<br>

<strong>Buzzer GPIO:</strong> 18<br>

<strong>SSID:</strong> )rawliteral";

  page += WiFi.SSID();

  page += R"rawliteral(<br>

<strong>IP Address:</strong> )rawliteral";

  page += WiFi.localIP().toString();

  page += R"rawliteral(<br>

<strong>RSSI:</strong> )rawliteral";

  page += String(WiFi.RSSI());

  page += R"rawliteral( dBm

</div>

<p class="warning">
Dashboard automatically refreshes every 2 seconds.
</p>

</div>

</body>

</html>
)rawliteral";

  return page;
}

// --------------------------------------------------
// Root Web Page
// --------------------------------------------------

void handleRoot() {

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Alarm Status Endpoint
// --------------------------------------------------

void handleStatus() {

  String status = "{";

  status += "\"motion\":";
  status += motionDetected ? "true" : "false";

  status += ",\"alarm\":";
  status += alarmActive ? "true" : "false";

  status += "}";

  server.send(
    200,
    "application/json",
    status
  );
}

// --------------------------------------------------
// 404 Handler
// --------------------------------------------------

void handleNotFound() {

  String message = "404 - Page Not Found\n\n";

  message += "Requested URI: ";
  message += server.uri();

  server.send(
    404,
    "text/plain",
    message
  );
}

// --------------------------------------------------
// Connect to Wi-Fi
// --------------------------------------------------

void connectToWiFi() {

  WiFi.mode(WIFI_STA);

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.print("Connecting to Wi-Fi");

  while (
    WiFi.status() != WL_CONNECTED
  ) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("Wi-Fi connected!");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println();

  Serial.println("================================");
  Serial.println("      IoT Student Lab");
  Serial.println(" Project 29: Wi-Fi Motion Alarm");
  Serial.println("================================");

  connectToWiFi();

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/status",
    handleStatus
  );

  server.onNotFound(
    handleNotFound
  );

  server.begin();

  Serial.println("Motion alarm web server started.");

  Serial.print("Open: http://");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println("System armed.");
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------

void loop() {

  updateMotionState();

  server.handleClient();

  delay(20);
}
