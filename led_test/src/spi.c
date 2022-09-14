#include "drivers.h"
#include "pins.h"
#include "spi.h"

#define SPI_PREAMBLE    0xAAU

#define SPI_DUMMY_BYTE  0xFFU

void SPI_Delay(void)
{
  for (int i = 0; i < 20; i++)
  {
    __NOP();
  }
}

static void SPI_SendByte(uint8_t data)
{
  GPIO_ClearPin(SPI_CS_PORT, SPI_CS_PIN);
  for (int i = 0; i < 8; i++)
  {
    if (data & 0x80)
    {
      GPIO_SetPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
    } else
    {
      GPIO_ClearPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
    }
    GPIO_SetPin(SPI_SCLK_PORT, SPI_SCLK_PIN);
    data <<= 1;
    GPIO_ClearPin(SPI_SCLK_PORT, SPI_SCLK_PIN);
  }
  GPIO_SetPin(SPI_CS_PORT, SPI_CS_PIN);
  SPI_Delay();
}

static uint8_t SPI_GetByte(uint8_t data)
{
  uint8_t result = 0;

  GPIO_ClearPin(SPI_CS_PORT, SPI_CS_PIN);
  for (int i = 0; i < 8; i++)
  {
    result <<= 1;
    if (data & 0x80)
    {
      GPIO_SetPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
    } else
    {
      GPIO_ClearPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
    }
    GPIO_SetPin(SPI_SCLK_PORT, SPI_SCLK_PIN);
    if (GPIO_GetPin(SPI_MISO_PORT, SPI_MISO_PIN) == true)
    {
      result++;
    }
    GPIO_ClearPin(SPI_SCLK_PORT, SPI_SCLK_PIN);
    data <<= 1;
  }
  GPIO_SetPin(SPI_CS_PORT, SPI_CS_PIN);
  SPI_Delay();

  return result;
}

void SPI_SendString(char *str)
{
  SPI_SendByte(SPI_PREAMBLE);
  int i = strlen(str) + 2;
  SPI_SendByte((uint8_t)i);
  SPI_SendByte(0x02);  // cmd+op code
  SPI_SendByte(0x00);  // data code
  for (int x = 0; x < i; x++)
  {
    SPI_SendByte(str[x]);
  }
}

void SPI_ClearLcd(void)
{
  SPI_SendByte(SPI_PREAMBLE);  // signature
  SPI_SendByte(0x01);  // length
  SPI_SendByte(0x00);  // cmd+op code
}

uint8_t SPI_GetButtons(void)
{
  //SPI_SendByte(SPI_PREAMBLE);  // signature
  //SPI_SendByte(0x01);  // length
  //SPI_SendByte(0x10);  // cmd+op code
  return SPI_GetByte(SPI_PREAMBLE);
}

void SPI_SetLeds(uint8_t value)
{
  SPI_SendByte(SPI_PREAMBLE);  // signature
  SPI_SendByte(0x02);  // length
  SPI_SendByte(0x20);  // cmd+op code
  SPI_SendByte(value);
}

void SPI_SetPwm(uint8_t value)
{
  SPI_SendByte(SPI_PREAMBLE);  // signature
  SPI_SendByte(0x01);  // length
  SPI_SendByte(0x10 + (value & 0x0F));  // cmd+op code
}

void SPI_Init(void)
{
  GPIO_SetDir(SPI_SCLK_PORT, SPI_SCLK_PIN, true);
	GPIO_ClearPin(SPI_SCLK_PORT, SPI_SCLK_PIN);
  GPIO_SetDir(SPI_MOSI_PORT, SPI_MOSI_PIN, true);
	GPIO_ClearPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
  GPIO_SetDir(SPI_CS_PORT, SPI_CS_PIN, true);
	GPIO_ClearPin(SPI_CS_PORT, SPI_CS_PIN);
  GPIO_SetDir(SPI_MISO_PORT, SPI_MISO_PIN, false);
}

