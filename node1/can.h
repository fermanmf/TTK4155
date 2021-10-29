#pragma once

#include <stdint.h>

void can_init();
void can_loopback_init();

void can_send_empty(uint8_t id);
void can_send(uint8_t id, uint8_t data_length, uint8_t data[]);
