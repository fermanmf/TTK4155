#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_consts.h"
#include "mcp2515.h"

static void (*message_read_cb)(uint8_t, uint8_t[], uint8_t);

static void message_received_cb() {
	uint8_t id;
	uint8_t data[8];
	uint8_t data_length;
	mcp2515_read_rx_buffer(&id, data, &data_length);
	(*message_read_cb)(id, data, data_length);
}

void can_init(void (*callback)(uint8_t, uint8_t[], uint8_t)) {
	message_read_cb = callback;
	mcp2515_init(&message_received_cb);
}

void can_send_empty(uint8_t id) {
	mcp2515_load_tx_buffer_empty(id);
	mcp2515_rts();
}
	
void can_send(uint8_t id, uint8_t data[], uint8_t data_length) {
	mcp2515_load_tx_buffer(id, data, data_length);
	mcp2515_rts();
}
