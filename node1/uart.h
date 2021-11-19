/**
 * @file
 * @brief 
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stdint.h>

void uart_init(unsigned int baud_rate);
void uart_transmit(uint8_t data);
uint8_t uart_recieve();