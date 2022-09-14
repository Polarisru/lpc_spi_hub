# lpc_spi_hub
SPI hub for alpha-numeric display and keyboard based on LPC11U24 MCU

# Board Capabilities
1. Update the display:
- as the whole
- by line
- by row/column/length
2. Control backlight value
3. Set the state of two status LEDs
4. Check for button presses

# SPI protocol specification

### Packet format

| Byte offset | 0 | 1 | 2 | 3 |
|----------|:----:|:----:|:----:|:----:|
| Meaning  | Preamble<br>0xAA | Data Len<br>(Cmd.code + Data) | Cmd.code + Op.code | Data |

Every packet must be started with a preamble.

Data length is provided in bytes and can't be longer than 127 bytes.

Command code is a higher nibble of the byte (bits 7..4).

Operation code is a lower nibble of the byte (bits 3..0).

### List of command codes

| Cmd.code | Meaning| Op.codes | Data |
|----------|--------|----------|------|
| 0b0000 | Update the display | See below | Text string |
| 0b0001 | Set backlight value | Backlight value (1..15) | No |
| 0b0010 | Set state of status LEDs | No | 1 byte (See below) |

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

### Data byte for "Set state of status LEDs" command

State of up to 7 LEDs can be set

| Bit offset<br>(MSB first) | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---------------------------|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Meaning| Reserved | LED6 | LED5 | LED4 | LED3 | LED2 | LED1 | LED0 |

0 means switch LED off, 1 - switch LED on.

### Reading state of the buttons

Every byte transmitted from an SPI master will be responsed with a state of the buttons through MISO line.

| Bit offset<br>(MSB first) | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---------------------------|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Meaning| BTN7 | BTN6 | BTN5 | BTN4 | BTN3 | BTN2 | BTN1 | BTN0 |

0 means switch button was not pressed, 1 - button was pressed.

All bits will be reser after readout.