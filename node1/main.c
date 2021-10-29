#include <stdio.h>

#include "uart.h"
#include "utils.h"
#include "../shared/em.h"


int main(){
	uart_init(9600);
	init_xmem();

	
	printf("Terminated\n");	
}