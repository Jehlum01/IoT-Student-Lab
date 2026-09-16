# Project 25 — ESP32 Wi-Fi Fundamentals

> **Learning path:** Setup → Scan → Connect → Test → Wi-Fi Modes → Troubleshoot → IoT Control

## 🎯 Goal
Learn to configure an ESP32 in Arduino IDE, verify its Wi-Fi hardware, scan networks, connect in Station (STA) mode, inspect IP/RSSI information, test LAN reachability, understand AP/AP+STA modes, and diagnose common failures.

## 1. ESP32 + Arduino IDE Setup

```text
Arduino IDE
    ↓
Preferences
    ↓
Additional Boards Manager URLs
    ↓
Espressif ESP32 package index
    ↓
Boards Manager
    ↓
Install "esp32" by Espressif Systems
    ↓
Select ESP32 board + USB/serial port
    ↓
Upload test sketch
    ↓
Serial Monitor
```

**Official stable package index:**
`https://espressif.github.io/arduino-esp32/package_esp32_index.json`

Checklist:
- [ ] Arduino IDE installed
- [ ] ESP32 package URL added
- [ ] `esp32` platform installed
- [ ] Correct board selected
- [ ] Correct serial port selected
- [ ] Test sketch uploaded
- [ ] Serial Monitor verified

## 2. Wi-Fi Basics

```text
                    Wi-Fi Network

             ┌─────────────────────┐
             │   Wi-Fi Router/AP    │
             └──────────┬──────────┘
                        │
              ┌─────────┴─────────┐
              │                   │
           ESP32              Laptop/Phone
        Wi-Fi Client           Wi-Fi Client
```

| Term | Meaning |
|---|---|
| Wi-Fi | Wireless networking technology |
| SSID | Wi-Fi network name |
| Password | Network authentication credential |
| AP | Access Point providing a Wi-Fi network |
| STA | Station/client joining an AP |
| IP address | Network-layer device address |
| MAC address | Network-interface identifier |
| Router | Device that forwards traffic between networks; commonly provides DHCP/NAT |
| LAN | Local Area Network |
| RSSI | Received signal strength indicator |

Local communication does not necessarily require Internet access:

```text
ESP32 ── Wi-Fi Router ── Laptop
          LOCAL LAN
```

## 3. First Wi-Fi Test — Scan Networks

```text
ESP32
  ↓
Scan nearby networks
  ↓
SSID + RSSI + Security + Channel
  ↓
Serial Monitor
```

Example:

```text
Scanning for Wi-Fi networks...

Network 1
SSID: HomeWiFi
RSSI: -48 dBm

Network 2
SSID: SchoolLab
RSSI: -67 dBm

Network 3
SSID: MobileHotspot
RSSI: -81 dBm
```

For negative dBm values, a value closer to zero generally indicates a stronger received signal.

## 4. Connect ESP32 to Wi-Fi

```cpp
#include <WiFi.h>

const char* SSID = "YOUR_WIFI_NAME";
const char* PASSWORD = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("SSID: "); Serial.println(SSID);
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  Serial.print("Signal Strength: ");
  Serial.print(WiFi.RSSI()); Serial.println(" dBm");
}

void loop() {}
```

Expected:

```text
Connecting.....
Wi-Fi connected!

SSID: SchoolLab
IP Address: 192.168.1.42
Signal Strength: -53 dBm
```

Concept:

```text
SSID + Password → WiFi.begin()
                 ↓
       Authentication/association
                 ↓
          Network configuration
                 ↓
             IP address
```

## 5. How to Test Wi-Fi

### Test A — Serial Monitor
Check `WiFi.status()`, `WiFi.localIP()`, and `WiFi.RSSI()`.

### Test B — Ping

```bash
ping 192.168.1.42
```

Replace the example IP with the ESP32's actual address.

```text
ESP32 connected → ESP32 has IP → Computer reaches IP → LAN path verified
```

A failed ping does not always mean Wi-Fi is broken; firewall, client isolation, VLANs and router policy can block ICMP.

### Test C — Disconnect/reconnect
Turn Wi-Fi off, restart the router, move the ESP32 away from the AP, restore connectivity, and observe recovery.

## 6. ESP32 Wi-Fi Modes

### STA — Station

ESP32 joins an existing network.

```text
Wi-Fi Router
     │
    Wi-Fi
     ↓
   ESP32
```

```cpp
WiFi.mode(WIFI_STA);
```

### AP — Access Point

ESP32 creates its own network.

```text
             ESP32 AP
             /               Phone     Laptop
```

```cpp
WiFi.mode(WIFI_AP);
WiFi.softAP("ESP32-Student-Lab", "12345678");
```

### AP + STA

ESP32 joins an existing network and also creates an AP.

```text
Router ──→ ESP32 ←── Phone/Laptop
            │
          AP + STA
```

```cpp
WiFi.mode(WIFI_AP_STA);
```

## 7. Mode Comparison

| Mode | Joins router/AP? | Creates network? | Typical use |
|---|---:|---:|---|
| STA | ✅ | ❌ | LAN/Internet IoT |
| AP | ❌ | ✅ | Direct ESP32 control |
| AP + STA | ✅ | ✅ | Advanced networking |

## 8. Troubleshooting Lab

### Cannot find network
Check SSID, compatible Wi-Fi band, signal strength and AP availability.

### Connects but no IP
Investigate DHCP/network configuration.

### Has IP but ping fails
Check correct IP, same reachable LAN, firewall, client isolation and VLAN/network boundaries.

### Disconnects repeatedly
Check RSSI, power supply, interference, AP stability and reconnect logic.

## 9. Mini Challenges

1. Scan nearby networks and sort results by RSSI.
2. Display SSID, IP, RSSI and MAC.
3. Connect automatically to one of two known networks.
4. Create an ESP32 AP and connect a phone.
5. Build:

```text
Phone → ESP32 AP → ESP32 GPIO → LED
```

This is the bridge to browser-based ESP32 control.

## Learning Checklist

- [ ] Install ESP32 support
- [ ] Select board and port
- [ ] Upload a test sketch
- [ ] Scan Wi-Fi
- [ ] Read SSID/RSSI/security
- [ ] Connect in STA mode
- [ ] Read IP address
- [ ] Test LAN reachability
- [ ] Understand AP and AP+STA
- [ ] Diagnose a deliberate Wi-Fi failure

## Official References
- https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
- https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html
