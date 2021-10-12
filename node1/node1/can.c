#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_register.h"
#include "mcp2515.h"

#define F_CPU       4915200
#define MSC         1/16000000
#define BRP         0
#define TQ          2 * BRP / MSC

#define SJW             2
#define PROPSEG         2
#define PH1             5
#define PH2             4

#define REQOP_OFFSET    5


#include "util/delay.h"


#define RXB0DLC 0b01100101
#define RXB0D0 0b01100110

typedef struct {
    uint16_t id;
    char data_length;
    char data[8];
} can_message;

void can_send_message(can_message* message){
    // write id to idH and idL registers
    char idL_address = 0b00110010;
    char idH_address = 0b00110001;
    char idL = (message->id & 0b111) << 5;
    char idH = message->id >> 3;
    mcp2515_write(idL_address, idL);
    mcp2515_write(idH_address,idH);
    //write to data length register
    char data_length_address = 0b00110101;
    mcp2515_write(data_length_address, message->data_length);
    //write data to data registers 
    char data_address = 0b00110110;
    for (char i = 0;i < 8;i++){
        mcp2515_write(data_address, message->data[i]);
        data_address = data_address + 1;
    //tell controller to send message
    char txb0ctrl  = mcp2515_read(MCP_TXB0CTRL);
	mcp2515_write(MCP_TXB0CTRL, txb0ctrl | 1 << 3);
    }
}

void can_loopback_init(){
    // set can_controllerer in loopback mode
    char offset = 5;
    char canctrl = mcp2515_read(MCP_CANCTRL);
    canctrl &= 0b00011111;
    canctrl |= (0b010<<offset);
    mcp2515_write(MCP_CANCTRL,canctrl);

    //enable interrupt on full receive buffer
    mcp2515_write(MCP_CANINTE,1);
}
void can_normal_init(){
    //set can_controller in configuration mode
    char canctrl = mcp2515_read(MCP_CANCTRL);
    canctrl &= 0b00011111;
    canctrl |= 100 << REQOP_OFFSET;
    mcp2515_write(MCP_CANCTRL,canctrl);

    //set NBT values
    char cnf1 = (BRP - 1) || (SJW - 1)<<6;
    mcp2515_write(MCP_CNF1,cnf1);
    char cnf2 = (PROPSEG - 1) || (PH1 - 1)<<3;
    //TODO: consider setting cnf3

    // set can_controllerer in normal mode
    char canctrl = mcp2515_read(MCP_CANCTRL);
    canctrl &= 0b00011111;
    mcp2515_write(MCP_CANCTRL,canctrl);

    //enable interrupt on full receive buffer
    mcp2515_write(MCP_CANINTE,1);
}

bool can_message_received(){
    char interrupt_flag = mcp2515_read(MCP_CANINTF); 
    return interrupt_flag & 1; 
}
void can_read_message(){
    char idH_shifted = (mcp2515_read(MCP_RXB0SIDH) << 3);
    char idL = mcp2515_read(MCP_RXB0SIDH + 1)>>5;
	printf("%u %u\n", mcp2515_read(MCP_RXB0SIDH), mcp2515_read(MCP_RXB0SIDH + 1));
    can_message message;
    message.id = idH_shifted | idL;
    message.data_length = mcp2515_read(RXB0DLC);
    for(int i = 0;i < 8;i++){
        message.data[i] = mcp2515_read(RXB0D0 + i);
    }
    printf("id: %u\n", message.id);
    printf("data_length : %u\n", message.data_length);
    for(int i = 0;i < 8;i++){
        printf("data : %c\n", message.data[i]);
    }
}

void can_test(){
    can_normal_init();
    printf("first %d\n", can_message_received());
    can_message message = {
		2, 1, "T"
	};
	while (1) {
		can_send_message(&message);
		_delay_ms(50);
	}
    
	
    printf("%d\n",can_message_received());
    can_read_message();
}