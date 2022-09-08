#include "chip.h"
#include "pins.h"
#include "spi.h"
#include "st7066u.h"

#define SPI_START_SIGN		0xAA

#define SPI_MAX_LEN			(128 + 3)

#define SPI_OFS_CMD			0
#define SPI_OFS_OP			1
#define SPI_OFS_LEN			2
#define SPI_OFS_STRING		3

#define SPI_CMD_LCD			0

uint8_t SPI_buff[SPI_MAX_LEN];
uint8_t SPI_head;
uint8_t SPI_len;

//void SSP0_IRQHandler(void)
//{
//  uint32_t regValue;
//
//  regValue = LPC_SSP0->MIS;
//  if (regValue & SSPMIS_RORMIS)	/* Receive overrun interrupt */
//  {
//	LPC_SSP0->ICR = SSPICR_RORIC;	/* clear interrupt */
//  }
//  if (regValue & SSPMIS_RTMIS)	/* Receive timeout interrupt */
//  {
//	LPC_SSP0->ICR = SSPICR_RTIC;	/* clear interrupt */
//  }
//  if (regValue & SSPMIS_RXMIS)	/* Rx at least half full */
//  {
//	/* receive until it's empty */
//  }
//  return;
//}

void SPI_Init(void)
{
	// configure SPI pins
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for SCLK */
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for CS */
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for MISO */
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for MOSI */

	Chip_SSP_Init(LPC_SSP0);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SSP0);
	Chip_SSP_SetFormat(LPC_SSP0, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_MODE0);
	Chip_SSP_Set_Mode(LPC_SSP0, SSP_MODE_SLAVE);
	Chip_SSP_Enable(LPC_SSP0);

	SPI_head = 0;
	SPI_len = 0;
}

void SPI_Process(void)
{
	uint8_t byte;
	if (LPC_SSP0->SR & SSP_STAT_RNE) {
		// SPI receive buffer is not empty
		byte = (uint8_t)LPC_SSP0->DR;
		if (byte == SPI_START_SIGN) {
			// new command received
			SPI_head = 0;
			SPI_len = 1;
		} else {
			SPI_buff[SPI_head++] = byte;
			if (SPI_head == 1) {
				// command received
				switch (SPI_buff[SPI_OFS_CMD]) {
					case SPI_CMD_LCD:
						SPI_len += 2;
						break;
				}
			} else
			if (SPI_head == 3) {
				SPI_len += SPI_buff[SPI_OFS_LEN];
			} else
			if (SPI_head == SPI_len) {
				// command received
				ST7066U_WriteLine((const char*)&SPI_buff[SPI_OFS_STRING], 0);
			} else
			if ((SPI_head > SPI_MAX_LEN) || (SPI_head > SPI_len)) {
				SPI_head = 0;
			}
		}
	}
}
