#include "FakePID.h"

#define VREG_AIM_VOLTAGE 13.85f
#define AD2VO_COEF 0.0241f

#define AD_Vo 2
#define vDuty 9

void setup() {
  float readVo = 0.0;
  float duty = 0.0;

  FPID_GainSet gainUsing = {0.01f, 0.0001f, 0.01f, 0};
  FPIDController ctrl;
  FPIDConfig cnfUsing(gainUsing);
  
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  ADCSRA = ADCSRA & 0b11111010;

  pinMode(vDuty, OUTPUT);

  while (1) {
    readVo = (float)(analogRead(AD_Vo)) * AD2VO_COEF;
    ctrl.control(cnfUsing, VREG_AIM_VOLTAGE, readVo, &duty);
    if (duty >= 255.0f)
    {
      duty = 255.0f;
    }
    if (duty <= 0.0f)
    {
      duty = 0.0f;
    }
    analogWrite(vDuty, (uint8_t)duty);
  }
}

void loop() {}
