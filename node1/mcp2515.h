#pragma once

#include <stdint.h>
#include <stdbool.h>

void mcp2515_init(bool loopback_mode);

void mcp2515_reset();
uint8_t mcp2515_read(uint8_t address);
void mcp2515_read_rx_buffer(uint8_t *id, uint8_t data[8], uint8_t *data_length);
void mcp2515_write(uint8_t address, uint8_t data);
void mcp2515_load_tx_buffer(uint8_t id, uint8_t data[8], uint8_t data_length);
void mcp2515_rts();
