"""
IoT Student Lab
Project 34: IoT Dashboard & Data Visualization

Purpose:
    Receive MQTT sensor telemetry and display it
    through a local web dashboard.

Architecture:

    ESP32
       ↓
    MQTT Broker
       ↓
    Python MQTT Client
       ↓
    Flask Web Dashboard
"""

import json
import threading
import time

import paho.mqtt.client as mqtt
from flask import Flask, jsonify, render_template_string


# ============================================================
# MQTT CONFIGURATION
# ============================================================

MQTT_BROKER = "YOUR_MQTT_BROKER"
MQTT_PORT = 1883
MQTT_TOPIC = "iot-student-lab/project32/telemetry"
MQTT_CLIENT_ID = "iot-student-dashboard-34"


# ============================================================
# WEB SERVER CONFIGURATION
# ============================================================

WEB_HOST = "0.0.0.0"
WEB_PORT = 5000


# ============================================================
# APPLICATION STATE
# ============================================================

latest_data = {
    "reading": None,
    "temperature": None,
    "humidity": None,
    "timestamp": None,
    "connected": False,
}


app = Flask(__name__)


# ============================================================
# MQTT CALLBACKS
# ============================================================

def on_connect(client, userdata, flags, reason_code, properties=None):
    print()
    print("========================================")
    print("Connected to MQTT broker.")
    print("========================================")

    latest_data["connected"] = True

    result, _ = client.subscribe(MQTT_TOPIC)

    if result == mqtt.MQTT_ERR_SUCCESS:
        print("Subscribed to:")
        print(MQTT_TOPIC)
    else:
        print("ERROR: MQTT subscription failed.")


def on_disconnect(client, userdata, disconnect_flags, reason_code, properties=None):
    print()
    print("MQTT connection lost.")
    latest_data["connected"] = False


def on_message(client, userdata, message):
    global latest_data

    try:
        payload = message.payload.decode("utf-8")
        data = json.loads(payload)

        temperature = data.get("temperature")
        humidity = data.get("humidity")
        reading = data.get("reading")

        latest_data = {
            "reading": reading,
            "temperature": temperature,
            "humidity": humidity,
            "timestamp": time.time(),
            "connected": True,
        }

        print()
        print("========== MQTT DATA ==========")
        print(f"Topic: {message.topic}")
        print(f"Reading: {reading}")
        print(f"Temperature: {temperature} °C")
        print(f"Humidity: {humidity} %")
        print("===============================")

    except json.JSONDecodeError:
        print("ERROR: Received invalid JSON.")

    except Exception as error:
        print(f"ERROR processing MQTT message: {error}")


# ============================================================
# DASHBOARD HTML
# ============================================================

DASHBOARD_HTML = """
<!DOCTYPE html>
<html>

<head>
    <meta name="viewport"
          content="width=device-width, initial-scale=1">

    <title>IoT Student Lab — Project 34</title>

    <style>
        body {
            font-family: Arial, sans-serif;
            background: #f4f4f4;
            margin: 0;
            padding: 30px 15px;
            text-align: center;
        }

        .container {
            max-width: 900px;
            margin: auto;
        }

        .header {
            background: white;
            padding: 25px;
            border-radius: 14px;
            margin-bottom: 20px;
        }

        .cards {
            display: grid;
            grid-template-columns:
                repeat(auto-fit, minmax(220px, 1fr));
            gap: 20px;
        }

        .card {
            background: white;
            padding: 25px;
            border-radius: 14px;
        }

        .label {
            font-size: 16px;
        }

        .value {
            font-size: 38px;
            font-weight: bold;
            margin: 15px 0;
        }

        .unit {
            font-size: 18px;
        }

        .status {
            margin-top: 20px;
            padding: 15px;
            border-radius: 10px;
            background: #eeeeee;
        }

        .footer {
            margin-top: 20px;
            color: #666;
        }
    </style>
</head>

<body>

<div class="container">

    <div class="header">

        <h1>IoT Student Lab</h1>

        <p>Project 34 — IoT Dashboard & Visualization</p>

        <div class="status">
            MQTT Status:
            <strong id="connection">
                Loading...
            </strong>
        </div>

    </div>

    <div class="cards">

        <div class="card">
            <div class="label">Temperature</div>

            <div class="value">
                <span id="temperature">--</span>
                <span class="unit">°C</span>
            </div>
        </div>

        <div class="card">
            <div class="label">Humidity</div>

            <div class="value">
                <span id="humidity">--</span>
                <span class="unit">%</span>
            </div>
        </div>

        <div class="card">
            <div class="label">Reading Number</div>

            <div class="value">
                <span id="reading">--</span>
            </div>
        </div>

    </div>

    <div class="footer">
        Last update:
        <span id="timestamp">Waiting for data...</span>
    </div>

</div>

<script>

async function updateDashboard() {

    try {

        const response =
            await fetch("/api/data");

        const data =
            await response.json();

        document.getElementById(
            "temperature"
        ).textContent =
            data.temperature ?? "--";

        document.getElementById(
            "humidity"
        ).textContent =
            data.humidity ?? "--";

        document.getElementById(
            "reading"
        ).textContent =
            data.reading ?? "--";

        document.getElementById(
            "connection"
        ).textContent =
            data.connected
                ? "CONNECTED"
                : "DISCONNECTED";

        if (data.timestamp) {

            const date =
                new Date(
                    data.timestamp * 1000
                );

            document.getElementById(
                "timestamp"
            ).textContent =
                date.toLocaleTimeString();

        } else {

            document.getElementById(
                "timestamp"
            ).textContent =
                "Waiting for data...";
        }

    } catch (error) {

        document.getElementById(
            "connection"
        ).textContent =
            "DASHBOARD ERROR";

        console.error(error);
    }
}

updateDashboard();

setInterval(
    updateDashboard,
    2000
);

</script>

</body>
</html>
"""


# ============================================================
# WEB ROUTES
# ============================================================

@app.route("/")
def dashboard():
    return render_template_string(DASHBOARD_HTML)


@app.route("/api/data")
def api_data():
    return jsonify(latest_data)


# ============================================================
# MQTT CLIENT
# ============================================================

def start_mqtt():

    client = mqtt.Client(
        mqtt.CallbackAPIVersion.VERSION2,
        client_id=MQTT_CLIENT_ID
    )

    client.on_connect = on_connect
    client.on_disconnect = on_disconnect
    client.on_message = on_message

    print("Starting MQTT client...")

    client.connect(
        MQTT_BROKER,
        MQTT_PORT,
        keepalive=60
    )

    client.loop_forever()


# ============================================================
# MAIN
# ============================================================

if __name__ == "__main__":

    print()
    print("========================================")
    print("        IoT Student Lab")
    print(" Project 34: IoT Dashboard")
    print("========================================")

    mqtt_thread = threading.Thread(
        target=start_mqtt,
        daemon=True
    )

    mqtt_thread.start()

    print()
    print(
        f"Dashboard starting on "
        f"http://localhost:{WEB_PORT}"
    )

    app.run(
        host=WEB_HOST,
        port=WEB_PORT,
        debug=False
    )
