# 🤖 PID-Control-Line-Following-Robot

A **line-following robot** built with **Arduino** and controlled using a **PID (Proportional–Integral–Derivative)** algorithm.  
It uses an array of IR sensors to detect a black line and continuously adjusts motor speeds for smooth and precise tracking.

## 🔍 Overview

This robot demonstrates how feedback control can be applied to autonomous navigation.  
Using PID, it calculates how far the robot has drifted from the line and instantly corrects its movement.

## ⚙️ Features

- Smooth and stable motion with PID-based control  
- Adjustable PID constants (`Kp`, `Kd`) for tuning  
- 6 IR sensors for accurate line detection  
- Real-time serial output for debugging  
- Works with any L298N or L293D motor driver module  

## 🧠 How It Works

1. The IR sensors detect surface reflectivity (black or white).  
2. The readings are used to find the average position of the line.  
3. The **error** = (actual position) − (center position).  
4. The PID controller computes a correction value based on:
   - **Proportional (Kp):** reacts to the current error  
   - **Derivative (Kd):** reacts to the rate of change of error  
5. The correction adjusts motor speeds to bring the robot back on track.

## 🧩 Components Required

| Component | Quantity | Description |
|------------|-----------|-------------|
| **Arduino Nano** | 1 | Main microcontroller for processing sensor data and PID control |
| **L298N Motor Driver** | 1 | Drives the left and right DC motors |
| **IR Sensor Array (6-channel)** | 1 | Detects the line on the surface |
| **2S 7.4V LiPo Battery** | 1 | Power source for the robot |
| **Buck Converter Module (Step-Down 8.4V → 5V)** | 1 | Powers the Arduino from the LiPo battery |
| **Boost Converter Module (Step-Up 8.4V → 12V)** | 1 | Powers the motor driver for higher torque |
| **DC Motors** | 2 | Left and right wheel drive |
| **Robot Chassis** | 1 | Base structure for all components |
| **Jumper Wires & Connectors** | — | For connections between modules |
| **Power Switch (optional)** | 1 | To turn the robot on/off easily |

---

## ⚡ Circuit Diagram

Below is the full power and connection layout for the PID line-following robot:

![Circuit Diagram](https://github.com/ajajaquil03/PID-Control-Line-Following-Robot/blob/750c60650b619eb7dcb2a062a9c2ed4cc311c8ce/Image/Circuit%20Diagram%20for%20LFR.png)

**Power Flow Summary:**
- **2S 7.4V LiPo Battery** → feeds both **Buck** and **Boost** modules  
- **Buck Module (8.4V → 5V)** → powers the Arduino Nano  
- **Boost Module (8.4V → 12V)** → powers the L298N Motor Driver  
- **IR Sensor Array** → connected to Arduino analog inputs  
- **L298N** → controls both DC motors based on PID output  

---

## 💻 Code Details

The main logic is implemented in **C++ (Arduino)**.  
Check the [`PID_LFR.ino`](https://github.com/ajajaquil03/PID-Control-Line-Following-Robot/tree/750c60650b619eb7dcb2a062a9c2ed4cc311c8ce/PID_LFR) file for the full source code.

**Key variables to tune:**

```cpp
float kp = 50;   // Proportional constant
float kd = 1000; // Derivative constant
int threshold = 512; // Line detection threshold

int lbase = 200; // Base speed for left motor
int rbase = 200; // Base speed for right motor
````

These values can be adjusted to balance speed and accuracy.

## 📐 PID Formula & Control Diagram

The PID controller calculates the correction using the formula:

$$
\text{Correction} = (K_p \times \text{Error}) + (K_i \times \text{Integral}) + (K_d \times \text{Derivative})
$$

Where:

* **Error** is the difference between the desired and actual position
* **Kp** controls the proportional response
* **Ki** reduces steady-state error (not used in this project)
* **Kd** dampens oscillation and predicts future error

Visual representation of the PID control loop:

```
        +-----------------------------+
        |                             |
        |      +------------------+   |
 Setpoint ---> |     Controller    | ---> Control Signal ---> Motor Driver ---> Robot
                +------------------+                           |
                        ^                                      |
                        |             Sensor Array              |
                        +--------------------------------------+
```

This feedback loop ensures the robot constantly corrects its path based on sensor input.

## 🧪 PID Tuning Guide

1. Start by increasing **Kp** until the robot starts oscillating.
2. Then increase **Kd** until oscillations settle.
3. Keep adjusting both until the robot moves smoothly along the line.

## 📊 Serial Monitor Output

The Arduino sends sensor readings, error, and PID correction data over the Serial Monitor.
Use this data to observe how changes in PID constants affect performance.

## 🚀 Future Improvements

* Add **Ki (Integral)** term for better long-term correction
* Automatic sensor calibration
* Bluetooth or Wi-Fi module for remote PID tuning
* OLED display for live PID values


## 👤 Author

**Ajaj Mahmud Aquil** - **[Github](https://github.com/ajajaquil03)**
**Ajaj Mahmud Aquil** - **[LinkedIn Profile](https://www.linkedin.com/in/ajajmahmudaquil/)**

## ⭐ Support

If you find this project helpful, please give it a ⭐ on GitHub!
