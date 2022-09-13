#include "drivers.h"
//#include "outputs.h"
#include "pins.h"
#include "spi.h"
//#include "st7066u.h"

char str1[] = "Test string 1   ";
char str2[] = "New test, wait  ";
char str3[32];

int main(void)
{
	CLK_Init();
	TIMER_Init();
  GPIO_Init();
  GPIO_ClearPin(LED_BOARD_PORT, LED_BOARD_PIN);
  GPIO_SetDir(LED_BOARD_PORT, LED_BOARD_PIN, true);
  GPIO_SetFunction(LED_BOARD_PORT, LED_BOARD_PIN, GPIO_PIN_FUNC_OFF);
  //OUTPUTS_Init();
  SPI_Init();

  //ST7066U_Init(4, 20);
  //ST7066U_WriteLine("Hello world!", 0);

  while (1)
  {
    GPIO_TogglePin(LED_BOARD_PORT, LED_BOARD_PIN);
    SPI_SendString(str1);
    TIMER_DelayMs(1000);
    GPIO_TogglePin(LED_BOARD_PORT, LED_BOARD_PIN);
    SPI_SendString(str2);
    TIMER_DelayMs(1000);
    GPIO_TogglePin(LED_BOARD_PORT, LED_BOARD_PIN);
    //SPI_ClearLcd();
    sprintf(str3, "Button: 0x%02X    ", SPI_GetButtons());
    TIMER_DelayMs(10);
    SPI_SendString(str3);
    TIMER_DelayMs(1000);
    //SPI_SetLeds(0x00);
    SPI_SetPwm(1);
    TIMER_DelayMs(1000);
    //SPI_SetLeds(0x01);
    SPI_SetPwm(9);
    TIMER_DelayMs(1000);
  }
}
