#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_consts.h"
#include "mcp2515.h"

static void message_received_cb() {
	printf("Hello from can cb\n");
	uint8_t id;
	uint8_t data[8];
	uint8_t data_length;
	mcp2515_read_rx_buffer(&id, data, &data_length);
	(*can_message_received_cb)(id, data, data_length);
}

void can_init() {
	mcp2515_message_received_cb = &message_received_cb;
	mcp2515_init(false);
}
	
void can_loopback_init(){
	mcp2515_message_received_cb = &message_received_cb; 
	mcp2515_init(true);
}

void can_send_empty(uint8_t id) {
	mcp2515_load_tx_buffer_empty(id);
	mcp2515_rts();
}
	
void can_send(uint8_t id, uint8_t data[], uint8_t data_length) {
	mcp2515_load_tx_buffer(id, data, data_length);
	mcp2515_rts();
}
