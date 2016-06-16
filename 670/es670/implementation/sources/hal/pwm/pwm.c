/**
 *
 * File name:        	pwm.c                             
 * File description: 	Source file containing methods for initializing
 * 						and operating the PWM function on TPM modules
 *           			
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	20May2016                                       
 * Revision date:    	03Jun2016                                        
 *
 */

#include "pwm.h"
#include "MKL25Z4.h"
#include <stdint.h>

#define TPM0_CHANNEL_INSTANCES 6
#define TPM1_CHANNEL_INSTANCES 2
#define TPM2_CHANNEL_INSTANCES 2


#define BOARD_DEBUG_PWM_INSTANCE
/*
Comment #define above for production code
*/

/**
 * Method name:			initPwm
 * Method description:  Initializes PWM module with specified configuration
 * Input params:      	tTimer = TPMx base address
 * 						tTpmConfig = Configuration for TPM module
 * Output params:     	int = Error (0) or Success (0)
 */
int pwm_initPwm(TPM_Type * tTimer, tpm_config_t tTpmConfig)
{
	uint64_t cnt_period;

	if(TPM0 == tTimer)
		SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	else if(TPM1 == tTimer)
		SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	else if(TPM2 == tTimer)
		SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	else return 0;

	cnt_period = ((tTpmConfig.uiPeriod_us*(uint64_t)(tTpmConfig.uiXtal_frequency/(1 << tTpmConfig.ePrescaler_value)))/1000000);
	if(Center == tTpmConfig.eAlignment)
		cnt_period = cnt_period/2;
	if (cnt_period > 65536)
		return 0;

	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(tTpmConfig.eClock_source); // Set clock source for TMPx

	#ifdef BOARD_DEBUG_PWM_INSTANCE
		tTimer->CONF |= TPM_CONF_DBGMODE(0b11);
	#endif

	tTimer->SC &= !TPM_SC_CMOD_MASK; 				// Disable clock to TMPx  (SC,CMOD)
    while (tTimer->SC&TPM_SC_CMOD_MASK); 			// Wait to acknowledge tTimer is disabled (SC,CMOD)
    tTimer->SC |= TPM_SC_TOF(0); 					// Clear tTimer Overflow Flag (SC,TOF)
    tTimer->SC |= TPM_SC_CPWMS(tTpmConfig.eAlignment);// Set up counting mode (SC,CPWMS)
    tTimer->CNT = 0;								// Reset Counter  (CNT)

    tTimer->MOD = cnt_period;						// Set TPM counter period (MOD)
    tTimer->SC |= TPM_SC_PS(tTpmConfig.ePrescaler_value);
	tTimer->SC |= TPM_SC_CMOD(1);					//Selects the LPTPM counter clock modes

	return 1;
}

/**
 * Method name:			channelInit
 * Method description:  Initializes the PWM channel with specified configuration
 * Input params:      	tTimer = TPMx base address
 * 						tTpmConfig = Configuration for TPM module
 * 						tChannelConfig = Configuration for PWM channel
 * Output params:     	int = Error (0) or Success (0)
 */
int pwm_channelInit (TPM_Type * tTimer, tpm_config_t tTpmConfig, channel_config_t tChannelConfig)
{
	uint64_t cnt_period, cnv_period, cnsc;

	cnsc = 0x00;
	cnt_period = ((tTpmConfig.uiPeriod_us*(uint64_t)(tTpmConfig.uiXtal_frequency/(1 << tTpmConfig.ePrescaler_value)))/1000000);
	if(Center == tTpmConfig.eAlignment)
		cnt_period = cnt_period/2;
	if (cnt_period > 65536)
		return 0;
	cnv_period = (cnt_period*tChannelConfig.uiPulse_width_us)/tTpmConfig.uiPeriod_us;

	if(TPM0 == tTimer)
		if(tChannelConfig.uiChannel > TPM0_CHANNEL_INSTANCES - 1) return 0;
	else if(TPM1 == tTimer)
		if(tChannelConfig.uiChannel > TPM1_CHANNEL_INSTANCES - 1) return 0;
	else if(TPM2 == tTimer)
		if(tChannelConfig.uiChannel > TPM2_CHANNEL_INSTANCES - 1) return 0;
	else return 0;

	if(DisableChannel == tChannelConfig.eChannelOutput)
	{
		cnsc = 0;
	}
	else if(NoInversion == tChannelConfig.eChannelOutput)
	{
		cnsc |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	}
	else if(Inversion == tChannelConfig.eChannelOutput)
	{
		cnsc |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	}

	if(0 != tChannelConfig.uiInterrupt_enable)
		cnsc |= TPM_CnSC_CHIE_MASK;

	tTimer->CONTROLS[tChannelConfig.uiChannel].CnSC = cnsc;
	tTimer->CONTROLS[tChannelConfig.uiChannel].CnV = cnv_period;

	return 1;
}

/**
 * Method name:			changeChannelPeriod
 * Method description:  Changes the period of the PWM on the channel
 * Input params:      	tTimer = TPMx base address
 * 						tTpmConfig = Configuration for TPM module
 * 						uiChannel = PWM channel
 * 						uiPulseWidth_us = Channel period in us
 * Output params:     	int = Error (0) or Success (0)
 */
int pwm_changeChannelDuty(TPM_Type * tTimer, tpm_config_t tTpmConfig, uint16_t uiChannel, uint32_t uiPulseWidth_us)
{
	uint64_t cnt_period, cnv_period;

	cnt_period = ((tTpmConfig.uiPeriod_us*(uint64_t)(tTpmConfig.uiXtal_frequency/(1 << tTpmConfig.ePrescaler_value)))/1000000);
	if(Center == tTpmConfig.eAlignment)
		cnt_period = cnt_period/2;
	if (cnt_period > 65536)
		return 0;
	cnv_period= (cnt_period*uiPulseWidth_us)/tTpmConfig.uiPeriod_us;

	tTimer->CONTROLS[uiChannel].CnV = cnv_period;
	return 1;
}

/**
 * Method name:			changeModulePeriod
 * Method description:  Changes the TPM module period
 * Input params:      	tTimer = TPMx base address
 * 						tTpmConfig = Configuration for TPM module
 * Output params:     	int = Error (0) or Success (0)  	                        
 */
int pwm_changeModulePeriod(TPM_Type * tTimer, tpm_config_t tTpmConfig)
{
	uint64_t cnt_period;

	cnt_period = ((tTpmConfig.uiPeriod_us*(uint64_t)(tTpmConfig.uiXtal_frequency/(1 << tTpmConfig.ePrescaler_value)))/1000000);
	if(Center == tTpmConfig.eAlignment)
		cnt_period = cnt_period/2;
	if (cnt_period > 65536)
		return 0;
    tTimer->MOD = cnt_period;
	tTimer->CNT = 0;

	return 1;
}

/**
 * Method name:			deinitPwm
 * Method description:  Deinitializes PWM module
 * Input params:      	tTimer = TPMx base address
 * Output params:     	n/a
 */
void pwm_deinitPwm(TPM_Type * tTimer)
{
	tTimer->SC &= !TPM_SC_CMOD_MASK; 					// Disable clock to TMPx  (SC,CMOD)
    while (tTimer->SC&TPM_SC_CMOD_MASK); 				// Wait to acknowledge tTimer is disabled (SC,CMOD)
	tTimer->SC |= TPM_SC_TOF(0); 						// Clear tTimer Overflow Flag (SC,TOF)
    tTimer->CNT = 0;									// Reset Counter  (CNT)
    if(TPM0 == tTimer)
		SIM_BASE_PTR->SCGC6 &= !SIM_SCGC6_TPM0_MASK;
	else if(TPM1 == tTimer)
		SIM_BASE_PTR->SCGC6 &= !SIM_SCGC6_TPM1_MASK;
	else if(TPM2 == tTimer)
		SIM_BASE_PTR->SCGC6 &= !SIM_SCGC6_TPM2_MASK;
}

/**
 * Method name:			disableCounter
 * Method description:  Disables the module counter
 * Input params:      	tTimer = TPMx base address
 * Output params:     	n/a
 */
void pwm_disableCounter(TPM_Type * tTimer)
{
	tTimer->SC &= !TPM_SC_CMOD_MASK; 					// Disable clock to TMPx  (SC,CMOD)
    while (tTimer->SC&TPM_SC_CMOD_MASK); 				// Wait to acknowledge tTimer is disabled (SC,CMOD)
}

/**
 * Method name:			enableCounter
 * Method description:  Enables the module counter
 * Input params:      	tTimer = TPMx base address
 * Output params:     	n/a
 */
void pwm_enableCounter(TPM_Type * tTimer)
{
	tTimer->SC |= TPM_SC_CMOD(1);
}

