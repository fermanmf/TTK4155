#include "replay.h"
#include "em.h"
#include <stdbool.h>
#include <stdint.h>
#include "motor.h"
#include "printf-stdarg.h"
#include "timer.h"
#include "solenoid.h"
#define QUEUE_MAX_LENGTH 500


typedef struct {
    uint32_t time;
    EmEvent event;
}Incident;

static int32_t end_index = -1;
static Incident log[QUEUE_MAX_LENGTH] = {};

static void append(Incident incident) {
	if (end_index < QUEUE_MAX_LENGTH-1) {
		log[++end_index] = incident;		
	}
	else{
		printf("replay error: log append error\n\r");
	}
}

void replay_reset_log(){
	end_index = -1;
}

void replay_log_event(EmEvent event){
    Incident incident = {timer_get_game_clock(),event};
    append(incident);
}

void replay_run(){
	timer_game_clock_start();
	uint8_t index = 0;
	while(index <= end_index){
		if (timer_get_game_clock() == log[index].time){
			switch (log[index].event.type){
				case EmSliderLeftChanged:
					pid.ref = log[index].event.slider_left;
					break;
				case emJoystickDown:
					//solenoid_on();
				case EmJoystickYChanged:
					//servo_set(event.joystick_y/100.0);
				default:
					break;
			}
		}
		index++;
	}
	em_replay_end();
}