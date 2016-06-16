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


#ifndef SOURCES_HEATER_H_
#define SOURCES_HEATER_H_

/**
 * Method name:			heater_initPwm
 * Method description: 	Initializes the heater for PWM control
 * Input params:      	n/a
 * Output params:     	n/a
 */
void heater_initForPwm();

/**
 * Method name:			heater_getTemperature
 * Method description: 	Gets heater temperature
 * Input params:      	n/a
 * Output params:     	uint16_t = Temperature in degrees C
 */
uint16_t heater_getTemperature();

#endif /* SOURCES_HEATER_H_ */
