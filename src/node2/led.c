#include "led.h"

#include <stdbool.h>

#include "sam.h"

#define D1 PIO_PA19
#define D2 PIO_PA20

void led_init() {
	PIOA->PIO_PER |= D1 | D2;
	PIOA->PIO_OER |= D1 | D2;
}

void led_set(Led led, bool on) {
	switch (led) {
		case led_1:
			if (on) {
				PIOA->PIO_SODR |= D1;
			} else {
				PIOA->PIO_CODR |= D1;
			}
			break;
		case led_2:
			if (on) {
				PIOA->PIO_SODR |= D2;
				} else {
				PIOA->PIO_CODR |= D2;
			}
			break;
		default:
			break;
	}
}