/**
 *
 * File name:        	tach.c                             
 * File description: 	Source file containing methods for setting and
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

/**
 * Method name:			tach_init
 * Method description: 	Initializes TPM0 module for counter
 * 						operation on external clock.
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
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

/**
 * Method name:			tach_startCounter
 * Method description: 	Starts the counter.
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_startCounter()
{
	TPM0_BASE_PTR->SC |= TPM_SC_CMOD(TACH_CLK_SRC); // Set TPM clock (SC/CMOD)
}

/**
 * Method name:			tach_stopCounter
 * Method description: 	Stops the counter.
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_stopCounter()
{
	TPM0_BASE_PTR->SC |= TPM_SC_CMOD(0); 				// Disable clock to TMP0  (SC/CMOD)
	while (TPM0_BASE_PTR->SC&TPM_SC_CMOD_MASK); 		// Wait to acknowledge timer is disabled (SC/CMOD)
}

/**
 * Method name:			tach_readCounter
 * Method description: 	Returns the value on the counter.
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
uint16_t tach_readCounter()
{
	return TPM0_BASE_PTR->CNT;
}

/**
 * Method name:			tach_resetCounter
 * Method description: 	Resets the count.
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_resetCounter()
{
	TPM0_BASE_PTR->CNT = 0;
}

/**
 * Method name:			tach_Hz
 * Method description: 	Returns the value of the tachometer
 * 						in units of Hertz.
 * Input params:      	uitimeBase_ms = Period used
 * 						between readings
 * Output params:     	Revolutions per second                       
 */
uint16_t tach_Hz(uint16_t timeBase_ms)
{
	uint16_t count = tach_readCounter();
	tach_resetCounter();
	return count/(timeBase_ms/1000)/7;
}

/**
 * Method name:			tach_RPM
 * Method description: 	Returns the value of the tachometer
 * 						in units of RPM.
 * Input params:      	uitimeBase_ms = Period used
 * 						between readings
 * Output params:     	Revolutions per minute                          
 */
uint16_t tach_RPM(uint16_t timeBase_ms)
{
	return tach_Hz(timeBase_ms)/60/7;
}
