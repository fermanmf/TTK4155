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
	for (int i = 0; i<16; i++) {
		if (i < strlen(string)) {
			write_char(string[i], line, i);
		}
		else {
			write_char(' ', line, i);
		}
	}
	oled_update();
}
	
	
void display_invert_line(int line) {
	for (int i = 128 * line; i<128 * (line + 1); i++){
		oled_segments[i] = ~oled_segments[i];
	}
	oled_update();
}
