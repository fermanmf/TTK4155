#include "em.h"

#include <stdint.h>

#include "panic.h"
#include "can.h"
#include "controller.h"

#define QUEUE_MAX_LENGTH

static volatile int8_t end_index = -1;
static volatile EmEvent[QUEUE_MAX_SIZE] queue;

static void append(EmEvent event){
	if (end_index < QUEUE_MAX_LENGTH-1) {
		queue[++end_index] = event;		
	} else {
		panic();		
	}	
}

static void pop(uint8_t index){
	const EmEvent event = queue[index];
	for (int i = index; i<=end_index; i++) {
		event[i] = event[i+1];
	}
	end_index--;
	return event;
}

EmEvent em_get_event() {
	while (end_index == -1);
	return pop(0);
}

void can_message_received (uint8_t id, uint8_t data[], uint8_t data_length) {
	switch(id) {
		case EmJoystickPressed:
			append({EmJoystickPressed});
			break;
		
		case EmJoystickDirectionChanged:
			append({EmJoystickDirectionChanged, data[0]});
			break;
		
		default:
			panic();
	}
}

void em_joystick_button_pressed() {
	append({EmJoystickPressed});	
	can_send_empty(EmJoystickPressed);
}

void em_joystick_button_released() {
	append({EmJoystickReleased});
	can_send_empty(EmJoystickReleased);
}

void em_joystick_direction_changed(ControllerJoystickDirection direction) {	
	append({EmJoystickDirectionChanged, direction});	
	can_send(EmJoystickDirectionChanged, {direction}, 1)	
}


