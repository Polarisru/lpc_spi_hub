#include "chip.h"
#include "cmd.h"
#include "pins.h"
#include "spi.h"
#include "st7066u.h"

uint8_t SPI_buff[SPI_MAX_LEN];
uint8_t SPI_head;
uint8_t SPI_len;

void SPI_SetData(uint8_t tx_data)
{
	Chip_SSP_SendFrame(LPC_SSP0, (uint16_t)tx_data);
}

void SSP0_IRQHandler(void)
{
	uint32_t regValue;
	uint8_t byte;

	regValue = LPC_SSP0->MIS;
	if (regValue & SSP_RORMIS)	/* Receive overrun interrupt */
	{
		LPC_SSP0->ICR = SSP_RORIC;	/* clear interrupt */
	}
	if (regValue & SSP_RTMIS)	/* Receive timeout interrupt */
	{
		LPC_SSP0->ICR = SSP_RTIC;	/* clear interrupt */
	}
	if (regValue & SSP_RXMIS)	/* Rx at least half full */
	{
		if (LPC_SSP0->SR & SSP_STAT_RNE) {
			byte = (uint8_t)LPC_SSP0->DR;
			if (byte == CMD_START_SIGN) {
				// new command received
				SPI_head = 0;
				SPI_len = 0;
				SPI_SetData(0);
			} else {
				if (SPI_len == 0) {
					SPI_len = byte;
				} else {
					SPI_buff[SPI_head++] = byte;
					if (SPI_head >= SPI_len) {
						// command received
						SPI_head = 0;
						CMD_SetReady(SPI_buff, SPI_len);
					}
				}
			}
		}
	}
	return;
}

void SPI_Init(void)
{
	// configure SPI pins
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_SCLK_PORT, SPI_SCLK_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); 	/* SCLK */
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_CS_PORT, SPI_CS_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); 		/* CS */
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_MISO_PORT, SPI_MISO_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); 	/* MISO */
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_MOSI_PORT, SPI_MOSI_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); 	/* MOSI */

	Chip_SSP_Init(LPC_SSP0);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SSP0);
	Chip_SSP_SetFormat(LPC_SSP0, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_MODE0);
	Chip_SSP_Set_Mode(LPC_SSP0, SSP_MODE_SLAVE);
	Chip_SSP_SetClockRate(LPC_SSP0, 1, 2);
	Chip_SSP_Enable(LPC_SSP0);

	SPI_head = 0;
	SPI_len = 0;

	// set interrupt
	LPC_SSP0->IMSC |= SSP_RXIM;
	NVIC_EnableIRQ(SSP0_IRQn);
}
