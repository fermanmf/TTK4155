#include "adc.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "consts.h"
#define F_CPU MCK_NODE1
#include "util/delay.h"

#define ADC ((volatile uint8_t*)0x1400)

void adc_init() {
	// ADC clock
	DDRB = 1 << PINB0; // PB0/OC0 as output 
	OCR0 = 0; // Output compare register at 0, i.e. ck = MCK/2
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS00); // fast PWM mode, toggle on compare match, no prescaling
	
	
	// Timer interrupt
	OCR1A = 480; // Output compare register at 480, i.e. 10 Hz interrupt frequency with prescalar 1024
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, 1024 prescaling
	TIMSK |= 1 << OCIE1A; //output compare interrupt enable
}

ISR(TIMER1_COMPA_vect) {
	printf("Hello from TC1\n\r");
	*ADC = 0;	
	_delay_ms(1);
	/*
	while (1) { //!(PORTE & (1 << PINE0))
		printf("%u\n", PORTE);
	}
	*/
	uint8_t v1 = ADC[0];
	uint8_t v2 = *ADC;	
	uint8_t v3 = *ADC;	
	uint8_t v4 = *ADC;	
	(*adc_reading_received_cb)(v1, v2, v3, v4);
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
