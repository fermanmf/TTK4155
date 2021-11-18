#include "snake.h"
#include "led.h"
#include "gpio.h"

bool aPushed() {
  
  if (!(GPIO->IN & (1 << 17))) {
    return true;
  }
  return false;
 }

 bool bPushed() {
    if (!(GPIO->IN & (1 << 26))) {
      return true;
    }
    return false;
 }