#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "em.h"
#include "timer.h"
#include "dac.h"
#include "motor.h"
#include "panic.h"
#include "em.h"
#include "ir.h"


void ir_print() {
	printf("Hello from IR callback\n\r");
}


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
    configure_uart();
	timer_init();
	dac_init();
	motor_init();
	em_init();
	ir_beam_broken_cb = &ir_print;
	ir_init();
    printf("Start\n\r");
	//printf("%u\n\r", TC0->TC_CHANNEL[0].TC_SR);
	//motor_control_pos(5);
	while(1) {
		 EmEvent event = em_get_event();
		 switch(event.type) {
		 	case EmSliderLeftChanged:
		 		printf("Hello from em slider left %u\n\r", event.slider_left);
		 		pid.ref = event.slider_left;
		 		break;
		 }
		


	}

    printf("Terminated\n\r");
}
