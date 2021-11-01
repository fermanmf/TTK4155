#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "em.h"
#include "panic.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
    configure_uart();
	   	 
    printf("Start\n\r");  
	while(1) {
		EmEvent event = em_get_event();
		switch (event.type) {
			case EmJoystickPressed:
				break;
			
			case EmJoystickReleased:
				break;
			
			case EmJoystickXDirectionChanged:
				break;
			
			case EmJoystickYDirectionChanged:
				break;
			
			default:
				panic();
				break;
		}
	}	

    printf("Terminated\n\r");
}
