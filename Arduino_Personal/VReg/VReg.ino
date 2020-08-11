#include "FakePID.h"

#define VREG_AIM_VOLTAGE 13.85f
#define VREG_LIMIT_VOLTAGE 13.9
#define AD2VO_COEF 0.0244f

#define MC_PWM_TO_PFM_FLIPCOUNT 2048
#define MC_PFM_TO_PWM_FLIPCOUNT 2048
#define MODE_PFM 1
#define MODE_PWM 0

#define AD_Vo 2
#define vDuty 9

#define FLIPCTR_MAX (int16_t)32700

void setup() 
{
	float readVo = 0.0;
	float flipTiming = 0.0;
	float duty = 0.0;

	int16_t flipTiming_u16 = 0;
	int16_t flipctr = 0;
	uint16_t mcCount = 0;
	uint32_t ctrlStatus = 0;
	uint8_t modeStatus = 0;

	FPID_GainSet gainUsingPFM = {2.0f, 0.00002f, 0.02f, 0};
	FPIDController ctrlPFM;
	FPIDConfig cnfUsingPFM(gainUsingPFM);

	FPID_GainSet gainUsingPWM = {0.01f, 0.0001f, 0.01f, 0};
	FPIDController ctrlPWM;
	FPIDConfig cnfUsingPWM(gainUsingPWM);

	pinMode(vDuty, OUTPUT);
	digitalWrite(vDuty, LOW);
	flipctr = 0;
	ADCSRA = ADCSRA & 0b11111010;

	while (1) 
	{
		readVo = (float)(analogRead(AD_Vo)) * AD2VO_COEF;
		if(modeStatus == MODE_PFM)
		{
			ctrlPFM.control(cnfUsingPFM, VREG_AIM_VOLTAGE, readVo, &flipTiming);
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
				analogWrite(vDuty, 255);
				flipctr = 0;
			}
			else
			{
				analogWrite(vDuty, 0);
				flipctr++;
			}
			if(flipTiming_u16 > MC_PFM_TO_PWM_FLIPCOUNT)
			{
				modeStatus = MODE_PWM;
			}
		}
		else if(modeStatus == MODE_PWM)
		{
			ctrlPWM.control(cnfUsingPWM, VREG_AIM_VOLTAGE, readVo, &duty);
			if (duty >= 255.0f)
			{
			duty = 255.0f;
			}
			if (duty <= 0.0f)
			{
			duty = 0.0f;
			}
			analogWrite(vDuty, (uint8_t)duty);
			if((duty==255)&&(readVo<VREG_AIM_VOLTAGE))
			{
				mcCount++;
				if(mcCount > MC_PWM_TO_PFM_FLIPCOUNT)
				{
					modeStatus = MODE_PFM;
					mcCount = 0;
				}
			}
		}
		else
		{
			analogWrite(vDuty, 0);
		}
	}
}

void loop() {}
