// ===== Defining CLOCK registers =====
#include <stdint.h>

#define CLOCK ((CLOCK_REGS*)0x40000000)

typedef struct {
  volatile unsigned int HFCLKSTART;      // 0x000 Start HFCLK crystal oscillator
  volatile unsigned int HFCLKSTOP;       // Stop HFCLK crystal oscillator
  volatile unsigned int LFCLKSTART;      // Start LFCLK source
  volatile unsigned int LFCLKSTOP;       // Stop LFCLK source
  volatile unsigned int CAL;             // 0x010 Start calibration of LFCLK RC oscillator
  volatile unsigned int CTSTART;         // 0x014 Start calibration timer
  volatile unsigned int CTSTOP;          // 0x018 Stop calibration timer
  volatile unsigned int aDummy[57];  
  volatile unsigned int HFCLKSTARTED;    // 0x100 16 MHz oscillator started
  volatile unsigned int LFCLKSTARTED;    // 32 kHz oscillator started
  volatile unsigned int Dummy1;  
  volatile unsigned int DONE;            // Calibration of LFCLK RC oscillator complete event
  volatile unsigned int CTTO;            // Calibration timer timeout
} CLOCK_REGS;

typedef struct {
  int RowUnmapped;
  int ColUnmapped;
} _LED_MAP;

void _InitLEDs();

void _SetLED(int Row, int Col);