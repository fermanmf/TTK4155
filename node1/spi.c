#include "spi.h"

#include <avr/io.h>
#include <stdint.h>

#define MOSI 5
#define SCK 7


void spi_init() {
	DDRB |= (1<<MOSI)|(1<<SCK); // Set MOSI and SCK as outputs
	SPCR = (1<<SPE)|(1<<MSTR); // SPI enable and master
	SPSR = 1 << SPI2X; // f_osc / 2
}

void spi_transmit(uint8_t data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

