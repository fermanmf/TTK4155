/**
 * @file
 * @brief Communtiaction driver from node2 to node3
 */
#pragma once

#include "em.h"

/**
 * @brief Initializes driver
 * 
 */
void node3_init();

/**
 * @brief Starts countdown on node3 display
 * 
 */
void node3_countdown();

/**
 * @brief Plays snake on node3 display
 * 
 * @param direction Direction of joystick
 */
void node3_snake(EmJoystickDirection direction);