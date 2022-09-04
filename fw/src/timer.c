#include "chip.h"
#include "timer.h"

#define TIMER_TICK_MS		1
#define TIMER_TICKRATE		(1000 / TIMER_TICK_MS)

volatile static uint32_t TIMER_counter;

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	TIMER_counter++;
}

void TIMER_Init(void)
{
	TIMER_counter = 0;
	SysTick_Config(SystemCoreClock / TIMER_TICKRATE);
}

void TIMER_WaitMs(uint16_t ms)
{
	uint32_t stop = TIMER_counter + ms;
	while (TIMER_counter < stop) {}
}
