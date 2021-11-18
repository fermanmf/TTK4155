#include "menu.h"
#include "display.h"
#include "em.h"
#include "player.h"
#include <stdbool.h>
#include <stdio.h>

#define HIGHSCOREMENU		{{"HighScore","1.","2.","3.","4.","5.","6.","<--Back"}, 8, 7, 7}
#define MAIN_MENU			{{"Main menu","Play","HighScore"}, 3, 1, 1};
#define CHARACTERMENU		{{"Pick character","<3",":)",":(","-_-",":S",":,("}, 7, 1, 1};
#define ENDMENU				{{"End of Game", "Play again", "Replay", "Highscore"}, 4, 1, 1};

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
MenuItem player1_character_item = {player1.emoji, play_id};
MenuItem player2_character_item = {player2.emoji, play_id};
MenuItem player3_character_item = {player3.emoji, play_id};
MenuItem player4_character_item = {player4.emoji, play_id};
MenuItem player5_character_item = {player5.emoji, play_id};
MenuItem player6_character_item = {player6.emoji, play_id};
MenuItem back_item = {"<-- back",main_menu_id};
MenuItem replay_item = {"Replay", replay_id};
MenuItem main_menu_item = {"Main menu",main_menu_id};



Menu main_menu = {"Main menu", {&play_item, &highscore_item}, 2, 0, 0, main_menu_id};
Menu character_menu = {"Character select", {&player1_character_item, &player2_character_item, &player3_character_item, &player4_character_item, &player5_character_item, &player6_character_item, &back_item}, 7, 0, 0, character_menu_id};
Menu highscore_menu = {"Highscore", {&back_item, &back_item, &back_item, &back_item, &back_item, &back_item, &back_item}, 7, 6, 6, highscore_menu_id};
Menu end_menu= {"Well played!", {&main_menu_item, &replay_item}, 2, 0, 0, end_menu_id}; 
Menu *menu = &main_menu;

static MenuItem *get_choice(Menu *menu) {
	return menu->items[menu->choice];
}
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
void menu_init() {
	menu = &main_menu;
	write_menu();
}

static void scroll(bool down) {
	if (down){
		if (menu->choice == menu->n_items - 1){
			return;
		}
		menu->choice++;
	}
	else {
		if (menu->choice == menu->default_choice){
			return;
		}
		menu->choice--;
	}
	if (menu->choice < menu->default_choice || menu->choice >= menu->n_items){
		printf("menu error: choice out of range");
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

void menu_handle_select() {
	switch(get_choice_id(menu)){
		case character_menu_id:
			menu = &character_menu;
			menu_update();
			break;
		
		case highscore_menu_id:
			menu = &highscore_menu;
			menu_update();
			break;
		
		case play_id:
			player_select(menu->choice);
			em_game_started();			
			display_character();
			menu = &end_menu;
			break;
			
		case end_menu_id:
			menu = &highscore_menu;
			menu_update();
			break;
		
		case replay_id:
			em_replay_started();
			//printf("re play started from menu\n");
			display_character();
			menu = &main_menu;
			break;
		
		case main_menu_id:
			menu = &main_menu;
			menu_update();
			break;
			
		default:
			//printf_P("menu error: invalid choice in menu_handle_select\n");
			break;
	}
	
	
}

void menu_handle_scroll(bool down) {
	scroll(down);
	menu_update();
	//printf("handle scroll\n\r");

}
