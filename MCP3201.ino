

#include <SPI.h>

const int chipSelectPinADC = 6;
unsigned int result = 0;
byte inByte = 0;
int saida;

const int PIN_CS = 7;
const int GAIN_1 = 0x1;
const int GAIN_2 = 0x0;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_CS, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  pinMode(chipSelectPinADC, OUTPUT);
  digitalWrite(chipSelectPinADC, HIGH);
}


void analog_to_digital()
{
  digitalWrite(chipSelectPinADC, LOW);
  result = SPI.transfer(0x00);
  result = result << 8;
  inByte = SPI.transfer(0x00);
  result = result | inByte;
  digitalWrite(chipSelectPinADC, HIGH);
  result = result >> 1;
  result = result & 0b0000111111111111;
}

void digital_to_analog(unsigned int val)
{
  saida = val;
  byte lowByte = (val & 0xff) ;
  byte highByte = ((val >> 8) & 0xff) | 0x10;
  //PORTB &= 0xfb;    // baixo
  SPI.transfer(highByte);
  SPI.transfer(lowByte);
  //PORTB |= 0x4;     // alto
}

void loop()
{
  analog_to_digital();
  digital_to_analog(result);
}
