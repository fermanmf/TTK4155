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
#include "oled.h"
#include "can.h"
#include "../shared/em.h"



// Send joystick data and slider data continuously in CAN message with id. Send other game data in another CAN message with sepearte id. Different receive buffers on the arduino

int main(){
	uart_init(9600);
	init_xmem();
	adc_init();
	display_init();
	
	can_init();
	

	
	printf("Terminated\n");	
}