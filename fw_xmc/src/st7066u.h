#ifndef ST7066U_H_
#define ST7066U_H_

#define ST7066U_CMD_CLEARDISPLAY 	0x01 // Resets the whole display to blank
#define ST7066U_CMD_RETURNHOME 		0x02 // Sets the cursor to the beginning of the screen. 0x02 = 0000 0010
//#define ST7066U_CMD_ENTRYMODE 		0x06 // Sets Entry Mode. 0x06 = 0000 0110
//#define ST7066U_CMD_SETDISPLAY 		0x0C // Sets Entire Display on, Display on, Cursor on. 0x0C = 0000 1011
#define ST7066U_CMD_SETCURSOR 		0x10 // Sets cursor moving and display shift, and direction without changing DDRAM data. 0x10 = 0001 0000
//#define ST7066U_CMD_FUNCTIONSET 	0x28 // Sets the interface data type to 4 bits, 2 lines, and font size 5x8. 0x28 = 0010 1000
#define ST7066U_CMD_WAKEUP 			0x30 //

/* Function Set Defines */
#define     FUNCTION_SET      0x20  // Must be set to execute FUNCTION_SET_CMD
#define     INTFC_DATA_LEN    0x10  // HIGH: 8-bit interface | LOW: 4-bit interface
#define     TWO_LINE_DISP     0x08  // HIGH: 2-line display | LOW: 1-line display
#define     CHAR_FONT_SIZE    0x04  // HIGH: 5x10 dots | LOW: 5x8 dots (only usable with 1-line display)
/* Function Set Command - modify to liking */
#define     ST7066U_CMD_FUNCTIONSET  (FUNCTION_SET | TWO_LINE_DISP)

/* Display Initialization Defines */
#define     DISPLAY_ON        0x08  // Must be set to execute DISPLAY_ON_CMD
#define     ENTIRE_DISP_ON    0x04
#define     CURSOR_ON         0x02  // Show the cursor at current position
#define     CURSOR_BLINK_ON   0x01  // Make the cursor blink
/* Display Initialization Command - modify to liking */
#define     ST7066U_CMD_SETDISPLAY    (DISPLAY_ON | ENTIRE_DISP_ON)

/* Entry Mode Initialization Defines */
#define     ENTRY_MODE        0x04  // Must be set to execute ENTRY_MODE_CMD
#define     CURSOR_INCR       0x02  // Cursor increment on character write, else decrement
#define     DISPLAY_SHIFT_ON  0x01  // Shift display according to CURSOR_INCR
/* Entry Mode Initialization Command - modify to liking */
#define     ST7066U_CMD_ENTRYMODE    (ENTRY_MODE | CURSOR_INCR)

extern void ST7066U_Clear(void);
extern void ST7066U_Write(const char* text);
extern void ST7066U_WriteLine(const char* text, int line);
extern void ST7066U_WriteCharacter(const char c, int row, int column);
extern void ST7066U_WriteCharacters(const char* text, int row, int column);
extern void ST7066U_Init(int rows, int columns);

#endif /* ST7066U_H_ */
