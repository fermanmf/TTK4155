#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog

    configure_uart();   
	 
    printf("Start\n\r");  

    printf("Terminated\n\r");
}
