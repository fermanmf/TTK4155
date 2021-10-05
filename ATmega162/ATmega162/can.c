#include "can.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mcp2515_register.h"
#include "mcp2515.h"



typedef struct {
    uint16_t id;
    char data_length;
    char data[8];
} can_message;

void can_send_message(can_message* message){
    // write id to idH and idL registers
    char idL_address = 0b00110010;
    char idH_address = 0b00110001;
    char idL = message->id & 0b11111111;
    char idH = (message->id & 0xff00) << 8;
    mcp2515_write(idL_address, idL);
    mcp2515_write(idH_address,idH);
    //write to data length register
    char data_length_address = 0b00110101;
    mcp2515_write(data_length_address, message->data_length);
    //write data to data registers 
    char data_address = 0b00110110;
    for (char i = 0;i < 8;i++){
        mcp2515_write(data_address, message->data[0]);
        data_address = data_address + 0b1;
    //tell controller to send message
    char txb0ctrl  = mcp2515_read(MCP_TXB0CTRL);
    char new_txb0ctrl = txb0ctrl | 0b1000;
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

bool can_message_received(){
    char interrupt_flag = mcp2515_read(MCP_CANINTF); 
    return interrupt_flag & 1; 
}

void can_test(){
    can_loopback_init();
    printf("%d\n", can_message_received());
    can_message message = {
		2, 1, "T"
	};
    can_send_message(&message);
    while (1){
        printf("%d\n",can_message_received());
    }
}