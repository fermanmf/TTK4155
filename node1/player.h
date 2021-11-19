

#include <stdio.h>

/**
 * @brief This function lets Player.c know how is currently playing.
 * 
 * @param id The id of the player lastly selected. 
 */
void player_select(uint8_t id);
/**
 * @brief Updates the highscore of the players and reranks them.
 * 
 * @param score The new score of the player who just played
 */
void player_highscore_update(uint8_t score);
/**
 * @brief This functions returns the emoji of the player specified by @c id .
 * 
 * @param id Specifies player to retrieve emoji from.
 * @return char*, A string of size 8 at most.
 */
char* player_get_emoji(uint8_t id);
/**
 * @brief This function returns the "highscore string" containing rank, emoji, score. 
 * The @c rank is the rank of the player, thus the function chooses player based on its rank. 
 * 
 * @param rank This parameter decides which player´s string to return.
 * @return char* Highscore string, to display in highscore menu.
 */
char* player_get_highscore_str(uint8_t rank);
/**
 * @brief Initiates the functionality of player. It reads the eeprom and loads
 *  the highscores from it.
 * 
 */

void player_init();