/**
 * @file game.h
 * @date 19 Nov 2021
 * @brief File containing funcitons for updating the micro bit display
 */
#include <stdint.h>

 /**
 * @brief Starts the snake game
 * @param image  Takes in a refernece to the display and changes this accordingly when the game is played
 * @param dir  Gets the direction as a uint8_t and uses this to move the snake in the given direction
 */
void game(uint8_t image[], uint8_t dir);
