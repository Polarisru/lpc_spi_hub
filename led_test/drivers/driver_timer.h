#ifndef DRV_TIMER_H
#define DRV_TIMER_H

#include "defines.h"

void TIMER_Init(void);
void TIMER_StartMs(uint16_t timeout);
void TIMER_StartUs(uint16_t usec);
void TIMER_Stop(void);
bool TIMER_IsTimeout(void);
void TIMER_DelayMs(uint16_t msec);
void TIMER_DelayUs(uint16_t usec);

#endif
