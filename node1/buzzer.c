#include "buzzer.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void buzzer_init(){
    // buzzer pwm
	DDRB = 1 << PINB1; // PB0/OC0 as output 
	OCR2 = 191; //generate 200 hz signal
	TCCR2 = (1 << WGM21) | (1 << COM20) | (1 << CS22); // CRC, toggle on compare match, no prescaling
}