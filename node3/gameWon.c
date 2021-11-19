#include "gameWon.h"
#include "updateImage.h"
#include <stdint.h>

  uint8_t imageOfO_won[5] = {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  };

  uint8_t imageOfM_won[5] = {
    0b10001,
    0b11011,
    0b10101,
    0b10001,
    0b10001
  };

  uint8_t imageOfG_won[5] = {
    0b01111,
    0b10000,
    0b10111,
    0b10001,
    0b01110
  };
    
    void gameWonDisplay() {
            int i;
            i = 5000;
            while(--i > 0) {
              updateImage(imageOfO_won);
              }
            i = 5000;
            while(--i > 0) {
              updateImage(imageOfM_won);
              }
            i = 5000;
            while(--i > 0) {
              updateImage(imageOfG_won);
            }
    }