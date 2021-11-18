#include "mcp2515.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "mcp2515_consts.h"
#include "consts.h"
#include "panic.h"

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
#define TXREQ 3

static void (*message_received_cb)();

void mcp2515_init(void (*callback)()) {
	message_received_cb = callback;
	
	DDRB |= 1 << SS; // enable slave select as output
	spi_init();
	
	// Enable interrupt on PD2
	PORTD |= 1 << PIND2; // With pull-up resistor
	MCUCR |= 1 << ISC01; // Interrupt on falling edge
	GICR |= 1 << INT0; // Enable INT0 (interrupt on pin 0)
	
	mcp2515_reset();
	mcp2515_write(MCP_RXB0CTRL, (1 << RXM0) | (1 << RXM1)); // disable filter
	mcp2515_write(MCP_CNF1, ((CAN_SJW - 1) << SJW0) | (CAN_NODE1_BRP - 1));
	mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((CAN_PS1 - 1) << PHSEG10) | (CAN_PROPSEG - 1));
	mcp2515_write(MCP_CNF3, CAN_PS2 - 1);
	mcp2515_write(MCP_CANCTRL, MODE_NORMAL);	
	mcp2515_write(MCP_CANINTE, MCP_ERRIF | MCP_RX0IF); // enable receive buffer 0 full and error interrupt
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
	const uint8_t id_high = SPDR;
	spi_transmit(0); // receive buffer 0 standard identifier low
	*id = (id_high << 3) | (SPDR >> 5);
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
	spi_transmit(0); // transmit buffer 0 extended identifier high
	spi_transmit(0); // transmit buffer 0 extended identifier low
	spi_transmit(0); // transmit buffer 0 data length code
	slave_deselect();	
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	slave_select();
	spi_transmit(MCP_BITMOD);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	slave_deselect();
}


void mcp2515_rts(){	
    slave_select();
	spi_transmit(MCP_RTS_TX0);
	slave_deselect();
	while (mcp2515_read(MCP_TXB0CTRL) & (1 << TXREQ)); // wait for buffer to not have pending transmission
	
}


ISR(INT0_vect) {
	const uint8_t canintf = mcp2515_read(MCP_CANINTF) & ~(MCP_TX0IF | MCP_MERRF);
	switch(canintf) {
		case MCP_ERRIF:
			printf("mcp2515 error: error flag set. EFLG: 0x%x\n", mcp2515_read(MCP_EFLG));
			mcp2515_bit_modify(MCP_CANINTF, MCP_ERRIF, 0);
			break;
		
		case MCP_RX0IF:
			(*message_received_cb)();
			mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
			break;
		
		default:
			printf("mcp2515 error: unsupported interrupt flag. CANINTF: 0x%x\n", canintf);
			mcp2515_write(MCP_CANINTF, 0);
			break;
	}
}


