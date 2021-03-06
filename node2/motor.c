#include "motor.h"
#include "dac.h"
#include "sam.h"
#include "timer.h"
#include "printf-stdarg.h"
#include "dac.h"

#include <math.h>


#define NOT_OE PIO_PD0 
#define NOT_RST PIO_PD1
#define SEL PIO_PD2
#define EN  PIO_PD9
#define DIR PIO_PD10
#define MOTOR_OUTPUT_MASK 0x1fe



void set_speed(float speed){
	
	float value = speed/100*0xfff;
	
	if (value >= 0){
		if (value > 0xfff){value = 0xfff;}
		PIOD->PIO_SODR = DIR;
		dac_write_uint(value);
	}
	else{
		value = -value;
		if (value > 0xfff){value = 0xfff;}

		PIOD->PIO_CODR = DIR;
		dac_write_uint(value);
	}
}

void motor_init(){
    //Provide clock for input at PIOC
    PMC->PMC_PCER0 |= PMC_PCER0_PID13;

    // enable I/O D controller and set as output
    PIOD->PIO_PER |= NOT_OE | NOT_RST | SEL | EN |DIR;
    PIOD->PIO_OER |= NOT_OE | NOT_RST | SEL | EN |DIR;

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
    .k_p = 1, 
    .k_i = 3 , 
    .k_d = 0, 
    .deviation_sum = 0, 
    .prev_deviation = 0
};
void motor_control_pos(int interrupt_period){
	
    pid.period = interrupt_period;
    pid.pos = 100*motor_read_encoder()/8820;

    pid.deviation = pid.ref - pid.pos;
    pid.p_actuation = pid.k_p * pid.deviation;
    pid.i_actuation = pid.k_i * pid.period * pid.deviation_sum;
    pid.d_actuation = pid.k_d / pid.period * (pid.deviation - pid.prev_deviation);
    pid.actuation = pid.p_actuation + pid.i_actuation + pid.d_actuation;
	
	set_speed(pid.actuation);
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
    return - (int16_t) ((msb <<8) | lsb); //apparently int16_t is implemented as twos complement so this will do
}