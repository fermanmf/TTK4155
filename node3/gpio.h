/**
 * @file gpio.h
 * @date 19 Nov 2021
 * @brief File containing setup for the GPIO register
 */

#define GPIO ((GPIO_REGS*)0x50000000)

/**
 * @brief Struct for GPIO register
 */
typedef struct {
  volatile unsigned int RESERVED0[321];
  volatile unsigned int OUT;          // 0x504 Write GPIO port
  volatile unsigned int OUTSET;       //       Set individual bits in GPIO port
  volatile unsigned int OUTCLR;       //       Clear individual bits in GPIO port
  volatile unsigned int IN;           // 0x510 Read GPIO port
  volatile unsigned int DIR;          //       Direction of GPIO pins
  volatile unsigned int DIRSET;       //       Setting DIR register
  volatile unsigned int DIRCLR;       //       Clearing DIR register
  volatile unsigned int RESERVED1[120]; // 0x600 Reserved
  volatile unsigned int PIN_CNF[31];  // 0x700 Configuration of pin 0-31
} GPIO_REGS;