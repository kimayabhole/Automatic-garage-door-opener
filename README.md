# Automatic-garage-door-opener
An automated garage door control system using ESP32, HC-SR04 ultrasonic sensor, and a servo motor with Wokwi simulation.

# Smart Automated Garage Door System using ESP32

> **Short Description:** An automated garage door control system using ESP32, HC-SR04 ultrasonic sensor, and a servo motor with Wokwi simulation.

An automated garage door/gate control system implemented on an **ESP32 DevKit v4** using an **HC-SR04 ultrasonic sensor** and an **SG90/MG995 servo motor**. 

The system detects incoming vehicles/objects within a defined threshold, automatically swings the gate open, holds it open while the vehicle passes, and safely closes once the path is clear.


## Components & Hardware

| Component | Description |
| :--- | :--- |
| **ESP32 DevKit v1** | Main microcontroller |
| **HC-SR04** | Ultrasonic distance sensor |
| **Servo Motor (SG90/MG995)** | Door / barrier actuator |
| **Resistors ($10\text{ k}\Omega \times 2$)** | Voltage divider for HC-SR04 Echo pin ($5\text{V} \rightarrow 2.5\text{V}$) |

----


## Calculations and Value Derivations

### 1. Distance Calculation (HC-SR04)
The sensor measures the two-way travel time of the sound pulse. Using the speed of sound (0.0343 cm/us):

Distance (cm) = (Duration in microseconds * 0.0343) / 2

We divide by 2 because the sound wave travels to the object and bounces back.

---

### 2. Servo Pulse Width Mapping
The servo uses a standard 50 Hz PWM frequency (20 ms period) with pulse widths between 500 us and 2400 us:

* 0 degrees (Open): 500 us pulse
* 90 degrees (Closed): 1450 us pulse

---

### 3. Voltage Divider (Echo Pin Protection)
The HC-SR04 outputs a 5V logic signal, but ESP32 pins are 3.3V tolerant. Two 10k ohm resistors split the voltage in half:

V_out = 5V * (10k / (10k + 10k)) = 2.5V

This 2.5V signal safely protects the ESP32 GPIO while still registering as a valid digital HIGH.

---

## Pin Mapping & Circuit Connection

| ESP32 Pin | Connected Component | Function / Notes |
| :--- | :--- | :--- |
| **GPIO 14** | Servo `PWM` (Orange/Yellow) | PWM control signal ($50\text{ Hz}$) |
| **GPIO 5** | Ultrasonic `TRIG` | Trigger pulse output |
| **GPIO 18** | Ultrasonic `ECHO` | Distance measurement input (via voltage divider) |
| **5V / VIN** | Sensor `VCC` & Servo `V+` | $5\text{V}$ power rail |
| **GND** | Sensor `GND` & Servo `GND` | Common ground rail |

> **Hardware Safety Note:** The HC-SR04 operates at $5\text{V}$ logic on its `ECHO` line. A 2-resistor voltage divider ($10\text{k}\Omega / 10\text{k}\Omega$) is placed between the `ECHO` pin and `GPIO 18` to safely step down the signal to $2.5\text{V}$, preventing damage to the $3.3\text{V}$-rated ESP32 GPIOs.




## How It Works
```text
idle condition--> door closed at 90 degrees--->object detected at <=10cm---> door opens at 0 degrees--->object passes through---> door back closed at 90 degrees
```

