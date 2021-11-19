#include "uart.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

#include "consts.h"

void uart_transmit(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

uint8_t uart_recieve() {
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

static int put(char c, FILE * file) {
	uart_transmit(c);
	return 0;
}

static int get(FILE * file) {
	return 0;
}

void uart_init(unsigned int baud_rate) {
	unsigned char ubrr = MCK_NODE1 / 16 / baud_rate - 1;
	UBRR0H = ubrr >> 8;
	UBRR0L = ubrr;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable transmit and receive
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00); // set frame format: 8 bit data, 2 bit stop
	
	fdevopen(put, get);
}
