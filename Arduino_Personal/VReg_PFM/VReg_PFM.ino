#include "FakePID.h"

#define VREG_AIM_VOLTAGE 13.85f
#define VREG_LIMIT_VOLTAGE 13.9
#define AD2VO_COEF 0.0235f
#define AD2VO_OFFS (51.0174f)

#define AD_Vo 2
#define vDuty 9

#define FLIPCTR_MAX (int16_t)32700
#define AVG_bits 5
#define AVG_SIZE uint8_t(1<<AVG_bits)

void setup() 
{
	float readVo = 0.0;
	float flipTiming = 0.0;
	int16_t flipTiming_u16 = 0;
	int16_t flipctr = 0;
	uint32_t ctrlStatus = 0;
	uint8_t printctr = 0;
	uint8_t AVGCtr = 0;
	uint16_t VAvg = 0;
	uint8_t tempctr = 0;
	uint16_t VRaw[AVG_SIZE] = {0};

	FPID_GainSet gainUsing = {1.2f, 0.00003f, 0.01f, 0};
	FPIDController ctrl;
	FPIDConfig cnfUsing(gainUsing);

	pinMode(vDuty, OUTPUT);

	digitalWrite(vDuty, LOW);
	flipctr = 0;
	ADCSRA = ADCSRA & 0b11111010;
	Serial.begin(115200);

	AVGCtr = 0;
	while (1) 
	{
		VRaw[AVGCtr] = analogRead(AD_Vo);
		while(tempctr < AVG_SIZE)
		{
			VAvg += VRaw[tempctr];
			tempctr++;
		}
		tempctr = 0;
		VAvg >>= AVG_bits;
		AVGCtr = (AVGCtr+1)&(AVG_SIZE-1);
		//Serial.println(AVGCtr);

		readVo = (float)VAvg * AD2VO_COEF;
		/*
		if(printctr == 0)
		{
			Serial.println(readVo);
		}
		printctr++;
		printctr%250;
		*/
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
