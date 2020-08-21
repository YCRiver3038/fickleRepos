#include "FakePID.h"

#define VREG_AIM_VOLTAGE 13.85f
#define AD2VO_COEF 0.0235f

#define AD_Vo 2
#define vDuty 9

#define AVG_bits 5
#define AVG_SIZE uint8_t(1<<AVG_bits)

void setup() {
	float readVo = 0.0;
	float duty = 0.0;
	uint8_t AVGCtr = 0;
	uint16_t VAvg = 0;
	uint8_t tempctr = 0;
	uint16_t VRaw[AVG_SIZE] = {0};
	uint8_t printctr = 0;

	FPID_GainSet gainUsing = {0.8f, 0.00001f, 1.0f, 0};
	FPIDController ctrl;
	FPIDConfig cnfUsing(gainUsing);
	Serial.begin(115200);

	TCCR1B = (TCCR1B & 0b11111000) | 0x01;
	ADCSRA = ADCSRA & 0b11111010;

	pinMode(vDuty, OUTPUT);

	while (1) {
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
		if(printctr == 0)
		{
			Serial.println(readVo);
		}
		printctr++;
		printctr%250;
		
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
