#include "updateImage.h"
#include "led.h"


 void updateImage(uint8_t image[5]) {
   for (int i = 0; i < 5; i++) {
     uint8_t n = image[i];
     for (int j = 4; j >= 0; j--) {
     if(1&(n>>j)) {
         setSelectedLED(i, 4-j);
        }
      }
    }
  }

  void buildSnakeImage(uint8_t image[], int foodX, int foodY, int snakeX, int snakeY, int length, int globalCounter, int lastPositionX[200], int lastPositionY[200]) {
    // Set food in image
    for (int i = 0; i < 5; i++) {
    image[i] = 0b00000;
    }
    image[foodY] = (image[foodY]|(0b1<<(4-foodX)));
    image[snakeY] = (image[snakeY]|(0b1<<(4-snakeX)));
    
    for (int i = 0; i < (length+1); i++) {
      image[(lastPositionY[globalCounter-1-i])] = image[lastPositionY[globalCounter-1-i]]|(0b1<<(4-lastPositionX[globalCounter-1-i]));
    };
    

    updateImage(image);
  }