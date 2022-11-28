#include "led.h"
#include "pins.h"

typedef struct {
	XMC_GPIO_PORT_t *const  port;	/* Pin port */
	uint8_t pin;					/* Pin number */
} LED_T;

static const LED_T LEDS[LED_LAST] = {
	{LED_BOARD_PORT, LED_BOARD_PIN},
	{LED_STAT0_PORT, LED_STAT0_PIN},
	{LED_STAT1_PORT, LED_STAT1_PIN}
};

/* Initializes board LED(s) */
void LED_Init(void)
{
	for (int i = 0; i < LED_LAST; i++) {
		XMC_GPIO_SetMode(LEDS[i].port, LEDS[i].pin, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	}
}

/* Sets the state of a board LED to on or off */
void LED_Set(uint8_t number, bool on)
{
	if (number >= LED_LAST) {
		return;
	}
	if (on == true) {
		XMC_GPIO_SetOutputHigh(LEDS[number].port, LEDS[number].pin);
	} else {
		XMC_GPIO_SetOutputLow(LEDS[number].port, LEDS[number].pin);
	}
}

/* Returns the current state of a board LED */
bool LED_Test(uint8_t number)
{
	if (number >= LED_LAST) {
		return false;
	}
	//return Chip_GPIO_GetPinState(LPC_GPIO, LEDS[number].port, LEDS[number].pin);
	return false;
}

void LED_Toggle(uint8_t number)
{
	if (number >= LED_LAST) {
		return;
	}
	XMC_GPIO_ToggleOutput(LEDS[number].port, LEDS[number].pin);
}

