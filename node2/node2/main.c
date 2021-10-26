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

#include "servo_driver.h"


int main(void)
{
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;
	configure_uart();

	setup_servo(84000000);


	can_init_def_tx_rx_mb(0x1143);
	
	CAN_MESSAGE msg1;
	CAN_MESSAGE msg2;

	while (can_receive(&msg1, 1) && can_receive(&msg2, 2))
	{
		printf("In loop\n\r");
		
	}
	printf("Before\n\r");
	
	printf(msg1.data);
	printf(msg2.data);
	

    printf("Terminated\n\r");
}
