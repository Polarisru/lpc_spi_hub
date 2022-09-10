#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "defines.h"

enum {
	BUTTONS_BTN_UP,
	BUTTONS_BTN_LEFT,
	BUTTONS_BTN_DOWN,
	BUTTONS_BTN_PWR,
	BUTTONS_BTN_SELECT,
	BUTTONS_BTN_RIGHT,
	BUTTONS_BTN_RUN,
	BUTTONS_LAST
};

void BUTTONS_Init(void);
uint8_t BUTTONS_GetStatus(void);

#endif /* BUTTONS_H_ */
