#ifndef PINS_H_
#define PINS_H_

#ifdef DEF_OLD_PCB
	#define LED_BOARD_PORT		0
	#define LED_STAT0_PORT		1
	#define LED_STAT1_PORT		1
	#define BTN_UP_PORT			0
	#define BTN_LEFT_PORT		0
	#define BTN_DOWN_PORT		0
	#define BTN_PWR_PORT		1
	#define BTN_SELECT_PORT		1
	#define BTN_RIGHT_PORT		1
	#define BTN_RUN_PORT		1
	#define OUT_LCD_DB4_PORT	0
	#define OUT_LCD_DB5_PORT	0
	#define OUT_LCD_DB6_PORT	0
	#define OUT_LCD_DB7_PORT	0
	#define OUT_LCD_EN_PORT		1
	#define OUT_LCD_RW_PORT		1
	#define OUT_LCD_RS_PORT		1
	#define SPI_CS_PORT			0
	#define SPI_MOSI_PORT		0
	#define SPI_MISO_PORT		0
	#define SPI_SCLK_PORT		1
	#define BACKLIGHT_PORT		0

	#define LED_BOARD_PIN		7
	#define LED_STAT0_PIN		28
	#define LED_STAT1_PIN		5
	#define BTN_UP_PIN			17
	#define BTN_LEFT_PIN		18
	#define BTN_DOWN_PIN		23
	#define BTN_PWR_PIN			13
	#define BTN_SELECT_PIN		14
	#define BTN_RIGHT_PIN		15
	#define BTN_RUN_PIN			22
	#define OUT_LCD_DB4_PIN		11
	#define OUT_LCD_DB5_PIN		12
	#define OUT_LCD_DB6_PIN		13
	#define OUT_LCD_DB7_PIN		14
	#define OUT_LCD_EN_PIN		19
	#define OUT_LCD_RW_PIN		21
	#define OUT_LCD_RS_PIN		20
	#define SPI_CS_PIN			2
	#define SPI_MOSI_PIN		9
	#define SPI_MISO_PIN		8
	#define SPI_SCLK_PIN		29
	#define BACKLIGHT_PIN		16
#else
	#define LED_BOARD_PORT		0
	#define LED_STAT0_PORT		1
	#define LED_STAT1_PORT		1
	#define BTN_UP_PORT			0
	#define BTN_LEFT_PORT		0
	#define BTN_DOWN_PORT		0
	#define BTN_PWR_PORT		1
	#define BTN_SELECT_PORT		1
	#define BTN_RIGHT_PORT		1
	#define BTN_RUN_PORT		1
	#define OUT_LCD_DB4_PORT	XMC_GPIO_PORT1
	#define OUT_LCD_DB5_PORT	XMC_GPIO_PORT1
	#define OUT_LCD_DB6_PORT	XMC_GPIO_PORT1
	#define OUT_LCD_DB7_PORT	XMC_GPIO_PORT1
	#define OUT_LCD_EN_PORT		XMC_GPIO_PORT1
	#define OUT_LCD_RW_PORT		XMC_GPIO_PORT1
	#define OUT_LCD_RS_PORT		XMC_GPIO_PORT1
	#define SPI_CS_PORT			0
	#define SPI_MOSI_PORT		0
	#define SPI_MISO_PORT		0
	#define SPI_SCLK_PORT		0
	#define BACKLIGHT_PORT		0

	#define LED_BOARD_PIN		7
	#define LED_STAT0_PIN		28
	#define LED_STAT1_PIN		5
	#define BTN_UP_PIN			17
	#define BTN_LEFT_PIN		18
	#define BTN_DOWN_PIN		19
	#define BTN_PWR_PIN			1
	#define BTN_SELECT_PIN		12
	#define BTN_RIGHT_PIN		15
	#define BTN_RUN_PIN			22
	#define OUT_LCD_DB4_PIN		22
	#define OUT_LCD_DB5_PIN		29
	#define OUT_LCD_DB6_PIN		11
	#define OUT_LCD_DB7_PIN		11
	#define OUT_LCD_EN_PIN		26
	#define OUT_LCD_RW_PIN		27
	#define OUT_LCD_RS_PIN		4
	#define SPI_CS_PIN			2
	#define SPI_MOSI_PIN		9
	#define SPI_MISO_PIN		8
	#define SPI_SCLK_PIN		10
	#define BACKLIGHT_PIN		13
#endif

#endif /* PINS_H_ */
