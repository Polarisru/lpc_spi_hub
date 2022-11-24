#ifndef TIMER_H_
#define TIMER_H_

#include "defines.h"

void TIMER_Init(void);
void TIMER_StartMs(uint16_t ms);
bool TIMER_IsTimeout(void);
void TIMER_WaitMs(uint16_t ms);

#endif /* TIMER_H_ */
