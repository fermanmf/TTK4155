#include "uart.h"
#include "gpio.h"
#include "led.h"
#include "snake.h"
#include <stdlib.h>
#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include <stdbool.h>

#define print(arg) _print(arg, strlen(arg))

enum dir{right, down, left, up};

int main(void) {
  volatile int i;
  int Row;
  int Col;
  // Init clocks + pins
  _InitLEDs();
  uart_init();
  
  char test[7] = "Testing";
  //print(test);
  _print(test, 7);

  // Configure buttons
  // A
  GPIO->PIN_CNF[17] = 0;
  // B
  GPIO->PIN_CNF[26] = 0;

  Row = 0;
  Col = 0;
  enum dir run;
  run = right;

  // Length
  int globalCounter = 0;
  bool first = true;
  int length = 0;
  int lastPositionX[200];
  int lastPositionY[200];

  // Food
  int food[4][2] = {  
   {0, 1},
   {4, 3},  
   {2, 4},
   {2, 2},
};
  int foodX = 0;
  int foodY = 1;
  int counter = 0;
  int maxFood = 4;

  uint8_t emptyImage[5] = {
    0b00000,
    0b00001,
    0b00010,
    0b10100,
    0b01000
  };

  void updateImage(uint8_t image[5]) {
    for (int i = 0; i < 5; i++) {
      uint8_t n = image[i];
      for (int j = 4; j >= 0; j--) {
      if(1&(n>>j)) {
          _SetLED(i, 4-j);
        }
      }
    }
  }


void buildSnakeImage(int foodX, int foodY, int snakeX, int snakeY, int length) {
    uint8_t image[5] = {
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000
    };
    // Set food in image
    image[foodY] = (image[foodY]|(0b1<<(4-foodX)));
    image[snakeY] = (image[snakeY]|(0b1<<(4-snakeX)));
    for (int i = 0; i < length; i++) {
      image[(lastPositionY[globalCounter-2-i])] = image[lastPositionY[globalCounter-2-i]]|(0b1<<(4-lastPositionX[globalCounter-2-i]));
    };

    updateImage(image);
  }
  

  // ============= START OF GAME =============
  
  i = 10000;
  while(--i > 0) {
    updateImage(imageOf3);
    }
  i = 10000;
  while(--i > 0) {
    updateImage(imageOf2);
    }
  i = 10000;
  while(--i > 0) {
    updateImage(imageOf1);
  }
  
  do {

  switch (run)
  {
      case right:
        for (int ColCounter = Col; ColCounter < 5; ColCounter++) {

        /*
        for (int i = 0; i < length; i++) {
          if ((lastPositionY[globalCounter-2-i]==Row)|(lastPositionX[globalCounter-2-i]==ColCounter)) {
          run = 5;
          break;
          }
        }
        */

        // Shit code
          lastPositionX[globalCounter] = ColCounter;
          lastPositionY[globalCounter] = Row;
          globalCounter++;

          if ((ColCounter==foodX)&(Row==foodY)) {
          // Update food
          length++;
          counter++;
          if (counter==maxFood) {
             run = 4;
             break;
          }
          foodX = food[counter][0];
          foodY = food[counter][1];
          }
          i = 10000;
          while(--i > 0) {
            buildSnakeImage(foodX,foodY,ColCounter, Row, length);
            if (aPushed()) {
              run = up;
              Col = ColCounter;
            }
            if (bPushed()) {
              run = down;
              Col = ColCounter;
            }
          }
          if(run!=right) break;
        }
        if(run==right) Col = 0;
        break;
      
      case down:
        for (int RowCounter = Row; RowCounter < 5; RowCounter++) {

                // Shit code
          lastPositionX[globalCounter] = Col;
          lastPositionY[globalCounter] = RowCounter;
          globalCounter++;

          if ((Col==foodX)&(RowCounter==foodY)) {
          // Update food
          length++;
          counter++;
          if (counter==maxFood) {
          run = 4;
          break;
          }
            foodX = food[counter][0];
            foodY = food[counter][1];
          }
          i = 10000;
          while(--i > 0) {
            buildSnakeImage(foodX,foodY,Col, RowCounter, length);
            if (bPushed()) {
              run=right;
              Row = RowCounter;
              }
            if (aPushed()) {
              run=left;
              Row = RowCounter;
              }
          }
          if(run!=down) break;
        }
        if(run==down) Row = 0;
        break;

      case left:
        for(int ColCounter = Col; ColCounter >= 0; ColCounter--) {

        // Shit code
          lastPositionX[globalCounter] = ColCounter;
          lastPositionY[globalCounter] = Row;
          globalCounter++;

          if ((ColCounter==foodX)&(Row==foodY)) {
          // Update food
          length++;
          counter++;
          if (counter==maxFood) {
          run = 4;
          break;
          }
            foodX = food[counter][0];
            foodY = food[counter][1];
          }
          i = 10000;
          while(--i > 0) {
            buildSnakeImage(foodX,foodY,ColCounter, Row, length);
            if (aPushed()) {
              run = down;
              Col = ColCounter;
            }
            if (bPushed()) {
              run = up;
              Col = ColCounter;
            }
          }
          if(run!=left) break;
        }
        if(run==left) Col = 4;
        break;
        
        case up:
          for(int RowCounter = Row; RowCounter >= 0; RowCounter--){

        // Shit code
          lastPositionX[globalCounter] = Col;
          lastPositionY[globalCounter] = RowCounter;
          globalCounter++;

          if ((Col==foodX)&(RowCounter==foodY)) {
          // Update food
          length++;
          counter++;
          if (counter==maxFood) {
          run = 4;
          break;
          }
            foodX = food[counter][0];
            foodY = food[counter][1];
          }
            i = 10000;
            while(--i > 0) {
              buildSnakeImage(foodX,foodY,Col, RowCounter, length);
              if (aPushed()) {
                run = left;
                Row = RowCounter;
              }
              if (bPushed()) {
                run = right;
                Row = RowCounter;
              }
            }
            if(run!=up) break;
          }
          if(run==up) Row = 4;

          break;

        case 4:
          while(1) {
            i = 5000;
            while(--i > 0) {
              updateImage(imageOfO);
              }
            i = 5000;
            while(--i > 0) {
              updateImage(imageOfM);
              }
            i = 5000;
            while(--i > 0) {
              updateImage(imageOfG);
            }
            i = 20000;
            while(--i > 0) {
              updateImage(emptyImage);
            }
          }

          case 5:
            while(1) {
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfG);
                }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfA);
                }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfM);
              }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfE);
              }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfCross);
              }
              i = 5000;
              while(--i > 0){
              updateImage(imageOfO);
              }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfV);
                }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfE);
              }
              i = 5000;
              while(--i > 0) {
                updateImage(imageOfR);
              }
              i = 20000;
              while(--i > 0) {
                updateImage(imageOfCross);
              }
            }

        default:
          break;

  }

  } while(1);
  
  
  return 0;
}

