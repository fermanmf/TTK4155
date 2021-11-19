#include "adc.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC ((volatile uint8_t*)0x1400)

static void (*reading_received_cb)(uint8_t , uint8_t, uint8_t, uint8_t);

void adc_init(void (*callback)(uint8_t, uint8_t, uint8_t, uint8_t)) {
	reading_received_cb = callback;
	// ADC clock
	DDRB = 1 << PINB0; // PB0/OC0 as output 
	OCR0 = 0; // Output compare register at 0, i.e. ck = MCK/2
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS00); // Fast PWM mode, toggle on compare match, no prescaling
	
	// Timer interrupt
	OCR1A = 480; // Output compare register at 480, i.e. 10 Hz interrupt frequency with prescalar 1024
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, 1024 prescaling
	TIMSK |= 1 << OCIE1A; // Output compare interrupt enable
}

ISR(TIMER1_COMPA_vect) {
	*ADC = 0; // Start conversion
	while (!(PINE & (1 << PINE0))); // While busy
	const uint8_t v1 = *ADC;
	const uint8_t v2 = *ADC;
	const uint8_t v3 = *ADC;
	const uint8_t v4 = *ADC;
	(*reading_received_cb)(v1, v2, v3, v4);
}
