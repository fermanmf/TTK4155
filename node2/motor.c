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

static int make_pos_signed(uint32_t twos_complement){
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
    //Reset encoder register
    PIOD->PIO_CODR = NOT_RST;
    PIOD->PIO_SODR = NOT_RST;
}
void motor_run_open_loop(){
    while (1){
        set_speed(joystick_read());
    }
}
struct controlVariables pid = {
    .pos = 0, 
    .ref = 0,
    .k_p = 3, 
    .k_i = 1 , 
    .k_d = 1, 
    .deviation_sum = 0, 
    .prev_deviation = 0
};
void motor_control_pos(int interrupt_period){
    pid.period = interrupt_period;
    pid.pos = motor_read_encoder();
    pid.ref = pid.pos + 0.1;
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
    //PIOD->PIO_CODR = NOT_RST;
    PIOD->PIO_SODR = NOT_RST;
    printf("lsb: %x msb: %x\n\r", lsb, msb);
    uint32_t twos_complement_pos  = (msb <<8) | lsb;
    int signed_pos = make_pos_signed((msb <<8) | lsb);
    //printf("twos complement: %d signed int: %d\n\r", twos_complement_pos, signed_pos);
    return make_pos_signed((msb <<8) | lsb);
}