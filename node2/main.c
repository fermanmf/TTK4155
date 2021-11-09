#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "em.h"
#include "timer.h"
#include "dac.h"
#include "motor.h"
#include "panic.h"
#include "em.h"


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
    printf("Start\n\r");
	//printf("%u\n\r", TC0->TC_CHANNEL[0].TC_SR);
	//motor_control_pos(5);
	while(1) {
		// EmEvent event = em_get_event();
		// switch(event.type) {
		// 	case EmSliderLeftChanged:
		// 		//printf("Hello from em slider left %u\n\r", event.slider_left);
		// 		//pid.ref = (int8_t) event.slider_left;
		// 		break;
		// }
		timer_delay(1);
		pid.ref = pid.ref + 8820/200;

	}

	

    printf("Terminated\n\r");
}
