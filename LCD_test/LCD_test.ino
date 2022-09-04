#define ST7066U_CMD_CLEARDISPLAY   0x01 // Resets the whole display to blank
#define ST7066U_CMD_RETURNHOME    0x02 // Sets the cursor to the beginning of the screen. 0x02 = 0000 0010
//#define ST7066U_CMD_ENTRYMODE     0x06 // Sets Entry Mode. 0x06 = 0000 0110
//#define ST7066U_CMD_SETDISPLAY    0x0C // Sets Entire Display on, Display on, Cursor on. 0x0C = 0000 1011
#define ST7066U_CMD_SETCURSOR     0x10 // Sets cursor moving and display shift, and direction without changing DDRAM data. 0x10 = 0001 0000
//#define ST7066U_CMD_FUNCTIONSET   0x28 // Sets the interface data type to 4 bits, 2 lines, and font size 5x8. 0x28 = 0010 1000
#define ST7066U_CMD_WAKEUP      0x30 //

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

#define OUTPUTS_LCD_D7   2
#define OUTPUTS_LCD_D6   3
#define OUTPUTS_LCD_D5   4
#define OUTPUTS_LCD_D4   5
#define OUTPUTS_LCD_EN    11
#define OUTPUTS_LCD_RS    12

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
    digitalWrite(OUTPUTS_LCD_EN, HIGH);
    delay(1);
    digitalWrite(OUTPUTS_LCD_EN, LOW);
    delay(1);
}

static void ST7066U_StartUp(void) {
    for(int i = 0; i < 3; i++) {
      digitalWrite(OUTPUTS_LCD_D7, LOW);
      digitalWrite(OUTPUTS_LCD_D6, LOW);
      digitalWrite(OUTPUTS_LCD_D5, HIGH);
      digitalWrite(OUTPUTS_LCD_D4, HIGH);
        ST7066U_WriteTime();
        delay(5);
    }
    digitalWrite(OUTPUTS_LCD_D7, LOW);
    digitalWrite(OUTPUTS_LCD_D6, LOW);
    digitalWrite(OUTPUTS_LCD_D5, HIGH);
    digitalWrite(OUTPUTS_LCD_D4, LOW);
    ST7066U_WriteTime();
    delay(5);
}

static void ST7066U_WriteData(char value) {
    //Send upper four bits
  digitalWrite(OUTPUTS_LCD_D7, (value >> 7) & 0x01);
  digitalWrite(OUTPUTS_LCD_D6, (value >> 6) & 0x01);
  digitalWrite(OUTPUTS_LCD_D5, (value >> 5) & 0x01);
  digitalWrite(OUTPUTS_LCD_D4, (value >> 4) & 0x01);
    ST7066U_WriteTime();
    //Send lower four bits
    digitalWrite(OUTPUTS_LCD_D7, (value >> 3) & 0x01);
    digitalWrite(OUTPUTS_LCD_D6, (value >> 2) & 0x01);
    digitalWrite(OUTPUTS_LCD_D5, (value >> 1) & 0x01);
    digitalWrite(OUTPUTS_LCD_D4, (value >> 0) & 0x01);
    ST7066U_WriteTime();
}

static void ST7066U_WriteCommand(char value){
    digitalWrite(OUTPUTS_LCD_RS, LOW);
    ST7066U_WriteData(value);
}

static void ST7066U_WriteChar(char value){
    digitalWrite(OUTPUTS_LCD_RS, HIGH);
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
  delay(100);

    ST7066U_StartUp();

    ST7066U_WriteCommand(ST7066U_CMD_FUNCTIONSET);
    delay(1);
    //ST7066U_WriteCommand(ST7066U_CMD_SETCURSOR);
    delay(1);
    ST7066U_WriteCommand(ST7066U_CMD_SETDISPLAY);
    delay(1);
    ST7066U_WriteCommand(ST7066U_CMD_ENTRYMODE);
    delay(1);
    //ST7066U_WriteCommand(ST7066U_CMD_CLEARDISPLAY);
    delay(1);
}

void setup() {
  digitalWrite(OUTPUTS_LCD_D7, LOW);
  digitalWrite(OUTPUTS_LCD_D6, LOW);
  digitalWrite(OUTPUTS_LCD_D5, LOW);
  digitalWrite(OUTPUTS_LCD_D4, LOW);
  digitalWrite(OUTPUTS_LCD_EN, LOW);
  digitalWrite(OUTPUTS_LCD_RS, LOW);
  pinMode(OUTPUTS_LCD_D7, OUTPUT);
  pinMode(OUTPUTS_LCD_D6, OUTPUT);
  pinMode(OUTPUTS_LCD_D5, OUTPUT);
  pinMode(OUTPUTS_LCD_D4, OUTPUT);
  pinMode(OUTPUTS_LCD_EN, OUTPUT);
  pinMode(OUTPUTS_LCD_RS, OUTPUT);

  ST7066U_Init(4, 20);
  ST7066U_WriteLine("Hello world!", 0);
  ST7066U_WriteLine("Sosi pisju!", 2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
