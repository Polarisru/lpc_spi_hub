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
//#include <SPI.h>

#define NOP __asm__ __volatile__ ("nop\n\t")

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
const int mosiPin = 11;
const int misoPin = 12;
const int sclkPin = 13;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(sclkPin, LOW);
  digitalWrite(mosiPin, LOW);
  pinMode(mosiPin, OUTPUT);
  pinMode(sclkPin, OUTPUT);
  pinMode(misoPin, INPUT);
  // initialize SPI:
  //SPI.begin();
  Serial.begin (115200) ;   // NOTE BAUD RATE  
}

char str1[] = "Test string 1   ";
char str2[] = "New test, wait  ";

void send_byte(uint8_t value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //SPI.transfer(value);
  for (int i = 0; i < 8; i++) {
    if (value & 0x80)
      digitalWrite(mosiPin, HIGH);
    else
      digitalWrite(mosiPin, LOW);
    digitalWrite(sclkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(sclkPin, LOW);    
    value <<= 1;
  }
  digitalWrite(mosiPin, LOW);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);  
}

uint8_t read_byte(uint8_t value) {
  uint8_t result = 0;
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //SPI.transfer(value);
  for (int i = 0; i < 8; i++) {
    result <<= 1;
    if (value & 0x80)
      digitalWrite(mosiPin, HIGH);
    else
      digitalWrite(mosiPin, LOW);
    digitalWrite(sclkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(sclkPin, LOW);
    if (digitalRead(misoPin) > 0) {
      result |= 0x01;    
    } else {
    }
    value <<= 1;
  }
  digitalWrite(mosiPin, LOW);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
  return result;  
}


void send_str(char str[]) {
  //  send in the address and value via SPI:
  send_byte(0xAA);  // signature
  int i = strlen(str) + 3;
  send_byte((uint8_t)i);
  send_byte(0x02);  // cmd+op code
  send_byte(0x00);  // data code
  for (int x = 0; x < i; x++) {
    send_byte(str[x]);
    delayMicroseconds(5);
  }
  send_byte(0x00);  // end of string
}

void clear_lcd(void) {
  send_byte(0xAA);  // signature
  send_byte(0x01);  // length
  send_byte(0x00);  // cmd+op code
}

uint8_t get_buttons(void) {
  send_byte(0xAA);  // signature
  send_byte(0x01);  // length
  send_byte(0x10);  // cmd code
  return read_byte(0x00); 
}

char str3[32];

void loop() {
  send_str(str1);
  delay(2000);
  //send_str(str2);
  //delay(2000);
  //Serial.print(get_buttons(), HEX);
  uint8_t value = get_buttons();
  delay(100);
  str3[0] = (value / 100) + '0'; 
  str3[1] = ((value % 100) / 10) + '0';
  str3[2] = (value % 10) + '0';
  str3[3] = ' '; 
  str3[4] = ' ';
  str3[5] = 0;
  send_str(str3);
  delay(2000);
}
