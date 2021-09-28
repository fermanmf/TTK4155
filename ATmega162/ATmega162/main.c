/*
 * ATmega162.c
 *
 * Created: 31.08.2021 10:55:40
 * Author : vetlesr
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

#include "uart.h"
#define F_CPU 4915200
#include "util/delay.h"
#include "utils.h"
#include "adc.h"
#include "display.h"



int main()
{
	uart_init(9600);
	init_xmem();
	
	display_init();
	display_write_line("HelloHelloHelloHello", 0);
	display_write_line("HelloHelloHelloHello", 2);
	
	printf("Terminated\n");
}