#ifndef SPI_H_
#define SPI_H_

#include "defines.h"

void SPI_SendString(char *str);
void SPI_ClearLcd(void);
uint8_t SPI_GetButtons(void);
void SPI_SetLeds(uint8_t value);
void SPI_SetPwm(uint8_t value);
void SPI_Init(void);

#endif
