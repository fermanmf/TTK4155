#include "controls.h"

#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>

#include "adc.h"

void controls_init() {
	adc_init();
	DDRB &= ~1;
	PORTB |= 1;	
}

bool controls_joystick_pressed() {
	return !(PINB & 1);
}
ControlsJoytickDirection controls_joystick_direction(){
	int values[4];
	adc_read_pretty(values);
	const int y = values[0];
	
	if (y < -10) {
		return down;
	} else if (y > 10) {
		return up;
	} else {
		return neutral;		
	}	
}