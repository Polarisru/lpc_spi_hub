#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include "defines.h"

enum {
	OUTPUTS_LCD_DB4,
	OUTPUTS_LCD_DB5,
	OUTPUTS_LCD_DB6,
	OUTPUTS_LCD_DB7,
	OUTPUTS_LCD_EN,
	OUTPUTS_LCD_RS,
	OUTPUTS_LCD_RW,
	OUTPUTS_LAST
};

void OUTPUTS_Init(void);
void OUTPUTS_Set(int number, bool on);

#endif /* OUTPUTS_H_ */
