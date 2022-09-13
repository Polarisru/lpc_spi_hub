#ifndef SPI_H_
#define SPI_H_

#include "defines.h"

#define SPI_START_SIGN		0xAA

#define SPI_MAX_LEN			(128 + 3)

void SPI_Init(void);
void SPI_SetData(uint8_t tx_data);

#endif /* SPI_H_ */
