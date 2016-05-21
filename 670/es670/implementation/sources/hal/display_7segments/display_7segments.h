/**
 *
 * File name:        	display_7segmants.h                             
 * File description: 	Header file containing the functions/methods    
 *                   	and interfaces for handling the four 7 segment  
 *                   	displays present on the peripheral board       
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	01Apr2016                                       
 * Revision date:    	08Apr2016                                       
 *
 */


#ifndef SOURCES_DISPLAY_7SEGMENTS_DISPLAY_7SEGMENTS_H_
#define SOURCES_DISPLAY_7SEGMENTS_DISPLAY_7SEGMENTS_H_

/**
 * Defining 'D7S_UNGATE_CLOCK' disables PORTC clock on the MCG
 * after initialization to preserve power.
 * May interfere with the behavior of third-party code. Use with caution.
 */
//#define D7S_UNGATE_CLOCK

typedef enum
{
    _0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	_A,
	_B,
	_C,
	_D,
	_E,
	_F,
	_decimal,
	_clear

} display_charater_e;

typedef enum
{
    DS1,
	DS2,
	DS3,
	DS4,
	ALL

} display_position_e;

/**
 * Method name:			display_7segments_initDisplays
 * Method description: 	Initializes the ports for the four 7 segment displays
 * Input params:      	n/a                         
 * Output params:     	n/a                         
 */
void display_7segments_initDisplays();

/**
 * Method name:			display_7segments_setDisplay
 * Method description:	Sets the eDispPos display to the character
 * 						eChar. All other displays are turned off
 * Input params:      	eDispPos 	= Display position
 * 						eChar		= Char to be displayed
 * Output params:     	n/a
 */
void display_7segments_setDisplay(display_position_e eDispPos, display_charater_e eChar);

/**
 * Method name:			display_7segments_setChar
 * Method description:	Sets the character to all active displays
 * Input params:      	eChar		= Char to be displayed
 * Output params:     	n/a
 */
void display_7segments_setChar(display_charater_e eChar);

/**
 * Method name:			display_7segments_displayOn
 * Method description:	Enables the display eDispPos
 * Input params:      	eDispPos 	= Display position
 * Output params:     	n/a
 */
void display_7segments_displayOn(display_position_e eDispPos);

/**
 * Method name:			display_7segments_displayOff
 * Method description:	Disables the display eDispPos
 * Input params:      	eDispPos 	= Display position
 * Output params:     	n/a
 */
void display_7segments_displayOff(display_position_e eDispPos);

/**
 * Method name:			display_7segments_displayMany
 * Method description:	Displays 4 characters, one at a time for 3.125ms
 * Input params:      	eChar1		= Char for DS1
 * 						eChar2		= Char for DS2
 * 						eChar3		= Char for DS3
 * 						eChar4		= Char for DS4
 * Output params:     	n/a
 */
void display_7segments_displayMany(display_charater_e eChar1, display_charater_e eChar2, display_charater_e eChar3, display_charater_e eChar4);

#endif /* SOURCES_DISPLAY_7SEGMENTS_DISPLAY_7SEGMENTS_H_ */
