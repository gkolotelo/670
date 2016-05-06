/* ***************************************************************** */
/* File name:        lcd.c                                           */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*                   controller                                      */
/* Author name:      dloubach                                        */
/* Modified by:      Guilherme Kairalla Kolotelo                     */
/*                   Kaique Arce de Almeida Camargo                  */
/* Creation date:    16out2015                                       */
/* Revision date:    06may2016                                       */
/* ***************************************************************** */

#include "lcd.h"
#include "../es670_peripheral_board.h"
#include "../util/util.h"

/* system includes */
//#include "fsl_clock_manager.h"
//#include "fsl_port_hal.h"
//#include "fsl_gpio_hal.h"

/* line and columns */
#define LINE0        0U
#define COLUMN0      0U

#define L0C0_BASE    0x80 /* line 0, column 0 */
#define L1C0_BASE    0xC0 /* line 1, column 0 */
#define MAX_COLUMN   15U

/* ************************************************ */
/* Method name:        lcd_initLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_initLcd(void)
{
    /* pins configured as outputs */

    /* un-gate port clock*/
    //CLOCK_SYS_EnablePortClock(PORTC_IDX);
	SIM_SCGC5 |= (SIM_SCGC5_PORTC_MASK);


    /* set pin as gpio */
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_RS_PIN, LCD_RS_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_ENABLE_PIN, LCD_ENABLE_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB0_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB1_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB2_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB3_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB4_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB5_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB6_PIN, LCD_DATA_ALT);
    //PORT_HAL_SetMuxMode(LCD_PORT_BASE_PNT, LCD_DATA_DB7_PIN, LCD_DATA_ALT);
    PORTC_PCR0 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR1 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR2 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR3 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR4 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR5 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR6 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR7 = PORT_PCR_MUX(LCD_DATA_ALT));
    PORTC_PCR8 = PORT_PCR_MUX(LCD_RS_ALT);
    PORTC_PCR9 = PORT_PCR_MUX(LCD_ENABLE_ALT);

    /* set pin as digital output */
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_RS_PIN, LCD_RS_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_ENABLE_PIN, LCD_ENABLE_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB0_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB1_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB2_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB3_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB4_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB5_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB6_PIN, LCD_DATA_DIR);
    //GPIO_HAL_SetPinDir(LCD_GPIO_BASE_PNT, LCD_DATA_DB7_PIN, LCD_DATA_DIR);
    GPIOC_PDDR |= GPIO_PDDR_PDD(LCD_RS_PIN);
    GPIOC_PDDR |= GPIO_PDDR_PDD(LCD_ENABLE_PIN);
    GPIOC_PDDR |= GPIO_PDDR_PDD(LCD_DATA_DIR);

    // turn-on LCD, with no cursor and no blink
    lcd_sendCommand(CMD_NO_CUR_NO_BLINK);

    // init LCD
    lcd_sendCommand(CMD_INIT_LCD);

    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // LCD with no cursor
    lcd_sendCommand(CMD_NO_CURSOR);

    // cursor shift to right
    lcd_sendCommand(CMD_CURSOR2R);

}



/* ************************************************ */
/* Method name:        lcd_write2Lcd                */
/* Method description: Send command or data to LCD  */
/* Input params:       ucBuffer => char to be send  */
/*                     cDataType=>command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
    /* writing data or command */
    if(LCD_RS_CMD == cDataType)
        /* will send a command */
        //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_RS_PIN, LCD_RS_CMD);
        GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_RS_PIN))) | (LCD_RS_CMD << LCD_RS_PIN));

    else
        /* will send data */
        //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_RS_PIN, LCD_RS_DATA);
        GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_RS_PIN))) | (LCD_RS_DATA << LCD_RS_PIN));

    /* write in the LCD bus */
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB0_PIN, ((ucBuffer & (1u << 0u)) >> 0u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB1_PIN, ((ucBuffer & (1u << 1u)) >> 1u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB2_PIN, ((ucBuffer & (1u << 2u)) >> 2u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB3_PIN, ((ucBuffer & (1u << 3u)) >> 3u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB4_PIN, ((ucBuffer & (1u << 4u)) >> 4u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB5_PIN, ((ucBuffer & (1u << 5u)) >> 5u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB6_PIN, ((ucBuffer & (1u << 6u)) >> 6u));
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_DATA_DB7_PIN, ((ucBuffer & (1u << 7u)) >> 7u));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB0_PIN))) | ((ucBuffer & (1u << 0u)) << LCD_DATA_DB0_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB1_PIN))) | ((ucBuffer & (1u << 1u)) << LCD_DATA_DB1_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB2_PIN))) | ((ucBuffer & (1u << 2u)) << LCD_DATA_DB2_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB3_PIN))) | ((ucBuffer & (1u << 3u)) << LCD_DATA_DB3_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB4_PIN))) | ((ucBuffer & (1u << 4u)) << LCD_DATA_DB4_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB5_PIN))) | ((ucBuffer & (1u << 5u)) << LCD_DATA_DB5_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB6_PIN))) | ((ucBuffer & (1u << 6u)) << LCD_DATA_DB6_PIN));
    //GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_DATA_DB7_PIN))) | ((ucBuffer & (1u << 7u)) << LCD_DATA_DB7_PIN));
    GPIOC_PDOR = ((GPIOC_PDOR & (~(0xFF << LCD_DATA_DB0_PIN))) | (ucBuffer << LCD_DATA_DB0_PIN));


    /* enable, delay, disable LCD */
    /* this generates a pulse in the enable pin */
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_ENABLE_PIN, LCD_ENABLED);
    GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_ENABLE_PIN))) | (LCD_ENABLED << LCD_ENABLE_PIN));
    util_genDelay1ms();
    //GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_ENABLE_PIN, LCD_DISABLED);
    GPIOC_PDOR = ((GPIOC_PDOR & (~(1 << LCD_ENABLE_PIN))) | (LCD_DISABLED << LCD_ENABLE_PIN));
    util_genDelay1ms();
    util_genDelay1ms();
}



/* ************************************************ */
/* Method name:        lcd_writeData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeData(unsigned char ucData)
{
    /* just a relay to send data */
    lcd_write2Lcd(ucData, LCD_RS_DATA);
}



/* ************************************************ */
/* Method name:        lcd_sendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd)
{
    /* just a relay to send command */
    lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}



/* ************************************************ */
/* Method name:        lcd_setCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:       n/a                         */
/* ************************************************ */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn)
{
    char cCommand;

    if(LINE0 == cLine)
        /* line 0 */
        cCommand = L0C0_BASE;
    else
        /* line 1 */
        cCommand = L1C0_BASE;

    /* maximum MAX_COLUMN columns */
    cCommand += (cColumn & MAX_COLUMN);

    // send the command to set the cursor
    lcd_sendCommand(cCommand);
}



/* ************************************************ */
/* Method name:        lcd_writeString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer)
{
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
    };
}



/* ************************************************ */
/* Method name:        lcd_dummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_dummyText(void)
{
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // set the cursor line 0, column 1
    lcd_setCursor(0,1);

    // send string
    lcd_writeString("*** ES670 ***");

    // set the cursor line 1, column 0
    lcd_setCursor(1,0);
    lcd_writeString("Prj Sis Embarcad");
}
