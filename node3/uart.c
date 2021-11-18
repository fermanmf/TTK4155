#include "uart.h"
#include "gpio.h"


void uart_init(){
    GPIO->DIRSET = (1 << TXD_PIN);
    GPIO->DIRCLR = (1 << RXD_PIN);
    UART->BAUDRATE = BAUDRATE_9600;
    UART->PSELTXD = TXD_PIN;
    UART->PSELRXD = RXD_PIN;
    UART->PSELCTS = -1;
    UART->PSELRTS = -1;
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uart_send(char letter) {
    UART->STARTTX = 1;
    UART->TXDRDY = 0;
    UART->TXD = letter;
    while (!UART->TXDRDY);
    UART->STOPTX = 1;
}

void _print(char *string, int length) {
  for (int i = 0; i < length; ++i) {
    uart_send(string[i]);
  }
}
