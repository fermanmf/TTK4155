#include "spi_driver.h"

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#define SS 4
#define MOSI 5
#define SCK 7

void SPI_MasterInit() {
  /* Set MOSI and SCK output, all others input */
  DDRB = (1<<MOSI)|(1<<SCK)|(1<<SS);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData) {
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */ 
    while(!(SPSR & (1<<SPIF)));
}

