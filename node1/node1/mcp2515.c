#include "mcp2515.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#include "spi.h"
#include "mcp2515_register.h"

#define SS 4

static void slave_select(){
	PORTB &= ~(1<<SS);
}

static void slave_deselect(){
	PORTB |= 1<<SS;
}

void mcp2515_init() {
	spi_init();
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

void mcp2515_read_rx_buffer(uint8_t data[8], uint8_t data_length) {
	slave_select();
	spi_transmit(MCP_READ_RX0 | (0b01 << 1));
	for (uint8_t i = 0; i<data_length; i++) {
		spi_transmit(0);
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

void mcp2515_load_tx_buffer(uint8_t data[8], uint8_t data_length){
	slave_select();
	spi_transmit(MCP_LOAD_TX0 | 1);
	for (uint8_t i = 0; i<data_length; i++) {
		spi_transmit(data[i]);
	}
	slave_deselect();
}


void mcp2515_rts(){
    slave_select();
	spi_transmit(MCP_RTS_TX0);
	slave_deselect();
}
