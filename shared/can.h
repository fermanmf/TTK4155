#pragma once

#include <stdint.h>

void can_init(void (*callback)(uint8_t, uint8_t[], uint8_t));

void can_send_empty(uint8_t id);
void can_send(uint8_t id, uint8_t data[], uint8_t data_length);
