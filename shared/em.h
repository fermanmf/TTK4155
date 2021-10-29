#pragma once

#include "controller.h"

typedef enum {
	EmJoystickPressed,
	EmJoystickDirectionChanged	
} EmEventType;

typedef struct {
	EmEventType type;
	union {
		ControllerJoystickDirection joystick_direction;
	};
} EmEvent;

EmEvent em_get_event();