/*
  Digital Pot Control

  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.

 The AD5206 is SPI-compatible,and to command it, you send two bytes,
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).

 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

 created 10 Aug 2010
 by Tom Igoe

 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005

*/


// inslude the SPI library:
#include <SPI.h>

#define NOP __asm__ __volatile__ ("nop\n\t")

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
}

char str1[] = "Test string 1   ";
char str2[] = "New test, wait  ";

void send_byte(uint8_t value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);  
}

void send_str(char str[]) {
  //  send in the address and value via SPI:
  send_byte(0xAA);  // signature
  int i = strlen(str) + 3;
  send_byte((uint8_t)i);
  send_byte(0x00);  // cmd code
  send_byte(0x00);  // op code
  for (int x = 0; x < i; x++) {
    send_byte(str[x]);
    delayMicroseconds(5);
  }
  send_byte(0x00);  // end of string
}

void loop() {
  send_str(str1);
  delay(2000);
  send_str(str2);
  delay(2000);
}
