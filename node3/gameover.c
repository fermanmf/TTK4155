#include "gameover.h"
#include "updateImage.h"
#include <stdint.h>

  uint8_t imageOfO[5] = {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  };

    uint8_t imageOfM[5] = {
    0b10001,
    0b11011,
    0b10101,
    0b10001,
    0b10001
  };

    uint8_t imageOfG[5] = {
    0b01111,
    0b10000,
    0b10111,
    0b10001,
    0b01110
  };

    uint8_t imageOfA[5] = {
    0b01110,
    0b10001,
    0b11111,
    0b10001,
    0b10001
  };

    uint8_t imageOfE[5] = {
    0b11111,
    0b10000,
    0b11111,
    0b10000,
    0b11111
  };

      uint8_t imageOfV[5] = {
    0b10001,
    0b10001,
    0b01010,
    0b01010,
    0b00100
  };

    uint8_t imageOfR[5] = {
    0b11110,
    0b10001,
    0b11110,
    0b10100,
    0b10010
  };

    uint8_t imageOfCross[5] = {
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001
  };

void gameOver() {
              int i;
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