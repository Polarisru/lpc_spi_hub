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
| bit no. | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---------|---|---|---|---|---|---|---|---|
| meaning <td colspan=4>cmd.code</td><td colspan=4>op.code</td>

List of command codes:

| cmd.code | meaning|
|----------|--------|
| 0b0000 | Update the display |
| 0b0001 | Read buttont presses |
| 0b0010 | Set state of status LEDs |
| 0b0011 | Set backlight value (1..15) |
