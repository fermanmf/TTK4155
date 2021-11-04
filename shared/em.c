#include "em.h"

#include <stdint.h>

#include "panic.h"
#include "can.h"
#include "controller.h"

#define QUEUE_MAX_LENGTH

static volatile int8_t end_index = -1;
static volatile EmEvent queue[QUEUE_MAX_LENGTH] = {};

static void append(EmEvent event){
	if (end_index < QUEUE_MAX_LENGTH-1) {
		queue[++end_index] = event;		
	} else {
		panic();		
	}	
}

static EmEvent pop(uint8_t index){
	const EmEvent event = queue[index];
	for (int i = index; i<=end_index; i++) {
		queue[i] = queue[i+1];
	}
	end_index--;
	return event;
}

void em_init() {
	
}

EmEvent em_get_event() {
	while (end_index == -1);
	return pop(0);
}

void em_can_message_received (uint8_t id, uint8_t data[], uint8_t data_length) {
	switch(id) {
		case EmJoystickPressed:
			append((EmEvent){EmJoystickPressed});
			break;
		
		case EmJoystickXDirectionChanged:
			append((EmEvent){EmJoystickXDirectionChanged, data[0]});
			break;
		
		case EmJoystickYDirectionChanged:
			append((EmEvent){EmJoystickYDirectionChanged, data[0]});
			break;
		
		default:
			panic();
	}
}

void em_joystick_button_pressed() {
	append((EmEvent){EmJoystickPressed});	
	can_send_empty(EmJoystickPressed);
}

void em_joystick_x_direction_changed(ControllerJoystickDirection direction) {	
	append((EmEvent){EmJoystickXDirectionChanged, direction});	
	can_send(EmJoystickXDirectionChanged, (uint8_t[]){direction}, 1);	
}

void em_joystick_y_direction_changed(ControllerJoystickDirection direction) {
	append((EmEvent){EmJoystickYDirectionChanged, direction});
	can_send(EmJoystickYDirectionChanged, (uint8_t[]){direction}, 1);
}


