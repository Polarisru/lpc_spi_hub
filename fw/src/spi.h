#ifndef SPI_H_
#define SPI_H_

#include "defines.h"

#define SPI_START_SIGN		0xAA

#define SPI_MAX_LEN			(128 + 3)

#define SPI_OFS_CMD			0
#define SPI_OFS_OP			1
#define SPI_OFS_STRING		2

void SPI_Init(void);
void SPI_SetData(uint8_t tx_data);
void SPI_Process(void);
void SPI_ProcessNew(void);

#endif /* SPI_H_ */
