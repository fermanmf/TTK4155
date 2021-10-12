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
	configure_uart();
	can_init_def_tx_rx_mb(0x1143);

    printf("Hello\n");
}
