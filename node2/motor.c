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

static int make_pos_signed(int twos_complement){
    if (twos_complement & 1<<15){
        int unsigned_pos = (~twos_complement) + 1;
        return -unsigned_pos;
    }
    int pos = twos_complement;
    return pos;
}
static void set_speed(int value){
    dac_write(value);
}

void motor_init(){
    //Provide clock for input at PIOC
    PMC->PMC_PCER0 |= PMC_PCER0_PID13;
    //TODO: Verify that setting PMC_PCR register is not neccessary.

    // enable I/O D controller and set as output
    PIOD->PIO_PER |= 0b111 | 0b11<<9;
    PIOD->PIO_OER |= 0b111 | 0b11<<9;

    // enable PIOD controller and set as input
    PIOD->PIO_PER |= MOTOR_OUTPUT_MASK;
    PIOD->PIO_IER |= MOTOR_OUTPUT_MASK;
}
void motor_run_open_loop(){
    while (1){
        set_speed(joystick_read());
    }
}
int pos = 0;
int ref = 0;
int deviation = 0;
int prev_deviation = 0;
int period = 0;
int deviation_sum = 0;
int k_p = 1;
int k_i = 0;
int k_d = 1;
int p_actuation = 0;
int i_actuation =0;
int d_actuation = 0;
int actuation = 0;

void motor_control_pos(int interrupt_period){
	printf("motor_control_pos\n\r");
    period = interrupt_period;
    pos = motor_read_encoder();
    ref = 0.5;
    deviation = ref - pos;
    p_actuation = k_p * deviation;
    i_actuation = k_i * period * deviation_sum;
    d_actuation = k_d / period * (deviation - prev_deviation);
    actuation = p_actuation + i_actuation + d_actuation;
    set_speed(actuation);
    prev_deviation = deviation;
}


int motor_read_encoder(){
	PIOD->PIO_SODR = EN;
	 
    PIOD->PIO_CODR = NOT_OE;
    PIOD->PIO_CODR = SEL;
    timer_delay_u(20);
    int msb = (PIOC->PIO_PDSR | MOTOR_OUTPUT_MASK)>>1;
    PIOD->PIO_SODR = SEL;
    timer_delay_u(20);
    int lsb = (PIOC->PIO_PDSR | MOTOR_OUTPUT_MASK)>>1;
    PIOD->PIO_CODR = NOT_RST;
    PIOD->PIO_SODR = NOT_RST;

    return (msb <<8) | lsb;
    //TODO: verify that lsb and msb should be shifted by 1
}