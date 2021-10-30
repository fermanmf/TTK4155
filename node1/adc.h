#pragma once

#include <stdint.h>

void adc_init();
void adc_read(void (*callback)(uint8_t[4]));