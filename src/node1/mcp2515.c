#include "spi_driver.h"

#include <avr/io.h>

#include <stdbool.h>

#define SS 4

static void reset_set_ss(bool s){
    if (s){
        PORTB &= ~(1<<SS);
    }
    else{
        PORTB |= (1<<SS);
    }
}

char mcp2515_read(char adress){
    //Set slave select low
    reset_set_ss(1);
    SPI_MasterTransmit(0b11);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(0);
    //set ss high
    reset_set_ss(0);
    return SPDR;
}
void mcp2515_write(char adress, char data){
    reset_set_ss(1);
    SPI_MasterTransmit(0b10);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(data);
    reset_set_ss(0);
}
void mcp2515_rts(char txb){
    reset_set_ss(1);
    char instruction = 0b10000000|txb;
    SPI_MasterTransmit(instruction);
    reset_set_ss(0);
}
char mcp2515_read_status(){
    char instruction = 0b10100000;
    reset_set_ss(1);
    SPI_MasterTransmit(instruction);
    SPI_MasterTransmit(0);
    reset_set_ss(0);
    return SPDR;
}
void mcp2515_bit_modify(char adress, char mask, char data){
    char instruction = 0b00000101;
    reset_set_ss(1);
    SPI_MasterTransmit(instruction);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(mask);
    SPI_MasterTransmit(data);
    reset_set_ss(0);
}
void mcp2515_reset(){
    char instruction = 0b11000000;
    reset_set_ss(1);
    SPI_MasterTransmit(instruction);
    reset_set_ss(0);
}