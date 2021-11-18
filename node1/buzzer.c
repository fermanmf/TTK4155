#include "buzzer.h"

#include "consts.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU MCK_NODE1
//#include <util/delay.h>
//
//void buzzer_init(){
    //// buzzer pwm
	//DDRB = 0 << PINB1; // disable PB0/OC0 as output 
	//OCR2 = 191; //generate 200 hz signal
	//TCCR2 = (1 << WGM21) | (1 << COM20) | (1 << CS22); // CRC, toggle on compare match, no prescaling
//}
//
//static void disable(){
	//DDRB = 0 << PINB1; // disable PB0/OC0 as output 
//}
//
//static void enable(){
	//DDRB = 1 << PINB1; // enable PB0/OC0 as output
//}
//
//void buzzer_short_buzz(){
	//enable();
	//_delay_ms(100);
	//disable();
//}
//
//void buzzer_long_buzz(){
	//enable();
	//_delay_ms(500);
	//disable();
//}
//
//void buzzer_start_game_buzz(){
	//buzzer_short_buzz();
	//_delay_ms(300);
	//buzzer_short_buzz();
	//_delay_ms(300);
	//buzzer_long_buzz();	
//}