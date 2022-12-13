#include "defines.h"
#include "st7066u.h"
#include "outputs.h"
#include "timer.h"
#include "led.h"

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

volatile uint32_t counter = 0;
volatile uint32_t len = 0;
uint8_t data[256];
uint8_t data_count = 0;

void SPI_SlaveSelected(void)
{
  counter++;
}

void SPI_GetByte(void)
{
  len = SPI_SLAVE_0.runtime->rx_data_count;
  SPI_SLAVE_Receive(&SPI_SLAVE_0, &data[data_count++], 1);
}

int main(void)
{
  DAVE_STATUS_t status;
  char msg[] = "Device started!\n";
  char str[16];
  uint32_t ticks = 1000;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  //UART_Transmit(&UART_0, (uint8_t*)msg, strlen(msg));
  //SPI_SLAVE_Receive(&SPI_SLAVE_0, data, 1);

  TIMER_Init();
  OUTPUTS_Init();
  LED_Init();

  ST7066U_Init(4, 20);
  ST7066U_WriteLine("Hello, world #1!", 0);
  ST7066U_WriteLine("Hello, world #2!", 2);
  TIMER_WaitMs(1000);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
//	  if (SYSTIMER_GetTickCount() > ticks)
//	  {
//		  ticks += 1000;
//		  sprintf(str, "%d\n", ticks);
//		  UART_Transmit(&UART_0, (uint8_t*)str, strlen(str));
//	  }
	LED_Set(LED_BOARD, true);
	TIMER_WaitMs(500);
	LED_Set(LED_BOARD, false);
	TIMER_WaitMs(500);
  }
}
