#pragma once

#include <stdint.h>

void adc_init(void (*callback)(uint8_t, uint8_t, uint8_t, uint8_t));