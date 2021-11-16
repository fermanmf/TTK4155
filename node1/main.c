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
	menu_init();
	sei();
}

typedef enum {
	inMenu,
	inReplay,
	inGame
} State;

void _main() {
	State state = inMenu;
	while(1){
		EmEvent event = em_get_event();
		
		switch (state){

			case(inMenu):
			switch(event.type) {
				case EmReplayStart:
				state = inReplay;
				break;
				case EmGameStart:
				printf("started game from menu\n");
				state = inGame;
				break;
				case EmJoystickPressed:
				menu_handle_select();
				printf("em: joystick pressed\n\r");
				break;
				case EmJoystickYDirectionChanged:
				printf("em: joystick y direction changed, %u\n\r", event.joystick_y_direction);
				if (event.joystick_y_direction == emJoystickDown){
					menu_handle_scroll(true);
				}
				else if (event.joystick_y_direction == emJoystickUp) {
					menu_handle_scroll(false);
				}
				break;
				case EmJoystickXDirectionChanged:
				printf("em: joystick x direction changed, %u\n\r", event.joystick_x_direction);
				break;
				
				case EmJoystickXChanged:
				printf("em: joystick x changed, %d\n\r", event.joystick_x);
				break;
				
				case EmJoystickYChanged:
				printf("em: joystick y changed, %d\n\r", event.joystick_y);
				break;
				
				case EmSliderLeftChanged:
				printf("em: slider left changed, %u\n\r", event.slider_left);
				break;
				
				case EmSliderRightChanged:
				printf("em: slider right changed, %u\n\r", event.slider_left);
				break;
				
				case EmIrBeamBroken:
				printf("em: ir beam broken\n\r");
				break;
				default:
				break;
			}
			break;

			case(inGame):
			switch (event.type){
				case EmGameEnd:
				state = inMenu;
				break;
				
				default:
				break;
			}
			break;

			case(inReplay):
			switch (event.type){
				case EmReplayEnd:
				state = inMenu;
				break;
				
				default:
				break;
			}
			break;
			default:
			break;
		}
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

