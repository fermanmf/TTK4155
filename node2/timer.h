#pragma once

#include <stdint.h>

void timer_init();
void timer_delay_u(uint32_t time_u);
void timer_delay(uint32_t time);