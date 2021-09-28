#include "display.h"

#include <string.h>

#include "oled.h"
#include "fonts.h"

static void write_char(char c, int line, int pos) {
	const int offset = 128 * line + 8 * pos;
	for (int i = 0; i<8; i++) {
		const char segment = pgm_read_byte(&(font8[c-32][i]));
		oled_segments[offset+i] = segment;
	}	
}

void display_init() {
	oled_init();
}

void display_write_line(char string[], int line) {
	// fix overflow
	for (int i = 0; i<strlen(string); i++) {
		write_char(string[i], line, i);
	}
	oled_update();
}
	
	
void display_invert_line(int line) {}
	
	