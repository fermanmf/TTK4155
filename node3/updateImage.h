/**
 * @file updateImage.h
 * @date 19 Nov 2021
 * @brief File containing funcitons for updating the micro bit display
 */

#include <stdint.h>

/**
 * @brief updateImage
 *
 * This function takes in an array of uint8_t as a reference, @p image. This array describes which of the
 * leds that should be turned on or not by checking if the bits in the arrray is 1 or 0.
 * @param image  The image parameter is an array of 5 uint8_t where the bits describe if a led i the matrix should be turned off or on
 */

void updateImage(uint8_t image[5]);

/**
 * @brief buildSnakeImage
 *
 * This function takes in an array of uint8_t as a reference. This array describes which of the
 * leds that should be turned on or not by checking if the bits in the arrray is 1 or 0.
 * @param image  The image parameter is an array of 5 uint8_t where the bits describe if a led i the matrix should be turned off or on
 * @param foodX  Gives the x-position of the fruit the snake wil try to eat
 * @param foodY  Gives the y-position of the fruit the snake wil try to eat
 * @param snakeX  Gives the current x-position position to the head of the snake
 * @param snakeY  Gives the current y-position position to the head of the snake
 * @param length  Tells how many lights should be turned on behind the head of the snake
 * @param globalCounter  Counts how many steps the snake has moved
 * @prarm lastPositionX  Stores the path the snake has moved n x-positiones
 * @prarm lastPositionX  Stores the path the snake has moved n y-positiones
 */
void buildSnakeImage(uint8_t image[], int foodX, int foodY, int snakeX, int snakeY, int length, int globalCounter, int lastPositionX[200], int lastPositionY[200]);