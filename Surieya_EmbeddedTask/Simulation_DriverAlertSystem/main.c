/*
 */

#define F_CPU 16000000UL
#define AREF ((float)5.0)
#define RES 1023
#define THRESH 2.0
#include <avr/io.h>
#include<util/delay.h>



void ADC_init(void){
   //this line not need we use the default AREF as reference;
  //ADMUX = (1 << REFS0);
  ADMUX = 0x00;
  //ADMUX &= ~(1 << MUX0);
  //10000111
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

}



int ADC_Read(void){

  ADCSRA |= (1 << ADSC);
  while(ADCSRA & (1 << ADSC));
  return ADC;
}


float Get_Analog_Voltage(int adc_value){

    float voltage = (adc_value * AREF) / RES;
    return voltage;

}

int main(void)
{
    //setting the 4th pin of B as output;
    DDRB = DDRB | (1 << DDB4);
    //setting the 1st pin of C as input;
    DDRC = DDRC & ~(1 << DDC1);

    //initalize the ADC
    ADC_init();


    while(1){
        //PINC0,PORTC0,DDC0
        //checking whether the PINC0 is 1
        int pc1_input = PINC & (1 << PINC1);
        int adc_value = ADC_Read();

         //getting the value voltage value;
        float voltage = Get_Analog_Voltage(adc_value);


        //calculating the corresponding voltage

        if(voltage >= THRESH && !(pc1_input)){
            //setting PB4 as high
            PORTB = PORTB| (1 << PORTB4);
        }
        else{
            PORTB = PORTB& ~(1 << PORTB4);
        }

    }
        return 0;

    }


