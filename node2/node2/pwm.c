#include "pwm.h"

#include <math.h>

#include "sam.h"
#include "config.h"
#include "utils.h"
#include "printf-stdarg.h"

void pwm_init(unsigned int frequency) {
	PIOB->PIO_PDR |= PIO_PB25;
	PIOB->PIO_ABSR |= PIO_PB25;
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	TC0->TC_CHANNEL->TC_CMR = TC_CMR_WAVSEL_UP_RC | TC_CMR_WAVE | TC_CMR_ACPA_SET | TC_CMR_ACPC_CLEAR;
	
	const unsigned int COUNTER_FREQUENCY = MCK / 2;
	const unsigned int TOP = COUNTER_FREQUENCY / frequency;
	TC0->TC_CHANNEL->TC_RA = TOP;
	TC0->TC_CHANNEL->TC_RC = TOP;
	TC0->TC_CHANNEL->TC_CCR = TC_CCR_CLKEN; //enable
}

	
void pwm_set(float duty_cycle) {
	if (duty_cycle < 0 || duty_cycle > 1) {
		printf("Invalid duty cycle %f", duty_cycle);
		panic();
	}
	
	const unsigned int TOP = TC0->TC_CHANNEL->TC_RC;
	TC0->TC_CHANNEL->TC_RA = round(TOP * (1 - duty_cycle));
}
