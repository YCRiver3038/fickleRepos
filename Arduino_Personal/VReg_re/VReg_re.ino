#include "FakePID.h"

#define VREG_AIM_VOLTAGE 12.2f
#define AD2VO_COEF 0.0244f

#define AD_Vo 3
#define vDuty 9

void setup() {
  float readVo = 0.0;
  float duty = 0.0;

  FPID_GainSet gainUsing = {1.0f, 0.0001f, 1.0f, 100000};
  FPIDController ctrl;
  FPIDConfig cnfUsing(gainUsing);
  
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
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
