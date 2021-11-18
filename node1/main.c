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
		
		switch(event.type) {
			/*
			case EmReplayStarted:
				printf("em: replay started\n");
				break;
			
			case EmGameStarted:
				printf("em: game started\n");
				break;
			
			case EmJoystickPressed:
				printf("em: joystick pressed\n");
				break;
			
			case EmJoystickXDirectionChanged:
				printf("em: joystick x direction changed, %u\n", event.joystick_x_direction);
				break;
			
			case EmJoystickYDirectionChanged:
				printf("em: joystick y direction changed, %u\n", event.joystick_y_direction);
				break;
			
			case EmJoystickXChanged:
				printf("em: joystick x changed, %d\n", event.joystick_x);
				break;
			
			case EmJoystickYChanged:
				printf("em: joystick y changed, %d\n", event.joystick_y);
				break;
			
			case EmSliderLeftChanged:
				printf("em: slider left changed, %u\n", event.slider_left);
				break;
			
			case EmSliderRightChanged:
				printf("em: slider right changed, %u\n", event.slider_left);
				break;
			
			case EmIrBeamBroken:
				printf("em: ir beam broken\n");
				break;
			
			case EmGameEnded:
				printf("em: game ended\n");
				break;
			
			case EmReplayEnded:
				printf("em: replay ended\n");
				break;
			*/
			default:
				printf("em: unknown event %d\n", event.type);
				break;
		}
		
		switch (state){
			case(inMenu):
				switch(event.type) {
					case EmReplayStarted:
						state = inReplay;
						break;

					case EmGameStarted:
						state = inGame;
						break;

					case EmJoystickPressed:
						menu_handle_select();
						break;

					case EmJoystickYDirectionChanged:
						if (event.joystick_y_direction == emJoystickDown){
							menu_handle_scroll(true);
						} else if (event.joystick_y_direction == emJoystickUp) {
							menu_handle_scroll(false);
						}
						break;

					default:
						break;
				}
				break;
				

			case(inGame):
				switch (event.type){
					case EmIrBeamBroken:
						player_highscore_update(event.score);
					case EmGameEnded:
						state = inMenu;
						menu_update();
						break;
					
					default:
						break;
				}
				break;

			case(inReplay):
				switch (event.type){
					case EmReplayEnded:
						state = inMenu;
						menu_update();
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
	printf("Setting up\n");
	setup();
	printf("Done setting up. Starting main\n");
	_main();
	printf("Main is done\n");
}

