# L5-T07 — IoT Security & Reliability

## How to Study This Lesson

Do not memorize the vocabulary first. Trace every diagram from left to right and ask **what data moves, who creates it, who receives it, and what happens when something fails**. Use the experiments and reflection questions to test whether you can explain the concept without looking at the notes.

## Learning Objectives

Understand:

- Authentication
- Authorization
- Confidentiality
- Integrity
- Availability
- Credentials
- Failure handling
- Secure system design

---

# 1. Why IoT Security Matters

A connected device is part of a network.

Therefore it becomes part of a larger attack surface.

```text
IoT Device
    ↓
Network
    ↓
Services
    ↓
Users
````

Security must be considered throughout the architecture.

---

# 2. Authentication

Authentication asks:

> Who are you?

Examples:

- Username/password
- API key
- Certificate
- Token

---

# 3. Authorization

Authorization asks:

> What are you allowed to do?

Example:

```text
Student
  → View temperature

Administrator
  → View temperature
  → Configure device
```

Authentication and authorization are different concepts.

---

# 4. Confidentiality

Confidentiality means preventing unauthorized access to information.

Example:

```text
Sensor Data
   ↓
Protected Communication
   ↓
Authorized System
```

---

# 5. Integrity

Integrity means data should not be modified without authorization.

Example:

```text
Temperature = 25°C
```

should not silently become:

```text
Temperature = 95°C
```

during transmission.

---

# 6. Availability

Availability asks:

> Is the system available when required?

IoT systems must consider:

```text
Power failure
Wi-Fi failure
Broker failure
Sensor failure
Server failure
```

---

# 7. Credentials

Never publish real credentials in a public repository.

Bad:

```cpp
const char* password = "real-password";
```

Better for student examples:

```cpp
const char* password = "YOUR_PASSWORD";
```

Production systems require proper secret-management practices.

---

# 8. Failure Handling

A robust IoT system should consider:

```text
Wi-Fi lost
   ↓
Reconnect / local operation

Sensor failure
   ↓
Report invalid state

Server unavailable
   ↓
Buffer / retry / operate locally

Power restart
   ↓
Safe startup state
```

The exact strategy depends on the application.

---

# 9. Secure by Design

Security should not be added only at the end.

Think about it during architecture.

```text
Device
 ↓
Identity
 ↓
Communication
 ↓
Authentication
 ↓
Authorization
 ↓
Data
```

---

# 10. Reliability vs Security

A system can be:

```text
Connected
but insecure

Secure
but unreliable

Reliable
but poorly designed
```

Good engineering considers the whole system.

---

# 11. Threat Questions

Ask:

```text
Who can connect?
Who can publish?
Who can subscribe?
Who can control?
What data is exposed?
What happens after compromise?
```

---

# 12. Reflection

1. What is authentication?
2. What is authorization?
3. What is confidentiality?
4. What is integrity?
5. What is availability?
6. Why should credentials not be committed to GitHub?
7. What should happen if Wi-Fi disappears?

---

# Challenge

Create a threat model for a smart-home system.

Identify:

### Assets

What needs protection?

### Threats

What could go wrong?

### Controls

What could reduce the risk?

### Recovery

What happens after failure?

````


---
