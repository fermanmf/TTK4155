

#include "timer.h"
#include "em.h"
#include "sam.h"
#include "dac.h"
#include "motor.h"
#include "printf-stdarg.h"
#include <stdint.h>
#define REGISTER_C 6563 
#define TC4_REGISTER_C 656250
#define TC5_REGISTER_C 65625
#define TC1_REGISTER_C 13125000 //20s
#define INT_PERIOD REGISTER_C*128/84000000

//waveform mode clock is MCK/128 period is therefore about 10 ms when Register_C = 6563
void timer_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27 | PMC_PCER0_PID28| PMC_PCER0_PID31;
	PMC->PMC_PCER1 |= PMC_PCER1_PID32;
	

	//TC0 PID controller clock
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
    TC0->TC_CHANNEL[0].TC_RC = REGISTER_C; 
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	
	//TC1 Game clock
	TC0->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
	TC0->TC_CHANNEL[1].TC_RC = TC1_REGISTER_C;
	TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;

	// TC4 test
	//TC1->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
	//TC1->TC_CHANNEL[1].TC_RC = TC4_REGISTER_C;
	//TC1->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	//TC1->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	
	//TC5 Timer IR
	TC1->TC_CHANNEL[2].TC_IER = TC_IER_CPCS;
	TC1->TC_CHANNEL[2].TC_RC = TC5_REGISTER_C;
	TC1->TC_CHANNEL[2].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	TC1->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	
	//pid interrupt
    NVIC_EnableIRQ(TC0_IRQn);

	
	
}
int test = 1;
void TC0_Handler(){
	motor_control_pos(INT_PERIOD);	
    TC0->TC_CHANNEL[0].TC_SR;	//Clear interrupt flag
	
}

void TC1_Handler(){
	em_game_ended();
    TC0->TC_CHANNEL[1].TC_SR;	//Clear interrupt flag
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

void timer_pid_clock_start(){
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}
void timer_pid_clock_disable(){
	TC0->TC_CHANNEL[0].TC_CCR = 0b10 | TC_CCR_SWTRG;
}
void timer_game_clock_start(bool replay){
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	if (!replay){
		NVIC_EnableIRQ(TC1_IRQn);
	}
}
uint32_t timer_get_game_clock(){
	return TC0->TC_CHANNEL[1].TC_CV/65625;
}
void timer_game_clock_disable(){
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS | TC_CCR_SWTRG;
	NVIC_DisableIRQ(TC1_IRQn);
}