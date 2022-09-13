# lpc_spi_hub
SPI hub for alpha-numeric display and keyboard based on LPC11U24 MCU

# Board Capabilities
1. Update the display:
- as the whole
- by line
- by row/column/length
2. Check for button presses
3. Set the state of two status LEDs
4. Control backlight value

# SPI protocol specification

### Packet format

| Byte offset | 0 | 1 | 2 | 3 |
|----------|:----:|:----:|:----:|:----:|
| Meaning  | Preamble<br>0xAA | Data Len<br>(Cmd.code + Data) | Cmd.code + Op.code | Data |

Every packet must be started with a preamble.

Data length is provided in bytes and can't be longer than 128 bytes.

Command code is a higher nibble of the byte (bits 7..4).

Operation code is a lower nibble of the byte (bits 3..0).

### List of command codes

| Cmd.code | Meaning| Op.codes |
|----------|--------|----------|
| 0b0000 | Update the display | Yes |
| 0b0001 | Read buttont presses | No |
| 0b0010 | Set state of status LEDs | No |
| 0b0011 | Set backlight value | Backlight value (1..15) |

### List of operation codes for "Update the display" command

| Op.code | Meaning |
|---------|---------|
| 0b0000  | Clear display |
| 0b0001  | Write to whole display |
| 0b0002  | Write line |
| 0b0002  | Write at row/column |

First data byte contents row and column number for addressing the LCD output.

| Bit no. | 7 | 6..5 | 4..0 |
|---------|:-:|:----:|:----:|
| Meaning | Reserved | Row index<br>(0..3) | Column index<br>(0..19) |

### Packet example for "Update the display" command

| Byte offset | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
| Value | 0xAA | 0x06<br>(5 bytes + Cmd.code) | 0x02<br>Write line |  0x00<br>Line 0 | 0x54 ('T') | 0x65 ('e') | 0x73 ('s') | 0x74 ('t') |