#include "defines.h"
#include "outputs.h"
#include "st7066u.h"
#include "timer.h"

static int _row;
static int _column;
static int row_count;
static int col_count;

static int ST7066U_Address(int row, int column) {
    if ((row < row_count) && (column < col_count)) {
    	return 0x80 + ((row / 2) * 0x14) + ((row % 2) * 0x40) + column;
    } else {
        return 0x80;
    }
}

static void ST7066U_Locate(int row, int column) {
     _row = row;
    _column = column;
}

static void ST7066U_WriteTime(void) {
	OUTPUTS_Set(OUTPUTS_LCD_EN, true);
    TIMER_WaitMs(1);
	OUTPUTS_Set(OUTPUTS_LCD_EN, false);
    TIMER_WaitMs(1);
}

static void ST7066U_StartUp(void) {
    for(int i = 0; i < 3; i++) {
    	OUTPUTS_Set(OUTPUTS_LCD_DB7, false);
    	OUTPUTS_Set(OUTPUTS_LCD_DB6, false);
    	OUTPUTS_Set(OUTPUTS_LCD_DB5, true);
    	OUTPUTS_Set(OUTPUTS_LCD_DB4, true);
        ST7066U_WriteTime();
        TIMER_WaitMs(5);
    }
	OUTPUTS_Set(OUTPUTS_LCD_DB7, false);
	OUTPUTS_Set(OUTPUTS_LCD_DB6, false);
	OUTPUTS_Set(OUTPUTS_LCD_DB5, true);
	OUTPUTS_Set(OUTPUTS_LCD_DB4, false);
    ST7066U_WriteTime();
    TIMER_WaitMs(5);
}

static void ST7066U_WriteData(char value) {
    //Send upper four bits
	OUTPUTS_Set(OUTPUTS_LCD_DB7, (value >> 7) & 0x01);
	OUTPUTS_Set(OUTPUTS_LCD_DB6, (value >> 6) & 0x01);
	OUTPUTS_Set(OUTPUTS_LCD_DB5, (value >> 5) & 0x01);
	OUTPUTS_Set(OUTPUTS_LCD_DB4, (value >> 4) & 0x01);
    ST7066U_WriteTime();
    //Send lower four bits
    OUTPUTS_Set(OUTPUTS_LCD_DB7, (value >> 3) & 0x01);
    OUTPUTS_Set(OUTPUTS_LCD_DB6, (value >> 2) & 0x01);
    OUTPUTS_Set(OUTPUTS_LCD_DB5, (value >> 1) & 0x01);
    OUTPUTS_Set(OUTPUTS_LCD_DB4, (value >> 0) & 0x01);
    ST7066U_WriteTime();
}

static void ST7066U_WriteCommand(char value){
	OUTPUTS_Set(OUTPUTS_LCD_RS, false);
    ST7066U_WriteData(value);
}

static void ST7066U_WriteChar(char value){
	OUTPUTS_Set(OUTPUTS_LCD_RS, true);
    ST7066U_WriteData(value);
}

static void ST7066U_Character(int row, int column,  char c) {
    uint8_t a = ST7066U_Address(row, column);
    ST7066U_WriteCommand(a);
    ST7066U_WriteChar(c);
    // update position
    if (_column < col_count) {
        _column++;
    }
    if (_column >= col_count) {
        if (_row == 0){
            _column = 0;
            _row++;
        } else {
            _row = 0;
            _column = 0;
        }
    }
}

void ST7066U_Clear(void) {
	ST7066U_WriteCommand(ST7066U_CMD_CLEARDISPLAY);
    _row = 0;
    _column = 0;
}

void ST7066U_Write(const char* text) {
    _row = 0;
    _column = 0;
    int characterAmount =0;

    for(int i = 0; text[i] != '\0'; i++) {
        characterAmount++;
    }
    for (int i = 0; (i < characterAmount) && (i < row_count * col_count); i++) {
    	ST7066U_Character(_row, _column, text[i]);
    }
}

void ST7066U_WriteLine(const char* text, int line) {
    _row = line;
    _column = 0;
    int characterAmount =0;

    for(int i = 0; text[i] != '\0'; i++) {
        characterAmount++;
    }
    for (int i = 0; (i < characterAmount)  && (i < col_count); i++) {
    	ST7066U_Character(_row, _column, text[i]);
    }
}

void ST7066U_WriteCharacter(const char c, int row, int column) {
	ST7066U_Locate(row, column);
    ST7066U_Character(_row, _column, c);
}

void ST7066U_WriteCharacters(const char* text, int row, int column) {
	ST7066U_Locate(row, column);

    int characterAmount =0;

    for(int i = 0; text[i] != '\0'; i++) {
        characterAmount++;
    }
    for (int i = 0; (i < characterAmount)  && (i < col_count - column); i++) {
    	ST7066U_Character(_row, _column, text[i]);
    }
}

void ST7066U_Init(int rows, int columns) {
	row_count = rows;
	col_count = columns;

	// delay to wait for stable startup
	TIMER_WaitMs(100);

    ST7066U_StartUp();

    ST7066U_WriteCommand(ST7066U_CMD_FUNCTIONSET);
    TIMER_WaitMs(1);
    //ST7066U_WriteCommand(ST7066U_CMD_SETCURSOR);
    TIMER_WaitMs(1);
    ST7066U_WriteCommand(ST7066U_CMD_SETDISPLAY);
    TIMER_WaitMs(1);
    ST7066U_WriteCommand(ST7066U_CMD_ENTRYMODE);
    TIMER_WaitMs(1);
    //ST7066U_WriteCommand(ST7066U_CMD_CLEARDISPLAY);
    TIMER_WaitMs(1);
}
