#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "em.h"
#include "timer.h"
#include "dac.h"
#include "motor.h"
#include "panic.h"
#include "em.h"
#include "consts.h"
#include "menu.h"


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
	typedef enum {
		inMenu
	}State;
	State state = menu;
	while(1) {
		EmEvent event = em_get_event();
		
		
		switch (state){
			case(setup):
				switch(event.type) {
					case EmSliderLeftChanged:
					//printf("Hello from em slider left %u\n\r", event.slider_left);
					pid.ref = (int8_t) event.slider_left;
				break;
		}
				break;
			case(inMenu):
				menu();
				break;
			case(highScore):
				break;
			case(characterSelect):
				break;
			case(inGame):
				break;
			case(endOfGame):
				break;
			case(replay):
				break;
			default:
				break;
		}
	}

	

    printf("Terminated\n\r");
}
