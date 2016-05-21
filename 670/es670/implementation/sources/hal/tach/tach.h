/**
 *
 * File name:        	tach.h                            
 * File description: 	Header file containing methods for setting
 * 						and reading the tachometer through the TPM0
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	13May2016                                       
 * Revision date:    	20May2016                                       
 *
 */

#ifndef SOURCES_TACH_H_
#define SOURCES_TACH_H_

/**
 * Method name:			tach_init
 * Method description: 	Initializes TPM0 module for counter
 * 						operation on external clock
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_init();

/**
 * Method name:			tach_startCounter
 * Method description: 	Starts the counter
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_startCounter();

/**
 * Method name:			tach_stopCounter
 * Method description: 	Stops the counter
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_stopCounter();

/**
 * Method name:			
 * Method description: 	
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void tach_resetCounter();

/**
 * Method name:			readCounter
 * Method description: 	Returns the value on the counter
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
uint16_t tach_readCounter();

/**
 * Method name:			tach_Hz
 * Method description: 	Returns the value of the tachometer
 * 						in units of Hertz
 * Input params:      	uitimeBase_ms = Period used
 * 						between readings
 * Output params:     	Revolutions per second                       
 */
uint16_t tach_Hz(uint16_t uitimeBase_ms);

/**
 * Method name:			tach_RPM
 * Method description: 	Returns the value of the tachometer
 * 						in units of RPM
 * Input params:      	uitimeBase_ms = Period used
 * 						between readings
 * Output params:     	Revolutions per minute                          
 */
uint16_t tach_RPM(uint16_t uitimeBase_ms);


#endif /* SOURCES_TACH_H_ */
