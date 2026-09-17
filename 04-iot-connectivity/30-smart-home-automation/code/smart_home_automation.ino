/*
  IoT Student Lab
  Project 30: Smart Home Automation

  Platform: ESP32

  Concept:
  Wi-Fi + Web Server + Multiple GPIO Outputs
  + State Management + Home Automation

  Learning Flow:

  Browser
      ↓
    Wi-Fi
      ↓
    ESP32
      ↓
  ┌───┼───┐
  ↓   ↓   ↓
Light Fan  Appliance
*/

#include <WiFi.h>
#include <WebServer.h>

// --------------------------------------------------
// Wi-Fi Configuration
// --------------------------------------------------

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// --------------------------------------------------
// GPIO Configuration
// --------------------------------------------------

const int LIGHT_RELAY_PIN = 5;
const int FAN_RELAY_PIN = 18;
const int AUX_RELAY_PIN = 19;

// Most relay modules are active LOW.
// LOW  = Relay ON
// HIGH = Relay OFF

const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

// --------------------------------------------------
// Web Server
// --------------------------------------------------

WebServer server(80);

// --------------------------------------------------
// Device States
// --------------------------------------------------

bool lightState = false;
bool fanState = false;
bool auxState = false;

// --------------------------------------------------
// Apply Relay States
// --------------------------------------------------

void applyRelayStates() {

  digitalWrite(
    LIGHT_RELAY_PIN,
    lightState ? RELAY_ON : RELAY_OFF
  );

  digitalWrite(
    FAN_RELAY_PIN,
    fanState ? RELAY_ON : RELAY_OFF
  );

  digitalWrite(
    AUX_RELAY_PIN,
    auxState ? RELAY_ON : RELAY_OFF
  );
}

// --------------------------------------------------
// Web Page
// --------------------------------------------------

String buildWebPage() {

  String page = R"rawliteral(
<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<meta http-equiv="refresh"
      content="3">

<title>ESP32 Smart Home</title>

<style>

body {
  font-family: Arial, sans-serif;
  background: #f4f4f4;
  text-align: center;
  margin: 0;
  padding: 30px 15px;
}

.container {
  max-width: 800px;
  margin: auto;
  background: white;
  padding: 30px;
  border-radius: 14px;
}

h1 {
  margin-bottom: 5px;
}

.dashboard {
  display: flex;
  justify-content: center;
  flex-wrap: wrap;
  gap: 15px;
  margin-top: 25px;
}

.card {
  width: 210px;
  padding: 22px;
  background: #eeeeee;
  border-radius: 12px;
}

.status {
  font-size: 25px;
  font-weight: bold;
  margin: 15px 0;
}

.button {
  display: inline-block;
  padding: 12px 20px;
  margin: 5px;
  color: white;
  text-decoration: none;
  border-radius: 7px;
  font-size: 16px;
}

.on {
  background: green;
}

.off {
  background: red;
}

.info {
  text-align: left;
  line-height: 1.9;
  margin-top: 25px;
}

.note {
  margin-top: 25px;
  font-size: 14px;
}

</style>

</head>

<body>

<div class="container">

<h1>IoT Student Lab</h1>

<p>
Project 30 — Smart Home Automation
</p>

<div class="dashboard">

<!-- LIGHT -->

<div class="card">

<h2>Light</h2>

<div class="status">
)rawliteral";

  page += lightState ? "ON" : "OFF";

  page += R"rawliteral(
</div>

<a class="button on"
   href="/light/on">
ON
</a>

<a class="button off"
   href="/light/off">
OFF
</a>

</div>

<!-- FAN -->

<div class="card">

<h2>Fan</h2>

<div class="status">
)rawliteral";

  page += fanState ? "ON" : "OFF";

  page += R"rawliteral(
</div>

<a class="button on"
   href="/fan/on">
ON
</a>

<a class="button off"
   href="/fan/off">
OFF
</a>

</div>

<!-- AUX -->

<div class="card">

<h2>Auxiliary</h2>

<div class="status">
)rawliteral";

  page += auxState ? "ON" : "OFF";

  page += R"rawliteral(
</div>

<a class="button on"
   href="/aux/on">
ON
</a>

<a class="button off"
   href="/aux/off">
OFF
</a>

</div>

</div>

<div class="card info">

<h2>Network Information</h2>

<strong>SSID:</strong>
)rawliteral";

  page += WiFi.SSID();

  page += R"rawliteral(
<br>

<strong>IP Address:</strong>
)rawliteral";

  page += WiFi.localIP().toString();

  page += R"rawliteral(
<br>

<strong>RSSI:</strong>
)rawliteral";

  page += String(WiFi.RSSI());

  page += R"rawliteral(
 dBm
<br>

<strong>Light GPIO:</strong> 5
<br>

<strong>Fan GPIO:</strong> 18
<br>

<strong>Auxiliary GPIO:</strong> 19

</div>

<p class="note">
Local network smart-home demonstration.
</p>

</div>

</body>

</html>
)rawliteral";

  return page;
}

// --------------------------------------------------
// Root Handler
// --------------------------------------------------

void handleRoot() {

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Light Control
// --------------------------------------------------

void handleLightOn() {

  lightState = true;

  digitalWrite(
    LIGHT_RELAY_PIN,
    RELAY_ON
  );

  Serial.println("Light → ON");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

void handleLightOff() {

  lightState = false;

  digitalWrite(
    LIGHT_RELAY_PIN,
    RELAY_OFF
  );

  Serial.println("Light → OFF");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Fan Control
// --------------------------------------------------

void handleFanOn() {

  fanState = true;

  digitalWrite(
    FAN_RELAY_PIN,
    RELAY_ON
  );

  Serial.println("Fan → ON");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

void handleFanOff() {

  fanState = false;

  digitalWrite(
    FAN_RELAY_PIN,
    RELAY_OFF
  );

  Serial.println("Fan → OFF");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Auxiliary Device Control
// --------------------------------------------------

void handleAuxOn() {

  auxState = true;

  digitalWrite(
    AUX_RELAY_PIN,
    RELAY_ON
  );

  Serial.println("Auxiliary → ON");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

void handleAuxOff() {

  auxState = false;

  digitalWrite(
    AUX_RELAY_PIN,
    RELAY_OFF
  );

  Serial.println("Auxiliary → OFF");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// All Devices OFF
// --------------------------------------------------

void handleAllOff() {

  lightState = false;
  fanState = false;
  auxState = false;

  applyRelayStates();

  Serial.println("All devices → OFF");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Status API
// --------------------------------------------------

void handleStatus() {

  String status = "{";

  status += "\"light\":";
  status += lightState ? "true" : "false";

  status += ",\"fan\":";
  status += fanState ? "true" : "false";

  status += ",\"auxiliary\":";
  status += auxState ? "true" : "false";

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
// Wi-Fi Connection
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

  pinMode(
    LIGHT_RELAY_PIN,
    OUTPUT
  );

  pinMode(
    FAN_RELAY_PIN,
    OUTPUT
  );

  pinMode(
    AUX_RELAY_PIN,
    OUTPUT
  );

  // Safe startup state
  lightState = false;
  fanState = false;
  auxState = false;

  applyRelayStates();

  Serial.println();

  Serial.println("================================");
  Serial.println("      IoT Student Lab");
  Serial.println(" Project 30: Smart Home");
  Serial.println("          Automation");
  Serial.println("================================");

  connectToWiFi();

  // Main page
  server.on(
    "/",
    handleRoot
  );

  // Light
  server.on(
    "/light/on",
    handleLightOn
  );

  server.on(
    "/light/off",
    handleLightOff
  );

  // Fan
  server.on(
    "/fan/on",
    handleFanOn
  );

  server.on(
    "/fan/off",
    handleFanOff
  );

  // Auxiliary
  server.on(
    "/aux/on",
    handleAuxOn
  );

  server.on(
    "/aux/off",
    handleAuxOff
  );

  // Emergency / master OFF
  server.on(
    "/all/off",
    handleAllOff
  );

  // Machine-readable status
  server.on(
    "/status",
    handleStatus
  );

  server.onNotFound(
    handleNotFound
  );

  server.begin();

  Serial.println(
    "Smart Home web server started."
  );

  Serial.print("Open: http://");

  Serial.println(
    WiFi.localIP()
  );

  Serial.println();
  Serial.println("All devices initialized OFF.");
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------

void loop() {

  server.handleClient();

  delay(10);
}
