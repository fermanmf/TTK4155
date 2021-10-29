#include "controller.h"

#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>

#include "adc.h"

void controller_init() {
	
}

void controls_init() {
	adc_init();
	DDRB &= ~1;
	PORTB |= 1;	
}

bool controls_joystick_pressed() {
	return !(PINB & 1);
}
