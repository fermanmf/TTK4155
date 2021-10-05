/*
 * Node2.c
 *
 * Created: 05.10.2021 15:00:46
 * Author : vetlesr
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();

    printf("Hello\n");
}
