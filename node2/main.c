#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"

// include other files under this
#include "em.h"


void ir_print() {
	printf("Hello from IR callback\n\r");
}

void setup(){
	em_init();	
}

void _main(){
	while(1) {
		EmEvent event = em_get_event();
		switch(event.type) {
			case EmJoystickPressed:
				printf("em: joystick pressed\n\r");
				break;
			
			case EmJoystickXDirectionChanged:
				printf("em: joystick x direction changed, %u\n\r", event.joystick_x_direction);
				break;
				
			case EmJoystickYDirectionChanged:
				printf("em: joystick y direction changed, %u\n\r", event.joystick_y_direction);
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
			
			default:
				break;
		}
	}	
}

int main(){
	SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
	configure_uart();
	
	printf("Setting up\n\r");
	setup();
	printf("Done setting up. Starting main\n\r");
	_main();
	printf("Main is done\n\r");
	
}