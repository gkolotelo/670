/**
 *
 * File name:        	display_7segmants.c                             
 * File description: 	file containing the methods for interacting
 * 						with the 7 segment displays on the peripheral
 * 						board   
 *                    
 * Authors:          	Guilherme Kairalla Kolotelo                     
 * 		             	Kaique Arce de Almeida Camargo                  
 * Creation date:    	01Apr2016                                       
 * Revision date:    	08Apr2016                                       
 *
 */

#include "display_7segments.h"
#include "hal/es670_peripheral_board.h"
#include "hal/util/util.h"


void display_7segments_initDisplays()
{
	// Gate clock to PORTC
	SIM_SCGC5 |= (SIM_SCGC5_PORTC_MASK);

	// Setting pin muxes to ALT1 (GPIO)
	PORTC_PCR0 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR1 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR2 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR3 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR4 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR5 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR6 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR7 = PORT_PCR_MUX(D7S_ALT);

	PORTC_PCR10 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR11 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR12 = PORT_PCR_MUX(D7S_ALT);
	PORTC_PCR13 = PORT_PCR_MUX(D7S_ALT);

	// Ungating port clock to preserve power if defined
	#ifdef D7S_UNGATE_CLOCK
		SIM_SCGC5 &= ~SIM_SCGC5_PORTC_MASK;
	#endif

	// Setting GPIO direction to output
	GPIOC_PDDR |= GPIO_PDDR_PDD(D7S_DIR);

}

void display_7segments_setDisplay(display_position_e eDispPos, display_charater_e eChar)
{
	// Disable all displays first
	display_7segments_displayOff(ALL);
	display_7segments_setChar(eChar);
	display_7segments_displayOn(eDispPos);

}

void display_7segments_setChar(display_charater_e eChar)
{
	// Sets pins to produce the output eChar
	switch(eChar)
	{
		case _0:
			GPIOC_PSOR = 0b00111111u;
			GPIOC_PCOR = 0b11000000u;
			break;
		case _1:
			GPIOC_PSOR = 0b00000110u;
			GPIOC_PCOR = 0b11111001u;

			break;
		case _2:
			GPIOC_PSOR = 0b01011011u;
			GPIOC_PCOR = 0b10100100u;

			break;
		case _3:
			GPIOC_PSOR = 0b01001111u;
			GPIOC_PCOR = 0b10110000u;

			break;
		case _4:
			GPIOC_PSOR = 0b01100110u;
			GPIOC_PCOR = 0b10011001u;

			break;
		case _5:
			GPIOC_PSOR = 0b01101101u;
			GPIOC_PCOR = 0b10010010u;

			break;
		case _6:
			GPIOC_PSOR = 0b01111101u;
			GPIOC_PCOR = 0b10000010u;

			break;
		case _7:
			GPIOC_PSOR = 0b00000111u;
			GPIOC_PCOR = 0b11111000u;

			break;
		case _8:
			GPIOC_PSOR = 0b01111111u;
			GPIOC_PCOR = 0b10000000u;

			break;
		case _9:
			GPIOC_PSOR = 0b01101111u;
			GPIOC_PCOR = 0b10010000u;

			break;
		case _A:
			GPIOC_PSOR = 0b01110111u;
			GPIOC_PCOR = 0b10001000u;

			break;
		case _B:
			GPIOC_PSOR = 0b01111100u;
			GPIOC_PCOR = 0b10000011u;

			break;
		case _C:
			GPIOC_PSOR = 0b00111001u;
			GPIOC_PCOR = 0b11000110u;

			break;
		case _D:
			GPIOC_PSOR = 0b01011110u;
			GPIOC_PCOR = 0b10100001u;

			break;
		case _E:
			GPIOC_PSOR = 0b01111001u;
			GPIOC_PCOR = 0b10000110u;

			break;
		case _F:
			GPIOC_PSOR = 0b01110001u;
			GPIOC_PCOR = 0b10001110u;

			break;
		case _decimal:
			GPIOC_PSOR = 0b10000000u;
			GPIOC_PCOR = 0b01111111u;

			break;
		default:
		case _clear:
			GPIOC_PSOR = 0b00000000u;
			GPIOC_PCOR = 0b11111111u;

			break;
	}
}

void display_7segments_displayOn(display_position_e eDispPos)
{
	// Enables display cDispNum
	switch(eDispPos)
	{
		case DS1:
			GPIOC_PSOR = GPIO_PSOR_PTSO(DS1_EN_PIN);
			break;
		case DS2:
			GPIOC_PSOR = GPIO_PSOR_PTSO(DS2_EN_PIN);
			break;
		case DS3:
			GPIOC_PSOR = GPIO_PSOR_PTSO(DS3_EN_PIN);
			break;
		case DS4:
			GPIOC_PSOR = GPIO_PSOR_PTSO(DS4_EN_PIN);
			break;
		case ALL:
			GPIOC_PSOR = GPIO_PSOR_PTSO(DS1_EN_PIN | DS2_EN_PIN | DS3_EN_PIN | DS4_EN_PIN);
			break;
	}
}

void display_7segments_displayOff(display_position_e eDispPos)
{
	// Disables display cDispNum
	switch(eDispPos)
	{
		case DS1:
			GPIOC_PCOR = GPIO_PCOR_PTCO(DS1_EN_PIN);
			break;
		case DS2:
			GPIOC_PCOR = GPIO_PCOR_PTCO(DS2_EN_PIN);
			break;
		case DS3:
			GPIOC_PCOR = GPIO_PCOR_PTCO(DS3_EN_PIN);
			break;
		case DS4:
			GPIOC_PCOR = GPIO_PCOR_PTCO(DS4_EN_PIN);
			break;
		case ALL:
			GPIOC_PCOR = GPIO_PCOR_PTCO(DS1_EN_PIN | DS2_EN_PIN | DS3_EN_PIN | DS4_EN_PIN);
			break;
	}
}

void display_7segments_displayMany(display_charater_e eChar1, display_charater_e eChar2, display_charater_e eChar3, display_charater_e eChar4)
{
	display_7segments_setDisplay(DS1, eChar1);
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay180us();
	display_7segments_setDisplay(DS2, eChar2);
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay180us();
	display_7segments_setDisplay(DS3, eChar3);
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay180us();
	display_7segments_setDisplay(DS4, eChar4);
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay1ms();
	util_genDelay180us();
	display_7segments_displayOff(ALL);
}
