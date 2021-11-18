#include "uart.h"
#include "gpio.h"
#include "led.h"
#include "snake.h"
#include "gpiote.h"
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
  
  // Food array
 

  int foodX = 3;
  int foodY = 4;
  int victoryCounter = 0;
  do {
  
  switch (run)
  {
      case right:
        for (int ColCounter = Col; ColCounter < 5; ColCounter++) {
          if ((ColCounter==foodX)&(Row==foodY)) {
            foodX = 1;
            foodY = 2;
          }
          i = 60000;
          while(--i > 0) {
            _SetLED(Row, ColCounter);
            _SetLED(foodY,foodX);
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
          i = 60000;
          while(--i > 0) {
            _SetLED(RowCounter, Col);
            _SetLED(foodY,foodX);
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
          i = 60000;
          while(--i > 0) {
            _SetLED(Row, ColCounter);
            _SetLED(foodY,foodX);
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
            i = 60000;
            while(--i > 0) {
              _SetLED(RowCounter, Col);
              _SetLED(foodY,foodX);
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
          _SetLED(3, 0);
          _SetLED(4, 1);
          _SetLED(3, 2);
          _SetLED(2, 3);
          _SetLED(1, 4);

          }

        default:
          break;

  }

  } while(1);
  
  return 0;
}

