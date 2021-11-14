#include "menu.h"
#include "display.h"
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
	replay_id
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
MenuItem player1 = {"<3", play_id};
MenuItem player2 = {":)", play_id};
MenuItem player3 = {":(", play_id};
MenuItem player4 = {"--__--", play_id};
MenuItem player5 = {":S", play_id};
MenuItem player6 = {":,(", play_id};
MenuItem back_item = {"<-- back",main_menu_id};
MenuItem replay_item = {"Replay", replay_id};
MenuItem main_menu_item = {"Main menu",main_menu_id};

Menu main_menu = {"Main menu", {&play_item, &highscore_item}, 2, 0, 0, main_menu_id};
Menu character_menu = {"Character select", {&player1, &player2, &player3, &player4, &player5, &player6, &back_item}, 7, 0, 0, character_menu_id};
//foreløpig en liten hack på highscore
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
	uint8_t display_offset = 1;
	display_write_line(menu->header,0);
	for (int i = 0;i<menu->n_items ;i++){
		if (i == menu->choice){
			display_write_line(get_item_text(i),i + display_offset);
			display_invert_line(i+1);
		}
		else {
			display_write_line(get_item_text(i),i+1);
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
	for (int i = 0;i<character_menu.n_items;i++){
		if (i == character_menu.choice){
			display_write_line(character_menu.items[i]->text,5);
		}
	}
}


static void update_menu(){
	write_menu(menu);
}
void menu_handle_select() {
	switch(get_choice_id(menu)){
		case character_menu_id:
			menu = &character_menu;
			update_menu();
			break;
			
		case highscore_menu_id:
			menu = &highscore_menu;
			update_menu();
			break;
			
		case play_id:
			//em_game_start();
			display_character();
			menu = &end_menu;
			break;
			
		case end_menu_id:
			menu = &highscore_menu;
			update_menu();
			break;
			
		case replay_id:
			//em_replay_start();
			display_character();
			menu = &main_menu;
			break;
			
		case main_menu_id:
			menu = &main_menu;
			break;
			
		default:
			printf("menu error: invalid main menu choice: %u\n", get_choice_id(menu));
			break;
	}
}

void menu_handle_scroll(bool up) {
	scroll(up);
}
