/**
 *
 * File name:        	tach.c                             
 * File description: 	file containing methods for setting and
 * 						reading the tachometer through the TPM0
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	13May2016                                       
 * Revision date:    	20May2016                                       
 *
 */
#include "../es670_peripheral_board.h"
#include "tach.h"

void tach_init()
{
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1);				// Clock source for TPM modules
	SIM_SCGC6 |= (SIM_SCGC6_TPM0_MASK);						// Enable clock to TPM0
	SIM_SCGC5 |= (SIM_SCGC5_PORTE_MASK);					// Enable clock to PORTE
	PORT_PCR_REG(PORTE,TACH_PIN) = PORT_PCR_MUX(TACH_ALT);  // Set PTE pin ALT

	tach_stopCounter();

	TPM0_BASE_PTR->SC |= TPM_SC_TOF(0); 					// Clear Timer Overflow Flag (SC/TOF)
	TPM0_BASE_PTR->CNT = 0;									// Reset Counter  (CNT)
	TPM0_BASE_PTR->MOD = 0xFFFF; 							// 16bit Counter final value (MOD)
	TPM0_BASE_PTR->CONTROLS->CnSC |= TPM_CnSC_CHIE(0); 		// Disable all channels (CnSC/CHIE)
	TPM0_BASE_PTR->SC |= TPM_SC_CPWMS(0); 					// Set up counting mode (SC/CPWMS)
	TPM0_BASE_PTR->SC |= TPM_SC_PS(0); 						// Set Prescaler to 1 (SC/PS)

	tach_startCounter();
}

void tach_startCounter()
{
	TPM0_BASE_PTR->SC |= TPM_SC_CMOD(TACH_CLK_SRC); // Set TPM clock (SC/CMOD)
}

void tach_stopCounter()
{
	TPM0_BASE_PTR->SC |= TPM_SC_CMOD(0); 				// Disable clock to TMP0  (SC/CMOD)
	while (TPM0_BASE_PTR->SC&TPM_SC_CMOD_MASK); 		// Wait to acknowledge timer is disabled (SC/CMOD)
}

void tach_resetCounter()
{
	TPM0_BASE_PTR->CNT = 0;
}

uint16_t tach_readCounter()
{
	return TPM0_BASE_PTR->CNT;
}

uint16_t tach_Hz(uint16_t timeBase_ms)
{
	uint16_t count = tach_readCounter();
	tach_resetCounter();
	return count/(timeBase_ms/1000)/7;
}

uint16_t tach_RPM(uint16_t timeBase_ms)
{
	return tach_Hz(timeBase_ms)/60/7;
}
