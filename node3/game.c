#include "game.h"
#include "updateImage.h"
#include "gameover.h"
#include "gameWon.h"
#include "snake.h"

enum dir{up, down, left, right, won, lost};

  // Init game
  volatile int i;
  int Row = 0;
  int Col = 0;
  enum dir run;

  // Init snake
  int globalCounter = 0;
  int length = 0;
  int lastPositionX[200];
  int lastPositionY[200];

  // Init food
  int food[4][2] = {  
   {0, 1},
   {4, 3},  
   {2, 4},
   {2, 2}
   };
  int foodX = 0;
  int foodY = 1;
  int counter = 0;
  int maxFood = 4;

  // Tick
  int tick = 0;

void game(uint8_t image[], uint8_t direction) {

  // Sets the run direction for the snake
  run = direction;

  // Sets a counter so that the snake holds itself in one position in x seconds
  if (tick==0) {
  tick = 10000;
  
  // If time is up, send the user to game over
  if (globalCounter==200) { run = 5; }

  switch (run)
  {
      case right:
        // Store last position
        lastPositionX[globalCounter] = Col;
        lastPositionY[globalCounter] = Row;
        globalCounter++;
        // If snake hits food, extend length and spawns new food
        if ((Col==foodX)&(Row==foodY)) {
          length++;
          counter++;
          if (counter==maxFood) { run = 4; break;}
          else { foodX = food[counter][0]; foodY = food[counter][1]; }
          }
        // Update the screen
        buildSnakeImage(image, foodX, foodY, Col, Row, length, globalCounter, lastPositionX, lastPositionY);
        // Update next position
        if (Col==4) { Col = 0; }
        else {Col++;}
        break;

      case left:
        // Store last position
        lastPositionX[globalCounter] = Col;
        lastPositionY[globalCounter] = Row;
        globalCounter++;
        // If snake hits food, extend length and spawns new food
        if ((Col==foodX)&(Row==foodY)) {
          length++;
          counter++;
          if (counter==maxFood) { run = 4; break;}
          else { foodX = food[counter][0]; foodY = food[counter][1]; }
          }
        // Update the screen
        buildSnakeImage(image, foodX, foodY, Col, Row, length, globalCounter, lastPositionX, lastPositionY);
        // Update next position
        if (Col==0) { Col = 4; }
        else {Col--;}
        break;

      case up:
        // Store last position
        lastPositionX[globalCounter] = Col;
        lastPositionY[globalCounter] = Row;
        globalCounter++;
        // If snake hits food, extend length and spawns new food
        if ((Col==foodX)&(Row==foodY)) {
          length++;
          counter++;
          if (counter==maxFood) { run = 4; break;}
          else { foodX = food[counter][0]; foodY = food[counter][1]; }
          }
        // Update the screen
        buildSnakeImage(image, foodX, foodY, Col, Row, length, globalCounter, lastPositionX, lastPositionY);
        // Update next position
        if (Row==0) { Row = 4; }
        else {Row--;}
        break;

      case down:
        // Store last position
        lastPositionX[globalCounter] = Col;
        lastPositionY[globalCounter] = Row;
        globalCounter++;
        // If snake hits food, extend length and spawns new food
        if ((Col==foodX)&(Row==foodY)) {
          length++;
          counter++;
          if (counter==maxFood) { run = 4; break;}
          else { foodX = food[counter][0]; foodY = food[counter][1]; }
          }
        // Update the screen
        buildSnakeImage(image, foodX, foodY, Col, Row, length, globalCounter, lastPositionX, lastPositionY);
        // Update next position
        if (Row==4) { Row = 0; }
        else {Row++;}
        break;

      case 4:
        while(1) { gameWonDisplay(); }

      case 5:
        while(1) { gameOver(); }

      default:
        break;

   }
  }else {tick--;};

  }

