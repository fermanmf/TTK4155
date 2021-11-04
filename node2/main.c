#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "panic.h"
#include "em.h"

void setup() {
	em_init();	
}

void _main() {
	while(1) {
		EmEvent event = em_get_event()
		switch(event.type) {
			case EmSliderLeftChanged:
				event.slider_left
		}
	}
	
}

int main()
{
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
    configure_uart();
		
	printf("Setting up\n\r");
	setup();
    printf("Done setting up. Starting main\n\r");
	_main();
    printf("Main is done\n\r");
}

