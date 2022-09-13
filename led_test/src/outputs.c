#include "outputs.h"
#include "pins.h"

typedef struct {
	uint32_t port : 8;			/* Pin port */
	uint32_t pin : 8;			/* Pin number */
} OUT_T;

static const OUT_T OUTS[OUTPUTS_LAST] = {
	{OUT_LCD_DB4_PORT, OUT_LCD_DB4_PIN},
	{OUT_LCD_DB5_PORT, OUT_LCD_DB5_PIN},
	{OUT_LCD_DB6_PORT, OUT_LCD_DB6_PIN},
	{OUT_LCD_DB7_PORT, OUT_LCD_DB7_PIN},
	{OUT_LCD_EN_PORT, OUT_LCD_EN_PIN},
	{OUT_LCD_RS_PORT, OUT_LCD_RS_PIN},
	{OUT_LCD_RW_PORT, OUT_LCD_RW_PIN}
};

/* Initializes board output(s) */
void OUTPUTS_Init(void)
{
	for (int i = 0; i < OUTPUTS_LAST; i++) {
		GPIO_SetDir(OUTS[i].port, OUTS[i].pin, true);
		GPIO_ClearPin(OUTS[i].port, OUTS[i].pin);
	}
}

/* Sets the state of an output pin to on or off */
void OUTPUTS_Set(int number, bool on)
{
	if (number >= OUTPUTS_LAST) {
		return;
	}
	if (on == true) {
	  GPIO_SetPin(OUTS[number].port, OUTS[number].pin);
	} else
	{
	  GPIO_ClearPin(OUTS[number].port, OUTS[number].pin);
	}
}
