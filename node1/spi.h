/**
 * @file
 * @brief SPI driver 
 */
#pragma once

#include <stdint.h>

/**
 * @brief Initializes driver
 * 
 */
void spi_init();

/**
 * @brief Transmits data. Read @c SPDR to get received data
 * 
 * @param data[in] 
 */
void spi_transmit(uint8_t data);
