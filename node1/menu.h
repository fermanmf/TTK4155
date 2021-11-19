/**
 * @file menu.h
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "em.h"
#include <stdbool.h>
/**
 * @brief initiate the menu by setting the first state to main menu, and it writes
 * the menu for the first time.
 * 
 */
void menu_init();
/**
 * @brief This function handles the attempt to scroll the menu. If at the edge or 
 * in Highscore mode the attempt will fail correctly.
 * 
 * @param down lets the function know whether to scroll up or down.
 */
void menu_handle_scroll(bool down);
/**
 * @brief This function decides what happens to the menu when a choice is selected.
 * 
 */
void menu_handle_select();
/**
 * @brief This function refreshes the menu.
 * 
 */
void menu_update();
/**
 * @brief This function updates the strings for the display
 * with potential new highscores and new ranking.
 * 
 */
void menu_update_highscores();