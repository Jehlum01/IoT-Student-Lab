/*
  IoT Student Lab
  Project 25: ESP32 Wi-Fi LED Control

  Platform: ESP32
  Concept: Wi-Fi + HTTP + Remote GPIO Control

  Learning flow:
  Browser → Wi-Fi → ESP32 → GPIO → LED
*/

#include <WiFi.h>
#include <WebServer.h>

// -----------------------------
// Wi-Fi Configuration
// -----------------------------
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// -----------------------------
// Hardware
// -----------------------------
const int LED_PIN = 5;   // ESP32 GPIO5

// -----------------------------
// Web Server
// -----------------------------
WebServer server(80);

bool ledState = false;

// -----------------------------
// Web Page
// -----------------------------
void sendHomePage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>IoT Student Lab</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin-top: 50px;
    }

    h1 {
      margin-bottom: 10px;
    }

    .status {
      font-size: 22px;
      margin: 25px;
    }

    a {
      display: inline-block;
      padding: 15px 30px;
      margin: 8px;
      text-decoration: none;
      border-radius: 8px;
      color: white;
      font-size: 18px;
    }

    .on {
      background: green;
    }

    .off {
      background: red;
    }
  </style>
</head>

<body>

  <h1>IoT Student Lab</h1>
  <h2>Project 25: ESP32 Wi-Fi LED Control</h2>

  <div class="status">
    LED Status:
)rawliteral";

  page += ledState ? "ON" : "OFF";

  page += R"rawliteral(
  </div>

  <a class="on" href="/on">Turn ON</a>
  <a class="off" href="/off">Turn OFF</a>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

// -----------------------------
// LED ON
// -----------------------------
void handleLedOn() {
  ledState = true;
  digitalWrite(LED_PIN, HIGH);

  Serial.println("LED → ON");

  sendHomePage();
}

// -----------------------------
// LED OFF
// -----------------------------
void handleLedOff() {
  ledState = false;
  digitalWrite(LED_PIN, LOW);

  Serial.println("LED → OFF");

  sendHomePage();
}

// -----------------------------
// Wi-Fi Connection
// -----------------------------
void connectToWiFi() {

  Serial.print("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

// -----------------------------
// Setup
// -----------------------------
void setup() {

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("      IoT Student Lab");
  Serial.println(" Project 25: Wi-Fi LED Control");
  Serial.println("================================");

  connectToWiFi();

  server.on("/", sendHomePage);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);

  server.begin();

  Serial.println("Web server started.");
  Serial.println("Open the ESP32 IP address in a browser.");
}

// -----------------------------
// Main Loop
// -----------------------------
void loop() {
  server.handleClient();
