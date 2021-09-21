#pragma once

#include <stdint.h>

volatile char *oled_segments;
void oled_init();
void oled_update();
void oled_write_char(char c, uint8_t pos, uint8_t line);
void oled_flush();
