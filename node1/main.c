#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include "shared/panic.h"
#include "shared/em.h"


int main(){
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // release JTAG pins from external memory address pins
	
	uart_init(9600);
	em_init();
	
	while(1) {
		EmEvent event = em_get_event();
		switch (event.type) {
			case EmJoystickPressed: 
				break;
				
			case EmJoystickReleased:
				break;
				
			case EmJoystickXDirectionChanged:
				break;
				
			case EmJoystickYDirectionChanged:
				break;
			
			default:
				panic();
				break;
		}
	}	
	printf("Terminated\n");	
}
