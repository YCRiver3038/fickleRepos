#include <Wire.h>
#include "SPI.h"
#define BUFFER_SIZE_SERIAL 64
#define SRCLK 2
#define SRCLR 3
#define OE 4
#define SER 7

uint8_t D_Rcv_Buf = 0;
uint8_t rcvBytes = 0;
uint8_t ctr1 = 0;
uint8_t ctr2 = 0;
uint16_t sendData = 0;
uint8_t rcvNoteNum = 0;
uint8_t rcvVelocity = 0;
uint8_t up4b = 0;
uint8_t rcvScale = 0;
bool rcvEX = false;
bool rcvSysRTMsg = false;
bool rcvNoteOn = false;
bool rcvNoteOff = false;
bool isZeroVel = false;

void receiveBytes(volatile int rcvSize)
{
  rcvBytes = Wire.available();
  ctr1 = 0;
  while(ctr1 < rcvBytes)
  {
    D_Rcv_Buf = Wire.read();
    
    if(D_Rcv_Buf == 0xF0)
    {
      rcvEX = true;
    }   
     
    if(D_Rcv_Buf == 0xF7)
    {
      rcvEX = false;
    }
    
    if(D_Rcv_Buf > 0xF7)
    {
      rcvSysRTMsg = true;
    }
    else
    {
      rcvSysRTMsg = false;
    }
    
    if(!rcvEX && !rcvSysRTMsg)
    {
      up4b = (D_Rcv_Buf >> 4);
      if( up4b == 0x09 )
      {
        rcvNoteOn = true;
        rcvNoteOff = false;
      }
      else if(up4b == 0x08)
      {
        rcvNoteOn = false;
        rcvNoteOff = true;
      }
      else if((D_Rcv_Buf < 0x80) && (rcvNoteOn || rcvNoteOff))
      {
        if(ctr2 == 0)
        {
          rcvNoteNum = D_Rcv_Buf;
          rcvScale = rcvNoteNum % 12;
        }
        else
        {
          rcvVelocity = D_Rcv_Buf;
          if(rcvVelocity == 0x00)
          {
            isZeroVel = true;
          }
          else
          {
            isZeroVel = false;
          }
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
        sendData = 0x00;
      }
    }    
    ctr1++;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SRCLR, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(SS, OUTPUT);
  SPI.beginTransaction(SPISettings((long)2000000, MSBFIRST, SPI_MODE0));
  SPI.begin(); 
  
  Wire.begin(57);
  digitalWrite(OE, HIGH);
  digitalWrite(SRCLR, LOW);
  delayMicroseconds(10);
  digitalWrite(SRCLR, HIGH);
  SPI.transfer16(0xFFFF);
  digitalWrite(OE, LOW);
  Wire.onReceive(receiveBytes);
}

void loop() {
  // put your main code here, to run repeatedly:
}
