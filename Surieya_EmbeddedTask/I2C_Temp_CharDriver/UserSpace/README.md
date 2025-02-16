# User-Space Application for BMP280 I2C Temperature Sensor

## Overview
This C program reads temperature data from the `/dev/i2c_temp` device file, which is created by the BMP280 I2C temperature sensor driver. It opens the device file, reads the temperature value, and displays it on the console.

## Features
- Opens the character device `/dev/i2c_temp`
- Reads temperature data from the sensor
- Displays temperature in degrees Celsius

---

## Steps Followed in the Application

```plaintext
+-------------------------+
|  Open Device File       |
+-------------------------+
            |
            v
+-------------------------+
|  Read Temperature Data  |
+-------------------------+
            |
            v
+-------------------------+
| Null-Terminate Buffer  |
+-------------------------+
            |
            v
+-------------------------+
| Print Temperature Value |
+-------------------------+
            |
            v
+-------------------------+
| Close Device File       |
+-------------------------+
```

## Compilation & Execution
### 1. Compile the Program
```bash
gcc -o read_temp read_temp.c
```
### 2. Run the Program
```bash
./read_temp
```

## Expected Output
```bash
Temperature: 25.63°C
```

## Debugging
If the program fails to read from the device:
```bash
dmesg | tail -n 20
ls /dev/i2c_temp  # Check if device exists
```

## License
This application is licensed under GPL.

