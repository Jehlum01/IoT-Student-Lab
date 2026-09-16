/*
  IoT Student Lab
  Project 26: ESP32 Web Server

  Platform: ESP32
  Concept: HTTP + Web Server + HTML + GPIO Control

  Learning Flow:
  Browser → Wi-Fi → HTTP → ESP32 → GPIO → LED
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

const int LED_PIN = 5;

// --------------------------------------------------
// Web Server
// --------------------------------------------------

WebServer server(80);

bool ledState = false;

// --------------------------------------------------
// Generate Web Page
// --------------------------------------------------

String buildWebPage() {

  String ledStatus = ledState ? "ON" : "OFF";

  String page = R"rawliteral(
<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<title>ESP32 Web Server</title>

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
  margin: 20px 0;
  padding: 20px;
  border-radius: 10px;
  background: #eeeeee;
}

.status {
  font-size: 24px;
  font-weight: bold;
}

.button {
  display: inline-block;
  padding: 14px 28px;
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

</style>

</head>

<body>

<div class="container">

<h1>IoT Student Lab</h1>

<p>Project 26 — ESP32 Web Server</p>

<div class="card">

<h2>LED Control</h2>

<p class="status">
LED: )rawliteral";

  page += ledStatus;

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

<h2>ESP32 Information</h2>

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

<strong>GPIO:</strong> 5

</div>

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
// LED ON
// --------------------------------------------------

void handleLedOn() {

  ledState = true;

  digitalWrite(
    LED_PIN,
    HIGH
  );

  Serial.println("HTTP request: /on");
  Serial.println("LED → ON");

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// LED OFF
// --------------------------------------------------

void handleLedOff() {

  ledState = false;

  digitalWrite(
    LED_PIN,
    LOW
  );

  Serial.println("HTTP request: /off");
  Serial.println("LED → OFF");

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

  message += "\nMethod: ";
  message +=
    (server.method() == HTTP_GET)
    ? "GET"
    : "OTHER";

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

  pinMode(
    LED_PIN,
    OUTPUT
  );

  digitalWrite(
    LED_PIN,
    LOW
  );

  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("      IoT Student Lab");
  Serial.println(" Project 26: ESP32 Web Server");
  Serial.println("================================");

  connectToWiFi();

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/on",
    handleLedOn
  );

  server.on(
    "/off",
    handleLedOff
  );

  server.onNotFound(
    handleNotFound
  );

  server.begin();

  Serial.println("Web server started.");

  Serial.print("Open: http://");
  Serial.println(WiFi.localIP());
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------

void loop() {

  server.handleClient();
}
