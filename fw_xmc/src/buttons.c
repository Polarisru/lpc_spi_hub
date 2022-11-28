#include "buttons.h"
#include "pins.h"

typedef struct {
	XMC_GPIO_PORT_t *const port;	/* Pin port */
	uint8_t pin;					/* Pin number */
} BTN_T;

static const BTN_T BTNS[BUTTONS_LAST] = {
	{BTN_UP_PORT, BTN_UP_PIN},
	{BTN_LEFT_PORT, BTN_LEFT_PIN},
	{BTN_DOWN_PORT, BTN_DOWN_PIN},
	{BTN_PWR_PORT, BTN_PWR_PIN},
	{BTN_SELECT_PORT, BTN_SELECT_PIN},
	{BTN_RIGHT_PORT, BTN_RIGHT_PIN},
	{BTN_RUN_PORT, BTN_RUN_PIN}
};

void BUTTONS_Init(void)
{
	for (int i = 0; i < BUTTONS_LAST; i++) {
		XMC_GPIO_SetMode(BTNS[i].port, BTNS[i].pin, XMC_GPIO_MODE_INPUT_PULL_UP);
	}
}

uint8_t BUTTONS_GetStatus(void)
{
	uint8_t ret = 0;

	for (int i = 0; i < BUTTONS_LAST; i++) {
		if (XMC_GPIO_GetInput(BTNS[i].port, BTNS[i].pin) > 0) {
			ret |= (uint8_t)(1UL << i);
		}
	}
	return ret;
}

