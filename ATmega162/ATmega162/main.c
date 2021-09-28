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
	SPI_MasterInit();
	mcp2515_write(0x41,69);
	printf("%i\n", mcp2515_read(0x41));

	
	

	
}


