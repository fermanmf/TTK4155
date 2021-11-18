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


//      Static data

//
// LED coordinates mapping table taken from  mbed example code as it was faster than complete reverse engineering it
// There are no schematics available, so mapping needs to be found out by try & error
// See explanation why coordinates need to be mapped in _InitLEDs()
//
// The array below covers [Row][Column] of the 5x5 matrix and holds the values for Row,Column for the 3x9 matrix
//
static const _LED_MAP _aLEDMap[5][5] = {
                                   {{0,0}, {1,3}, {0,1}, {1,4}, {0,2}},
                                   {{2,3}, {2,4}, {2,5}, {2,6}, {2,7}},
                                   {{1,1}, {0,8}, {1,2}, {2,8}, {1,0}},
                                   {{0,7}, {0,6}, {0,5}, {0,4}, {0,3}},
                                   {{2,2}, {1,6}, {2,0}, {1,5}, {2,1}}
                                 };

void _InitLEDs() {
  unsigned int v;
  //
  // The LED matrix on the BBC is a 5 x 5 one but logically/electrically it is a 3 x 9 one (row x column), two coordinates not connected to any LED (5x5 = 25, 3x9 = 27)
  // However, this confuses the user, so we the 5 x 5 coordinates to the 3 x 9 ones and make all our functions accept the 5 x 5 coordinates which the user can understand
  //
  // LEDs only lid if there is a voltage difference between both ends (each connected to a GPIO that controls a column and one that controls a row of LEDs)
  // Now there are the following possibilities:
  // R = HIGH  C = HIGH   => No voltage diff, LED off
  // R = LOW   C = HIGH   => Voltage diff, LED potentially on (depends on in which direction the LED blocks)
  // R = HIGH  C = LOW    => Voltage diff, LED potentially on (depends on in which direction the LED blocks)
  // R = LOW   C = LOW    => No voltage diff, LED off
  //
  // So there is only 1 combination that makes a LED lid
  // On the BBC it is this one:
  // R = HIGH, C = LOW
  //
  // We use R = LOW, C = HIGH as default, so we can switch on a LED by changing the row to HIGH and the col to LOW
  // This way, no other LED will lid
  //
  CLOCK->HFCLKSTARTED = 0;
  CLOCK->HFCLKSTART    = 1;
  while (CLOCK->HFCLKSTARTED == 0);
  CLOCK->HFCLKSTARTED = 0;
  GPIO->OUTCLR = MASK_ALL_LED_ROW;
  GPIO->OUTSET = MASK_ALL_LED_COL;
  GPIO->DIRSET = MASK_ALL_LED_ROW;
  GPIO->DIRSET = MASK_ALL_LED_COL;
}

// Declaring _SetLED
void _SetLED(int Row, int Col) {
  int RowUnmapped;
  int ColUnmapped;

  int foodRow;
  int foodCol;
  //
  // Clear all LEDs
  //
  GPIO->OUTCLR = MASK_ALL_LED_ROW;
  GPIO->OUTSET = MASK_ALL_LED_COL;
  //
  // Let the specific one lid
  // For that, we first need to map the 5x5 matrix coordinates to the 3x9 ones to find out the correct position
  //
  RowUnmapped = _aLEDMap[Row][Col].RowUnmapped;
  ColUnmapped = _aLEDMap[Row][Col].ColUnmapped;
  GPIO->OUTSET = (1uL << (RowUnmapped + PIN_LED_ROW_0));
  GPIO->OUTCLR = (1uL << (ColUnmapped + PIN_LED_COL_0));
}