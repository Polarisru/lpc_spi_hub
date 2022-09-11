#ifndef BACKLIGHT_H_
#define BACKLIGHT_H_

#include "defines.h"

#define BACKLIGHT_MAX_VALUE		10

void BACKLIGHT_Init(void);
void BACKLIGHT_SetValue(uint8_t value);

#endif /* BACKLIGHT_H_ */
