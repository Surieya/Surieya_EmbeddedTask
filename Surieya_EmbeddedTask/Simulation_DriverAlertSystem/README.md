# Seatbelt Detection System Simulation

## Project Overview
This project simulates the behavior of a seatbelt detection system using an AVR microcontroller. The system determines whether a person is seated based on an ADC voltage threshold and whether the seatbelt is fastened using a push button. The output is an LED connected to PB4, which turns on or off based on the given conditions.

## Components Used
- AVR Microcontroller (e.g., ATmega series)
- Potentiometer (for simulating seat occupancy)
- Push Button (for simulating seatbelt fastening)
- LED (indicating seatbelt status)
- Resistors (as required for button and LED connections)

## Working Principle
1. **Seat Occupancy Detection:**
   - The voltage from the potentiometer is read via ADC.
   - If the voltage exceeds a predefined threshold (THRESH), it indicates a person is seated.
   
2. **Seatbelt Fastening Detection:**
   - The push button is connected to PC1.
   - When pressed, it indicates that the seatbelt is fastened.

3. **Output Logic:**
   - The LED connected to PB4 turns **ON** if the ADC voltage is greater than the threshold and the seatbelt is **not** fastened.
   - Otherwise, the LED remains **OFF**.

## Code Explanation
The program is structured as follows:
- **ADC Initialization (`ADC_init`)**:
  - Configures the ADC with a reference voltage of 5V and a resolution of 10 bits.
- **ADC Read (`ADC_Read`)**:
  - Starts ADC conversion and returns the digital value.
- **Analog Voltage Calculation (`Get_Analog_Voltage`)**:
  - Converts ADC reading to voltage using the formula:
    
    ```
    voltage = (adc_value * AREF) / RES;
    ```
- **Main Function (`main`)**:
  - Configures PB4 as an output for LED control.
  - Configures PC1 as an input for the push button.
  - Continuously reads ADC values and push button status.
  - Implements the seatbelt detection logic to control the LED.

## Pin Configuration
| Component        | Pin Used  |
|-----------------|-----------|
| Potentiometer   | ADC Input |
| Push Button     | PC1 (Input) |
| LED Output      | PB4 (Output) |

## Circuit Diagram (Conceptual)
1. **Potentiometer** connected to ADC input.
2. **Push Button** connected to PC1 with a pull-down resistor.
3. **LED** connected to PB4 via a resistor.

## How to Run
1. Connect the components as per the pin configuration.
2. Load the provided code onto the microcontroller.
3. Adjust the potentiometer to vary the ADC voltage.
4. Press the push button to simulate fastening the seatbelt.
5. Observe the LED behavior based on the given conditions.

## Expected Output
- **LED ON:** When the seat is occupied (ADC voltage > THRESH) and the seatbelt is not fastened.
- **LED OFF:** When the seat is empty or the seatbelt is fastened.

## Future Enhancements
- Implement a buzzer for an audible warning when the seatbelt is not fastened.
- Use an actual weight sensor instead of a potentiometer for more realistic seat occupancy detection.
- Add an LCD display for status messages.

## Author
Developed by [Your Name].

