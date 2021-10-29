#pragma once

#include "controller.h"

typedef enum {
	EmJoystickPressed,
	EmJoystickReleased,
	EmJoystickDirectionChanged	
} EmEventType;

typedef struct {
	EmEventType type;
	union {
		ControllerJoystickDirection joystick_direction;
	};
} EmEvent;

EmEvent em_get_event();
void can_message_received (uint8_t id, uint8_t data[], uint8_t data_length);