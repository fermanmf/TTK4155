

typedef struct {
	char emoji[16];
	uint8_t id;
	uint8_t highscore;
	uint8_t highscore_str;
} Player;

Player player1;
Player player2;
Player player3;
Player player4;
Player player5;

void player_select(uint8_t id);
void player_highscore_update(Score score);