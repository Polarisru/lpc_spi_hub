#include "driver_timer.h"

#define TIMER_NUM         TC1
#define TIMER_MCLK        MCLK_APBCMASK_TC1
#define TIMER_PRESCALER   TC_CTRLA_PRESCALER_DIV1024_Val
#define TIMER_GCLK_FREQ   48000000UL
#define TIMER_GCLK_ID     TC1_GCLK_ID
#define TIMER_FREQ        (TIMER_GCLK_FREQ / 1024U)
#define TIMER_1MS_TICK    ((uint16_t)TIMER_FREQ / 1000U)

//void TC1_Handler(void)
//{
//  if ((TIMER_NUM->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF) >> TC_INTFLAG_OVF_Pos)
//  {
//    TIMER_NUM->COUNT8.INTFLAG.reg = TC_INTFLAG_OVF;
//    //PORT_IOBUS->Group[GPIO_PORTA].OUTTGL.reg = (1UL << 8);
//  }
//}

/** \brief Initialize timer module
 *
 * \return void
 *
 */
void TIMER_Init(void)
{
  /**< Power on the device */
  MCLK->APBCMASK.reg |= TIMER_MCLK;
  GCLK->PCHCTRL[TIMER_GCLK_ID].reg = GCLK_PCHCTRL_GEN_GCLK0_Val | (1 << GCLK_PCHCTRL_CHEN_Pos);

  TIMER_NUM->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while ((TIMER_NUM->COUNT16.SYNCBUSY.reg & TC_SYNCBUSY_SWRST) > 0U) {}
  TIMER_NUM->COUNT16.CTRLA.reg |= (TIMER_PRESCALER << TC_CTRLA_PRESCALER_Pos) | TC_CTRLA_MODE_COUNT16;
  TIMER_NUM->COUNT16.CTRLBSET.bit.DIR = 1;
}

/** \brief Start timer with preset timeout in milliseconds
 *
 * \param [in] timeout Timeout value in ms
 * \return void
 *
 */
void TIMER_StartMs(uint16_t timeout)
{
  uint16_t temp = timeout * TIMER_1MS_TICK;
  TIMER_NUM->COUNT16.COUNT.reg = temp;
  TIMER_NUM->COUNT16.CTRLBSET.bit.ONESHOT = 1;
  TIMER_NUM->COUNT16.CTRLA.reg |= (TC_CTRLA_ENABLE);
  while ((TIMER_NUM->COUNT16.SYNCBUSY.reg & TC_SYNCBUSY_ENABLE) > 0U) {}
}

/** \brief Start timer with preset timeout in microseconds
 *
 * \param [in] timeout Timeout value in us
 * \return void
 *
 */
void TIMER_StartUs(uint16_t usec)
{
  uint16_t temp = TIMER_1MS_TICK;
  uint32_t temp32 = ((uint32_t)temp * usec + 500U) / 1000U;
  if (temp32 == 0U)
  {
    temp32 = 1;
  }
  TIMER_NUM->COUNT16.COUNT.reg = (uint16_t)temp32;
  TIMER_NUM->COUNT16.CTRLBSET.bit.ONESHOT = 1;
  TIMER_NUM->COUNT16.CTRLA.reg |= (TC_CTRLA_ENABLE);
  while ((TIMER_NUM->COUNT16.SYNCBUSY.reg & TC_SYNCBUSY_ENABLE) > 0U) {}
}

/** \brief Stop timer
 *
 * \return void
 *
 */
void TIMER_Stop(void)
{
  TIMER_NUM->COUNT16.INTFLAG.reg = TC_INTFLAG_OVF;
  TIMER_NUM->COUNT16.CTRLA.reg &= (~TC_CTRLA_ENABLE);
  while ((TIMER_NUM->COUNT16.SYNCBUSY.reg & TC_SYNCBUSY_ENABLE) > 0U) {}
}

/** \brief Check if timeout occurred
 *
 * \return True if timeout occurred
 *
 */
bool TIMER_IsTimeout(void)
{
  //if (TIMER_NUM->COUNT16.INTFLAG.bit.OVF)
  //  return true;
  //return false;
  return (TIMER_NUM->COUNT16.INTFLAG.bit.OVF > 0U);
}

/** \brief Do delay in milliseconds
 *
 * \param [in] msec Delay value in msec
 * \return void
 *
 */
void TIMER_DelayMs(uint16_t msec)
{
  TIMER_StartMs(msec);
  while (!TIMER_IsTimeout()) {}
  TIMER_Stop();
}

/** \brief Do delay in microseconds
 *
 * \param [in] usec Delay value in usec
 * \return void
 *
 */
void TIMER_DelayUs(uint16_t usec)
{
  TIMER_StartUs(usec);
  while (!TIMER_IsTimeout()) {}
  TIMER_Stop();
}
