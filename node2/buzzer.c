#include "buzzer.h"

#include <stdint.h>
#include <math.h>

#include "sam.h"
#include "consts.h"

void buzzer_init() {
	PIOC->PIO_PDR |= PIO_PC9; // pwm 41
	PIOC->PIO_ABSR |= PIO_PC9;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	PWM->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024;
	
	//TC7
	PMC ->PMC_PCER1 |= PMC_PCER1_PID34;
	TC2->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;	
	TC2->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_CPCSTOP;
	TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN;
	
	NVIC_EnableIRQ(TC7_IRQn);
}
	
void buzzer_play_note(float tone, uint8_t invdur) {
	PWM->PWM_CH_NUM[3].PWM_CPRD = round(MCK_NODE2/(1024 * tone));
	PWM->PWM_CH_NUM[3].PWM_CDTY = PWM->PWM_CH_NUM[3].PWM_CPRD / 2; // 50 % duty cycle
	PWM->PWM_ENA = PWM_DIS_CHID3; // enable pwm
	
	TC2->TC_CHANNEL[1].TC_RC = MCK_NODE2 / (2 * 128 * invdur);
	TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG;
}

void TC7_Handler(){
	PWM->PWM_DIS = PWM_DIS_CHID3; // disable pwm
	TC2->TC_CHANNEL[1].TC_SR;			
}