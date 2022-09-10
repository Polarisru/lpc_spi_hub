#include "chip.h"
#include "cmd.h"
#include "pins.h"
#include "spi.h"
#include "st7066u.h"

#define SPI_CMD_LCD			0

uint8_t SPI_buff[SPI_MAX_LEN];
uint8_t SPI_cmd[SPI_MAX_LEN];
uint8_t SPI_head;
uint8_t SPI_len;
volatile bool SPI_ready;

void SSP0_IRQHandler(void)
{
	uint32_t regValue;
	uint8_t byte;

	regValue = LPC_SSP0->MIS;
//	if (regValue & SSP_RORMIS)	/* Receive overrun interrupt */
//	{
//		LPC_SSP0->ICR = SSP_RORIC;	/* clear interrupt */
//	}
//	if (regValue & SSP_RTMIS)	/* Receive timeout interrupt */
//	{
//		LPC_SSP0->ICR = SSP_RTIC;	/* clear interrupt */
//	}
	if (regValue & SSP_RXMIS)	/* Rx at least half full */
	{
		byte = (uint8_t)LPC_SSP0->DR;
		if (byte == SPI_START_SIGN) {
			// new command received
			SPI_head = 0;
			SPI_len = 0;
			SPI_ready = false;
		} else {
			if (SPI_len == 0) {
				SPI_len = byte;
			} else {
				SPI_buff[SPI_head++] = byte;
				if (SPI_head == SPI_len) {
					// command received
					SPI_head = 0;
					memcpy(SPI_cmd, SPI_buff, SPI_len);
					SPI_ready = true;
				}
			}
		}
	}
	return;
}

void SPI_Init(void)
{
	// configure SPI pins
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_SCLK_PORT, SPI_SCLK_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for SCLK */
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_CS_PORT, SPI_CS_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for CS */
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for MISO */
	Chip_IOCON_PinMuxSet(LPC_IOCON, SPI_MOSI_PORT, SPI_MOSI_PIN, IOCON_FUNC1 | IOCON_MODE_INACT); /* PIO0_18 used for MOSI */

	Chip_SSP_Init(LPC_SSP0);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SSP0);
	Chip_SSP_SetFormat(LPC_SSP0, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_MODE0);
	Chip_SSP_Set_Mode(LPC_SSP0, SSP_MODE_SLAVE);
	Chip_SSP_Enable(LPC_SSP0);

	SPI_head = 0;
	SPI_len = 0;
	SPI_ready = false;

	LPC_SSP0->IMSC |= SSP_RXIM;
	NVIC_EnableIRQ(SSP0_IRQn);
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
			SPI_len = 0;
		} else {
			if (SPI_len == 0) {
				SPI_len = byte;
			} else {
				SPI_buff[SPI_head++] = byte;
				if (SPI_head == SPI_len) {
					// command received
					switch (SPI_buff[SPI_OFS_CMD]) {
						case SPI_CMD_LCD:
							SPI_buff[SPI_head] = 0;
							ST7066U_WriteLine((const char*)&SPI_buff[SPI_OFS_STRING], 0);
							break;
						default:
							// unknown command, ignore
							break;
					}
				} else
				if ((SPI_head > SPI_MAX_LEN) || (SPI_head > SPI_len)) {
					SPI_head = 0;
				}
			}
		}
	}
}

void SPI_SetData(uint8_t tx_data)
{
	Chip_SSP_SendFrame(LPC_SSP0, (uint16_t)tx_data);
}

void SPI_ProcessNew(void)
{
	if (SPI_ready == true) {
		// command received
		switch (SPI_buff[SPI_OFS_CMD]) {
			case SPI_CMD_LCD:
				//SPI_buff[SPI_head] = 0;
				ST7066U_WriteLine((const char*)&SPI_cmd[SPI_OFS_STRING], 0);
				break;
			default:
				// unknown command, ignore
				break;
		}
		SPI_ready = false;
	}
}
