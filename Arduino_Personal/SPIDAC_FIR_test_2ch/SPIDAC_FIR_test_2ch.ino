#include "SPI.h"
#include "stdlib.h"

#define SRCLK 2
#define SRCLR 3
#define OE 4
#define SER 7

//#define FILTERED

#define PWMOUT 9
#define PWMOUT2 6

#define INT_MAX_USING 127
#define PI_USING 3.14159265358979323846

#define CUTOFF_FREQ 7000.0f
#define SMPL_FREQ 14880.0f

#define COEF_SIZE 8
#define SHIFT_OFFSET 0.0000001f

uint8_t SendValue = 0;
int16_t SendValueShort = 0;
uint8_t SendValue2 = 0;
int16_t  SendValueShort2 = 0;
float tableIndex = 0.0;
short tableIndexCasted = 0;

double fir_Coef = 0.0;
int8_t fir_Coef_byte[COEF_SIZE] = {0};
double fir_hx = {0.0};
double fir_Window = {0.0};
float windowIndex = 0.0;
short sampleCount = 0;
int ctr1 = 0; 
int ctr2 = 0;
byte sendBuf[2] = {0};
int returnVal = 0;
uint8_t sampledData[COEF_SIZE] = {0};
uint8_t sampledData2[COEF_SIZE] = {0};


void setup() {
  // put your setup code here, to run once: 
  float shiftedCtr1 = 0.0; 
  
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(SER, OUTPUT);
  pinMode(SS, OUTPUT);
  
  SPI.beginTransaction(SPISettings((long)2000000, MSBFIRST, SPI_MODE0));
  SPI.begin(); 
  
  digitalWrite(OE, HIGH);
  digitalWrite(SRCLR, LOW);
  delayMicroseconds(10);
  digitalWrite(SRCLR, HIGH);
  SPI.transfer16(0xFFFF);
  digitalWrite(OE, LOW);
  pinMode(SS,OUTPUT);
   
  for(ctr1 = 0; ctr1 < COEF_SIZE; ctr1++)
  {
    windowIndex = (float)ctr1 / (float)COEF_SIZE;
    shiftedCtr1 = (float)ctr1 - ((float)COEF_SIZE / 2.0) + SHIFT_OFFSET;
    fir_hx = sin(2.0*PI_USING*(CUTOFF_FREQ/SMPL_FREQ)*shiftedCtr1) / (PI_USING*shiftedCtr1);
    
    //矩形窓
    //fir_Window = 1.0;
    
    //Vorbis窓
    fir_Window = sin( (PI_USING / 2.0) * sin(PI_USING*windowIndex) * sin(PI_USING*windowIndex) );
    
    //Hanning窓
    //fir_Window = 0.5 - (0.5 * cos(2 * PI * windowIndex));
    
    //sin窓
    //fir_Window = sin(PI * windowIndex);

    //Blackman窓
    //fir_Window = 0.42 - (0.5 * cos(2 * PI * windowIndex)) + (0.08 * cos(4 * PI * windowIndex));

    //Nuttall窓
    //fir_Window = 0.355768 - (0.487396 * cos(2 * PI * windowIndex)) + (0.144232 * cos(4 * PI * windowIndex)) - (0.012604 * cos(6 * PI * windowIndex));

    //Blackman‐Harris窓
    //fir_Window = 0.35875 - 0.48829 * cos(2 * PI * windowIndex) + 0.14128 * cos(4 * PI * windowIndex) - 0.01168 * cos(6 * PI * windowIndex);

    fir_Coef = fir_hx *fir_Window;
    fir_Coef_byte[ctr1] = (int8_t)(fir_Coef * (double)INT_MAX_USING);
  }

  ADCSRA = ADCSRA & 0b11111001;
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifdef FILTERED
    sampledData[COEF_SIZE - 1] = analogRead(1) >> 2;
    sampledData2[COEF_SIZE - 1] = analogRead(0) >> 2;
  #else
    SendValue = (uint8_t)(analogRead(1) >> 2);
    SendValue2 = (uint8_t)(analogRead(0) >> 2);
  #endif
  
  #ifdef FILTERED
    for(ctr2 = 0; ctr2 < COEF_SIZE; ctr2++)
    {
      SendValueShort += (sampledData[COEF_SIZE - 1 - ctr2] * fir_Coef_byte[ctr2]);
      SendValueShort2 += (sampledData2[COEF_SIZE - 1 - ctr2] * fir_Coef_byte[ctr2]);
    }
  
    for(ctr2 = 0; ctr2 < (COEF_SIZE - 1); ctr2++)
    {
      sampledData[ctr2] = sampledData[ctr2 + 1];
      sampledData2[ctr2] = sampledData2[ctr2 + 1];
    }
  
    SendValue = (uint8_t)(SendValueShort >> 8);
    SendValueShort = 0;
    SendValue2 = (uint8_t)(SendValueShort2 >> 8);
    SendValueShort2 = 0;
  #endif
    
    digitalWrite(OE, HIGH);
    returnVal = SPI.transfer16(SendValue);
    digitalWrite(OE, LOW);

}
