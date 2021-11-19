/**
 * @file dac.h
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <stdint.h>
/**
 * @brief initiates the DAC by providing PMC and setting mode registers.
 * 
 */
void dac_init();
/**
 * @brief Writes a value to the dac determining the magnitude of the output voltage.
 * 
 * @param value A value in the range 0 - 0xfff.
 */
void dac_write_uint(uint32_t value);