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
#include "oled.h"
#include "spi_driver.h"

int main()
{
	uart_init(9600);
	init_xmem();
	oled_init();
	oled_flush();
	
	oled_write_char('a', 0, 0);

	
	

	
}


