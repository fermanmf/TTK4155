#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "consts.h"

// include other files under this
#include "controller.h"
#include "em.h"


void setup(){
	controller_init();
	em_init();
	sei();
}

void _main(){
	while (1) {
		EmEvent event = em_get_event();
		printf("%d %d\n", event.type, event.slider_left);
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

