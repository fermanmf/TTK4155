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

void em_init() {
	
}

EmEvent em_get_event() {
	while (end_index == -1);
	return pop(0);
}

void em_can_message_received (uint8_t id, uint8_t data[], uint8_t data_length) {
	switch(id) {
		case EmJoystickPressed:
			append({EmJoystickPressed});
			break;
		
		case EmJoystickPressed:
			append({EmJoystickReleased});
			break;
		
		case EmJoystickXDirectionChanged:
			append({EmJoystickXDirectionChanged, data[0]});
			break;
		
		case EmJoystickYDirectionChanged:
			append({EmJoystickYDirectionChanged, data[0]});
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

void em_joystick_x_direction_changed(ControllerJoystickDirection direction) {	
	append({EmJoystickXDirectionChanged, direction});	
	can_send(EmJoystickXDirectionChanged, {direction}, 1)	
}

void em_joystick_y_direction_changed(ControllerJoystickDirection direction) {
	append({EmJoystickYDirectionChanged, direction});
	can_send(EmJoystickYDirectionChanged, {direction}, 1)
}


