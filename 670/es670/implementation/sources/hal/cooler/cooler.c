/**
 *
 * File name:        	cooler.h                            
 * File description: 	Header file containing methods for
 * 						interacting with the cooler
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	13May2016                                       
 * Revision date:    	20May2016                                       
 *
 */

#include "../es670_peripheral_board.h"
#include "cooler.h"

void cooler_init()
{
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK);
	PORTA_PCR13 = PORT_PCR_MUX(1);
	PTA_BASE_PTR->PDDR = 1 << 13;
	PTA_BASE_PTR->PSOR = 1 << 13;
}
