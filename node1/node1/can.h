#pragma once

#include <stdint.h>

typedef struct {
	uint16_t id;
	uint8_t data_length;
	uint8_t data[8];
} CanMessage;

void can_send(CanMessage* can_message);
void can_init();
void can_loopback_init();
void can_print();