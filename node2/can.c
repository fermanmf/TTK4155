#include "can.h"

#include <stdint.h>

#include "sam.h"
#include "consts.h"
#include "printf-stdarg.h"
#include "controller.h"
#include "panic.h"

/*
	Dual mailbox setup.
	MB0 for controller and MB1 for em
	MB0 only receives messages with id 0xFF and MB1 takes all other messages
*/

void CAN0_Handler() {
	printf("Hello from CAN interrupt\n\r");
	const uint32_t mb_id = (CAN0->CAN_SR & 0xFF) / 2;	
	if (CAN0->CAN_MB[mb_id].CAN_MSR & CAN_MSR_MMI) {
		printf("Error: mailbox message ignored flag set for MB%u\n\r", mb_id);
		panic();
	}	
	uint32_t data_low = CAN0->CAN_MB[mb_id].CAN_MDL;
	uint32_t data_high = CAN0->CAN_MB[mb_id].CAN_MDL;
	const uint8_t id = (CAN0->CAN_MB[mb_id].CAN_MID & CAN_MID_MIDvA_Msk) >> CAN_MID_MIDvA_Pos;
	const uint8_t data_length = (CAN0->CAN_MB[mb_id].CAN_MSR & CAN_MSR_MDLC_Msk) >> CAN_MSR_MDLC_Pos;
	
	switch(id) {
		case 0:
			if (id != 0xFF || data_length != 4) {
				printf("Error: message received in MB0 had id %x and length %u\n\r", id, data_length);
				panic();
			}
			controller_joystick_x = data_low & 0xFF;
			controller_joystick_y = data_low & 0xFF00;
			controller_slider_left = data_low & 0xFF0000;
			controller_slider_right = data_low & 0xFF000000;
			break;
		
		case 1: {
			uint8_t data[data_length];
			for (int i = 0; i < data_length; i++) {
				if (i<4) {
					data[i] = data_low & 0xFF;
					data_low >>= 8;
				} else {
					data[i] = data_high & 0xFF;
					data_high >>= 8;
				}
			}		
			can_message_received_cb(id, data, data_length);			
			break;
		}
		
		default:
			printf("Error: message received in MB%u\n\r", id);
			break;
	}
	CAN0->CAN_MB[id].CAN_MCR = CAN_MCR_MTCR; // MB ready for new message
}

void can_init() {
	PIOA->PIO_PDR = PIO_PA1A_CANRX0 | PIO_PA0A_CANTX0; // PIO Disable Register
	PIOA->PIO_PUER = PIO_PA1A_CANRX0 | PIO_PA0A_CANTX0; // Pull-up Enable Register
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID43; //CAN0	
	CAN0->CAN_IER = CAN_IER_MB0 | CAN_IER_MB1; //enable interrupts
	CAN0->CAN_BR = (CAN_PS2 - 1) << CAN_BR_PHASE2_Pos | 
				   (CAN_PS1 - 1) << CAN_BR_PHASE1_Pos | 
				   (CAN_PROPSEG - 1) << CAN_BR_PROPAG_Pos | 
				   (CAN_SJW) << CAN_BR_SJW_Pos | 
				   (CAN_NODE2_BRP - 1) << CAN_BR_BRP_Pos; /*|
				   CAN_BR_SMP_THREE;
	*/
	CAN0->CAN_MB[0].CAN_MAM = 0xFF << CAN_MAM_MIDvA_Pos; // Message Acceptance Mask
	CAN0->CAN_MB[0].CAN_MID = 0xFF << CAN_MID_MIDvA_Pos; // Message ID
	CAN0->CAN_MB[0].CAN_MMR = CAN_MMR_MOT_MB_RX; // Message Mode Register
	CAN0->CAN_MB[1].CAN_MMR = CAN_MMR_MOT_MB_RX; // Message Mode Register
	
	CAN0->CAN_MR = CAN_MR_CANEN; //enable
	NVIC_EnableIRQ(ID_CAN0);
}



