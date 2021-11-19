/**
 * @file em.h
 * @brief Event manager (em) module for syncronizing and exchangig events interally and externally. 
 * External events are exchanged with CAN
 */
#pragma once

#include <stdint.h>

/**
 * @brief Event type
 * 
 */
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
	EmBeep,
	EmSnakeStarted,
	EmSnakeEnded
} EmEventType;

/**
 * @brief Joystick direction
 * 
 */
typedef enum {
	emJoystickUp,
	emJoystickDown,
	emJoystickLeft,
	emJoystickRight,
	emJoystickNeutral
} EmJoystickDirection;

/**
 * @brief Event struct. Union can be undefined.
 * 
 */
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

/**
 * @brief Initializes em and CAN
 */
void em_init();

/**
 * @brief Get next event in event queue
 * 
 * @return EmEvent 
 * 
 * @warning Blocks until message is received
 */
EmEvent em_get_event();

/**
 * @brief Emit event (add to internal event queues both internally and externally)
 * 
 * @param type[in] 
 * @param value[in] 
 */
void em_event(EmEventType type, uint8_t value);

/**
 * @brief Emit empty event (add to internal event queues both internally and externally)
 * 
 * @param type[in] 
 */
void em_event_empty(EmEventType type);
