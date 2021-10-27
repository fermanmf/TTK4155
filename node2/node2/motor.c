#include "motor.h"
#include "dac.h"
#include "sam.h"

void motor_init(){
    //Provide clock for input at PIOC
    PMC->PMC_PCER0 |= PMC_PCER0_PID13;
    //TODO: Verify that setting PMC_PCR register is not neccessary.

    // enable I/O D controller and set as output
    PIOD->PIO_PER |= 0b111 | 0b11<<9;
    PIOD->PIO_OER |= 0b111 | 0b11<<9;

    // enable PIOD controller and set as input
    PIOD->PIO_PER |= 0x1fe;
    PIOD->PIO_IER |= 0x1fe;

    //dac_init();
}
void motor_run_open_loop(){
    while (1){
        dac_write(joystick_read());
    }
}
void motor_run_closed_loop(){
    while (1){
        unsigned int pos = motor_read_encoder();

        dac_write(joystick_read());
    }
}
#define NOT_OE 0b1
#define NOT_RST 0b10
#define SEL 0b100
#define EN  1<<10
#define DIR 1<<10
#define MOTOR_OUTPUT_MASK 0x1fe

int motor_read_encoder(){
    PIOD->PIO_CODR = NOT_OE;
    PIOD->PIO_CODR = SEL;
    Delay(20);
    int msb = (PIOC->PIO_PDSR | MOTOR_OUTPUT_MASK)>>1;
    PIOD->PIO_SODR = SEL;
    Delay(20);
    int lsb = (PIOC->PIO_PDSR | MOTOR_OUTPUT_MASK)>>1;
    PIOD->PIO_CODR = NOT_RST;
    PIOD->PIO_SODR = NOT_RST;
    return (msb <<8) | lsb;
    //TODO: verify that lsb and msb should be shifted by 1
}