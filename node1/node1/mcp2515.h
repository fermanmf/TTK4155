#pragma once

char mcp2515_read(char adress);
void mcp2515_write(char adress, char data);
void mcp2515_rts(char txb);
char mcp2515_read_status();
void mcp2515_bit_modify(char adress, char mask, char data);
void mcp2515_reset();