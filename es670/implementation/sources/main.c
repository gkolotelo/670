
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
    char hello[12] = "Hello World!";
    lcd_writeString(hello);
    for (;;) {
    	//interpreter_readCommand();


    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
