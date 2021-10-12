/*
 * Node2.c
 *
 * Created: 05.10.2021 15:00:46
 * Author : vetlesr
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"


int main(void)
{
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;
	configure_uart();
	printf("Start\n\r");
	can_init_def_tx_rx_mb(0x00541144);
	
	CAN_MESSAGE msg1;
	CAN_MESSAGE msg2;
	printf("Start\n\r");

	while (can_receive(&msg1, 1) && can_receive(&msg2, 2))
	{
		printf("In loop\n\r");
		printf(msg1.data);
		printf(msg2.data);
		
	}
	printf("Before\n\r");
	
	printf(msg1.data);
	printf(msg2.data);
	

    printf("Terminated\n\r");
}
