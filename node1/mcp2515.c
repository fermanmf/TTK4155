#include "mcp2515.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#include "spi.h"
#include "mcp2515_consts.h"
#include "consts.h"
#include "panic.h"
#include <stdio.h>

#define SS 4

static void slave_select(){
	PORTB &= ~(1<<SS);
}

static void slave_deselect(){
	PORTB |= 1<<SS;
}


#define RXM0 5
#define RXM1 6
#define SJW0 6
#define PHSEG10 3

void mcp2515_init(bool loopback_mode) {
	DDRB |= 1 << SS; // enable slave select as output
	spi_init();
	
	
	mcp2515_reset();
	mcp2515_write(MCP_RXB0CTRL, (1 << RXM0) | (1 << RXM1)); // disable filter
	mcp2515_write(MCP_CNF1, (CAN_SJW << SJW0));
	mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((CAN_PS1 - 1) << PHSEG10) | (CAN_PROPSEG - 1));
	mcp2515_write(MCP_CNF3, CAN_PS2 - 1);
	
	if (loopback_mode) {
		mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);		
	} else {
		mcp2515_write(MCP_CANCTRL, MODE_NORMAL);
	}
	mcp2515_write(MCP_CANINTE, 1); // enable receieve buffer 0 full interrupt
}

void mcp2515_reset(){
	slave_select();
	spi_transmit(MCP_RESET);
	slave_deselect();
}

uint8_t mcp2515_read(uint8_t address){
	slave_select();
	spi_transmit(MCP_READ);
	spi_transmit(address);
	spi_transmit(0);
	slave_deselect();
    return SPDR;
}

void mcp2515_read_rx_buffer(uint8_t *id, uint8_t data[8], uint8_t *data_length) {
	slave_select();
	spi_transmit(MCP_READ_RX0);
	spi_transmit(0); // receive buffer 0 standard identifier high
	spi_transmit(0); // receive buffer 0 standard identifier low
	*id = SPDR;
	spi_transmit(0); // receive buffer 0 extended identifier high
	spi_transmit(0); // receive buffer 0 extended identifier low
	spi_transmit(0); // receive buffer 0 data length code
	*data_length = SPDR & 0b1111;
		
	for (uint8_t i = 0; i<*data_length; i++) {
		spi_transmit(0); // receive buffer 0 data byte
		data[i] = SPDR;
	}	
	slave_deselect();	
}

void mcp2515_write(uint8_t address, uint8_t data){
    slave_select();
    spi_transmit(MCP_WRITE);
    spi_transmit(address);
    spi_transmit(data);
    slave_deselect();
}

void mcp2515_load_tx_buffer(uint8_t id, uint8_t data[8], uint8_t data_length){
	if (data_length > 8) {
		panic();
	}
	slave_select();
	spi_transmit(MCP_LOAD_TX0);
	spi_transmit(id >> 3); // transmit buffer 0 standard identifier high
	spi_transmit(id << 5); // transmit buffer 0 standard identifier low
	spi_transmit(0); // transmit buffer 0 extended identifier high
	spi_transmit(0); // transmit buffer 0 extended identifier low
	spi_transmit(data_length); // transmit buffer 0 data length code
	
	for (uint8_t i = 0; i<data_length; i++) {
		spi_transmit(data[i]); // transmit buffer 0 data byte
	}
	slave_deselect();
}

void mcp2515_load_tx_buffer_empty(uint8_t id) {
	slave_select();
	spi_transmit(MCP_LOAD_TX0);
	spi_transmit(id >> 3); // transmit buffer 0 standard identifier high
	spi_transmit(id << 5); // transmit buffer 0 standard identifier low
	slave_deselect();	
}


void mcp2515_rts(){
    slave_select();
	spi_transmit(MCP_RTS_TX0);
	slave_deselect();
}
