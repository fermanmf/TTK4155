#include "spi.h"

#include <avr/io.h>
#include <stdint.h>

#define SS 4
#define MOSI 5
#define SCK 7


void spi_init() {
	// Set MOSI, SCK and SS as output
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);
	// Enable SPI, naster and set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void spi_transmit(uint8_t data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

