#include "ir.h"

#include "sam.h"
#include "printf-stdarg.h"

static void (*IR_BEAM_BROKEN_CB)();

void ir_init(void (*callback)()) {
	IR_BEAM_BROKEN_CB = callback;

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
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID32;

	
	TC1->TC_CHANNEL[2].TC_IER = TC_IER_CPCS;
	TC1->TC_CHANNEL[2].TC_RC = 65625/10;
	TC1->TC_CHANNEL[2].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	TC1->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; 
	
	NVIC_EnableIRQ(TC5_IRQn);
}

#define ir_value ((volatile uint32_t*) 0x400C0050)
#define TRESHOLD 300

static uint32_t last_ir_value = 0;

void TC5_Handler(){	
	if (*ir_value < TRESHOLD && last_ir_value > TRESHOLD) {
		(*IR_BEAM_BROKEN_CB)();
	}
	last_ir_value = *ir_value;
	TC1->TC_CHANNEL[2].TC_SR;
}
