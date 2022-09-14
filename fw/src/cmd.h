#ifndef CMD_H_
#define CMD_H_

#include "defines.h"

#define CMD_START_SIGN		0xAAU

#define CMD_LCD				0
#define CMD_BACKLIGHT		1
#define CMD_LEDS			2
#define CMD_BUTTONS			3

#define CMD_LCD_OP_CLEAR	0
#define CMD_LCD_OP_WHOLE	1
#define CMD_LCD_OP_LINE		2
#define CMD_LCD_OP_ADDR		3

#define CMD_OFFS_CMD		0
#define CMD_OFFS_DATA		1
#define CMD_OFFS_STRING		2

#define CMD_BYTE_OFFS		4
#define CMD_OP_MASK			0x0FU

#define CMD_LCD_OFFS_COL	0
#define CMD_LCD_OFFS_ROW	5
#define CMD_LCD_MASK_COL	((1UL << 5U) - 1U)
#define CMD_LCD_MASK_ROW	((1UL << 2U) - 1U)

void CMD_SetReady(uint8_t *data, uint8_t len);
void CMD_Process(void);

#endif /* CMD_H_ */
