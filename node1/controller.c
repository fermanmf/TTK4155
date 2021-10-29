#include "../shared/controller.h"

#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>
#include <math.h>

#include "adc.h"
#include "../shared/can.h"
#include "../shared/em.h"

#define joystick_direction_threshold 10

void controller_init() {
	// must init cotroller values
	
}

void controls_init() {
	adc_init();
	DDRB &= ~1;
	PORTB |= 1;	
}

bool controls_joystick_pressed() {
	return !(PINB & 1);
}

static void adc_read_cb(uint8_t data[4]) {
	data[0] = round(0.0007774 * pow(data[0], 2) + 0.5907 * data[0] - 101.18); // Y
	data[1] = round(0.0007774 * pow(data[1], 2) + 0.5907 * data[1] - 101.18); // X
	data[2] = data[2] * 100 / 255; //slider left
	data[3] = data[3] * 100 / 255; //slider right
	
	can_send(~0, data, 4);
	
	controller_joystick_x = data[0];
	controller_joystick_y = data[1];
	controller_slider_left = data[2];
	controller_slider_right = data[3];
	
	static ControllerJoystickDirection last_x_direction = controllerNeutral;
	ControllerJoystickDirection x_direction;
	if (controller_joystick_x < -joystick_direction_threshold) {
		x_direction = controllerLeft;				
	} else if (controller_joystick_x > joystick_direction_threshold) {
		x_direction = controllerRight;
	} else {
		x_direction = controllerNeutral;
	}
	if (last_x_direction != x_direction) {
		em_joystick_x_direction_changed(x_direction);
		last_x_direction = x_direction;
	}
	
	static ControllerJoystickDirection last_y_direction = controllerNeutral;
	ControllerJoystickDirection y_direction;
	if (controller_joystick_y > joystick_direction_threshold) {
		y_direction = controllerUp;
		} else if (controller_joystick_y < -joystick_direction_threshold) {
		y_direction = controllerDown;
		} else {
		y_direction = controllerNeutral;
	}
	if (last_y_direction != y_direction) {
		em_joystick_y_direction_changed(y_direction);
		last_y_direction = y_direction;
	}
}


void interrupt() {
	adc_read();
}



void adc_read_pretty(int pretty_values[4]) {
	uint8_t values[4];
	adc_read(values);	
}