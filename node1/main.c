#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "consts.h"

// include other files under this

#include "adc.h"


#define F_CPU MCK_NODE1
#include "util/delay.h"

void print_adc(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4) {
	printf("%u %u %u %u\n\r", v1, v2, v3, v4);
}


void setup(){
	adc_reading_received_cb = &print_adc;
	adc_init();
	sei();
}

void _main(){
	while (1) {
		printf("Hello from main\n\r");
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

