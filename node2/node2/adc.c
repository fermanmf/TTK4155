// Setup the internal adc on the arduino

#include <stdlib.h>


void adc_init() {

    // Enable ADC controller MCK in the PMC
    // ID_ADC = 37
    PMC->PMC_PCER1 |= 1 << (5);

    // Reset the adc
    ADC->ADC_CR |=1;

    // Enable register 0
    ADC->ADC_CHER |= 1 << 0;

    // Set Freerun mode
    ADC->ADC_MR |= 1 << 7;
    
    // ADC Control Register to start conversion
    ADC->ADC_CR |= 1 << 1;
    
}

void adc_read() {
    
    // Read the data from the analog input after it is sampled at ADC_CDR0 bit 0 to 11
    data = ADC->ADC_CDR[0];
    
    // Return data

}