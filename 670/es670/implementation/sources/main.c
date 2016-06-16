/**
 *
 * File name:        	main.c                             
 * File description: 	Source file containing main entry point of progam.
 *           			
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	01Apr2016                                       
 * Revision date:    	10Jun2016                                        
 *
 */

/* system includes */
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"

/* Peripheral includes */
#include "hal/mcg/mcg.h"
#include "hal/util/util.h"
#include "hal/util/tc_hal.h"
#include "hal/pwm/pwm.h"
#include "hal/buzzer/buzzer.h"
#include "hal/ledswi/ledswi.h"
#include "hal/display_7segments/display_7segments.h"
#include "hal/lcd/lcd.h"
#include "hal/cooler/cooler.h"
#include "hal/heater/heater.h"
#include "hal/adc/adc.h"
#include "hal/tach/tach.h"
#include "hal/uart/debugUart.h"
#include "hal/uart/interpreter.h"



/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         100 * 10000 /* 1000000 micro seconds */

/* globals */
volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

void main_cyclicExecuteIsr(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}

int boardInit()
{
    mcg_clockInit();
}

int peripheralInit()
{
	buzzer_init();
	ledswi_initLedSwitch(1,3);
	display_7segments_initDisplays();
	lcd_initLcd();
	cooler_initForPwm();
	heater_initForPwm();
	adc_initAdc();
	tach_init();

	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB_BASE_PTR->PCR[18] = PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(3);
	PTB_BASE_PTR->PDDR = 0b11 << 19;
	tpm_config_t tpmConfig =
	{
			.eClock_source = McgPllFllClk,
			.uiPeriod_us = 1000,
			.ePrescaler_value = Prescaler128,
			.uiXtal_frequency = 40000000,
			.eAlignment = Edge
	};
	/* Configure for 50% Duty Cycle */
	channel_config_t channelConfig_cooler =
	{
			.eChannelOutput = NoInversion,
			.uiChannel = 1,
			.uiInterrupt_enable = 0,
			.uiPulse_width_us = 500
	};

	pwm_initPwm(TPM1, tpmConfig);
	pwm_channelInit (TPM1, tpmConfig, channelConfig_cooler);

	interpreter_init();

	tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);
}

int main(void)
{
    boardInit();
    peripheralInit();
    /* Set Red LED for Status */
    SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK);
    PORTB_PCR18 = PORT_PCR_MUX(1);
    PTB_BASE_PTR->PDDR = 1 << 18;



    /* Local variables */
    char cTachReadout[15];
    uint16_t uiTachValue;

    /* Main loop */
    for (;;) {
    	/* Blink Red LED for Status */
    	PTB_BASE_PTR->PTOR = 1 << 18;

    	/* Serial CLI */
    	interpreter_readCommand();

    	/* Get temperature */
    	PRINTF("%d\r\n", adc_getValue());

    	/* Read and print tach value */
    	uiTachValue = tach_Hz(CYCLIC_EXECUTIVE_PERIOD/1000);
    	lcd_itoa(uiTachValue, cTachReadout);
    	lcd_clearLine(0);
    	lcd_writeString(cTachReadout);
    	lcd_writeString(" Hz");

    	/* Wait for next cycle */
    	while(!uiFlagNextPeriod);
    	uiFlagNextPeriod = 0;


    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
