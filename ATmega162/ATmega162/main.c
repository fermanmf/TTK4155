/*
 * ATmega162.c
 *
 * Created: 31.08.2021 10:55:40
 * Author : vetlesr
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "uart.h"
#include "utils.h"

int main()
{
	uart_init(9600);
	init_xmem();
	test_sram();
	
	DDRD |= 1 << 5;
}


