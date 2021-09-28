#include "oled.h"

#include <stdbool.h>
#include <stdint.h>

#include "fonts.h"

static volatile char *COMMAND;
static volatile char *DATA;

static void call_command(char command) {
	COMMAND[0] = command;
}

static void set_display_on_off(bool on) {
	call_command(0xAE + on);
}

typedef enum {
	horizontal,
	vertical,
	page
} MemoryAdressingMode;

static void set_memory_addressing_mode(MemoryAdressingMode mam) {
	call_command(0x20);
	call_command(mam);
}

static void set_column_address(uint8_t from, uint8_t to) {
	call_command(0x21);
	call_command(from);
	call_command(to);	
}

void oled_init() {
	COMMAND = (char*) 0x1000;
	DATA = (char*) 0x1200;
	oled_segments = (char*)0x1800;
	
	set_display_on_off(true);
	set_memory_addressing_mode(horizontal);
	set_column_address(0, 127);
}

void oled_update() {
	for (int i = 0; i<1024; i++) {
		DATA[0] = oled_segments[i];
	}
}

void oled_write_char(char c, uint8_t pos, uint8_t line) {
	const uint8_t offset = 128 * line + 8 * pos;
	for (int i = 0; i<8; i++) {
		oled_segments[offset+i] = font8[c - 31][i];
	}
}

void oled_flush() {
	for (int i = 0; i<1024; i++) {
		oled_segments[i] = 0;
		oled_update();
	}
}
