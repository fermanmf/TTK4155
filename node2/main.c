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
	while(1) {
		EmEvent event = em_get_event();
		
		
		
	}

    printf("Terminated\n\r");
}
