#ifndef ST7066U_H_
#define ST7066U_H_

#define ST7066U_CMD_CLEARDISPLAY 	0x01 // Resets the whole display to blank
#define ST7066U_CMD_RETURNHOME 		0x02 // Sets the cursor to the beginning of the screen. 0x02 = 0000 0010
#define ST7066U_CMD_ENTRYMODE 		0x06 // Sets Entry Mode. 0x06 = 0000 0110
#define ST7066U_CMD_SETDISPLAY 		0x0C // Sets Entire Display on, Display on, Cursor on. 0x0C = 0000 1011
#define ST7066U_CMD_SETCURSOR 		0x10 // Sets cursor moving and display shift, and direction without changing DDRAM data. 0x10 = 0001 0000
#define ST7066U_CMD_FUNCTIONSET 	0x28 // Sets the interface data type to 4 bits, 2 lines, and font size 5x8. 0x28 = 0010 1000
#define ST7066U_CMD_WAKEUP 			0x30 //

extern void ST7066U_Clear(void);
extern void ST7066U_Write(const char* text);
extern void ST7066U_WriteLine(const char* text, int line);
extern void ST7066U_WriteCharacter(const char c, int row, int column);
extern void ST7066U_WriteCharacters(const char* text, int row, int column);
extern void ST7066U_Init(int rows, int columns);

#endif /* ST7066U_H_ */
