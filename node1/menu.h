void display_menu(struct menu menu);

typedef struct {
	char lines [8][];
	int number_of_lines;
	int current_choice;
}menu;

typedef enum {
    setup,
    mainMenu,
    highScore,
    characterSelect,
    inGame,
    endOfGame,
    replay
}State;

State state;