#include "node3.h"

#include "sam.h"
#include "em.h"

#define VALID PIO_PC18 // pin 45
#define COM1 PIO_PC16 // pin 47
#define COM2 PIO_PC14 // pin 49
#define COM3 PIO_PC12 // pin 51

// VALID - COM1 - COM2 - COM3

void node3_init() {
	PIOC->PIO_PER = VALID | COM1 | COM2 | COM3;
	PIOC->PIO_OER = VALID | COM1 | COM2 | COM3;
}
void node3_countdown() {
	PIOC->PIO_CODR = VALID;
	PIOC->PIO_CODR = COM1 | COM2;
	PIOC->PIO_SODR = COM3;
	PIOC->PIO_SODR = VALID;
}


void node3_snake(EmJoystickDirection direction) {
	PIOC->PIO_CODR = VALID;
	switch(direction) {
		case emJoystickUp: // 0b00
			PIOC->PIO_CODR = COM2 | COM3;
			break;
		
		case emJoystickDown: // 0b01
			PIOC->PIO_CODR = COM2;
			PIOC->PIO_SODR = COM3;
			break;
		
		case emJoystickLeft: // 0b10
			PIOC->PIO_SODR = COM2;
			PIOC->PIO_CODR = COM3;
			break;
		
		case emJoystickRight: // 0b11
			PIOC->PIO_SODR = COM2 | COM3;
			break;
		
		default:
			break;
	}
	PIOC->PIO_OER = COM1 | VALID;
}