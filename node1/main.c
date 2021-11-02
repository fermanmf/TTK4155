#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include "panic.h"
#include "can.h"
#include "mcp2515.h"


void setup(){
	can_loopback_init();	
}

void _main(){
	can_send_empty(0xFF);
	uint8_t id = 0;
	uint8_t data[8];
	uint8_t data_length;
	
	while (id == 0)
	{
		mcp2515_read_rx_buffer(&id, data, &data_length);
	}
	
	printf("%u\n\r", id);
}

int main(){
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // release JTAG pins from external memory address pins
	uart_init(9600);
	
	printf("Setting up\n\r");
	setup();
	printf("Done setting up. Starting main\n\r");
	_main();
	printf("Main is done\n\r");
}

