/**
 *
 * File name:        	interpreter.h                             
 * File description: 	file containing the methods for interacting
 * 						with a serial host  
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	22Apr2016                                       
 * Revision date:    	28Apr2016                                       
 *
 */

#ifndef SOURCES_INTERPRETER_H_
#define SOURCES_INTERPRETER_H_

#define NONE 0
#define ERROR 1

/**
 * Method name:			interpreter_readCommand
 * Method description: 	Reads a serial input and executes its command, returning
 * 						an error or acknowledgement
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void interpreter_readCommand();

/**
 * Method name:			interpreter_init
 * Method description: 	Initializes UART for the interpreter
 * Input params:      	n/a
 * Output params:     	n/a
 */
void interpreter_init();

/**
 * Method name:			ledCommand
 * Method description: 	Executes commands pertinent to led operation.
 * Input params:      	n/a                      
 * Output params:     	char = error code.                       
 */
char interpreter_ledCommand();

/**
 * Method name:			switchCommand
 * Method description: 	Executes commands pertinent to switch operation.
 * Input params:      	n/a                      
 * Output params:     	char = error code.                       
 */
char interpreter_switchCommand();

/**
 * Method name:			buzzerCommand
 * Method description: 	Executes commands pertinent to buzzer operation.
 * Input params:      	n/a                      
 * Output params:     	char = error code.                       
 */
char interpreter_buzzerCommand();

#endif /*SOURCES_INTERPRETER_H_*/
