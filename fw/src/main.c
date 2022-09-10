//#include "board.h"
#include "backlight.h"
#include "buttons.h"
#include "chip.h"
#include "led.h"
#include "outputs.h"
#include "spi.h"
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
	/* Initialize GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	TIMER_Init();
	BUTTONS_Init();
	LED_Init();
	OUTPUTS_Init();
	BACKLIGHT_Init();
	SPI_Init();
	// Set the LED to the state of "On"
	LED_Set(LED_BOARD, true);
	ST7066U_Init(4, 20);
	ST7066U_WriteLine("Hello, world #1!", 0);
	ST7066U_WriteLine("Hello, world #2!", 2);
	TIMER_WaitMs(1000);

//	TIMER_StartMs(500);
    while(1) {
    	SPI_ProcessNew();
//    	if (TIMER_IsTimeout() == true) {
//    		LED_Toggle(LED_BOARD);
//    		TIMER_StartMs(500);
//    	}
    }
    return 0 ;
}
