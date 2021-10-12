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

void adc_read(char values[]) {
	volatile char *adc = (char*) 0x1400;
	adc[0] = 0;
	
	_delay_us(20);	
	for (int i = 0; i<4; i++) {
		values[i] = adc[0];
	}
}

void adc_read_pretty(int pretty_values[4]) {
	char values[4];
	adc_read(values);
	pretty_values[0] = round(0.0007774 * pow(values[0], 2) + 0.5907 * values[0] - 101.18); // Y
	pretty_values[1] = round(0.0007774 * pow(values[1], 2) + 0.5907 * values[1] - 101.18); // X
	pretty_values[2] = values[2] * 100 / 255; //slider left
	pretty_values[3] = values[3] * 100 / 255; //slider right
}