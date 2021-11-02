#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include "panic.h"
#include "can.h"


void setup(){
	can_init();	
}

void _main(){
	can_send_empty(0xFF);
	
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

