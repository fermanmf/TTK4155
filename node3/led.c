#include "led.h"
#include "gpio.h"

#define PIN_LED_ROW_0  13
#define PIN_LED_ROW_1  14
#define PIN_LED_ROW_2  15

#define MASK_LED_ROW_0  (1uL << 13)
#define MASK_LED_ROW_1  (1uL << 14)
#define MASK_LED_ROW_2  (1uL << 15)

#define PIN_LED_COL_0  (4)
#define PIN_LED_COL_1  (5)
#define PIN_LED_COL_2  (6)
#define PIN_LED_COL_3  (7)
#define PIN_LED_COL_4  (8)

#define MASK_LED_COL_0  (1uL <<  4)
#define MASK_LED_COL_1  (1uL <<  5)
#define MASK_LED_COL_2  (1uL <<  6)
#define MASK_LED_COL_3  (1uL <<  7)
#define MASK_LED_COL_4  (1uL <<  8)
#define MASK_LED_COL_5  (1uL <<  9)
#define MASK_LED_COL_6  (1uL << 10)
#define MASK_LED_COL_7  (1uL << 11)
#define MASK_LED_COL_8  (1uL << 12)

#define MASK_ALL_LED_COL (MASK_LED_COL_0 | MASK_LED_COL_1 | MASK_LED_COL_2 | MASK_LED_COL_3 | MASK_LED_COL_4 | MASK_LED_COL_5 | MASK_LED_COL_6 | MASK_LED_COL_7 | MASK_LED_COL_8)
#define MASK_ALL_LED_ROW (MASK_LED_ROW_0 | MASK_LED_ROW_1 | MASK_LED_ROW_2)

static const led_map _aLEDMap[5][5] = {
                                   {{0,0}, {1,3}, {0,1}, {1,4}, {0,2}},
                                   {{2,3}, {2,4}, {2,5}, {2,6}, {2,7}},
                                   {{1,1}, {0,8}, {1,2}, {2,8}, {1,0}},
                                   {{0,7}, {0,6}, {0,5}, {0,4}, {0,3}},
                                   {{2,2}, {1,6}, {2,0}, {1,5}, {2,1}}
                                 };

void initLEDs() {
  unsigned int v;

  CLOCK->HFCLKSTARTED = 0;
  CLOCK->HFCLKSTART = 1;
  while (CLOCK->HFCLKSTARTED == 0);
  CLOCK->HFCLKSTARTED = 0;
  GPIO->OUTCLR = MASK_ALL_LED_ROW;
  GPIO->OUTSET = MASK_ALL_LED_COL;
  GPIO->DIRSET = MASK_ALL_LED_ROW;
  GPIO->DIRSET = MASK_ALL_LED_COL;
}

void setSelectedLED(int Row, int Col) {
  int RowUnmapped;
  int ColUnmapped;

  // Turn all LEDs off
  GPIO->OUTCLR = MASK_ALL_LED_ROW;
  GPIO->OUTSET = MASK_ALL_LED_COL;

  // Set the selected led on
  RowUnmapped = _aLEDMap[Row][Col].RowUnmapped;
  ColUnmapped = _aLEDMap[Row][Col].ColUnmapped;
  GPIO->OUTSET = (1uL << (RowUnmapped + PIN_LED_ROW_0));
  GPIO->OUTCLR = (1uL << (ColUnmapped + PIN_LED_COL_0));
}