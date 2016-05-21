


#include "../es670_peripheral_board.h"


#define TPM0_CHANNEL_WIDTH 5
#define TPM1_CHANNEL_WIDTH 1
#define TPM2_CHANNEL_WIDTH 1

typedef enum
{
    NoneClk,
    McgPllFllClk,
    OscerClk,
    McgIrcClk
} pwm_clock_source_e;

typedef enum
{
	Edge,
	Center,
	EdgeInverted
} pwm_alignment_e;

typedef enum
{
	Prescaler1,
	Prescaler2,
	Prescaler4,
	Prescaler8,
	Prescaler16,
	Prescaler32,
	Prescaler64,
	Prescaler128
} pwm_prescaler_e;

typedef struct
{
	pwm_clock_source_e clock_source;
	pwm_prescaler_e prescaler_value;
	uint16_t period_ms;
} tpm_config;

typedef struct
{
	pwm_alignment_e alignment;
	uint16_t pulse_width_ms;
	bool interrupt_enable;
} channel_config;



void pwm_initPWM(TPM_Type * timer, tpm_config config)
{

	/*SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);


	SIM_SCGC5 |= (SIM_SCGC5_PORTD_MASK);
	PORTD_PCR1 = PORT_PCR_MUX(4);

	if(timer == TPM0)
	{
		if(uiChannel > TPM0_CHANNEL_WIDTH) return;
		SIM_SCGC6 |= (SIM_SCGC6_TPM0_MASK);
	}
	if(timer == TPM1)
	{
		if(uiChannel > TPM1_CHANNEL_WIDTH) return;
		SIM_SCGC6 |= (SIM_SCGC6_TPM1_MASK);
	}
	if(timer == TPM2)
	{
		if(uiChannel > TPM2_CHANNEL_WIDTH) return;
		SIM_SCGC6 |= (SIM_SCGC6_TPM2_MASK);
	}
	SIM_SOPT2	|= SIM_SOPT2_TPMSRC(0b11);
	timer->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
	timer->CNT = 1000u;
	timer->MOD = 16383u;
	timer->CONTROLS[uiChannel].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	timer->CONTROLS[uiChannel].CnV = 16383u;
*/

    //MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
    //MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK;
    SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
    SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);

    TPM2_BASE_PTR->SC |= TPM_SC_CMOD(0); 				// Disable clock to TMP2  (SC/CMOD)
    while (TPM2_BASE_PTR->SC&TPM_SC_CMOD_MASK); 		// Wait to acknowledge timer is disabled (SC/CMOD)
    TPM2_BASE_PTR->SC |= TPM_SC_TOF(0); 					// Clear Timer Overflow Flag (SC/TOF)
    TPM2_BASE_PTR->SC |= TPM_SC_CPWMS(0); 					// Set up counting mode (SC/CPWMS)
    TPM2_BASE_PTR->CNT = 0;									// Reset Counter  (CNT)
    TPM2_BASE_PTR->MOD = 32000;

    TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(0);


    SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORTB_BASE_PTR->PCR[18] = PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(3);

    PTB_BASE_PTR->PDDR = 0b11 << 19;

    TPM2_BASE_PTR->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
    TPM2_BASE_PTR->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;

    TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->CONTROLS[1].CnV = 16000;



}




