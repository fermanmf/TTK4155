
#include "oled.h"

#include <stdbool.h>
#include <stdint.h>

#include "fonts.h"

#include iom162.h

#define SS 4

void SPI_MasterInit(void) {
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

char mcp2515_read(char adress){
    //Set slave select low
    PORTB = 0<<SS;
    SPI_MasterTransmit(0b00000011);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(0);
    PORTB = 1<<SS;
    return SPDR;
}
void mcp2515_write(char adress, char data){
    PORTB = 0<<SS;
    SPI_MasterTransmit(0b00000010);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(data);
    PORTB = 1<<SS;
}
void mcp2515_rts(char txb){
    PORTB = 0<<SS;
    char instruction = 0b10000000|txb;
    SPI_MasterTransmit(instruction);
    PORTB = 1<<SS;
}
char mcp2515_read_status(){
    char instruction = 0b10100000;
    PORTB = 0<<SS;
    SPI_MasterTransmit(instruction);
    SPI_MasterTransmit(0);
    PORTB = 1<<SS;
    return SPDR
}
void mcp2515_bit_modify(char adress, char mask, char data){
    char instruction = 0b00000101
    PORTB = 0<<SS;
    SPI_MasterTransmit(instruction);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(mask);
    SPI_MasterTransmit(data);
    PORTB = 1<<SS;
}
void macp2515_reset(){
    char instruction = 0b11000000
    PORTB = 0<<SS;
    SPI_MasterTransmit(instruction);
    PORTB = 1<<SS;
}