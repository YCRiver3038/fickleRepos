#include <SPI.h>
#include "math.h"

#define P_PWM_OUT 9
#define P_INC_10P 2
#define P_INC_1P 3
#define P_DEC 4
#define P_OE 5
#define P_MODE 6

#define CHARS 36
#define DIGITS 4

int8_t pSta_di10 = 0;
int8_t pSta_di1 = 0;
int8_t pSta_dec = 0;
int8_t pSta_mode = 0;
int8_t pSta_incAnyHigh = 0;


uint8_t sDuty = 0;
int8_t sDuty_coef = 0;
bool isFlMode = false;


//int8_t onLED[CHARS][SEGMENTS] = {
///* G, F, E, D, C, B, A */
//  {0, 1, 1, 1, 1, 1, 1},/*0*/
//  {0, 0, 0, 0, 1, 1, 0},/*1*/
//  {1, 0, 1, 1, 0, 1, 1},/*2*/
//  {1, 0, 0, 1, 1, 1, 1},/*3*/
//  {1, 1, 0, 0, 1, 1, 0},/*4*/
//  {1, 1, 0, 1, 1, 0, 1},/*5*/
//  {1, 1, 1, 1, 1, 0, 1},/*6*/
//  {0, 1, 0, 0, 1, 1, 1},/*7*/
//  {1, 1, 1, 1, 1, 1, 1},/*8*/
//  {1, 1, 0, 1, 1, 1, 1},/*9*/
//  {1, 1, 1, 0, 1, 1, 1},/*A*/
//  {1, 1, 1, 1, 1, 0, 0},/*b*/
//  {0, 1, 1, 1, 0, 0, 1},/*C*/
//  {1, 0, 1, 1, 1, 1, 0},/*d*/
//  {1, 1, 1, 1, 0, 0, 1},/*E*/
//  {1, 1, 1, 0, 0, 0, 1} /*F*/
//};

uint8_t segments_i8con[CHARS] = {0x3F/*0*/, 0x06/*1*/, 0x5B/*2*/, 0x4F/*3*/,
                                 0x66/*4*/, 0x6D/*5*/, 0x7D/*6*/, 0x27/*7*/,
                                 0x7F/*8*/, 0x6F/*9*/, 0x77/*A*/, 0x7C/*b*/,
                                 0x39/*C*/, 0x5E/*d*/, 0x79/*E*/, 0x71/*F*/,

                                 0x3D/*0x10:G*/, 0x76/*0x11:H*/, 0x04/*0x12:I*/, 0x1E/*0x13:J*/,
                                 0x38/*0x14:L*/, 0x54/*0x15:n*/, 0x5C/*0x16:o*/, 0x73/*0x17:P*/,
                                 0x67/*0x18:q*/, 0x50/*0x19:r*/, 0x6D/*0x1A:S,5*/, 0x78/*0x1B:t*/,
                                 0x1C/*0x1C:u*/, 0x6E/*0x1D:y*/, 0x08/*0x1F:_*/, 0x40/*0x20:-*/,
                                 0x01/*0x21:^*/, 0x80/*0x22:.*/, 0x10/*0x23:,*/, 0x00/*0x24:(blank)*/
                                };

void showDuty()
{
  uint8_t sendChars[DIGITS] = {0};

  sendChars[0] = (segments_i8con[0x0d] | 0x80);
  sendChars[1] = segments_i8con[(int8_t)(sDuty / 100)];
  sendChars[2] = segments_i8con[(int8_t)((sDuty % 100) / 10)];
  sendChars[3] = segments_i8con[(int8_t)(sDuty % 10)];

  digitalWrite(P_OE, HIGH);
  SPI.transfer(sendChars, DIGITS);
  digitalWrite(P_OE, LOW);
}

void showDuty_Rat()
{
  uint8_t sendChars[DIGITS] = {0};
  float dutRat = 0;
  float rat_d1 = 0.0;
  float rat_d2 = 0.0;
  float rat_d3 = 0.0;

  if (sDuty == 255)
  {
    sendChars[0] = segments_i8con[0x17];
    sendChars[1] = segments_i8con[1];
    sendChars[2] = segments_i8con[0];
    sendChars[3] = (segments_i8con[0] | 0x80);
  }
  else
  {
    dutRat = ((float)sDuty / (float)255) * (float)100.0;
    if (dutRat < 1.0) /*0.000～0.999*/
    {
      rat_d1 = dutRat * 10.0;
      rat_d2 = fmod((dutRat * 100.0), 10.0);
      rat_d3 = fmod((dutRat * 1000.0), 10.0);

      sendChars[0] = (segments_i8con[0x17] | 0x80);
      sendChars[1] = segments_i8con[(int8_t)rat_d1];
      sendChars[2] = segments_i8con[(int8_t)rat_d2];
      sendChars[3] = segments_i8con[(int8_t)rat_d3];
    }
    else if (dutRat < 10.0) /*1.00～9.99*/
    {
      rat_d1 = dutRat;
      rat_d2 = fmod((dutRat * 10.0), 10.0);
      rat_d3 = fmod((dutRat * 100.0), 10.0);

      sendChars[0] = segments_i8con[0x17];
      sendChars[1] = (segments_i8con[(int8_t)rat_d1] | 0x80);
      sendChars[2] = segments_i8con[(int8_t)rat_d2];
      sendChars[3] = segments_i8con[(int8_t)rat_d3];
    }
    else/*10.0～99.9*/
    {
      rat_d1 = dutRat / 10.0;
      rat_d2 = fmod(dutRat, 10.0);
      rat_d3 = fmod((dutRat * 10.0), 10.0);

      sendChars[0] = segments_i8con[0x17];
      sendChars[1] = segments_i8con[(int8_t)rat_d1];
      sendChars[2] = (segments_i8con[(int8_t)rat_d2] | 0x80);
      sendChars[3] = segments_i8con[(int8_t)rat_d3];
    }
  }

  digitalWrite(P_OE, HIGH);
  SPI.transfer(sendChars, DIGITS);
  digitalWrite(P_OE, LOW);
}

void setup() {
  // put your setup code here, to run once:
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  /*
    Carrier Freq(Value below:1/2):
    0x01:15686.275Hz
    0x02:1960.58Hz
    0x03:245.10Hz
    0x04:61.275Hz
    0x05:15.32Hz
  */
  pinMode(P_INC_10P, INPUT);
  pinMode(P_INC_1P, INPUT);
  pinMode(P_DEC, INPUT);
  pinMode(P_PWM_OUT, OUTPUT);
  pinMode(P_OE, OUTPUT);
  pinMode(P_MODE, INPUT);
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  analogWrite(P_PWM_OUT, 0);
  isFlMode = true;
  SPI.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  pSta_di10 = (int8_t)digitalRead(P_INC_10P);
  pSta_di1 = (int8_t)digitalRead(P_INC_1P);
  pSta_dec = (int8_t)digitalRead(P_DEC);
  pSta_mode = (int8_t)digitalRead(P_MODE);

  if (pSta_di10 != 0)
  {
    if (pSta_dec == 0)
    {
      if (sDuty <= 245)
      {
        sDuty += 10;
      }
      else
      {
        sDuty = 255;
      }
    }
    else
    {
      if (sDuty > 9)
      {
        sDuty -= 10;
      }
      else
      {
        sDuty = 0;
      }
    }
  }

  if (pSta_di1 != 0)
  {
    if (pSta_dec == 0)
    {
      if (sDuty <= 254)
      {
        sDuty++;
      }
      else
      {
        sDuty = 255;
      }
    }
    else
    {
      if (sDuty >= 1)
      {
        sDuty--;
      }
      else
      {
        sDuty = 0;
      }
    }
  }

  if (pSta_mode != 0)
  {
    isFlMode = !isFlMode;
    while (digitalRead(P_MODE) == HIGH) {}
  }

  analogWrite(P_PWM_OUT, sDuty);

  if (!isFlMode)
  {
    showDuty();
  }
  else
  {
    showDuty_Rat();
  }

  pSta_incAnyHigh = 1;
  while (pSta_incAnyHigh > 0)
  {
    pSta_incAnyHigh = (int8_t)digitalRead(P_INC_10P) + (int8_t)digitalRead(P_INC_1P);

  }
  delay(20);
}
