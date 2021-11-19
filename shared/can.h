/**
 * @file
 * @brief CAN driver
 */
#pragma once

#include <stdint.h>

/**
 * @brief Initializes driver
 * 
 * @param callback[in] Callback to call when CAN message is received
 */
void can_init(void (*callback)(uint8_t, uint8_t[], uint8_t));

/**
 * @brief Sends empty CAN message 
 * 
 * @param id[in] CAN message id
 */
void can_send_empty(uint8_t id);

/**
 * @brief Sends CAN message
 * 
 * @param id[in] CAN message id
 * @param data[in] CAN message data
 * @param data_length[in] CAN message data length
 */
void can_send(uint8_t id, uint8_t data[], uint8_t data_length);
