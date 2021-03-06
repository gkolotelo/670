/* ***************************************************************** */
/* File name:        ledswi.h                                        */
/* File description: Header file containing the function/methods     */
/*                   prototypes of ledswi.c                          */
/* Author name:      dloubach                                        */
/* Modified by:      Guilherme Kairalla Kolotelo                     */
/*                   Kaique Arce de Almeida Camargo                  */
/* Creation date:    09jan2015                                       */
/* Revision date:    29Apr2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_LEDSWI_LEDSWI_H_
#define SOURCES_LEDSWI_LEDSWI_H_

#define MAX_LED_SWI        04

typedef enum
{
   OFF,
   ON
} status_type_e;

/* ************************************************ */
/* Method name:        ledswi_initLedSwitch         */
/* Method description: As the hardware board was    */
/*                     designed with LEDs/Switches  */
/*                     sharing the same pins, this  */
/*                     method configures how many   */
/*                     LEDS and switches will be    */
/*                     available for the application*/
/* Input params:       cLedNum    = num of LEDs     */
/*                     cSwitchNum = num of Switches */
/*                     cLedNum +                    */
/*                     cSwitchNum <= MAX_LED_SWI    */
/* Outpu params:       n/a                          */
/* ************************************************ */
void ledswi_initLedSwitch(char cLedNum, char cSwitchNum);


/* ************************************************ */
/* Method name:        ledswi_setLed                */
/* Method description: set the led ON               */
/* Input params:       cLedNum    = which LED {1..4}*/
/* Outpu params:       n/a                          */
/* ************************************************ */
void ledswi_setLed(char cLedNum);


/* ************************************************ */
/* Method name:        ledswi_clearLed              */
/* Method description: set the led OFF              */
/* Input params:       cLedNum    = which LED {1..4}*/
/* Outpu params:       n/a                          */
/* ************************************************ */
void ledswi_clearLed(char cLedNum);


/* ************************************************ */
/* Method name:        ledswi_getSwitchStatus       */
/* Method description: return the switch status     */
/* Input params:       cSwitchNum = which switch    */
/* Outpu params:       status_type_e                */
/* ************************************************ */
status_type_e ledswi_getSwitchStatus(char cSwitchNum);

/* ************************************************ */
/* Method name:        ledswi_getLedStatus          */
/* Method description: return the LED status        */
/* Input params:       char cLedNum = which led     */
/* Outpu params:       status_type_e                */
/* ************************************************ */
status_type_e ledswi_getLedStatus(char cLedNum);

#endif /* SOURCES_LEDSWI_LEDSWI_H_ */
