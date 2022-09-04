#include "board.h"
#include "buttons.h"
#include "led.h"
#include "outputs.h"
#include "st7066u.h"
#include "timer.h"

#include <cr_section_macros.h>

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#endif
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	TIMER_Init();
	BUTTONS_Init();
	LED_Init();
	OUTPUTS_Init();
	ST7066U_Init(4, 20);
	// Set the LED to the state of "On"
	LED_Set(LED_BOARD, true);
	ST7066U_WriteLine("      Hello!", 0);

    while(1) {
        //for (int i = 0; i < 200000; i++) {}
    	TIMER_WaitMs(500);
        LED_Toggle(LED_BOARD);
    }
    return 0 ;
}