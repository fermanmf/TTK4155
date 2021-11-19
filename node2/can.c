#include "can.h"

#include <stdint.h>

#include "sam.h"
#include "consts.h"
#include "printf-stdarg.h"
#include "panic.h"

/*
	Dual mailbox setup.
	MB0 rx
	MB1 tx
*/

static void (*message_received_cb)(uint8_t, uint8_t[], uint8_t);

void can_init(void (*callback)(uint8_t, uint8_t[], uint8_t)) {
	message_received_cb = callback;
	PIOA->PIO_PDR = PIO_PA1A_CANRX0 | PIO_PA0A_CANTX0; // PIO Disable Register
	PIOA->PIO_PUER = PIO_PA1A_CANRX0 | PIO_PA0A_CANTX0; // Pull-up Enable Register
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID43; //CAN0	
	CAN0->CAN_IER = CAN_IER_MB0; // Interrupt Enable Register
	CAN0->CAN_BR = (CAN_PS2 - 1) << CAN_BR_PHASE2_Pos | 
				   (CAN_PS1 - 1) << CAN_BR_PHASE1_Pos | 
				   (CAN_PROPSEG - 1) << CAN_BR_PROPAG_Pos | 
				   (CAN_SJW) << CAN_BR_SJW_Pos | 
				   (CAN_NODE2_BRP - 1) << CAN_BR_BRP_Pos |
				   CAN_BR_SMP_THREE;
	
	CAN0->CAN_MB[0].CAN_MMR = CAN_MMR_MOT_MB_RX; // Message Mode Register
	CAN0->CAN_MB[1].CAN_MMR = CAN_MMR_MOT_MB_TX; // Message Mode Register
	
	CAN0->CAN_MR = CAN_MR_CANEN; // CAN ENable
	NVIC_EnableIRQ(ID_CAN0);
}

void can_send(uint8_t id, uint8_t data[], uint8_t data_length) {
	if (data_length > 8) {
		printf("can error: data length (%u) is greater than 8", data_length);
	}
	
	while (!(CAN0->CAN_MB[1].CAN_MSR & CAN_MSR_MRDY)); // Wait for Mailbox ReaDY
	CAN0->CAN_MB[1].CAN_MID = id << CAN_MID_MIDvA_Pos; // Message ID
	CAN0->CAN_MB[1].CAN_MDL = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
	CAN0->CAN_MB[1].CAN_MDH = data[7] << 24 | data[6] << 16 | data[5] << 8 | data[4];
	CAN0->CAN_MB[1].CAN_MCR = data_length << CAN_MCR_MDLC_Pos; // Message Control Register
		
	CAN0->CAN_TCR = CAN_TCR_MB1; // Transfer Command Register
}

void can_send_empty(uint8_t id) {
	while (!(CAN0->CAN_MB[1].CAN_MSR & CAN_MSR_MRDY)); // Wait for Mailbox ReaDY
	CAN0->CAN_MB[1].CAN_MID = id << CAN_MID_MIDvA_Pos; // Message ID
	CAN0->CAN_MB[1].CAN_MCR = 0; // Message Control Register (data length)
	
	CAN0->CAN_TCR = CAN_TCR_MB1; // Transfer Command Register
}


void CAN0_Handler() {
	if (CAN0->CAN_MB[0].CAN_MSR & CAN_MSR_MMI) {
		printf("can error: mailbox message ignored flag set for MB0\n\r");
		panic();
	}
	uint32_t data_low = CAN0->CAN_MB[0].CAN_MDL;
	uint32_t data_high = CAN0->CAN_MB[0].CAN_MDL;
	const uint8_t id = (CAN0->CAN_MB[0].CAN_MID & CAN_MID_MIDvA_Msk) >> CAN_MID_MIDvA_Pos;
	const uint8_t data_length = (CAN0->CAN_MB[0].CAN_MSR & CAN_MSR_MDLC_Msk) >> CAN_MSR_MDLC_Pos;
	
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
	(*message_received_cb)(id, data, data_length);

	CAN0->CAN_MB[0].CAN_MCR = CAN_MCR_MTCR; // MB ready for new message
}
