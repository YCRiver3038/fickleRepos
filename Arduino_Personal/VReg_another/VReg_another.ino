#include "FakePID.h"

#define VREG_AIM_VOLTAGE 13.85f
#define VREG_LIMIT_VOLTAGE 13.9
#define AD2VO_COEF 0.0244f

#define AD_Vo 2
#define vDuty 9

#define FLIPCTR_MAX (int16_t)32700

void setup() 
{
	float readVo = 0.0;
	float flipTiming = 0.0;
	int16_t flipTiming_u16 = 0;
	int16_t flipctr = 0;
	uint32_t ctrlStatus = 0;

	FPID_GainSet gainUsing = {15.0f, 0.0005f, 3.0f, 0};
	FPIDController ctrl;
	FPIDConfig cnfUsing(gainUsing);
	pinMode(vDuty, OUTPUT);
	digitalWrite(vDuty, LOW);
	flipctr = 0;
	ADCSRA = ADCSRA & 0b11111010;

	while (1) 
	{
		readVo = (float)(analogRead(AD_Vo)) * AD2VO_COEF;
		ctrl.control(cnfUsing, VREG_AIM_VOLTAGE, readVo, &flipTiming);
		if(flipTiming > ((float)FLIPCTR_MAX-1.0f))
		{
			flipTiming = (float)FLIPCTR_MAX;
		}
		flipTiming_u16 = FLIPCTR_MAX - (int16_t)flipTiming;

		if(flipTiming_u16 < 1)
		{
			flipTiming_u16 = 1;
		}

		if((flipTiming_u16-flipctr) <= 0)
		{
			digitalWrite(vDuty, HIGH);
			flipctr = 0;
		}
		else
		{
			digitalWrite(vDuty, LOW);
			flipctr++;
		}
	}
}

void loop() {}
