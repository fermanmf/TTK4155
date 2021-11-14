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
	EmReplayStart,
	EmGameStart,
	EmIrBeamBroken
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
		EmJoystickDirection joystick_x_direction;
		EmJoystickDirection joystick_y_direction;
		int8_t joystick_x;
		int8_t joystick_y;
		uint8_t slider_left;
		uint8_t slider_right;
	};
} EmEvent;

void em_init();
EmEvent em_get_event();
void em_can_message_received (uint8_t id, uint8_t data[], uint8_t data_length);

void em_joystick_button_pressed();
void em_joystick_x_direction_changed(EmJoystickDirection direction);
void em_joystick_y_direction_changed(EmJoystickDirection direction);
void em_joystick_x_changed(int8_t value);
void em_joystick_y_changed(int8_t value);
void em_slider_left_changed(uint8_t value);
void em_slider_right_changed(uint8_t value);
void em_replay_start();
void em_game_start();
void em_ir_beam_broken();
