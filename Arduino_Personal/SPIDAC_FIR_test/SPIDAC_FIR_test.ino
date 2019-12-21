#include "SPI.h"
#include "stdlib.h"
#include "ringbuffer.h"

#define SRCLR 3
#define OE 4
//#define FILTERED

#define INT_MAX_USING 127
#define PI_USING 3.14159265358979323846

#define CUTOFF_FREQ 2000.0f
#define SMPL_FREQ 13265.0f

#define COEF_SIZE 32
#define SHIFT_OFFSET 1e-16

int8_t SendValue = 0;
int16_t SendValueShort = 0;
int8_t SendValue2 = 0;
int16_t  SendValueShort2 = 0;
float tableIndex = 0.0;
short tableIndexCasted = 0;

double fir_Coef = 0.0;
float fir_Coef_fl[COEF_SIZE] = {0};
int8_t fir_Coef_byte[COEF_SIZE] = {0};
double fir_hx = {0.0};
double fir_Window = {0.0};
float windowIndex = 0.0;
short sampleCount = 0;
int ctr1 = 0; 
int ctr2 = 0;
int ctr3 = 0;
byte sendBuf[2] = {0};
uint8_t sampledData[COEF_SIZE] = {0};
uint8_t sampledData2[COEF_SIZE] = {0};
int16_t adOffs = 127;

void setup() {
  // put your setup code here, to run once: 

  float shiftedCtr1 = 0.0; 
 
  pinMode(SRCLR, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(SS, OUTPUT);
  
  SPI.beginTransaction(SPISettings((long)2000000, MSBFIRST, SPI_MODE0));
  SPI.begin();  
  digitalWrite(OE, HIGH);
  digitalWrite(SRCLR, LOW);
  delayMicroseconds(10);
  digitalWrite(SRCLR, HIGH);
  SPI.transfer16(0xFFFF);
  digitalWrite(OE, LOW);
  
  for(ctr1 = 0; ctr1 < COEF_SIZE; ctr1++)
  {
    windowIndex = (float)ctr1 / (float)COEF_SIZE;
    shiftedCtr1 = (float)ctr1 - ((float)COEF_SIZE / 2.0) + SHIFT_OFFSET;
    
    fir_hx = sin(2.0*PI_USING*(CUTOFF_FREQ/SMPL_FREQ)*shiftedCtr1) / (PI_USING*shiftedCtr1);

    //Hanning窓
    fir_Window = 0.5 - (0.5 * cos(2 * PI * windowIndex));

    fir_Coef_fl[ctr1] = fir_hx *fir_Window;
    fir_Coef_byte[ctr1] = (int8_t)(fir_Coef_fl[ctr1] * (double)INT_MAX_USING);
  }
  ADCSRA = ADCSRA & 0b11111010;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(OE, HIGH);
  
  #ifdef FILTERED
    sampledData[COEF_SIZE - 1] = (int8_t)((analogRead(1) - adOffs) / 4);

    for(ctr2 = 0; ctr2 < COEF_SIZE; ctr2++)
    {
      SendValueShort += (int16_t)(sampledData[COEF_SIZE - 1 - ctr2] * fir_Coef_byte[ctr2]);
    }
  
    for(ctr2 = 0; ctr2 < (COEF_SIZE - 1); ctr2++)
    {
      sampledData[ctr2] = sampledData[ctr2 + 1];
    }
    SendValueShort *= 2;
  #else
    SendValueShort = (int16_t)((analogRead(1) - adOffs) * 32);
  #endif

  SPI.transfer16(~SendValueShort);
  digitalWrite(OE, LOW);
}

/*
     
    //矩形窓
    fir_Window = 1.0;
    
    //Vorbis窓
    fir_Window = sin( (PI_USING / 2.0) * sin(PI_USING*windowIndex) * sin(PI_USING*windowIndex) );
    
    //sin窓
    fir_Window = sin(PI * windowIndex);
    
    //Hanning窓
    fir_Window = 0.5 - (0.5 * cos(2 * PI * windowIndex));
    
    //Blackman窓
    fir_Window = 0.42 - (0.5 * cos(2 * PI * windowIndex)) + (0.08 * cos(4 * PI * windowIndex));
    
    //Nuttall窓
    fir_Window = 0.355768 - (0.487396 * cos(2 * PI * windowIndex)) + (0.144232 * cos(4 * PI * windowIndex)) - (0.012604 * cos(6 * PI * windowIndex));
    
    //Blackman‐Harris窓
    fir_Window = 0.35875 - 0.48829 * cos(2 * PI * windowIndex) + 0.14128 * cos(4 * PI * windowIndex) - 0.01168 * cos(6 * PI * windowIndex);

*/
