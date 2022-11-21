/*
 * main.c
 *
 *  Created on: 2022 Nov 20 19:19:00
 *  Author: Alex
 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

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

  UART_Transmit(&UART_0, (uint8_t*)msg, strlen(msg));

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  if (SYSTIMER_GetTickCount() > ticks)
	  {
		  ticks += 1000;
		  sprintf(str, "%d\n", ticks);
		  UART_Transmit(&UART_0, (uint8_t*)str, strlen(str));
	  }
  }
}
