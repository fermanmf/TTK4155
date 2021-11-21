
#include "eeprom.h"
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include <avr/io.h>

void eeprom_write(uint8_t adress, uint8_t data){

	while(EECR & (1<<EEWE));
	
	EEAR = adress;
	EEDR = data;
	
	cli();
	
	EECR |= (1<<EEMWE);
	
	EECR |= (1<<EEWE);
	
	sei();
}

uint8_t eeprom_read(uint8_t adress){
	  
	while(EECR & (1 << EEWE));
	cli();
	EEAR = adress;
	
	   
	EECR |= (1 << EERE);

	// enable interrupt
	sei();
	   
	return EEDR;
  }




