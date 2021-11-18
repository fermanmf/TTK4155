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

typedef struct {
  int RowUnmapped;
  int ColUnmapped;
} _LED_MAP;

void _InitLEDs();

void _SetLED(int Row, int Col);

  // Safety
      /*
        if(n&(1<<j)) {
          _SetLED(i, 4-j);
          }
          */