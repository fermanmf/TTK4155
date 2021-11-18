#include "player.h"
#include "eeprom.h"
Player* player = NULL;

Player player1 = {"<3", 0, 0};
Player player2 = {":)", 1, 0};
Player player3 = {":(", 2, 0};
Player player4 = {"--__--", 3, 0};
Player player5 = {":S", 4, 0};
Player player6 = {":,(", 5, 0};

Player players [6] = [player1, player2, player3, player4, player5, player6];
	
void player_highscore_update(Score score){
	if score > player->highscore{
		player->highscore = score;
	}
}

void player_select(uint8_t player_id){
	for (int i = 0;i<6;i++){
		if (player_id == players[i].id){
			player = &players[i];
		}
	}
}