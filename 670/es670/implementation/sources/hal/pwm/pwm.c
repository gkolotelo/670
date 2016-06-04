


#include "../es670_peripheral_board.h"
#include "../mcg/mcg.h"
#include "pwm.h"


#define TPM0_CHANNEL_WIDTH 5
#define TPM1_CHANNEL_WIDTH 1
#define TPM2_CHANNEL_WIDTH 1





void pwm_initPWM(TPM_Type * timer, tpm_config tpmConfig)
{

	/*SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);


	SIM_SCGC5 |= (SIM_SCGC5_PORTD_MASK);
	PORTD_PCR1 = PORT_PCR_MUX(4);


	SIM_SOPT2	|= SIM_SOPT2_TPMSRC(0b11);
	timer->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
	timer->CNT = 1000u;
	timer->MOD = 16383u;
	timer->CONTROLS[uiChannel].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	timer->CONTROLS[uiChannel].CnV = 16383u;
*/

    //MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
    //MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK;
	uint32_t cnt_period;
	cnt_period= (1000*(tpmConfig.xtal_frequency/((2 << tpmConfig.prescaler_value)/2))/tpmConfig.period_ms);
    if (cnt_period > 65536)
    	return;
	if(timer == TPM0)
	{
		SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	}
	if(timer == TPM1)
	{
		SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	}
	if(timer == TPM2)
	{
		SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	}

	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(tpmConfig.clock_source); // Set clock source for tpmx

    timer->SC |= TPM_SC_CMOD(0); 				// Disable clock to TMPx  (SC/CMOD)
    while (timer->SC&TPM_SC_CMOD_MASK); 		// Wait to acknowledge timer is disabled (SC/CMOD)
    timer->SC |= TPM_SC_TOF(0); 					// Clear Timer Overflow Flag (SC/TOF)
    timer->SC |= TPM_SC_CPWMS(0); 					// Set up counting mode (SC/CPWMS)
    timer->CNT = 0;									// Reset Counter  (CNT)

    timer->MOD = cnt_period;
    timer->SC = TPM_SC_PS(tpmConfig.prescaler_value);
	timer->SC = TPM_SC_CMOD(1);//Selects the LPTPM counter clock modes

}

void pwm_channelInit (TPM_Type * timer, tpm_config tpmConfig, channel_config channelConfig)
{
	uint32_t cnt_period, cnv_period;
	cnt_period= (1000*(tpmConfig.xtal_frequency/((2 << tpmConfig.prescaler_value)/2))/tpmConfig.period_ms);
	if (cnt_period > 65536)
		return;
	cnv_period= (1000*(tpmConfig.xtal_frequency/((2 << tpmConfig.prescaler_value)/2))/channelConfig.pulse_width_ms);
	if (cnv_period > cnt_period)
		return;
	if(timer == TPM0)
	{
		if(channelConfig.channel > TPM0_CHANNEL_WIDTH) return;
	}
	else if(timer == TPM1)
	{
		if(channelConfig.channel > TPM1_CHANNEL_WIDTH) return;
	}
	else if(timer == TPM2)
	{
		if(channelConfig.channel > TPM2_CHANNEL_WIDTH) return;
	}

	timer->CONTROLS[channelConfig.channel].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	timer->CONTROLS[channelConfig.channel].CnV = cnv_period;
}

void pwm_setPortPinPwm(PORT_Type * port, GPIO_Type * gpio, char pinNo)
{
	if(port == PORTA)
	{
		SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	}
	else if(port == PORTB)
	{
		SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	}
	else if(port == PORTC)
	{
		SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	}
	else if(port == PORTD)
	{
		SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	}
	else if(port == PORTE)
	{
		SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	}
    port->PCR[pinNo] = PORT_PCR_MUX(3);
    gpio->PDDR = 0b1 << pinNo;

}

