#include "countdown.h"
#include "updateImage.h"
#include <stdint.h>

  uint8_t imageOf3[5] = {
    0b11110,
    0b00010,
    0b01100,
    0b00010,
    0b11110
  };

  uint8_t imageOf2[5] = {
    0b01100,
    0b10010,
    0b00100,
    0b01000,
    0b11110
  };

  uint8_t imageOf1[5] = {
    0b01100,
    0b00100,
    0b00100,
    0b00100,
    0b01110
  };

void countDownDisplay() {
  int i;
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
 }