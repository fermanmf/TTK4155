#pragma once

#include <stdbool.h>

void led_init();

typedef enum {
	led_1,
	led_2
} Led;

void led_set(Led led, bool on);