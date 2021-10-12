#pragma once

#include <stdint.h>

void adc_init();
void adc_read(char values[]);
void adc_read_pretty(int pretty_values[4]);