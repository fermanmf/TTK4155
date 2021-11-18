

#include <stdio.h>

typedef struct {
	char emoji[8];
	uint8_t id;
	uint8_t highscore;
	char highscore_str[16];
} Player;

void player_select(uint8_t id);
void player_highscore_update(uint8_t score);

char* player_get_emoji(uint8_t id);

char* player_get_highscore_str(uint8_t rank);

void player_init();