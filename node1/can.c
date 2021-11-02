#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_consts.h"
#include "mcp2515.h"

#define TXB0SIDL 0x32
#define TXB0DLC 0x35


void can_init() {
	mcp2515_init(false);
}
	
void can_loopback_init(){
	mcp2515_init(true);
}

void can_send_empty(uint8_t id) {
	mcp2515_write(TXB0SIDL, id);
	mcp2515_write(TXB0DLC, 0);
	mcp2515_rts();
}
	
void can_send(uint8_t id, uint8_t data[], uint8_t data_length) {
	mcp2515_load_tx_buffer(id, data, data_length);
	mcp2515_rts();
}
