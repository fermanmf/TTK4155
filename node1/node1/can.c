#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_register.h"
#include "mcp2515.h"

#define F_CPU       4915200
#define MSC         16000000
#define BRP         16
#define TQ          2 * BRP / MSC

#define SJW             2
#define PROPSEG         2
#define PH1             5
#define PH2             5

#define REQOP_OFFSET    5


#include "util/delay.h"



void can_send(CanMessage* can_message) {
	mcp2515_write(MCP_TXB0SIDH, can_message->id >> 3);
	mcp2515_write(MCP_TXB0SIDL, (can_message->id & 0b111) << 5);
	mcp2515_write(MCP_TXB0DLC, can_message->data_length);
	mcp2515_load_tx_buffer(can_message->data, can_message->data_length);
	mcp2515_rts();
}

static void _can_init(uint8_t mode) {
	mcp2515_init();
	mcp2515_reset();
	mcp2515_write(MCP_RXB0CTRL, (1 << MCP_RXM0) | (1 << MCP_RXM1)); // disable filter
	mcp2515_write(MCP_CANCTRL, mode); // set operation mode
	mcp2515_write(MCP_CANINTE, 1); // enable receieve buffer 0 full interrupt
}

void can_init() {}
	
void can_loopback_init(){
	_can_init(MODE_LOOPBACK);
}

void can_print() {
	while (!mcp2515_read(MCP_CANINTF)); // wait for full buffer
	
	printf("id: %u\n", (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(MCP_RXB0SIDL) >> 5));
	
	const uint8_t data_length = mcp2515_read(MCP_RXB0DLC);
	printf("data_length : %u\n", data_length);
	
	uint8_t data[8];
	mcp2515_read_rx_buffer(data, data_length);	
	
	for(int i = 0; i < data_length; i++){
		printf("data : %c\n", data[i]);
	}
}