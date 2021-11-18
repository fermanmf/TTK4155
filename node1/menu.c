#include "menu.h"
#include "display.h"
#include "em.h"

#include "player.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef enum {
	main_menu_id,
	highscore_menu_id,
	character_menu_id,
	end_menu_id,
	play_id,
	replay_id,
	do_not_care_id
}Id;

typedef struct {
	char text[16];
	Id action_id;
} MenuItem;

typedef struct {
	char header[16];
	MenuItem *items[7];
	uint8_t n_items;
	uint8_t choice;
	uint8_t default_choice;
	Id	id; 
} Menu;

MenuItem play_item = {"Play",character_menu_id};
MenuItem highscore_item = {"Highscore",highscore_menu_id};
MenuItem player1_character_item = {"", play_id};
MenuItem player2_character_item = {"", play_id};
MenuItem player3_character_item = {"", play_id};
MenuItem player4_character_item = {"", play_id};
MenuItem player5_character_item = {"", play_id};
MenuItem player6_character_item = {"", play_id};
MenuItem first_highscore_item = {"", main_menu_id};
MenuItem back_item = {"<-- back",main_menu_id};
MenuItem replay_item = {"Replay", replay_id};
MenuItem main_menu_item = {"Main menu",main_menu_id};



Menu main_menu = {"Main menu", {&play_item, &highscore_item}, 2, 0, 0, main_menu_id};
Menu character_menu = {"Character select", {&player1_character_item, &player2_character_item, &player3_character_item, &player4_character_item,&player5_character_item, &player6_character_item, &back_item}, 7, 0, 0, character_menu_id};// 
Menu highscore_menu = {"Highscore", {&first_highscore_item, &first_highscore_item, &first_highscore_item, &first_highscore_item, &first_highscore_item, &first_highscore_item, &back_item}, 7, 6, 6, highscore_menu_id};
Menu end_menu= {"Well played!", {&main_menu_item, &replay_item}, 2, 0, 0, end_menu_id};

Menu *menu = &main_menu;


static Id get_choice_id(Menu *menu){
	return menu->items[(menu->choice)]->action_id;
}

static char* get_item_text(uint8_t item_number){
	return menu->items[item_number]->text;
}

static void write_menu(){
	uint8_t item_offset = 1;
	display_write_line(menu->header,0);
	for (int i = 0;i<7 ;i++){
		if (i < menu->n_items){
			if (i == menu->choice){
				display_write_line(get_item_text(i),i+item_offset);
				display_invert_line(i+1);
			}
			else {
				display_write_line(get_item_text(i),i+item_offset);
			}
		}
		else{
			display_write_line("",i+item_offset);
		}
	}
}


static void scroll(bool down) {
	if (down ){
		if (menu->choice == menu->n_items - 1){
			return;
		}
		menu->choice++;
		menu_update();
	}
	else {
		if (menu->choice == menu->default_choice){
			return;
		}
		menu->choice--;
		menu_update();
	}
	if (menu->choice < menu->default_choice || menu->choice >= menu->n_items){
		printf("menu err:OOrange");
	}
}

static void display_character(){
	display_write_line("Playing...",0);
	display_write_line(character_menu.items[character_menu.choice]->text,5);
	for (int i = 0; i<8;i++){
		if (i != 0 && i != 5){
			display_write_line("",i);
		}
	}
}


void menu_update(){
	write_menu();
}
void display_highscore(){
	display_write_line("Highscores",0);
	
	for (int i = 0; i<6;i++){
		display_write_line(player_get_highscore_str(i),i+1);
	}
	display_write_line("<--back",7);
	display_invert_line(7);
}

void menu_handle_select() {
	switch(get_choice_id(menu)){
		case character_menu_id:
			menu = &character_menu;
			menu_update();
			break;
		
		case highscore_menu_id:
			menu = &highscore_menu;
			display_highscore();
			break;
		
		case play_id:
			player_select(menu->choice);
			display_character();
			em_event_empty(EmGameStarted);			
			menu = &end_menu;
			break;
			
		case end_menu_id:
			menu = &end_menu;
			menu_update();
			break;
		
		case replay_id:
			display_character();
			em_event_empty(EmReplayStarted);
			menu = &main_menu;
			break;
		
		case main_menu_id:
			menu = &main_menu;
			menu_update();
			break;
			
		default:
			break;
	}
}

void menu_handle_scroll(bool down) {
	if (menu != &highscore_menu){
		scroll(down);
	}
}

void menu_init() {
	strcpy(player1_character_item.text, player_get_emoji(0));
	strcpy(player2_character_item.text, player_get_emoji(1));
	strcpy(player3_character_item.text, player_get_emoji(2));
	strcpy(player4_character_item.text, player_get_emoji(3));
	strcpy(player5_character_item.text, player_get_emoji(4));
	strcpy(player6_character_item.text, player_get_emoji(5));
	
	menu = &main_menu;
	write_menu();
}