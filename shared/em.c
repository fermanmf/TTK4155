#include "em.h"

#include <stdint.h>
#include <stdio.h>

#include "can.h"

#define QUEUE_MAX_LENGTH 10

static volatile int8_t end_index = -1;
static volatile EmEvent queue[QUEUE_MAX_LENGTH] = {};

static void append(EmEvent event) {
	if (end_index < QUEUE_MAX_LENGTH-1) {
		queue[++end_index] = event;		
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
	can_message_received_cb = &em_can_message_received;
	can_init();	
}

EmEvent em_get_event() {
	while (end_index == -1);
	return pop(0);
}

void em_can_message_received (uint8_t id, uint8_t data[], uint8_t data_length) {
	switch(id) {		
		case EmJoystickPressed: {
			const EmEvent event = {EmJoystickPressed};
			append(event);
			break;
		}
		
		case EmJoystickXDirectionChanged: {
			const EmEvent event = {EmJoystickXDirectionChanged, .joystick_x_direction=data[0]};
			append(event);
			break;
		}
		
		case EmJoystickYDirectionChanged: {
			const EmEvent event = {EmJoystickYDirectionChanged, .joystick_y_direction=data[0]};
			append(event);
			break;
		}
		
		case EmJoystickXChanged: {
			const EmEvent event = {EmJoystickXChanged, .joystick_x=data[0]};
			append(event);
			break;
		}
		
		case EmJoystickYChanged: {
			const EmEvent event = {EmJoystickYChanged, .joystick_y=data[0]};
			append(event);
			break;
		}	

		case EmSliderLeftChanged: {
			const EmEvent event = {EmSliderLeftChanged, .slider_left=data[0]};
			append(event);
			break;
		}
		
		case EmSliderRightChanged: {
			const EmEvent event = {EmSliderRightChanged, .slider_right=data[0]};
			append(event);
			break;
		}
		
		case EmIrBeamBroken: {
			const EmEvent event = {EmIrBeamBroken};
			append(event);
			break;
		}
		
		case EmGameStarted: {
			const EmEvent event = {EmGameStarted};
			append(event);
			break;
		}		
		
		case EmGameEnded: {
			const EmEvent event = {EmGameEnded};
			append(event);
			break;
		}
		
		case EmReplayStarted: {
			const EmEvent event = {EmReplayStarted};
			append(event);
			break;
		}
		
		case EmReplayEnded: {
			const EmEvent event = {EmReplayEnded};
			append(event);
			break;
		}
		
		default:
			break;
	}
}

void em_joystick_button_pressed() {
	const EmEvent event = {EmJoystickPressed};
	append(event);
	can_send_empty(event.type);
}

void em_joystick_x_direction_changed(EmJoystickDirection direction) {
	const EmEvent event = {EmJoystickXDirectionChanged, .joystick_x_direction=direction};
	append(event);
	uint8_t data[1] = {direction};
	can_send(event.type, data, 1);	
}

void em_joystick_y_direction_changed(EmJoystickDirection direction) {
	const EmEvent event = {EmJoystickYDirectionChanged, .joystick_y_direction=direction};
	append(event);
	uint8_t data[1] = {direction};
	can_send(event.type, data, 1);
}

void em_joystick_x_changed(int8_t value) {
	const EmEvent event = {EmJoystickXChanged, .joystick_x=value};
	append(event);
	uint8_t data[1] = {value};
	can_send(event.type, data, 1);
}

void em_joystick_y_changed(int8_t value) {
	const EmEvent event = {EmJoystickYChanged, .joystick_y=value};
	append(event);
	uint8_t data[1] = {value};
	can_send(event.type, data, 1);
}

void em_slider_left_changed(uint8_t value) {
	const EmEvent event = {EmSliderLeftChanged, .slider_left=value};
	append(event);
	uint8_t data[1] = {value};
	can_send(event.type, data, 1);
}

void em_slider_right_changed(uint8_t value) {
	const EmEvent event = {EmSliderRightChanged, .slider_right=value};
	append(event);
	uint8_t data[1] = {value};
	can_send(event.type, data, 1);
}

void em_ir_beam_broken() {
	const EmEvent event = {EmIrBeamBroken};
	append(event);
	can_send_empty(event.type);
}

void em_game_started() {
	const EmEvent event = {EmGameStarted};
	append(event);
	can_send_empty(event.type);
}

void em_game_ended() {
	const EmEvent event = {EmGameEnded};
	append(event);
	can_send_empty(event.type);	
}

void em_replay_started() {
	const EmEvent event = {EmReplayStarted};
	append(event);
	can_send_empty(event.type);
}

void em_replay_ended() {
	const EmEvent event = {EmReplayEnded};
	append(event);
	can_send_empty(event.type);
}