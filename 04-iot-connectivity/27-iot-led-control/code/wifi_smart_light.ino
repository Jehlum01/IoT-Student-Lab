/*
  IoT Student Lab
  Project 27: Wi-Fi Smart Light

  Platform: ESP32
  Actuator: Relay Module + Low-Voltage DC Light
  Concept: Wi-Fi + Web Control + Relay + IoT Actuator

  Learning Flow:
  Browser → Wi-Fi → ESP32 → Relay → Light
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

const int RELAY_PIN = 5;

// Most common relay modules are active LOW.
// LOW  = Relay ON
// HIGH = Relay OFF

const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

// --------------------------------------------------
// Web Server
// --------------------------------------------------

WebServer server(80);

bool lightState = false;

// --------------------------------------------------
// Generate Web Page
// --------------------------------------------------

String buildWebPage() {

  String status = lightState ? "ON" : "OFF";

  String page = R"rawliteral(
<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<title>ESP32 Smart Light</title>

<style>

body {
  font-family: Arial, sans-serif;
  background: #f4f4f4;
  text-align: center;
  margin: 0;
  padding: 30px 15px;
}

.container {
  max-width: 600px;
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
  padding: 20px;
  margin: 20px 0;
  border-radius: 10px;
}

.status {
  font-size: 30px;
  font-weight: bold;
}

.button {
  display: inline-block;
  padding: 15px 32px;
  margin: 8px;
  color: white;
  text-decoration: none;
  border-radius: 8px;
  font-size: 18px;
}

.on {
  background: green;
}

.off {
  background: red;
}

.info {
  text-align: left;
  line-height: 1.8;
}

.warning {
  margin-top: 20px;
  font-size: 14px;
}

</style>

</head>

<body>

<div class="container">

<h1>IoT Student Lab</h1>

<p>Project 27 — Wi-Fi Smart Light</p>

<div class="card">

<h2>Light Control</h2>

<p class="status">
Light: )rawliteral";

  page += status;

  page += R"rawliteral(
</p>

<a class="button on" href="/on">
Turn ON
</a>

<a class="button off" href="/off">
Turn OFF
</a>

</div>

<div class="card">

<h2>ESP32 Network</h2>

<div class="info">

<strong>SSID:</strong> )rawliteral";

  page += WiFi.SSID();

  page += R"rawliteral(<br>

<strong>IP Address:</strong> )rawliteral";

  page += WiFi.localIP().toString();

  page += R"rawliteral(<br>

<strong>RSSI:</strong> )rawliteral";

  page += String(WiFi.RSSI());

  page += R"rawliteral( dBm<br>

<strong>Relay GPIO:</strong> 5

</div>

</div>

<div class="warning">

Low-voltage demonstration only.
Do not connect mains voltage.

</div>

</div>

</body>

</html>
)rawliteral";

  return page;
}

// --------------------------------------------------
// Home Page
// --------------------------------------------------

void handleRoot() {

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Turn Light ON
// --------------------------------------------------

void handleLightOn() {

  lightState = true;

  digitalWrite(
    RELAY_PIN,
    RELAY_ON
  );

  Serial.println("Command received: LIGHT ON");
  Serial.println("Relay: ON");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Turn Light OFF
// --------------------------------------------------

void handleLightOff() {

  lightState = false;

  digitalWrite(
    RELAY_PIN,
    RELAY_OFF
  );

  Serial.println("Command received: LIGHT OFF");
  Serial.println("Relay: OFF");

  server.send(
    200,
    "text/html",
    buildWebPage()
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

  Serial.print("Signal Strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {

  pinMode(
    RELAY_PIN,
    OUTPUT
  );

  // Keep relay OFF during startup.
  digitalWrite(
    RELAY_PIN,
    RELAY_OFF
  );

  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("      IoT Student Lab");
  Serial.println(" Project 27: Wi-Fi Smart Light");
  Serial.println("================================");

  connectToWiFi();

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/on",
    handleLightOn
  );

  server.on(
    "/off",
    handleLightOff
  );

  server.onNotFound(
    handleNotFound
  );

  server.begin();

  Serial.println("Smart Light web server started.");

  Serial.print("Open: http://");
  Serial.println(WiFi.localIP());
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------

void loop() {

  server.handleClient();
}
