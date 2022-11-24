#include "buttons.h"
#include "pins.h"

typedef struct {
	uint32_t port : 8;			/* Pin port */
	uint32_t pin : 8;			/* Pin number */
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

//void BUTTONS_Init(void)
//{
//	for (int i = 0; i < BUTTONS_LAST; i++) {
//		Chip_IOCON_PinMuxSet(LPC_IOCON, BTNS[i].port, BTNS[i].pin, (IOCON_FUNC0 | IOCON_MODE_PULLUP));
//		Chip_GPIO_SetPinDIRInput(LPC_GPIO, BTNS[i].port, BTNS[i].pin);
//	}
//}
//
//uint8_t BUTTONS_GetStatus(void)
//{
//	uint8_t ret = 0;
//
//	for (int i = 0; i < BUTTONS_LAST; i++) {
//		if (Chip_GPIO_GetPinState(LPC_GPIO, BTNS[i].port, BTNS[i].pin) == false) {
//			ret |= (uint8_t)(1UL << i);
//		}
//	}
//	return ret;
//}

