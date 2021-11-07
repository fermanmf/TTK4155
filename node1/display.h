#pragma once

void display_init();
void display_write_line(char string[], int line);
void display_invert_line(int line);
void display_menu(struct menu menu);
struct menu{
	char lines [8][];
	int number_of_lines;
	int current_choice;
};
struct menu MainMenu = {["Main menu","Play","HighScore"], 3, 1};
struct menu CharacterMenu = {["Pick character","<3",":)",":(","-_-",":S",":,("],7,1};
struct menu HighscoreMenu = {["HighScore","1.","2.","3.","4.","5.","6.","7."], 8, 9};
struct menu EndMenu = {["End of Game", "Play again", "Replay", "Highscore"], 4, 1};