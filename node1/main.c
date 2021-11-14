#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "consts.h"

// include other files under this
#include "controller.h"
#include "em.h"
#include "display.h"
#include "menu.h"


void setup(){
	controller_init();
	em_init();
	display_init();
	sei();
	menu_init();
}

typedef enum {
	inMenu,
	inReplay,
	inGame	
} State;

int main(){
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // release JTAG pins from external memory address pins
	uart_init(9600);
	State state = inMenu;
	printf("Setting up\n\r");
	setup();
	printf("Done setting up. Starting main\n\r");
	printf("Main is done\n\r");
	while(1){
		EmEvent event = em_get_event();
		
		switch (state){

			case(inMenu):
				switch(event.type) {
					case EmReplayStart:
						state = inReplay;
						break;
					case EmGameStart:
						state = inGame;
						break;
					case EmJoystickPressed:
						menu_handle_select();
						break;
					case EmJoystickXDirectionChanged:
						if (event.joystick_x_direction<2){
							menu_handle_scroll(event.joystick_x_direction);	
						}
						break;
					default:
						break;
				}
			///*
			//case(inGame):
				////enable pid-interrupt
				////enable motor
				//switch (event.type){
				//case /* constant-expression */:
					///* code */
					//break;
				//
				//default:
					//break;
				//}
//
			//case(inReplay):
				////enable pid-interrupt
				////enable motor
				//switch (event.type){
				//case /* constant-expression */:
					///* code */
					//break;
				//
				//default:
					//break;
					//
				//}
				//
			default:
				break;
		}
	}
}

