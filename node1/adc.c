#include "adc.h"

#include <stdint.h>
#include <avr/io.h>
#include <math.h>

#define F_CPU 4915200
#include "util/delay.h"

void adc_init() {
	DDRD |= 1 << DDD5; //PD5 as output
	TCCR1B |= 1 << WGM12; // CTC with output compare
	TCCR1B |= 1 << CS10; //clock select (internal clock)
	OCR1AL = 3; // needs documenting
	TCCR1A |= 1 << COM1A0; //toggle output
	TIMSK |= 1 << OCIE1A; //output compare interrupt enable
}

/*
void adc_read(void (*callback)(uint8_t[4])) {
	volatile uint8_t *adc = (uint8_t*) 0x1400;
	adc[0] = 0;
	
	_delay_us(20);	
	for (int i = 0; i<4; i++) {
		data[i] = adc[0];
	}
}
*/
