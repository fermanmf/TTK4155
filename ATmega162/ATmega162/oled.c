#include "oled.h"

#include <stdbool.h>
#include <stdio.h>

#define COMMAND ((volatile char*)0x1000)
#define DATA ((volatile char*)0x1200)

volatile char *oled_segments = (char*)0x1800;

static void set_display_on_off(bool on) {
	*COMMAND = 0xAE + on;
}

typedef enum {
	horizontal,
	vertical,
	page
} MemoryAdressingMode;

static void set_memory_addressing_mode(MemoryAdressingMode mam) {
	*COMMAND = 0x20;
	*COMMAND = mam;
}

static void set_column_address(char from, char to) {
	*COMMAND = 0x21;
	*COMMAND = from;
	*COMMAND = to;	
}

static void set_page_address(char from, char to) {
	*COMMAND = 0x22;
	*COMMAND = from;
	*COMMAND = to;
}

static void entire_display_on(bool on) {
	*COMMAND = 0xA4 + on;
}

static void init_oled_segments() {	
	for (int i = 0; i<1024; i++) {
		oled_segments[i] = 0;
	}	
}

void oled_init() {
	*COMMAND = 0xA1;
	*COMMAND = 0xC8;	
	set_memory_addressing_mode(horizontal);
	set_column_address(0, 127);
	set_page_address(0, 7);	
	
	init_oled_segments();
	oled_update();
	set_display_on_off(true);
}

void oled_update() {
	set_column_address(0, 127);
	set_page_address(0, 7);	
	for (int i = 0; i<1024; i++) {
		*DATA = oled_segments[i];
	}
}