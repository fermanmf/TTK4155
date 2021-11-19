/**
 * @file timer.h
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
/**
 * @brief Initiates the Timer Counters and provides PMC.
 * 
 */
void timer_init();

/**
 * @brief Delays and blocks for @c time_u microseconds
 * 
 * @param time_u 
 */
void timer_delay_u(uint32_t time_u);

/**
 * @brief Delays and blocks for @c time milliseconds .
 * 
 * @param time 
 */

void timer_delay(uint32_t time);

/**
 * @brief starts and resets the pid clock and enables interrupt.
 * 
 */

void timer_pid_clock_start();
/**
 * @brief disables interrupt and stops clock.
 * 
 */
void timer_pid_clock_disable();

/**
 * @brief Starts game clock. With interrupt at 200 s if in game, but not in replay mode.
 * 
 * @param replay Determines whether interrupt at 200 s is necessary.
 */

void timer_game_clock_start(bool replay);
/**
 * @brief disables interrupt and timer clock.
 * 
 */
void timer_game_clock_disable();
/**
 * @brief This function provides game time in desiseconds. That is 1/10 s .
 * 
 * @return uint32_t A value in the range 0 - 2000
 */
uint32_t timer_get_game_clock_dseconds();

/**
 * @brief This function provides game time in seconds.
 * 
 * @return uint32_t A value in range 0-200.
 */

uint32_t timer_get_game_clock_seconds();