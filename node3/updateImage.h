#include <stdint.h>

void updateImage(uint8_t image[5]);

void buildSnakeImage(uint8_t image[], int foodX, int foodY, int snakeX, int snakeY, int length, int globalCounter, int lastPositionX[200], int lastPositionY[200]);