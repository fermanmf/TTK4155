#pragma once
/**
 * @brief This function runs oled_init()
 * 
 */
void display_init();
/**
 * @brief This function writes the input string to the oled 
 * display at the line chosen by the input line 
 * 
 * @param string determines the string to be wirtten on the oled
 * @param line determines the line it will be written at
 */
void display_write_line(char string[], int line);
/**
 * @brief This function inverts the oled colors at the line chosen by the input line 
 * 
 * @param line determines the line at which to invert
 */
void display_invert_line(int line);
