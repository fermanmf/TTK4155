#pragma once

#include <stdint.h>

void timer_init();
void timer_delay_u(uint32_t time_u);
void timer_delay(uint32_t time);

void timer_pid_clock_start();

void timer_pid_clock_disable();

void timer_game_clock_start();

void timer_get_game_clock();