
/* system includes */
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"

#include "hal/buzzer/buzzer.h"
#include "hal/mcg/mcg.h"
#include "hal/util/util.h"
#include "hal/ledswi/ledswi.h"
#include "hal/display_7segments/display_7segments.h"
#include "hal/uart/debugUart.h"
#include "hal/uart/interpreter.h"
#include "hal/lcd/lcd.h"
#include "hal/pwm/pwm.h"
#include "hal/util/tc_hal.h"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         100 * 10000 /* 1000000 micro seconds */

/* globals */
volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

void main_cyclicExecuteIsr(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}

int boardInit()
{
    mcg_clockInit();
}

int peripheralInit()
{
	interpreter_init();
	buzzer_init();
	ledswi_initLedSwitch(1,3);
	display_7segments_initDisplays();
	lcd_initLcd();
	cooler_init();
}
char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}
int pos = 0;
unsigned int value = 0;
char val[15];
int main(void)
{
    boardInit();
    peripheralInit();
    /* configure cyclic executive interruption */
    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);
    SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK);
    PORTB_PCR18 = PORT_PCR_MUX(1);
    PTB_BASE_PTR->PDDR = 1 << 18;
    tach_init();

    for (;;) {
    	//interpreter_readCommand();
    	PTB_BASE_PTR->PTOR = 1 << 18;
    	value = TPM0_BASE_PTR->CNT;
    	itoa(value, val);
    	lcd_writeString(val);

    	while(!uiFlagNextPeriod);
    	uiFlagNextPeriod = 0;
    	lcd_setCursor(0,0);

    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
