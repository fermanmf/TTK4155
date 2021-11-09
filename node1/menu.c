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
}Menu;

Menu MainMenu = {{"Main menu","Play","HighScore"}, 3, 1};
Menu CharacterMenu = {{"Pick character","<3",":)",":(","-_-",":S",":,("},7,1};
Menu Highscore = {{"HighScore","1.","2.","3.","4.","5.","6.","7."}, 8,7};
Menu EndMenu = {{"End of Game", "Play again", "Replay", "Highscore"}, 4, 1};
	
typedef enum {
    setup,
    mainMenu,
    highScore,
    characterSelect,
    inGame,
    endOfGame,
    replay
}MenuState;

MenuState state;

static void write_menu(Menu menu){
	char arrow [] = "--> ";
	for (int i = 0;i<menu.number_of_lines;i++){
		if (i == menu.current_choice){
			display_write_line(menu.lines[i],i);
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
void menu(){
	bool exit_menu = false;
	while (!exit_menu){
		switch (state){
			case(mainMenu):
				write_menu(MainMenu);
				break;
			case(characterSelect):
				write_menu(CharacterMenu);
				break;
			case(endOfGame):
				write_menu(EndMenu);
				break;
			case (highScore):
				write_menu(Highscore);
			default:
				break;
		}
	}
}


