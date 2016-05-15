
#include "../es670_peripheral_board.h"


void cooler_init()
{
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK);
	PORTA_PCR13 = PORT_PCR_MUX(1);
	PTA_BASE_PTR->PDDR = 1 << 13;
	PTA_BASE_PTR->PSOR = 1 << 13;
}
