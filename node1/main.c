#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include "panic.h"
#include "can.h"
#include "mcp2515.h"
#include "mcp2515_consts.h"


void setup(){
	can_loopback_init();	
}

void _main(){
	can_send_empty(0xFF);
	
	while (!mcp2515_read(MCP_CANINTF)); // wait for full buffer
	
	printf("id: %u\n", (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(0x62) >> 5));
	
	const uint8_t data_length = mcp2515_read(0x65);
	printf("data_length : %u\n", data_length);
	
	uint8_t data[8];
	mcp2515_read_rx_buffer(data, data_length);
	
	for(int i = 0; i < data_length; i++){
		printf("data : %c\n", data[i]);
	}
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

