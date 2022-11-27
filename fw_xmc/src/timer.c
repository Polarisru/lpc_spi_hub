#include "timer.h"

#define TIMER_TICK_MS		10U
#define TIMER_TICKRATE		(1000U * TIMER_TICK_MS)

//volatile static uint32_t TIMER_counter;
static uint32_t TIMER_stop;

void TIMER_Init(void)
{
	//TIMER_counter = 0;
	//SysTick_Config(SystemCoreClock / TIMER_TICKRATE);
}

void TIMER_StartMs(uint16_t ms)
{
	TIMER_stop = SYSTIMER_GetTickCount() + (uint32_t)ms * TIMER_TICK_MS;
}

bool TIMER_IsTimeout(void)
{
	return (SYSTIMER_GetTickCount() >= TIMER_stop);
}

void TIMER_WaitMs(uint16_t ms)
{
	uint32_t stop = SYSTIMER_GetTickCount() + (uint32_t)ms * TIMER_TICK_MS;
	while (SYSTIMER_GetTickCount() < stop) {}
}
