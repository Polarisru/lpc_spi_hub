#include "chip.h"
#include "led.h"
#include "pins.h"

typedef struct {
	uint32_t port : 8;			/* Pin port */
	uint32_t pin : 8;			/* Pin number */
} LED_T;

static const LED_T LEDS[LED_LAST] = {
	{LED_BOARD_PORT, LED_BOARD_PIN}
	//{LED_STAT0_PORT, LED_STAT0_PIN},
	//{LED_STAT1_PORT, LED_STAT1_PIN}
};

/* Initializes board LED(s) */
void LED_Init(void)
{
	for (int i = 0; i < LED_LAST; i++) {
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, LEDS[i].port, LEDS[i].pin);
	}
}

/* Sets the state of a board LED to on or off */
void LED_Set(uint8_t number, bool on)
{
	if (number >= LED_LAST) {
		return;
	}
	Chip_GPIO_SetPinState(LPC_GPIO, LEDS[number].port, LEDS[number].pin, on);
}

/* Returns the current state of a board LED */
bool LED_Test(uint8_t number)
{
	if (number >= LED_LAST) {
		return false;
	}
	return Chip_GPIO_GetPinState(LPC_GPIO, LEDS[number].port, LEDS[number].pin);
}

void LED_Toggle(uint8_t number)
{
	if (number >= LED_LAST) {
		return;
	}
	Chip_GPIO_SetPinToggle(LPC_GPIO, LEDS[number].port, LEDS[number].pin);
}

