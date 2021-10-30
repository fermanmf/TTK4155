#include "../shared/controller.h"

#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>
#include <math.h>

#include "adc.h"
#include "../shared/can.h"
#include "../shared/em.h"

#define JOYSTICK_DIRECTION_THRESHOLD 10

int8_t controller_joystick_x = 0;
int8_t controller_joystick_y = 0;
uint8_t controller_slider_left = 0;
uint8_t controller_slider_right = 0;

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

static void adc_read_cb(uint8_t data[4]) {
	data[0] = round(0.0007774 * pow(data[0], 2) + 0.5907 * data[0] - 101.18);
	data[1] = round(0.0007774 * pow(data[1], 2) + 0.5907 * data[1] - 101.18);
	data[2] = data[2] * 100 / 255;
	data[3] = data[3] * 100 / 255;
	
	can_send(0xFF, data, 4);
	
	controller_joystick_x = data[0];
	controller_joystick_y = data[1];
	controller_slider_left = data[2];
	controller_slider_right = data[3];
	
	static ControllerJoystickDirection last_x_direction = controllerNeutral;
	ControllerJoystickDirection x_direction;
	if (controller_joystick_x < -JOYSTICK_DIRECTION_THRESHOLD) {
		x_direction = controllerLeft;				
	} else if (controller_joystick_x > JOYSTICK_DIRECTION_THRESHOLD) {
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
	if (controller_joystick_y > JOYSTICK_DIRECTION_THRESHOLD) {
		y_direction = controllerUp;
	} else if (controller_joystick_y < -JOYSTICK_DIRECTION_THRESHOLD) {
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
	adc_read(&adc_read_cb);
}
