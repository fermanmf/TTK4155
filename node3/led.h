/**
 * @file led.h
 * @date 19 Nov 2021
 * @brief File containing funcitons for initalizing the leds on the microbit and set them specifically
 */
#include <stdint.h>

#define CLOCK ((CLOCK_REGS*)0x40000000)

/**
 * @brief Struct for CLOCL register
 */
typedef struct {
  volatile unsigned int HFCLKSTART;      // 0x000 Start HFCLK crystal oscillator
  volatile unsigned int HFCLKSTOP;       // Stop HFCLK crystal oscillator
  volatile unsigned int LFCLKSTART;      // Start LFCLK source
  volatile unsigned int LFCLKSTOP;       // Stop LFCLK source
  volatile unsigned int CAL;             // 0x010 Start calibration of LFCLK RC oscillator
  volatile unsigned int CTSTART;         // 0x014 Start calibration timer
  volatile unsigned int CTSTOP;          // 0x018 Stop calibration timer
  volatile unsigned int RESERVED0;  
  volatile unsigned int HFCLKSTARTED;    // 0x100 16 MHz oscillator started
  volatile unsigned int LFCLKSTARTED;    // 32 kHz oscillator started
  volatile unsigned int RESERVED1;  
  volatile unsigned int DONE;            // Calibration of LFCLK RC oscillator complete event
  volatile unsigned int CTTO;            // Calibration timer timeout
} CLOCK_REGS;

/**
 * @brief Struct for the led_map
 */
typedef struct {
  int RowUnmapped;  /**< Number of row in the led_mapt#a. */
  int ColUnmapped;  /**< Number of column in the led_map#a. */
} led_map;

/**
 * @brief Initialize the LEDs on the micro bit
 */
void initLEDs();

/**
 * @brief Sets the light on a spesific led from the led_map
 * 
 * @param Row  The selected row for the led in the led matrix
 * @param Col  The selected column for the led in the led matrix
 */
void setSelectedLED(int Row, int Col);