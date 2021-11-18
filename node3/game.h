#include <stdint.h>
void game(uint8_t image[], uint8_t dir);


// Old switch case
 /*
      case right:
        for (int ColCounter = Col; ColCounter < 5; ColCounter++) {

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
            buildSnakeImage(foodX,foodY,ColCounter, Row, length, globalCounter, lastPositionX, lastPositionY);
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
            buildSnakeImage(foodX,foodY,Col, RowCounter, length, globalCounter, lastPositionX, lastPositionY);
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
            buildSnakeImage(foodX,foodY,ColCounter, Row, length, globalCounter, lastPositionX, lastPositionY);
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
              buildSnakeImage(foodX,foodY,Col, RowCounter, length, globalCounter, lastPositionX, lastPositionY);
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
          */