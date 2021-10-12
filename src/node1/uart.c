#include "uart.h"

#include <avr/io.h>
#include <stdio.h>

// copy from datasheet
void uart_transmit(unsigned char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	
	UDR0 = c;
}

// copy from datasheet
unsigned char uart_recieve() {
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

// copy from datasheet
void uart_init(unsigned int baud_rate) {
	// set baud rate
	unsigned long clock_speed = 4915200;
	unsigned char ubrr = clock_speed / 16 / baud_rate - 1;
	UBRR0H = ubrr >> 8;
	UBRR0L = ubrr;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable transmit and receive
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00); // set frame format: 8 bit data, 2 bit stop
	
	fdevopen(put, get); // sets up printf
}
