#include "stdint.h"

#define UART ((NREF_UART_REG *)0x40002000)

typedef struct
{
    volatile uint32_t STARTRX;
    volatile uint32_t STOPRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVED5[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVED6[56];
    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVED7[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED8[1];
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED9[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVED10[110];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED0[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED1[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED2[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED4[17];
    volatile uint32_t CONFIG;
} NREF_UART_REG;

#define TXD_PIN 24
#define RXD_PIN 25
#define BAUDRATE_9600 0X00275000

void uart_init();
void uart_send(char letter);
void _print(char *string, int length);
