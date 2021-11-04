

#include "timer.h"

#include "sam.h"
#include "dac.h"
#include "motor.h"
#include "printf-stdarg.h"
#include <stdint.h>
#define REGISTER_C 657
#define INT_PERIOD REGISTER_C*128/84000000

//waveform mode clock is MCK/128 Period is therefore about 1 ms when RC = 657
void timer_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27;
	
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
    TC0->TC_CHANNEL[0].TC_RC = REGISTER_C; 
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

    NVIC_EnableIRQ(TC0_IRQn);
}
void TC0_Handler(){
	printf("value: %d \n\r",motor_read_encoder());
	//motor_control_pos(INT_PERIOD);
    TC0->TC_CHANNEL[0].TC_SR;
}

void timer_delay_u(uint32_t time_us){
    SysTick->LOAD |= 84*time_us;
	SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick->CTRL & (1<<16)));
}