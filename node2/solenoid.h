/**
 * @file solenoid.h
 * @brief Solenoid
 * 
 * Setting up timer counter and creating a pulse signal
 */

#pragma once

/**
 * @brief Starts a timer and selecting the width of the pulse signal.
 */
void solenoid_init();

/**
 * @brief Function for sending the pulse signal and push the solenoid
 */
void solenoid_on();