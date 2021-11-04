#pragma once

#include <stdint.h>

void adc_init();

void (*adc_reading_received_cb)(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4);