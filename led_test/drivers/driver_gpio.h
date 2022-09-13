#ifndef DRV_GPIO_H
#define DRV_GPIO_H

#include "defines.h"

#define GPIO_MAX_PIN    31U

enum {
  GPIO_PULLMODE_NONE,
  GPIO_PULLMODE_UP,
  GPIO_PULLMODE_DOWN
};

enum {
  GPIO_PIN_FUNC_A,
  GPIO_PIN_FUNC_B,
  GPIO_PIN_FUNC_C,
  GPIO_PIN_FUNC_D,
  GPIO_PIN_FUNC_E,
  GPIO_PIN_FUNC_F,
  GPIO_PIN_FUNC_G,
  GPIO_PIN_FUNC_H,
  GPIO_PIN_FUNC_I,
  GPIO_PIN_FUNC_OFF
};

/**
 * \brief PORT pull mode settings
 */
enum gpio_pull_mode { GPIO_PULL_OFF, GPIO_PULL_UP, GPIO_PULL_DOWN };

/**
 * \brief PORT direction settins
 */
enum gpio_direction { GPIO_DIRECTION_OFF, GPIO_DIRECTION_IN, GPIO_DIRECTION_OUT };

/**
 * \brief PORT level settings
 */
enum gpio_level {GPIO_LEVEL_LOW, GPIO_LEVEL_HIGH};

/**
 * \brief PORT group abstraction
 */
enum gpio_port { GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE };

/**< Set HIGH pin level macro */
#define GPIO_SetHigh(x, y)    PORT_IOBUS->Group[x].OUTSET.reg = (1UL << (y))
/**< Set LOW pin level macro */
#define GPIO_SetLow(x, y)     PORT_IOBUS->Group[x].OUTCLR.reg = (1UL << (y))
/**< Read pin status */
#define GPIO_ReadPin(x, y)    ((PORT->Group[x].IN.reg & (1UL << (y))) > 0U)

void GPIO_Init(void);
void GPIO_DisablePort(uint8_t port);
void GPIO_SetDir(uint8_t port, uint8_t pin, bool dir);
void GPIO_SetPullMode(uint8_t port, uint8_t pin, uint8_t mode);
void GPIO_SetFunction(uint8_t port, uint8_t pin, uint8_t mode);
void GPIO_SetPin(uint8_t port, uint8_t pin);
void GPIO_ClearPin(uint8_t port, uint8_t pin);
void GPIO_TogglePin(uint8_t port, uint8_t pin);
bool GPIO_GetPin(uint8_t port, uint8_t pin);
bool GPIO_GetOutputPin(uint8_t port, uint8_t pin);
void GPIO_SetupPin(uint8_t port, uint8_t pin, uint8_t mode, uint8_t dir, uint8_t on);

#endif
