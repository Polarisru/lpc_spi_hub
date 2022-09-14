#include "backlight.h"
#include "buttons.h"
#include "cmd.h"
#include "global.h"
#include "led.h"
#include "spi.h"
#include "st7066u.h"

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
	uint8_t value;
	uint8_t value2;

	if (CMD_ready == true) {
		// command received
		switch (CMD_buff[CMD_OFFS_CMD] >> CMD_BYTE_OFFS) {
			case CMD_LCD:
				switch (CMD_buff[CMD_OFFS_CMD] & CMD_OP_MASK) {
					case CMD_LCD_OP_CLEAR:
						ST7066U_Clear();
						break;
					case CMD_LCD_OP_WHOLE:
						break;
					case CMD_LCD_OP_LINE:
						value = (CMD_buff[CMD_OFFS_DATA] >> CMD_LCD_OFFS_ROW) & CMD_LCD_MASK_ROW;
						ST7066U_WriteLine((const char*)&CMD_buff[CMD_OFFS_STRING], value);
						break;
					case CMD_LCD_OP_ADDR:
						value = (CMD_buff[CMD_OFFS_DATA] >> CMD_LCD_OFFS_ROW) & CMD_LCD_MASK_ROW;
						value2 = (CMD_buff[CMD_OFFS_DATA] >> CMD_LCD_OFFS_COL) & CMD_LCD_MASK_COL;
						ST7066U_WriteCharacters((const char*)&CMD_buff[CMD_OFFS_STRING], value, value2);
						break;
					default:
						// unknown upcode, ignore
						break;
				}
				break;
			case CMD_BACKLIGHT:
				value = CMD_buff[CMD_OFFS_CMD] & CMD_OP_MASK;
				BACKLIGHT_SetValue(value);
				break;
			case CMD_LEDS:
				value = CMD_buff[CMD_OFFS_DATA];
				for (int i = 0; i < LED_LAST; i++) {
					LED_Set(i, (value & 0x01) > 0);
					value >>= 1;
				}
				break;
			case CMD_BUTTONS:
				SPI_SetData(GLOBAL_buttons);
				GLOBAL_buttons = 0;
				break;
			default:
				// unknown command, ignore
				break;
		}
		CMD_ready = false;
	}
}

