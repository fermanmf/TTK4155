#pragma once

#include <stdint.h>

typedef enum {
	controllerLeft,
	controllerRight,
	controllerUp,
	controllerDown,
	controllerNeutral,
} ControllerJoystickDirection;

int8_t controller_joystick_x;
int8_t controller_joystick_y;
uint8_t controller_slider_left;
uint8_t controller_slider_right;

void controller_init();




