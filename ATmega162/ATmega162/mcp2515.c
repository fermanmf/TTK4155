#include "spi_driver.h"
#include <avr/io.h>

char mcp2515_read(char adress){
    //Set slave select low
    PORTB = 0<<SS;
    SPI_MasterTransmit(0b11);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(0);
    PORTB = 1<<SS;
    return SPDR;
}
void mcp2515_write(char adress, char data){
    PORTB = 0<<SS;
    SPI_MasterTransmit(0b10);
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
    return SPDR;
}
void mcp2515_bit_modify(char adress, char mask, char data){
    char instruction = 0b00000101;
    PORTB = 0<<SS;
    SPI_MasterTransmit(instruction);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(mask);
    SPI_MasterTransmit(data);
    PORTB = 1<<SS;
}
void mcp2515_reset(){
    char instruction = 0b11000000;
    PORTB = 0<<SS;
    SPI_MasterTransmit(instruction);
    PORTB = 1<<SS;
}