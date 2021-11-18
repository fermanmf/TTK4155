
#include "eeprom.h"
#include "player.h"
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>

void eeprom_write(uint16_t adress, uint8_t data){

	while(EECR & (1<<EEWE));
	
	EEAR = adress;
	EEDR = data;
	
	EECR |= (1<<EEMWE);
	
	EECR |= (1<<EEWE);
}

Score Highscores [6];




