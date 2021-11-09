#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "consts.h"

// include other files under this
#include "controller.h"
#include "em.h"
#include "display.h"


void setup(){
	controller_init();
	em_init();
	display_init();
	sei();
}



int main(){
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // release JTAG pins from external memory address pins
	uart_init(9600);
	
	printf("Setting up\n\r");
	setup();
	printf("Done setting up. Starting main\n\r");
	printf("Main is done\n\r");
	menu();	
	
	//switch (state){
			//case(0):
				//break;
			//case(mainMenu):
				//display_menu(MainMenu);
				//break;
			//case(highScore):
				//display_menu(HighscoreMenu);
				//break;
			//case(characterSelect):
				//display_menu(CharacterMenu);
				//break;
			//case(inGame):
				////display_menu());
				//break;
			//case(endOfGame):
				//display_menu(EndMenu);
				//break;
			//case(replay):
				//break;
		//}
}

