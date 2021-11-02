#pragma once

void uart_init(unsigned int baud_rate);
void uart_transmit(unsigned char c);
unsigned char uart_recieve();