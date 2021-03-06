/* ***************************************************************** */
/* File name:        buzzer.h 	                                     */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling BUZZER from the         */
/*                   peripheral board                                */
/* Author name:      dloubach                                        */
/* Modified by:      Guilherme Kairalla Kolotelo                     */
/* 			         Kaique Arce de Almeida Camargo                  */
/* Creation date:    12jan2016                                       */
/* Revision date:    29jan2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_BUZZER_H_
#define SOURCES_BUZZER_H_

/* ************************************************ */
/* Method name:        buzzer_init                  */
/* Method description: Initialize the buzzer device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void buzzer_init(void);


/* ************************************************ */
/* Method name:        buzzer_clearBuzz             */
/* Method description: Clear the buzzer             */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void buzzer_clearBuzz(void);


/* ************************************************ */
/* Method name:        buzzer_setBuzz               */
/* Method description: Set the buzzer               */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void buzzer_setBuzz(void);


/* ************************************************ */
/* Method name:        buzzer_1khz                  */
/* Method description: Activates buzzer at 1kHz for */
/* 					   specified duration           */
/* Input params:       int duration = duration in ms*/
/* Output params:      n/a                          */
/* ************************************************ */
void buzzer_1khz(int duration);




#endif /* SOURCES_BUZZER_H_ */
