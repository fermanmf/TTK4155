#include "motor.h"
#include "dac.h"
#include "sam.h"
#include "timer.h"

#define NOT_OE 0b1
#define NOT_RST 0b10
#define SEL 0b100
#define EN  1<<9
#define DIR 1<<10
#define MOTOR_OUTPUT_MASK 0x1fe

static void set_speed(float value){
    dac_write(value);
}

void motor_init(){
    //Provide clock for input at PIOC
	//PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | 13;
    PMC->PMC_PCER0 |= PMC_PCER0_PID13;
    //TODO: Verify that setting PMC_PCR register is not neccessary.

    // enable I/O D controller and set as output
    PIOD->PIO_PER |= 0b111 | 0b11<<9;
    PIOD->PIO_OER |= 0b111 | 0b11<<9;

    // enable PIOD controller and set as input
    PIOD->PIO_PER |= MOTOR_OUTPUT_MASK;
    PIOD->PIO_IER |= MOTOR_OUTPUT_MASK;

    //enable motor
    PIOD->PIO_SODR = EN;
	
	//set dir 
	PIOD->PIO_CODR = DIR;
	
    //Reset encoder register
    PIOD->PIO_CODR = NOT_RST;
	timer_delay_u(5);
    PIOD->PIO_SODR = NOT_RST;
}
struct controlVariables pid = {
    .pos = 0, 
    .ref = 0,
    .k_p = 3, 
    .k_i = 1 , 
    .k_d = 0, 
    .deviation_sum = 0, 
    .prev_deviation = 0
};
void motor_control_pos(int interrupt_period){
    pid.period = interrupt_period;
    pid.pos = motor_read_encoder()/8820*100;
    pid.ref = 100;
    pid.deviation = pid.ref - pid.pos;
    pid.p_actuation = pid.k_p * pid.deviation;
    pid.i_actuation = pid.k_i * pid.period * pid.deviation_sum;
    pid.d_actuation = pid.k_d / pid.period * (pid.deviation - pid.prev_deviation);
    pid.actuation = pid.p_actuation + pid.i_actuation + pid.d_actuation;
	if (pid.actuation >= 0){
		PIOD->PIO_CODR = DIR;
		set_speed(pid.actuation);
	}
	else{
		PIOD->PIO_SODR = DIR;
		set_speed(pid.actuation);
	}
    pid.prev_deviation = pid.deviation;
    pid.deviation_sum += pid.deviation;
}


int motor_read_encoder(){
    PIOD->PIO_CODR = NOT_OE;
    PIOD->PIO_CODR = SEL;
    timer_delay_u(20);
    uint32_t msb = (PIOC->PIO_PDSR & MOTOR_OUTPUT_MASK)>>1;
    PIOD->PIO_SODR = SEL;
    timer_delay_u(20);
    uint32_t lsb = (PIOC->PIO_PDSR & MOTOR_OUTPUT_MASK)>>1;
    return (int16_t) ((msb <<8) | lsb); //apparently int16_t is implemented as twos complement so this will do
}