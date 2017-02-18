

#include <SPI.h>


unsigned int result = 0;
byte inByte = 0; 
byte byteOne = 0;              //Initialize an 8 bit variable to read the first byte from the MCP3201
byte byteTwo = 0;
int saida;

const int GAIN_1 = 0x1;
const int GAIN_2 = 0x0;

void setup()
{
  Serial.begin(9600);

  // ADC SETUP
  // CS PIN USED IS 10!
  SPI.begin(10);                           //Initialize the bus for a device on pin 4
  SPI.setDataMode(10,1);                   //Set SPI data mode to 1
  SPI.setBitOrder(10, MSBFIRST);           //Expect the most significant bit first, apply rule only to pin 10
  SPI.setClockDivider(10, 52);             //Set clock divider on pin 10 to 42 (84 MHz / 42 = 2 MHz SPI bus speed)
  //digitalWrite(ADC, HIGH);   // DAC SETUP

  // DAC SETUP
  // CS PIN USED IS 4!
  SPI.begin(4);      
  SPI.setDataMode(4,1);
  //Initialize the bus for a device on pin 10
  SPI.setBitOrder(4, MSBFIRST);           //Expect the most significant bit first, apply rule only to pin 10
}


int analog_to_digital()
{
  byteOne = SPI.transfer(10, 0x00, SPI_CONTINUE);              //Read the first byte from the MCP3201, keep CS active LOW for the next byte to transfer
  byteTwo = SPI.transfer(10, 0x00, SPI_LAST);                  //Read the second byte, take CS pin 10 HIGH to disable the MCP3201
  result = byteOne;                                           //Store the first byte into the result variable
  result = result << 8;                                       //Shift the first byte left 8 bits.
  result = result | byteTwo;                                  //Combine the two bytes into a 16 bit word (stored in a 32 bit variable) using OR function
  result = result >> 1;                                       //Shift the bits in the word to the right 1 places.  Bit 0 from MCP3201 is blank data.                                                      
  result = result & 0b00000000000000000000111111111111;       //Bit mask the first 20 bits using the AND function.  We only want to look at the last 12 bits
  //Serial.print( "entrada: ");
  //Serial.print( result );
  return result; 
}


void digital_to_analog(unsigned int val)
{
  Serial.print(" -- OUT:");
  Serial.println(val);
  byte b0 = (val & 0x000000ff) ;
  byte b1 = ((val >> 8) & 0x000000ff) | 0x00000010;
  //Serial.println(b1);
  //digitalWrite(4,LOW);   
  SPI.transfer(4, b1, SPI_CONTINUE); 
  SPI.transfer(4, b0); 
  //digitalWrite(4,HIGH);   
}

int sinal=0; 

void loop()
{
  sinal = analog_to_digital();
  //Serial.println(sinal);
  digital_to_analog(sinal);
  //delay(400);
}
