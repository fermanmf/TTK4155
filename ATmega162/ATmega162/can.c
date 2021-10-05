#include "mcp2515_register.h"
#include "mcp2515.h"
char can_read_interrupt(){
    char interrupt_flag = mcp2515_read(MCP_CANINTF);
    return interrupt_flag;
}

void can_loopback_init(){
    char offset = 5;
    char canctrl = mcp2515_read(MCP_CANCTRL);
    canctrl &= 0b00011111;
    canctrl |= (0b010<<offset);
    mcp2515_write(MCP_CANCTRL,canctrl);
}