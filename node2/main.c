#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "em.h"
#include "timer.h"
#include "dac.h"
#include "motor.h"
#include "panic.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
    configure_uart();
	timer_init();
	dac_init();
	motor_init(); 
    printf("Start\n\r");
	printf("%u\n\r", TC0->TC_CHANNEL[0].TC_SR);
	while(1) {
		
		//EmEvent event = em_get_event();
		//switch (event.type) {
			//case EmJoystickPressed:
				//break;
			//
			//case EmJoystickReleased:
				//break;
			//
			//case EmJoystickXDirectionChanged:
				//break;
			//
			//case EmJoystickYDirectionChanged:
				//break;
			//
			//default:
				//panic();
				//break;
		//}

	}	

    printf("Terminated\n\r");
}
