# BMP280 I2C Temperature Sensor Driver

## Overview
This Linux kernel module is a character driver for reading temperature data from the BMP280 sensor over I2C. The driver registers itself as a character device and provides a file interface for userspace applications to read temperature data.

## Features
- Communicates with BMP280 sensor via I2C
- Reads temperature data and converts it into human-readable format
- Registers as a character device for easy access
- Provides calibration handling

---

## Prerequisites
Ensure you have the following installed:
- Linux Kernel Headers
- I2C tools (`i2c-tools` package for debugging)
- A BMP280 sensor connected to an I2C bus
- A Raspberry Pi or STM32 with I2C enabled

## Steps Followed in the Driver

```plaintext
+-------------------------+
|  Module Initialization  |
+-------------------------+
            |
            v
+-------------------------+
| Register Character Dev  |
+-------------------------+
            |
            v
+-------------------------+
| Create Device Class     |
+-------------------------+
            |
            v
+-------------------------+
| Register I2C Adapter    |
+-------------------------+
            |
            v
+-------------------------+
| Probe BMP280 Sensor     |
+-------------------------+
            |
            v
+-------------------------+
| Read Calibration Data   |
+-------------------------+
            |
            v
+-------------------------+
| File Operations (Read)  |
+-------------------------+
            |
            v
+-------------------------+
| Module Exit - Cleanup   |
+-------------------------+
```

## Installation & Usage
### 1. Build and Insert the Module
```bash
make
sudo insmod i2c_temp.ko
```
### 2. Verify if Module is Loaded
```bash
dmesg | grep "MyDeviceDriver"
ls /dev/i2c_temp
```
### 3. Read Temperature Data
```bash
cat /dev/i2c_temp
```
### 4. Remove Module
```bash
sudo rmmod i2c_temp
```

## Debugging
If the sensor is not detected:
```bash
i2cdetect -y 1  # Verify BMP280 address (should be 0x76)
dmesg | tail -n 20
```

## License
This driver is licensed under GPL.

