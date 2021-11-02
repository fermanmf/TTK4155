// Setup the internal adc on the arduino
#include "adc.h"

#include "sam.h"


void adc_init() {

    // Enable ADC controller MCK in the PMC
    // ID_ADC = 37
	PIOA->PIO_PDR = PIO_PA2;
    PMC->PMC_PCER1 |= PMC_PCER1_PID37;

    // Reset the adc
    ADC->ADC_CR |=1;

    // Enable register 0
    ADC->ADC_CHER |= 1 << 0;

    // Set Freerun mode
    ADC->ADC_MR |= 1 << 7;
    
    // ADC Control Register to start conversion
    ADC->ADC_CR |= 1 << 1;
    
}

volatile unsigned int *IR = (unsigned int*) 0x400C0050;