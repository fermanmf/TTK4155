/**
 * @file
 * @brief Display driver
 */
#pragma once

/**
 * @brief Initializes driver
 */
void display_init();

/**
 * @brief Writes string to specified line on display
 * 
 * @param string[in] String to be written to display. Max 16 chars 
 * @param line[in] Line to write to. 0-7
 */
void display_write_line(char string[], int line);

/**
 * @brief Inverts specified line
 * 
 * @param line Line to invert
 */
void display_invert_line(int line);
