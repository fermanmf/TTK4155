#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	int8_t joystick_x;
	int8_t joystick_y;
	bool joystick_pressed;
	uint8_t slider_left;
	uint8_t slider_right;
} ControllerState;

typedef enum {
	controllerUp,
	controllerRight,
	controllerDown,
	controllerLeft,
	controllerNeutral,
} ControllerJoystickDirection;

ControllerState controller_state;

void controller_init();

typedef struct {
	int8_t joystick_x;
	int8_t joystick_y;
	uint8_t slider_left;
	uint8_t slider_right;
} EmControllerValues;


