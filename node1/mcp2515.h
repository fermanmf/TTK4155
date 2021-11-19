/**
 * @file
 * @brief CAN controller driver
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes driver
 * 
 * @param callback Callback to call when new message is received
 */
void mcp2515_init(void (*callback)());

/**
 * @brief Reset intruction
 */
void mcp2515_reset();

/**
 * @brief Read instruction
 * 
 * @param address[in] 
 * @return uint8_t value
 */
uint8_t mcp2515_read(uint8_t address);

/**
 * @brief Read RX buffer instruction
 * 
 * @param id[out] Pointer to store CAN message id
 * @param data[out] Array to store CAN message data
 * @param data_length[out] Pointer to store CAN message data length
 */
void mcp2515_read_rx_buffer(uint8_t *id, uint8_t data[8], uint8_t *data_length);

/**
 * @brief Write instruction
 * 
 * @param address[in] 
 * @param data[in] 
 */
void mcp2515_write(uint8_t address, uint8_t data);

/**
 * @brief Load TX buffer instruction
 * 
 * @param id CAN message id
 * @param data CAN message data
 * @param data_length CAN message data length
 * 
 * @warning Must be followed by @c mcp2515_rts to transmit
 */
void mcp2515_load_tx_buffer(uint8_t id, uint8_t data[8], uint8_t data_length);

/**
 * @brief Load TX buffer insttruction without data
 * 
 * @param id CAN message ID
 * 
 * @warning Must be followed by @c mcp2515_rts to transmit
 */
void mcp2515_load_tx_buffer_empty(uint8_t id);

/**
 * @brief Request to send instruction
 * 
 * @warning Blocks untill TX buffer is emptied/sent 
 */
void mcp2515_rts();
