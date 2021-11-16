#include "controller.h"

#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#include "adc.h"
#include "em.h"

#define JOYSTICK_DIRECTION_THRESHOLD 10
#define JOYSTICK_CHANGE_THRESHOLD 3
#define SLIDER_CHANGE_THRESHOLD 10

#define JOYSTICK_MIN 1
#define JOYSTICK_MID 145
#define JOYSTICK_MAX 255

static int8_t joystick_raw_convert(uint8_t value) {
	if (value < JOYSTICK_MID) {
		return round(0.694 * value - 100.694);
	} else if (value > JOYSTICK_MID){
		return round(0.91 * value - 131.8);
	} else {
		return 0;
	}
}

static void reading_received_cb(uint8_t joystick_x_raw, uint8_t joystick_y_raw, uint8_t slider_left_raw, uint8_t slider_right_raw) {
	static uint8_t joystick_x_raw_last = 127;
	static uint8_t joystick_y_raw_last = 127;
	static uint8_t slider_left_raw_last = 0;
	static uint8_t slider_right_raw_last = 0;	
	
	if (abs(joystick_x_raw_last - joystick_x_raw) > JOYSTICK_CHANGE_THRESHOLD) {
		const int8_t joystick_x = joystick_raw_convert(joystick_x_raw);
		em_joystick_x_changed(joystick_x);
		
		static EmJoystickDirection last_x_direction = emJoystickNeutral;
		EmJoystickDirection x_direction;
		if (joystick_x < -JOYSTICK_DIRECTION_THRESHOLD) {
			x_direction = emJoystickLeft;
		} else if (joystick_x > JOYSTICK_DIRECTION_THRESHOLD) {
			x_direction = emJoystickRight;
		} else {
			x_direction = emJoystickNeutral;
		}
		if (last_x_direction != x_direction) {
			em_joystick_x_direction_changed(x_direction);
			last_x_direction = x_direction;
		}	
		joystick_x_raw_last = joystick_x_raw;
	}
	
	if (abs(joystick_y_raw_last - joystick_y_raw) > JOYSTICK_CHANGE_THRESHOLD) {
		const int8_t joystick_y = joystick_raw_convert(joystick_y_raw);
		em_joystick_y_changed(joystick_y);
		
		static EmJoystickDirection last_y_direction = emJoystickNeutral;
		EmJoystickDirection y_direction;
		if (joystick_y > JOYSTICK_DIRECTION_THRESHOLD) {
			y_direction = emJoystickUp;
		} else if (joystick_y < -JOYSTICK_DIRECTION_THRESHOLD) {
			y_direction = emJoystickDown;
		} else {
			y_direction = emJoystickNeutral;
		}
		if (last_y_direction != y_direction) {
			em_joystick_y_direction_changed(y_direction);
			last_y_direction = y_direction;
		}
		joystick_y_raw_last = joystick_y_raw;
	}
	
	
	if (abs(slider_left_raw_last - slider_left_raw) > SLIDER_CHANGE_THRESHOLD) {
		em_slider_left_changed(slider_left_raw / 2.55);
		slider_left_raw_last = slider_left_raw;
	}
	
	if (abs(slider_right_raw_last - slider_right_raw) > SLIDER_CHANGE_THRESHOLD) {
		em_slider_right_changed(slider_right_raw / 2.55);
		slider_right_raw_last = slider_right_raw;
	}
}

void controller_init() {
	adc_init(&reading_received_cb);
	
	PORTD |= 1 << PIND3; // With pull-up resistor
	MCUCR |= 1 << ISC11; // Interrupt on falling edge
	GICR |= 1 << INT1; // Enable INT1 (interrupt on pin 1)
}

ISR(INT1_vect) {
	em_joystick_button_pressed();
}
