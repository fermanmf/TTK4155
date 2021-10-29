#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_consts.h"
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


void can_init() {
	mcp2515_init(false);
}
	
void can_loopback_init(){
	mcp2515_init(true);
}

void can_send_empty(uint8_t id) {}
	
void can_send(uint8_t id, uint8_t data_length, uint8_t data[]) {}

