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

#ifndef SOURCES_COOLER_H_
#define SOURCES_COOLER_H_

/**
 * Method name:			cooler_init
 * Method description: 	Initializes the cooler at top speed
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void cooler_init();

/**
 * Method name:			cooler_initPwm
 * Method description: 	Initializes the cooler for PWM control
 * Input params:      	n/a
 * Output params:     	n/a
 */
void cooler_initForPwm();

#endif /* SOURCES_COOLER_H_ */
