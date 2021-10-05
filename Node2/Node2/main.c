/*
 * Node2.c
 *
 * Created: 05.10.2021 09:30:19
 * Author : vetlesr
 */

#include "sam.h"
#include "led.h"
#include "uart.h"
#include "printf-stdarg.h"


int main(void)
{
    SystemInit();
	configure_uart();
	
	led_init();
	led_set(led_1, true);
	
	printf("Test\n");
}
