

#include "timer.h"

#include "sam.h"
#include "dac.h"
#include "motor.h"
#include "printf-stdarg.h"
#include <stdint.h>
#define REGISTER_C 6563 
#define TC1_REGISTER_C 65625
#define INT_PERIOD REGISTER_C*128/84000000

//waveform mode clock is MCK/128 period is therefore about 10 ms when Register_C = 6563
void timer_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27 | PMC_PCER0_PID31 |PMC_PCER0_PID30 | PMC_PCER0_PID28;
	
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
    TC0->TC_CHANNEL[0].TC_RC = REGISTER_C; 
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	
	TC1->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
	TC1->TC_CHANNEL[1].TC_RC = TC1_REGISTER_C;
	TC1->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	TC1->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

    NVIC_EnableIRQ(TC0_IRQn);
	NVIC_EnableIRQ(TC4_IRQn);
}
int test = 1;
void TC0_Handler(){
	/*
	if (test){
		dac_write(0.2);
		test = 0;	
	}
	else{
		dac_write(0.7);
		test = 1;
	}*/
	motor_control_pos(INT_PERIOD);	
    TC0->TC_CHANNEL[0].TC_SR;	//Clear interrupt flag
	
}
void TC4_Handler(){
	if (test){
		pid.ref = 300;
		test = 0;	
	}
	else{
		pid.ref = 800;
		test = 1;
	}
    TC1->TC_CHANNEL[1].TC_SR;	//Clear interrupt flag
	
}


void timer_delay_u(uint32_t time_us){
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    SysTick->LOAD |= 84*time_us;
	SysTick->VAL = 0;
    while(!(SysTick->CTRL & (1<<16)));
}

void timer_delay(uint32_t time){
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; //clocksource is MCK/8
    SysTick->LOAD |=  11*time*10^6;
	SysTick->VAL = 0;
    while(!(SysTick->CTRL & (1<<16)));
}

