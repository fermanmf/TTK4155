/**
 * @file
 * @brief OLED display driver
 */
#pragma once

/**
 * @brief 1024 byte array for storing OLED segments
 */
volatile char *oled_segments;
 
 /**
  * @brief Initializes driver
  */
void oled_init();

/**
 * @brief Updates OLED with the content of @c oled_segments
 */
void oled_update();