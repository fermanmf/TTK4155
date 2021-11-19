/** 
 * @file
 * @brief ADC driver that reads at 10 Hz
 */
#pragma once

#include <stdint.h>

/** 
 * @brief Initialize driver
 * 
 * @param[in] callback Called when ADC has read new values
 */
void adc_init(void (*callback)(uint8_t, uint8_t, uint8_t, uint8_t));