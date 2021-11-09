#pragma once
#include <stdint.h>

void dac_test(float value);
void dac_write(float value);
void dac_init();
void dac_write_uint(uint32_t value);