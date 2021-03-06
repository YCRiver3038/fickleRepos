#include <Wire.h>
#include "SPI.h"
#define BUFFER_SIZE_SERIAL 64
#define SRCLK 2
#define SRCLR 3
#define OE 4
#define SER 7

uint8_t D_Rcv_Buf[BUFFER_SIZE_SERIAL] = {0};
uint8_t KeyData[BUFFER_SIZE_SERIAL] = {0};
uint8_t rcvBytes = 0;
uint8_t ctr1 = 0;
uint8_t ctr2 = 0;
uint16_t sendData = 0;
uint8_t sendBytes[2] = {0x00, 0x00};
uint8_t rcvNoteNum = 0;
uint8_t rcvChannel = 0;
uint8_t rcvVelocity = 0;
uint8_t up4b = 0;
uint8_t rcvScale = 0;
bool rcvSysEX = false;
bool rcvNoteOn = false;
bool rcvNoteOff = false;
char scaleName[12][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

void receiveBytes(volatile int rcvSize)
{
  rcvBytes = Wire.available();
  while(ctr1 < rcvBytes)
  {
    D_Rcv_Buf[ctr1] = Wire.read();
    ctr1++;
  }
  ctr1 = 0;

  while(ctr1 < rcvBytes)
  {
    if(!rcvSysEX)
    {
      up4b = (D_Rcv_Buf[ctr1] & 0xF0);
      if( up4b == 0x90 )
      {
        rcvNoteOn = true;
        rcvNoteOff = false;
        Serial.print("\n\nCH: ");
        rcvChannel = (D_Rcv_Buf[ctr1] & 0x0F);
        Serial.print(rcvChannel + 1);
      }
      else if(up4b == 0x80)
      {
        rcvNoteOn = false;
        rcvNoteOff = true;
        Serial.print("\n\nCH: ");
        rcvChannel = (D_Rcv_Buf[ctr1] & 0x0F);
        Serial.print(rcvChannel + 1);
      }
      else if((D_Rcv_Buf[ctr1] < 0x80) || rcvNoteOn || rcvNoteOff)
      {
        if(ctr2 == 0)
        {
          rcvNoteNum = D_Rcv_Buf[ctr1];
          rcvScale = rcvNoteNum % 12;
          rcvScale++;
          Serial.print("\n");
          Serial.print("Note:");
          Serial.print(scaleName[rcvScale]);
          Serial.print( ((rcvNoteNum / 12) - 1) , DEC);
          
        }
        else
        {
          rcvVelocity = D_Rcv_Buf[ctr1];
          Serial.print("\n");
          Serial.print("Velocity:");
          Serial.print(rcvVelocity, HEX);
        }
        ctr2++;
        ctr2 %= 2;
        if(rcvNoteOn && !isZeroVel)
        {
          sendData = (uint16_t)(sendData | (0x0001 << rcvScale));
        }
        if(rcvNoteOff || isZeroVel)
        {
          sendData &= ~((uint16_t)(0x0001 << rcvScale));
        }
        digitalWrite(OE, HIGH);
        SPI.transfer16(~sendData);
        digitalWrite(OE, LOW);
      }
      else
      {
        rcvNoteOn = false;
        rcvNoteOff = false;
        sendData = 0;
      }
    }    
    if(D_Rcv_Buf[ctr1] == 0xF0)
    {
      rcvSysEX = true;
    }    
    if(D_Rcv_Buf[ctr1] == 0xF7)
    {
      rcvSysEX = false;
    }
    ctr1++;
  }
  ctr1 = 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(SER, OUTPUT);
  
  Wire.begin(57);
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
  Serial.begin(115200);
  digitalWrite(OE, HIGH);
  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);
  Wire.onReceive(receiveBytes);
}

void loop() {
  // put your main code here, to run repeatedly:
}
