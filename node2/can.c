#include "can.h"

#include "sam.h"
#include "consts.h"

/*
	Dual mailbox setup.
	MB0 for controller and MB1 for em
*/

void can_init() {
	PMC->PMC_PCER1 |= PMC_PCER1_PID43; //CAN0	
	CAN0->CAN_IER = CAN_IER_MB0 | CAN_IER_MB1; //enable interrupts
	CAN0->CAN_BR = (CAN_PS2 - 1) << CAN_BR_PHASE2_Pos | 
				   (CAN_PS1 - 1) << CAN_BR_PHASE1_Pos | 
				   (CAN_PROPSEG - 1) << CAN_BR_PROPAG_Pos | 
				   (CAN_SJW) << CAN_BR_SJW_Pos | 
				   (33 - 1) << CAN_BR_BRP_Pos | // round(CAN_TQ * MCK_NODE2) = 33
				   CAN_BR_SMP_THREE;
	CAN0->CAN_MB[0]->CAN_MMR = CAN_MMR_MOT_MB_RX_OVERWRITE;
	CAN0->CAN_MB[0]->CAN_MAM = 0xFF | CAN_MAM_MIDE; // CAN 2.0 B (not A)
	CAN0->CAN_MB[0]->CAN_MID = 0xFF;
	
	
	CAN0->CAN_MB[1]->CAN_MMR = CAN_MMR_MOT_MB_RX;
	CAN0->CAN_MR = CAN_MR_CANEN; //enable
}
