/**
 *
 * File name:        	heater.h
 * File description: 	Header file containing methods for
 * 						interacting with the heater
 *
 * Authors:          	Guilherme Kairalla Kolotelo
 * 		             	Kaique Arce de Almeida Camargo
 * Creation date:    	15Jun2016
 * Revision date:
 *
 */

#include "../es670_peripheral_board.h"
#include "heater.h"
#include "hal/adc/adc.h"
#include "hal/util/util.h"

#define HEATER_ADC_TRANSF_EQ_PARAM_A		0.4073
#define HEATER_ADC_TRANSF_EQ_PARAM_B		-123.76

/**
 * Method name:			heater_initPwm
 * Method description: 	Initializes the heater for PWM control
 * Input params:      	n/a
 * Output params:     	n/a
 */
void heater_initForPwm()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR(HEATER_PIN) = PORT_PCR_MUX(HEATER_ALT);
}

/**
 * Method name:			heater_getTemperature
 * Method description: 	Gets heater temperature
 * Input params:      	n/a
 * Output params:     	uint16_t = Temperature in degrees C
 */
uint16_t heater_getTemperature()
{
	adc_startConversion();
	for(int i = 0; i < 50; i++)
	{
		util_genDelay10ms();
	}
	if(adc_isAdcDone())
	{
		uint16_t uiTemperature = adc_getValue();
		uiTemperature = HEATER_ADC_TRANSF_EQ_PARAM_A*uiTemperature + HEATER_ADC_TRANSF_EQ_PARAM_B;
		return uiTemperature;
	}
	return 0;
}
