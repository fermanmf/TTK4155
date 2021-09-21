#pragma once

#include <stdint.h>

void adc_init();
void adc_read(uint8_t values[]);
void adc_read_pretty(int8_t pretty_values[4]);