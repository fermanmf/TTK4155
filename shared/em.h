#pragma once

#include <stdint.h>

typedef enum {
	EmJoystickPressed,
	EmJoystickXDirectionChanged,
	EmJoystickYDirectionChanged,
	EmJoystickXChanged,
	EmJoystickYChanged,
	EmSliderLeftChanged,
	EmSliderRightChanged,
	EmReplayStarted,
	EmGameStarted,
	EmIrBeamBroken,
	EmGameEnded,
	EmReplayEnded,
	EmBeep
} EmEventType;

typedef enum {
	emJoystickUp,
	emJoystickDown,
	emJoystickLeft,
	emJoystickRight,
	emJoystickNeutral
} EmJoystickDirection;

typedef struct {
	EmEventType type;
	union {
		uint8_t value;
		EmJoystickDirection joystick_x_direction;
		EmJoystickDirection joystick_y_direction;
		int8_t joystick_x;
		int8_t joystick_y;
		uint8_t slider_left;
		uint8_t slider_right;
		uint8_t score; 
	};
} EmEvent;

void em_init();
EmEvent em_get_event();
void em_event(EmEventType type, uint8_t value);
void em_event_empty(EmEventType type);
