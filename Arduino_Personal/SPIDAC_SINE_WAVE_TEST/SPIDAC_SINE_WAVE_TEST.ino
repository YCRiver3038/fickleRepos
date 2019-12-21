#include "SPI.h"
#include "math.h"
#include "stdlib.h"

//#define WF_SINE
#define SRCLR 3
#define SS 10

#define PI_USING 3.14159265358979323846f
#define AMPLITUDE_MAX 16384

#define SIN_TABLE_SIZE 512
#define VOL_AD_IN 1

uint16_t SendValueShort = 0;
uint16_t* sineTable = NULL;
uint16_t ctrM = 0;
uint16_t amplitude = 0;

void setup() {
  // put your setup code here, to run once: 
  uint16_t ctr1 = 0;
  
  //Serial.begin(115200);
  pinMode(SRCLR, OUTPUT);
  pinMode(SS, OUTPUT);

  SPI.beginTransaction(SPISettings((long)6000000, LSBFIRST, SPI_MODE0));
  SPI.begin();  
  digitalWrite(SS, HIGH);
  digitalWrite(SRCLR, LOW);
  delayMicroseconds(10);
  digitalWrite(SRCLR, HIGH);
  SPI.transfer16(0x0);
  digitalWrite(SS, LOW);
  //Serial.print("\r\nAmplitude\r\n");

  sineTable = (uint16_t*)calloc(SIN_TABLE_SIZE, sizeof(uint16_t));
  if(sineTable == NULL)
  {
    return;
  }

  ctr1 = 0;
  while(ctr1 < SIN_TABLE_SIZE)
  {
    #ifdef WF_SINE
    sineTable[ctr1] = (uint16_t)((float)AMPLITUDE_MAX * (float)(sin(2.0f*PI_USING*((float)ctr1/(float)SIN_TABLE_SIZE))+1.0f));
    #else
    sineTable[ctr1] = (uint16_t)((uint16_t)ctr1*(uint16_t)(AMPLITUDE_MAX / SIN_TABLE_SIZE));
    #endif
    ctr1++;
  }
  ctrM = 0;
  ADCSRA = ADCSRA & 0b11111010;
}

void loop() {
  // put your main code here, to run repeatedly:
  amplitude = (uint16_t)(analogRead(VOL_AD_IN)<<6);
  //Serial.print(amplitude, DEC);
  //Serial.print("     \r");
  
  #ifdef WF_SINE
    SendValueShort = (uint16_t)((float)amplitude * (float)(sin(2.0f*PI_USING*((float)ctrM/(float)SIN_TABLE_SIZE))+1.0f));
  #else
    SendValueShort = (uint16_t)((uint16_t)ctrM*(uint16_t)(amplitude / SIN_TABLE_SIZE));
  #endif

  digitalWrite(SS, HIGH);
  SPI.transfer16(SendValueShort);
  digitalWrite(SS, LOW);
  ctrM++;
  ctrM %= SIN_TABLE_SIZE;
}
