#include "menu.h"
#include "display.h"
#include "stdbool.h"


typedef struct {
	char lines [8][16];
	int number_of_lines;
	int current_choice;
}Display;

typedef struct {
	char lines [8][16];
	int number_of_lines;
	int current_choice;
	int default_choice;
}Menu;


#define HIGHSCOREMENU		{{"HighScore","1.","2.","3.","4.","5.","6.","<--Back"}, 8, 7, 7}
#define MAIN_MENU			{{"Main menu","Play","HighScore"}, 3, 1, 1};
#define CHARACTERMENU		{{"Pick character","<3",":)",":(","-_-",":S",":,("}, 7, 1, 1};
#define ENDMENU				{{"End of Game", "Play again", "Replay", "Highscore"}, 4, 1, 1};
	
Menu current_menu;

//Menu menus [] ={MAIN_MENU,CharacterMenu,HighscoreMenu,EndMenu};
////static void reset_menu__current_select(){
	//for (int i = 0;i < sizeof(menus)/sizeof(Menu);i++){
		//menus[i].current_choice = menus[i].default_choice;
	//}
	//
//} 
typedef enum {
    setup,
    MAIN_MENU,
    highScore,
    characterSelect,
    inGame,
    endOfGame,
    replay
}MenuState;

MenuState state = characterSelect;

void menu_scroll(bool up) {
	if (up){
		if (current_menu.current_choice == current_menu.default_choice){
			return;
		}
		current_menu.current_choice++;
	}
	else {
		if (current_menu.current_choice == current_menu.number_of_lines-1){
			return;
		}
		current_menu.current_choice--;
	}	
}



static void write_menu(Menu menu){
	for (int i = 0;i<menu.number_of_lines;i++){
		if (i == menu.current_choice){
			display_write_line(menu.lines[i],i);
			display_invert_line(i);
		}
		else {
			display_write_line(menu.lines[i],i);
		}
	}
}
static void write_static_display(Display display){
	for (int i = 0;i<display.number_of_lines;i++){
			display_write_line(display.lines[i],i);
	}
}
void menu_joystick_callback(){
					
}
void menu_select_callback(){
	
}

void menu(){
	bool exit_menu = false;
	while (!exit_menu){
		switch (state){
			case(MAIN_MENU):
			write_menu(MAIN_MENU);
			break;
			case(characterSelect):
			write_menu(CharacterMenu);
			break;
			case(endOfGame):
			write_menu(EndMenu);
			break;
			case (highScore):
			write_menu(HighscoreMenu);
			default:
			break;
		}
	}
}



void menu_init() {
	state = MAIN_MENU
	current_menu = MAIN_MENU;
	write_menu(current_menu);
}











typedef struct {
	char header[16];
	MenuItem *items[7];
	uint8_t n_items;
	uint8_t choice;
	uint8_t default_choice;
} Menu;

typedef struct {
	char text[16];
} MenuItem;
	
Menu *menu = &main_menu;

MenuItem play_item = {"Play"};
MenuItem highscore_item = {"Highscore"};
	
Menu main_menu = {"Main menu", {&play_item, &highscore_item}, 2, 1, 1};

MenuItem *get_choice(Menu *menu) {
	return menu->items[menu->choice];
}


void menu_select() {
	switch (menu){
		case(&main_menu):
			switch(get_choice(menu)){
				case &play_item:
					menu = &character_menu;
					update_menu();
				case &highscore_item:
					menu = &highscore_menu;
					update_menu();
				default:
					printf("menu error: invalid main menu choice\n");
					break;
			}
			break;
	}
}

