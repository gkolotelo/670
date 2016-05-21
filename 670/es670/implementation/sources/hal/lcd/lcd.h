/* ***************************************************************** */
/* File name:        lcd.h                                           */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the LCD hardware from   */
/*                   the hardware kit                                */
/* Author name:      dloubach                                        */
/* Modified by:      Guilherme Kairalla Kolotelo                     */
/*                   Kaique Arce de Almeida Camargo                  */
/* Creation date:    16out2015                                       */
/* Revision date:    06may2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

/* lcd basic commands list */
#define CMD_INIT_LCD        0x0F
#define CMD_CLEAR           0x01
#define CMD_NO_CURSOR       0x0C
#define CMD_CURSOR2R        0x06 /* cursor to right */
#define CMD_NO_CUR_NO_BLINK 0x38 /* no cursor, no blink */


/* ************************************************ */
/* Method name:        lcd_initLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_initLcd(void);


/* ************************************************ */
/* Method name:        lcd_writeData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeData(unsigned char ucData);


/* ************************************************ */
/* Method name:        lcd_sendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd);


/* ************************************************ */
/* Method name:        lcd_WriteString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer);


/* ************************************************ */
/* Method name:        lcd_setCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_setCursor(unsigned char ucLine, unsigned char ucColumn);

/* ************************************************ */
/* Method name:        lcd_clearLine                */
/* Method description: Clears chars from line       */
/* Input params:       ucLine = LINE0..LINE1        */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_clearLine(unsigned char ucLine);

/* ************************************************ */
/* Method name:        lcd_dummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_dummyText(void);

/* ************************************************ */
/* Method name:        itoa                         */
/* Method description: Integer to char array        */
/* Input params:       int i = integer to convert   */
/* I				   char* b = char array output  */
/* Output params:      char* char pointer to output */
/* ************************************************ */
char* lcd_itoa(int i, char b[]);


#endif /* SOURCES_LCD_HAL_H_ */
