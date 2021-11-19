/**
 * @file ir.h
 * @brief IR sensor
 * 
 * Setting up ir sensor
 */

#pragma once

/**
 * @brief IR Contains the value that the ADC writes constantly
 */

volatile unsigned int *IR;

/**
 * @brief Initializing the ADC and starts reading this signal.
 * @param callback Callback to call when ir beam is broken
 */
void ir_init(void (*callback)());