#include "driver_gpio.h"


/** \brief Initialize GPIO module
 *
 * \return void
 *
 */
void GPIO_Init(void)
{

}

/** \brief Disable port (set direction to input)
 *
 * \param [in] port Port number
 * \return void
 *
 */
void GPIO_DisablePort(uint8_t port)
{
  PORT->Group[port].DIRSET.reg = 0UL;
}

/** \brief Set pin direction
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \param [in] dir Direction: true - output, false - input
 * \return void
 *
 */
void GPIO_SetDir(uint8_t port, uint8_t pin, bool dir)
{
  if (pin > GPIO_MAX_PIN)
  {
    return;
  }
  if (dir == true)
  {
    PORT->Group[port].DIRSET.reg = (1UL << pin);
  } else
  {
    PORT->Group[port].DIRCLR.reg = (1UL << pin);
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_INEN;
  }
}

/** \brief Set pin function
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \param [in] mode Pin mode (alternate function)
 * \return void
 *
 */
void GPIO_SetFunction(uint8_t port, uint8_t pin, uint8_t mode)
{
  if (pin > GPIO_MAX_PIN)
  {
    return;
  }
  if (mode >= GPIO_PIN_FUNC_OFF)
  {
    PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PMUXEN;
  } else
  {
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PMUXEN;
    if ((pin % 2U) > 0U)
    {
      PORT->Group[port].PMUX[pin >> 1].bit.PMUXO = mode;
    } else
    {
      PORT->Group[port].PMUX[pin >> 1].bit.PMUXE = mode;
    }
  }
}

/** \brief Set pull-up or pull-down for pin
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \param [in] mode Mode for pin (no pulls/pull-up/pull-down)
 * \return void
 *
 */
void GPIO_SetPullMode(uint8_t port, uint8_t pin, uint8_t mode)
{
  if (pin > GPIO_MAX_PIN)
  {
    return;
  }
  switch (mode)
  {
    case GPIO_PULLMODE_NONE:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PULLEN;
      break;
    case GPIO_PULLMODE_UP:
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      PORT->Group[port].OUTSET.reg = (1UL << pin);
      break;
    case GPIO_PULLMODE_DOWN:
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      PORT->Group[port].OUTCLR.reg = (1UL << pin);
      break;
    default:
      /**< Undefined mode */
      break;
  }
}

/** \brief Set pin high
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \return void
 *
 */
void GPIO_SetPin(uint8_t port, uint8_t pin)
{
  //if (pin > GPIO_MAX_PIN)
  //  return;
  PORT->Group[port].OUTSET.reg = (1UL << pin);
}

/** \brief Set pin low
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \return void
 *
 */
void GPIO_ClearPin(uint8_t port, uint8_t pin)
{
  //if (pin > GPIO_MAX_PIN)
  //  return;
  PORT->Group[port].OUTCLR.reg = (1UL << pin);
}

/** \brief Toggle pin
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \return void
 *
 */
void GPIO_TogglePin(uint8_t port, uint8_t pin)
{
  //if (pin > GPIO_MAX_PIN)
  //  return;
  PORT->Group[port].OUTTGL.reg = (1UL << pin);
}

/** \brief Get pin value
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \return True if high, false otherwise
 *
 */
bool GPIO_GetPin(uint8_t port, uint8_t pin)
{
  //if (pin > GPIO_MAX_PIN)
  //  return false;
  return (PORT->Group[port].IN.reg & (1UL << pin));
}

/** \brief Get pin output
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \return True if high, false otherwise
 *
 */
bool GPIO_GetOutputPin(uint8_t port, uint8_t pin)
{
  //if (pin > GPIO_MAX_PIN)
  //  return false;
  return (PORT->Group[port].OUT.reg & (1UL << pin));
}

/** \brief Setup pin with one function
 *
 * \param [in] port Port number
 * \param [in] pin Pin number
 * \param [in] mode Pin mode (alternate function)
 * \param [in] dir Pin direction
 * \param [in] on Pin level for output, HIGH/LOW
 * \return void
 *
 */
void GPIO_SetupPin(uint8_t port, uint8_t pin, uint8_t mode, uint8_t dir, uint8_t level)
{
  if (dir == (uint8_t)GPIO_DIRECTION_OUT)
  {
    GPIO_SetDir(port, pin, true);
  } else
  {
    GPIO_SetDir(port, pin, false);
  }
  GPIO_SetFunction(port, pin, mode);
  if ((mode == GPIO_PIN_FUNC_OFF) && (dir == (uint8_t)GPIO_DIRECTION_OUT))
  {
    if (level == (uint8_t)GPIO_LEVEL_HIGH)
    {
      GPIO_SetPin(port, pin);
    } else
    {
      GPIO_ClearPin(port, pin);
    }
  }
}
