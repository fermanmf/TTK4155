#include "can.h"

#include "sam.h"
#include "consts.h"

/*
	Dual mailbox setup.
	Rx 0 for all em messages and rx 1 for controller messages
*/

void can_init() {
	PMC->PMC_PCER1 |= PMC_PCER1_PID43; //CAN0	
	CAN0->CAN_IER = CAN_IER_MB0; //enable interrupt on mailbox 0
	CAN0->CAN_BR = (CAN_PS2 - 1) << CAN_BR_PHASE2_Pos | 
				   (CAN_PS1 - 1) << CAN_BR_PHASE1_Pos | 
				   (CAN_PROPSEG - 1) << CAN_BR_PROPAG_Pos | 
				   (CAN_SJW) << CAN_BR_SJW_Pos | 
				   (33 - 1) << CAN_BR_BRP_Pos | // round(CAN_TQ * MCK_NODE2) = 33
				   CAN_BR_SMP_THREE;
	// continue from here
	CAN0->CAN_MR = CAN_MR_CANEN; //enable
}

