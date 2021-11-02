#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "panic.h"
#include "can.h"

void setup() {
	can_init();
	
}

void _main() {
	
}

int main(void)
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

