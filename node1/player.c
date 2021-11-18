#include "player.h"
#include "eeprom.h"
#include "menu.h"
#include <stdio.h>


Player players[] = {{"<3", 0, 0,""}, {":)", 1, 0,""}, {":(", 2, 0,""}, {"--__--", 3, 0,""}, {":S", 4, 0,""}, {":,(", 5, 0,""}};

Player* player = &players[0];
	
static void update_string(uint8_t rank, Player* player_to_update){
	snprintf(&(player_to_update->highscore_str), 16, "%u. %s  %u",rank, player_to_update->emoji,player_to_update->highscore);
}

static void update_highscore_table(){
	uint8_t rank = 0;
	for (int i = 0;i<6;i++){
		if (player->id == players[i].id){
			rank = i;
		}
	}
	for (int i = rank-1;i>=0;i--){
		if (player->highscore > players[i].highscore){
			players[i+1] = players[i];
			update_string(i+1,&players[i+1]);
			players[i] = *player;
			update_string(i,player);
		}
	}
}

void player_highscore_update(uint8_t score){
	if (score > player->highscore){
		player->highscore = score;
		update_highscore_table();
	}
	menu_update_highscores();
}


void player_select(uint8_t player_id){
	for (int i = 0;i<6;i++){
		if (player_id == players[i].id){
			player = &players[i];
		}
	}
}

char * player_get_emoji(uint8_t id){
	for (int i = 0;i<sizeof(players)/sizeof(Player);i++){
		if (players[i].id==id){
			return players[i].emoji;
		}
	}
	
	printf("player error: player_get_emoji out of range");
}

char* player_get_highscore_str(uint8_t rank){
	return players[rank].highscore_str;
}
