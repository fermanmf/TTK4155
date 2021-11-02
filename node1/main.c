#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include "panic.h"
#include "can.h"
#include "mcp2515.h"
#include "consts.h"
#include "controller.h"

#define F_CPU MCK_NODE1
#include "util/delay.h"


void setup(){
	can_init();	
	controller_init();
}

void _main(){
	while (1){
		uint8_t data[5] = "Hello";
		can_send(0xFE, data, 5);
		_delay_ms(1000);
		can_send_empty(0xFF);
		_delay_ms(1000);
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

