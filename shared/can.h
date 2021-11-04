#pragma once

#include <stdint.h>

void can_init();

void can_send_empty(uint8_t id);
void can_send(uint8_t id, uint8_t data[], uint8_t data_length);

void (*can_message_received_cb)(uint8_t id, uint8_t data[], uint8_t data_length);
