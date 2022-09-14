#ifndef SPI_H_
#define SPI_H_

#include "defines.h"

#define SPI_MAX_LEN			128

void SPI_SetData(uint8_t tx_data);
void SPI_Init(void);

#endif /* SPI_H_ */
