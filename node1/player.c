#include "player.h"
#include "eeprom.h"
#include "menu.h"
#include <stdio.h>


Player players[] = {{"<3    ", 0, 200,""}, {":)    ", 1, 200,""}, {":(    ", 2, 200,""}, {"--__--", 3, 200,""}, {":S    ", 4, 200,""}, {":,(   ", 5, 200,""}}; //
Player* player = &players[0];

static void update_string(uint8_t rank, Player* player_to_update){
	snprintf(&(player_to_update->highscore_str), 16, "%u. %s  %u",rank, player_to_update->emoji,player_to_update->highscore);
}
static void player_write_highscores_to_eeprom(){
	for (int rank = 0;rank<sizeof(players)/sizeof(Player);rank+=2){
		eeprom_write(rank,players[rank].id);
		eeprom_write(rank+1,players[rank].highscore);
	}
}
static void read_highscores_from_eeprom(){
	uint8_t eeprom_id = 0;
	Player store_player;
	for (int rank = 0;rank<sizeof(players)/sizeof(Player);rank+=2){
		eeprom_id = eeprom_read(rank);
		for (int i = 0;i<sizeof(players)/sizeof(Player);i++){
			if (players[i].id == eeprom_id){
				store_player = players[rank];
				players[rank] = players[i];
				players[i] = store_player;
				players[rank].highscore = eeprom_read(rank+1);
			}
		}
	}
	for (int rank = 0; rank<sizeof(players)/sizeof(Player);rank++){
		update_string(rank+1, &players[rank]);
	}
}

static void update_highscore_table(){
	uint8_t rank = 0;
	Player poor_player;
	for (int i = 0;i<sizeof(players)/sizeof(Player);i++){
		if (player->id == players[i].id){
			rank = i;
		}
	}
	for (int i = rank-1;i>=0;i--){
		if (player->highscore < players[i].highscore){
			poor_player = players[i];
			players[i] = players[i+1];
			players[i+1] = poor_player;
			player = &players[i];
			printf("pi: %i",i);
			update_string(i+2,&players[i+1]);
			update_string(i+1,player);
		}
	}
}

void player_highscore_update(uint8_t score){
	if (score < player->highscore){
		player->highscore = score;
		update_highscore_table();
		player_write_highscores_to_eeprom();
	}
}


void player_select(uint8_t player_id){
	for (int i = 0;i<sizeof(players)/sizeof(Player);i++){
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
void player_init(){
	read_highscores_from_eeprom();
}