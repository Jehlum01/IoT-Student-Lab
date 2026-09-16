/*
  IoT Student Lab
  Project 28: Wi-Fi Temperature Monitor

  Platform: ESP32
  Sensor: DHT22
  Concept: Sensor + Wi-Fi + HTTP + Web Monitoring

  Learning Flow:
  DHT22 → ESP32 → Wi-Fi → Web Browser
*/

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// --------------------------------------------------
// Wi-Fi Configuration
// --------------------------------------------------

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// --------------------------------------------------
// DHT22 Configuration
// --------------------------------------------------

const int DHT_PIN = 4;
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

// --------------------------------------------------
// Web Server
// --------------------------------------------------

WebServer server(80);

// --------------------------------------------------
// Sensor Data
// --------------------------------------------------

float temperatureC = NAN;
float humidity = NAN;

bool sensorValid = false;

unsigned long lastSensorRead = 0;

const unsigned long SENSOR_INTERVAL = 2000;

// --------------------------------------------------
// Read Sensor
// --------------------------------------------------

void readSensor() {

  float newHumidity = dht.readHumidity();
  float newTemperature = dht.readTemperature();

  if (
    isnan(newHumidity) ||
    isnan(newTemperature)
  ) {

    sensorValid = false;

    Serial.println("DHT22 reading failed.");

    return;
  }

  humidity = newHumidity;
  temperatureC = newTemperature;

  sensorValid = true;

  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");
}

// --------------------------------------------------
// Generate Web Page
// --------------------------------------------------

String buildWebPage() {

  String page = R"rawliteral(
<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<meta http-equiv="refresh"
      content="5">

<title>ESP32 Temperature Monitor</title>

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

.subtitle {
  margin-bottom: 30px;
}

.dashboard {
  display: flex;
  justify-content: center;
  gap: 15px;
  flex-wrap: wrap;
}

.card {
  min-width: 220px;
  padding: 25px;
  background: #eeeeee;
  border-radius: 12px;
}

.value {
  font-size: 36px;
  font-weight: bold;
  margin-top: 10px;
}

.info {
  text-align: left;
  line-height: 1.9;
  margin-top: 25px;
}

.success {
  font-weight: bold;
}

.error {
  font-weight: bold;
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

<p class="subtitle">
Project 28 — Wi-Fi Temperature Monitor
</p>
)rawliteral";

  if (sensorValid) {

    page += R"rawliteral(

<div class="dashboard">

<div class="card">

<div>Temperature</div>

<div class="value">)rawliteral";

    page += String(temperatureC, 1);

    page += R"rawliteral( °C</div>

</div>

<div class="card">

<div>Humidity</div>

<div class="value">)rawliteral";

    page += String(humidity, 1);

    page += R"rawliteral( %</div>

</div>

</div>

<p class="success">
Sensor Status: OK
</p>

)rawliteral";

  } else {

    page += R"rawliteral(

<div class="card">

<div class="error">
Sensor Status: ERROR
</div>

<p>
Unable to read the DHT22.
</p>

<p>
Check the sensor wiring.
</p>

</div>

)rawliteral";

  }

  page += R"rawliteral(

<div class="card info">

<h2>ESP32 Network</h2>

<strong>SSID:</strong> )rawliteral";

  page += WiFi.SSID();

  page += R"rawliteral(<br>

<strong>IP Address:</strong> )rawliteral";

  page += WiFi.localIP().toString();

  page += R"rawliteral(<br>

<strong>RSSI:</strong> )rawliteral";

  page += String(WiFi.RSSI());

  page += R"rawliteral( dBm<br>

<strong>DHT22 GPIO:</strong> 4

</div>

<p class="note">
Page refreshes automatically every 5 seconds.
</p>

</div>

</body>

</html>
)rawliteral";

  return page;
}

// --------------------------------------------------
// Web Server Root
// --------------------------------------------------

void handleRoot() {

  server.send(
    200,
    "text/html",
    buildWebPage()
  );
}

// --------------------------------------------------
// Sensor Data Endpoint
// --------------------------------------------------

void handleData() {

  if (!sensorValid) {

    server.send(
      503,
      "text/plain",
      "Sensor data unavailable"
    );

    return;
  }

  String data = "Temperature: ";
  data += String(temperatureC, 1);
  data += " C\n";

  data += "Humidity: ";
  data += String(humidity, 1);
  data += " %\n";

  server.send(
    200,
    "text/plain",
    data
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

  Serial.println();

  Serial.println("================================");
  Serial.println("      IoT Student Lab");
  Serial.println(" Project 28: Wi-Fi Temperature");
  Serial.println("             Monitor");
  Serial.println("================================");

  dht.begin();

  connectToWiFi();

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/data",
    handleData
  );

  server.onNotFound(
    handleNotFound
  );

  server.begin();

  Serial.println("Temperature monitor web server started.");

  Serial.print("Open: http://");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println("Waiting for sensor readings...");
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------

void loop() {

  server.handleClient();

  if (
    millis() - lastSensorRead >=
    SENSOR_INTERVAL
  ) {

    lastSensorRead = millis();

    readSensor();
  }
}
