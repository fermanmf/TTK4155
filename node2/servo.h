/**
 * @file
 * @brief Servo driver
 */
#pragma once

/**
 * @brief Initializes driver
 * 
 */
void servo_init();

/**
 * @brief Sets servo value
 * 
 * @param value[in] Servo value between -1 and 1. -1 is full left and 1 is full right
 */
void servo_set(float value);