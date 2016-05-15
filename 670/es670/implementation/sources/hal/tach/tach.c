
#include "../es670_peripheral_board.h"


void tach_init()
{
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM_SCGC6 |= (SIM_SCGC6_TPM0_MASK);
	SIM_SCGC5 |= (SIM_SCGC5_PORTE_MASK);
	PORTE_PCR29 = PORT_PCR_MUX(4);

	TPM0_BASE_PTR->SC |= TPM_SC_CMOD(3) | TPM_SC_PS(0);


}
