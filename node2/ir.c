// Setup the internal adc on the arduino
#include "ir.h"

#include "sam.h"
#include "printf-stdarg.h"

#include <stdbool.h>

void ir_init() {

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

    // ------- Setting up interrupt --------

    // Enable comparison interrupt
    ADC->ADC_IER |= ADC_IER_COMPE;

    // Selecting comparison mode to LOW
    ADC->ADC_EMR |= ADC_EMR_CMPMODE_LOW | ADC_EMR_CMPSEL(0);

    // Setting the LOW threshold
    ADC->ADC_CWR = 300;    
}

volatile unsigned int *IR = (unsigned int*) 0x400C0050;

void TC5_Handler(){
	static bool last_under_threshold = false;
	if (*IR < 300) {
		if (!last_under_threshold) {
			(*ir_beam_broken_cb)();
			last_under_threshold = true;
		}		
	} else if (*IR > 500) {
		last_under_threshold = false;
	}
	TC1->TC_CHANNEL[2].TC_SR;
}
