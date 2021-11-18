// ===== Defining CLOCK registers =====

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

  //
  // On the microbit there is a 5 x 5 LED matrix
  // Our LEDSet routine clears all LEDs and let the specified one lid
  // The function takes row and column as parameters, this is how we count:
  //    C0 C1 C2 C3 C4
  // R0 x  x  x  x  x
  // R1 x  x  x  x  x
  // R2 x  x  x  x  x
  // R3 x  x  x  x  x
  // R4 x  x  x  x  x
  //
  // Our LED routine works as follows: Clears all LEDs and then let the one specified one lid
  //

