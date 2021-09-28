#pragma once

#include <stdbool.h>

typedef enum {
	up,
	right,
	down,
	left,
	neutral
} ControlsJoytickDirection;

void controls_init();
bool controls_joystick_pressed();
ControlsJoytickDirection controls_joystick_direction();


