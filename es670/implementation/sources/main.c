
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
}
int pos = 0;
int main(void)
{
    boardInit();
    peripheralInit();
    lcd_setCursor(0,1);
    char hello[16] = "KAAC - 140721  ";
    lcd_writeString(hello);
    lcd_setCursor(1,2);
    char hello1[16] = "GKK - 135964  ";
    lcd_writeString(hello1);

    pwm_initPWM(TPM0, 1);


    for (;;) {
    	interpreter_readCommand();


    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
