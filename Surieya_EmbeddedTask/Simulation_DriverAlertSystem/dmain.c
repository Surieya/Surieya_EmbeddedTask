/**
 * @file adc_control.c
 * @brief Seatbelt Detection System
 * @author Surieya
 *
 */

/**
 * @brief CPU clock frequency in Hz
 */
#define F_CPU 16000000UL

/**
 * @brief Analog reference voltage in volts
 */
#define AREF ((float)5.0)

/**
 * @brief ADC resolution (10-bit ADC -> 1023 max value)
 */
#define RES 1023

/**
 * @brief Voltage threshold for triggering output
 */
#define THRESH 2.0

#include <avr/io.h>
#include <util/delay.h>

/**
 * @brief Initializes the ADC module with a prescaler of 128.
 * 
 * This function configures the ADC to use the default AREF, selects channel 0,
 * and enables the ADC with a prescaler of 128 for proper operation.
 */
void ADC_init(void) {
    ADMUX = 0x00;  /**< Select ADC channel 0, use AREF */
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); /**< Enable ADC, set prescaler to 128 */
}

/**
 * @brief Reads the ADC value from the selected channel.
 * 
 * This function starts an ADC conversion, waits for it to complete, 
 * and returns the resulting 10-bit digital value.
 * 
 * @return ADC conversion result (0 - 1023)
 */
int ADC_Read(void) {
    ADCSRA |= (1 << ADSC); /**< Start ADC conversion */
    while (ADCSRA & (1 << ADSC)); /**< Wait for conversion to complete */
    return ADC; /**< Return ADC result */
}

/**
 * @brief Converts an ADC digital value to an equivalent voltage.
 * 
 * This function calculates the analog voltage corresponding to the given ADC 
 * digital value using the reference voltage.
 * 
 * @param adc_value ADC digital reading (0 - 1023)
 * @return Corresponding analog voltage in volts
 */
float Get_Analog_Voltage(int adc_value) {
    return (adc_value * AREF) / RES;
}

/**
 * @brief Main function that continuously monitors the ADC and controls an output pin.
 * 
 * The program initializes the ADC and configures the necessary GPIO pins. It then 
 * continuously reads the ADC value, converts it to voltage, and toggles an output pin 
 * based on a threshold voltage.
 * 
 * @return int Always returns 0 (not used in embedded systems)
 */
int main(void) {
    DDRB |= (1 << DDB4); /**< Configure PB4 as output */
    DDRC &= ~(1 << DDC1); /**< Configure PC1 as input */
    
    ADC_init(); /**< Initialize ADC */

    while (1) {
        int pc1_input = PINC & (1 << PINC1); /**< Read input from PC1 */
        int adc_value = ADC_Read(); /**< Read ADC value */
        float voltage = Get_Analog_Voltage(adc_value); /**< Convert ADC value to voltage */

        if (voltage >= THRESH && !pc1_input) {
            PORTB |= (1 << PORTB4); /**< Set PB4 high if voltage >= threshold and PC1 is low */
        } else {
            PORTB &= ~(1 << PORTB4); /**< Set PB4 low otherwise */
        }
    }
    return 0;
}
