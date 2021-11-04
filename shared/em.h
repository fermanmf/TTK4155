#pragma once

#include <stdint.h>

typedef enum {
	EmJoystickPressed,
	EmJoystickXDirectionChanged,
	EmJoystickYDirectionChanged
} EmEventType;

typedef enum {
	controllerLeft,
	controllerRight,
	controllerUp,
	controllerDown,
	controllerNeutral,
} EmJoystickDirection;

typedef struct {
	EmEventType type;
	union {
		EmJoystickDirection joystick_x_direction;
		EmJoystickDirection joystick_y_direction;
	};
} EmEvent;



void em_init();
EmEvent em_get_event();
void em_can_message_received (uint8_t id, uint8_t data[], uint8_t data_length);
void em_joystick_button_pressed();
void em_joystick_x_direction_changed(EmJoystickDirection direction);
void em_joystick_y_direction_changed(EmJoystickDirection direction);