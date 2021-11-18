
#include "eeprom.h"
#include "player.h"

void eeprom_write(uint16_t adress, uint8_t data){

	while(EECR & (1<<EEWE));
	
	EEAR = address;
	EEDR = data;
	
	EECR |= (1<<EEMWE);
	
	EECR |= (1<<EEWE);
}

Score Highscores [6];




