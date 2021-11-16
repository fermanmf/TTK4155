#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"

// include other files under this
/*
#include "em.h"
#include "servo.h"
#include "ir.h"
#include "solenoid.h"
#include "timer.h"
#include "motor.h"
#include "replay.h"

typedef enum {
	idle,
	inReplay,
	inGame	
} State;
State state = idle;

void setup(){
	em_init();	
	servo_init();
	ir_init(&em_ir_beam_broken);
	solenoid_init();
	//timer_init();
	motor_init();
}

void _main(){
	while(1) {
		EmEvent event = em_get_event();
		switch (state){
			case(idle):
				switch(event.type) {
					case EmReplayStart:
						state = inReplay;
						break;
					case EmGameStart:
						state = inGame;
						break;
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
						servo_set(event.joystick_y / 100.0);
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
				timer_pid_clock_start();
				timer_game_clock_start();
				switch(event.type) {
					case EmJoystickPressed:
						//solenoid_on();
						replay_log_event(event);
						break;
					case EmSliderLeftChanged:
						pid.ref = event.slider_left;
						replay_log_event(event);
						break;
					case EmJoystickYChanged:
						replay_log_event(event);
						break;
					default:
						break;
				}
				if (timer_get_game_clock() >= 200){
					em_game_end();
					timer_pid_clock_disable();
					state = idle;
				}
				break;
			case(inReplay):
				timer_pid_clock_start();
				timer_game_clock_start();
				if (timer_get_game_clock() >= 200){
					em_replay_end();
					timer_pid_clock_disable();
					state = idle;
				}
				break;
			default:
				break;
		}
	}	
}
*/
int main(){
	SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog
	configure_uart();
	
	printf("Setting up\n\r");
	//setup();
	printf("Done setting up. Starting main\n\r");
	//_main();
	printf("Main is done\n\r");
	
}