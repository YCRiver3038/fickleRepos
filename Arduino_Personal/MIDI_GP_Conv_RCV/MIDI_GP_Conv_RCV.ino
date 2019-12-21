#include <Wire.h>
#define BUFFER_SIZE_SERIAL 64

uint8_t RcvBuf[BUFFER_SIZE_SERIAL] = {0};
uint8_t AvailableBytes = 0;
uint8_t ctr1 = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(31250);
}

void loop() {
  // put your main code here, to run repeatedly:
  AvailableBytes = Serial.available();

  if(AvailableBytes > 0)
  {
    ctr1 = 0;
    while(ctr1 < AvailableBytes)
    {
      RcvBuf[ctr1] = Serial.read();
      ctr1++;
    }
  }  
  Wire.beginTransmission(57);
  Wire.write(RcvBuf, AvailableBytes);
  Wire.endTransmission();
}
