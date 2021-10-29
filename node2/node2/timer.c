//reset counter?

#include "timer.h"

#include "sam.h"
#include "dac.h"
#define REGISTER_C 40
#define INT_PERIOD REGISTER_C*128/84000000

void timer_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27;

    TC0->TC_CHANNEL[0].TC_IMR |= TC_IMR_CPCS;
    TC0->TC_CHANNEL[0].TC_RC = REGISTER_C; 
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE;
    //waveform mode clock is MCK/128 Period is theref

    //enable interrupt
    NVIC_EnableIRQ(TC0_IRQn);
}
void TC0_Handler(){
    motor_control_pos(INT_PERIOD);
}