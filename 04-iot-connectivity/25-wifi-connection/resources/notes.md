# Project 25 — Learning Notes

## Why networking matters

The ESP32 becomes an IoT device when it can exchange information with other systems:

```text
Sensor → ESP32 → Wi-Fi → Network → Computer/Phone/Cloud
```

Before web control, students need a mental model of the network underneath the application.

## Core vocabulary

**SSID:** Wi-Fi network name.

**AP:** Access Point that provides a Wi-Fi network.

**STA:** Station/client that joins an AP.

**IP:** Network-layer address, for example `192.168.1.42`.

**MAC:** Network-interface identifier.

**RSSI:** Received signal strength indicator, commonly shown in dBm.

## RSSI

Example interpretation:

```text
-40 dBm → stronger
-60 dBm → weaker
-80 dBm → much weaker
```

RSSI is not a complete measure of network quality; interference, congestion, authentication and routing also matter.

## LAN vs Internet

```text
ESP32 ── Router/AP ── Laptop
          LOCAL LAN
```

Local communication can work without Internet access. Internet communication adds an external network path:

```text
ESP32 → Router → Internet → Remote server
```

## STA Mode

```cpp
WiFi.mode(WIFI_STA);
WiFi.begin(SSID, PASSWORD);
```

The ESP32 joins an existing Wi-Fi network.

## AP Mode

```cpp
WiFi.mode(WIFI_AP);
WiFi.softAP("ESP32-Student-Lab", "12345678");
```

The ESP32 creates the network and other devices join it.

## AP + STA

```cpp
WiFi.mode(WIFI_AP_STA);
```

The ESP32 can participate in an existing network while also operating as an AP.

## Wi-Fi scanning

Scanning can expose SSID, RSSI, encryption/security, BSSID and channel information. It is an excellent first experiment because it verifies wireless discovery before credentials are introduced.

## Connection sequence

```text
Choose network
     ↓
Authenticate / associate
     ↓
Network configuration
     ↓
Receive IP
     ↓
Test reachability
     ↓
Run application
```

## Layered troubleshooting

Do not change random code. Work from lower layers upward:

```text
1. Hardware / power
2. Radio / signal / band
3. Wi-Fi association / authentication
4. IP / DHCP / routing
5. Application protocol
6. Application logic
```

## Troubleshooting table

| Symptom | Investigate |
|---|---|
| Network invisible | SSID, band compatibility, signal, AP |
| Authentication fails | SSID/password/security |
| No IP | DHCP/network configuration |
| IP but ping fails | IP, LAN, firewall, isolation, VLAN |
| Repeated disconnects | RSSI, power, interference, AP stability, reconnect logic |

## Mini Experiments

### Distance vs RSSI

| Distance | RSSI | Connected? |
|---:|---:|---|
| 1 m | | |
| 3 m | | |
| 5 m | | |
| 10 m | | |

### Network failure recovery
Turn the AP off, observe the ESP32, restore the AP, and record recovery behaviour.

### STA vs AP
Compare who provides the Wi-Fi network in each mode.

## Reflection Questions

1. What is the difference between SSID and IP?
2. What does STA mean?
3. What does AP mean?
4. Who provides the network in STA mode?
5. Who provides the network in AP mode?
6. Can local communication work without Internet access?
7. What does RSSI indicate?
8. Why does Wi-Fi connection not automatically prove an HTTP application works?
9. What role does DHCP commonly play?
10. Why is layered troubleshooting useful?

## Engineering Connection

A typical IoT path is:

```text
Physical world
      ↓
Sensor
      ↓
Microcontroller
      ↓
Wireless network
      ↓
IP network
      ↓
Application protocol
      ↓
User interface
      ↓
Physical action
```

## Final Challenge

Build:

```text
Phone
  ↓
ESP32 AP
  ↓
GPIO
  ↓
LED
```

This naturally leads to:

```text
Browser → HTTP → Wi-Fi → ESP32 → GPIO → LED
```

That is the conceptual foundation for the next ESP32 web-control project.
