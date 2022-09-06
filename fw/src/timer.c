#include "chip.h"
#include "timer.h"

#define TIMER_TICK_MS		10U
#define TIMER_TICKRATE		(1000U * TIMER_TICK_MS)

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
	uint32_t stop = TIMER_counter + (uint32_t)ms * TIMER_TICK_MS;
	while (TIMER_counter < stop) {}
}
