/*
 * ATmega162.c
 *
 * Created: 31.08.2021 10:55:40
 * Author : vetlesr
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

#include "uart.h"
#define F_CPU 4915200
#include "util/delay.h"
#include "utils.h"
#include "adc.h"
#include "display.h"
#include "controls.h"
#include "oled.h"
#include "spi_driver.h"

int main()
{
	uart_init(9600);
	init_xmem();
	mcp

typedef struct {
	char name[16];
	void (*callback)();	
} MenuItem;

void menu(MenuItem items[], int n_items) {	
	for (int i = 0; i<n_items; i++) {
		display_write_line(items[i].name, i);		
	}	
	int i = 0;
	display_invert_line(i);	
		
	while (1) {
		switch (controls_joystick_direction()){
			case up:
				while (controls_joystick_direction() != neutral);
				if (i > 0) {
					display_invert_line(i);
					i--;
					display_invert_line(i);
				}
				break;
			case down:
				while (controls_joystick_direction() != neutral);
				if (i < n_items - 1) {
					display_invert_line(i);
					i++;
					display_invert_line(i);
				}
				break;
			default:
				break;
		}
		if (controls_joystick_pressed()) {
			while(controls_joystick_pressed());
			items[i].callback();			
		}
	}
}

void menu1() {
	printf("test1\n");
}

void menu2() {
	printf("test2\n");
}

void test_menu() {
	MenuItem items[3] = {
		{"test1", menu1},
		{"test2", menu2},
		{"testmenu", test_menu}		
	};
	menu(items, 3);
}


int main(){
	uart_init(9600);
	init_xmem();
	controls_init();
	display_init();
	test_menu();
	
	printf("Terminated\n");
}