#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"

// include other files under this
#include "em.h"


void ir_print() {
	printf("Hello from IR callback\n\r");
}

void setup(){
	em_init();	
}

void _main(){
	while(1) {
		EmEvent event = em_get_event();
		printf("Got event %u\n\r", event.type);
		switch(event.type) {
			case EmJoystickXChanged:
				break;
			
			default:
				break;
		}
	}	
}

int main(){
	SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
	configure_uart();
	
	printf("Setting up\n\r");
	setup();
	printf("Done setting up. Starting main\n\r");
	_main();
	printf("Main is done\n\r");
	
}