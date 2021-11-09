#include "menu.h"
#include "display.h"

void menu_display(menu menu){
	char arrow [] = "--> ";
	for (int i = 0;i<menu.number_of_lines;i++){
		if (i == menu.current_choice){
			display_write_line("%s %s",arrow,menu.lines[i]);
		}
		else {
			display_write_line("%s",menu.lines[i]);
		}
	}
}

menu MainMenu = {["Main menu","Play","HighScore"], 3, 1};
menu CharacterMenu = {["Pick character","<3",":)",":(","-_-",":S",":,("],7,1};
menu HighscoreMenu = {["HighScore","1.","2.","3.","4.","5.","6.","7."], 8, 9};
menu EndMenu = {["End of Game", "Play again", "Replay", "Highscore"], 4, 1};
