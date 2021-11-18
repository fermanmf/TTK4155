#include "gpio.h"
#include "led.h"
#include "countdown.h"
#include "game.h"
#include "updateImage.h"

#include <stdlib.h>
#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include <stdbool.h>

#define print(arg) _print(arg, strlen(arg))

#define valid !!(GPIO->IN&(1 << 16))
#define com_pin1 !!(GPIO->IN&(1 << 21))
#define com_pin2 !!(GPIO->IN&(1 << 22))
#define com_pin3 !!(GPIO->IN&(1 << 23))
#define com_pins (com_pin1 << 2)|(com_pin2 << 1)|(com_pin3 << 0) 


int main(void) {
  // Init clocks + pins
  _InitLEDs();
  // Configure buttons
  GPIO->PIN_CNF[17] = 0; // A
  GPIO->PIN_CNF[26] = 0; // B
  GPIO->PIN_CNF[16] = 0;
  GPIO->PIN_CNF[21] = 0;
  GPIO->PIN_CNF[22] = 0;
  GPIO->PIN_CNF[23] = 0;


  uint8_t image[5] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
  };

  uint8_t emptyImage[5] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
  };

  // ============= START OF GAME =============
  uint32_t com = 0;
  while(1) {
    if (valid) {
      com = com_pins;
    }

    if (com & 0b100) {
      game(image, com&0b011);
    } else if (com == 0b001) {
      countDownDisplay();
    }
    
    
    if (com==0) {
      updateImage(emptyImage);
    } else {
    updateImage(image);
    }
  }
  
  return 0;
}

