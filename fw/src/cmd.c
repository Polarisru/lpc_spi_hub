#include "backlight.h"
#include "buttons.h"
#include "cmd.h"
#include "led.h"
#include "spi.h"
#include "st7066u.h"

#define CMD_LCD			0
#define CMD_BUTTONS		1
#define CMD_LEDS		2
#define CMD_BACKLIGHT	3

static volatile bool CMD_ready = false;
static uint8_t CMD_buff[128];

void CMD_SetReady(uint8_t *data, uint8_t len)
{
	memcpy(CMD_buff, data, len);
	CMD_buff[len] = 0;
	CMD_ready = true;
}

void CMD_Process(void)
{
	if (CMD_ready == true) {
		// command received
		switch (CMD_buff[SPI_OFS_CMD]) {
			case CMD_LCD:
				//SPI_buff[SPI_head] = 0;
				ST7066U_WriteLine((const char*)&CMD_buff[SPI_OFS_STRING], 0);
				break;
			case CMD_BUTTONS:
				break;
			case CMD_BACKLIGHT:
				break;
			case CMD_LEDS:
				break;
			default:
				// unknown command, ignore
				break;
		}
		CMD_ready = false;
	}
}

