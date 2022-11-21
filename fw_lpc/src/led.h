#ifndef LED_H_
#define LED_H_

#include "defines.h"

enum {
	LED_BOARD,
	LED_STAT0,
	LED_STAT1,
	LED_LAST
};

void LED_Init(void);
void LED_Set(uint8_t number, bool on);
bool LED_Test(uint8_t number);
void LED_Toggle(uint8_t number);

#endif /* LED_H_ */
