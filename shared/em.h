#pragma once

#include "controller.h"

typedef enum {
	EmJoystickPressed,
	EmJoystickReleased,
	EmJoystickXDirectionChanged,
	EmJoystickYDirectionChanged
} EmEventType;

typedef struct {
	EmEventType type;
	union {
		ControllerJoystickDirection joystick_direction;
	};
} EmEvent;

void em_init();
EmEvent em_get_event();
void em_can_message_received (uint8_t id, uint8_t data[], uint8_t data_length);
void em_joystick_button_pressed();
void em_joystick_button_released();
void em_joystick_x_direction_changed(ControllerJoystickDirection direction);
void em_joystick_y_direction_changed(ControllerJoystickDirection direction);