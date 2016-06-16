/**
 *
 * File name:        	cooler.h                            
 * File description: 	Header file containing methods for
 * 						interacting with the cooler
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	13May2016                                       
 * Revision date:    	03Jun2016                                       
 *
 */

#include "../es670_peripheral_board.h"
#include "cooler.h"

/**
 * Method name:			cooler_init
 * Method description: 	Initializes the cooler at top speed
 * Input params:      	n/a
 * Output params:     	n/a
 */
void cooler_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR13 = PORT_PCR_MUX(1);
	PTA_BASE_PTR->PDDR = 1 << 13;
	PTA_BASE_PTR->PSOR = 1 << 13;
}

/**
 * Method name:			cooler_initPwm
 * Method description: 	Initializes the cooler for PWM control
 * Input params:      	n/a
 * Output params:     	n/a
 */
void cooler_initForPwm()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR13 = PORT_PCR_MUX(3);
	PTA_BASE_PTR->PDDR = 1 << 13;
}
