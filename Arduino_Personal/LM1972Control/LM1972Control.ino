#include "math.h"
#include "L1972ctrlDefs.h"

//#define USING_SERIAL

#define SS 10
#define MUTE_UNMUTE 6
#define ENC_UP 5
#define ENC_DOWN 8
#define CS_7SEG 3
#define DIGITS 4
#define CHARS 37

uint8_t serialData = 0;
uint8_t combuf[10] = {0};
uint8_t currentAtt = 0;
uint8_t sendChars[DIGITS] = {0};
float attLv = 0.0;
float rat_d1 = 0.0;
float rat_d2 = 0.0;
float rat_d3 = 0.0;

L1972Dev Target1(SS);

uint8_t segments_i8con[CHARS] = {0x3F/*0*/, 0x06/*1*/, 0x5B/*2*/, 0x4F/*3*/,
								 0x66/*4*/, 0x6D/*5*/, 0x7D/*6*/, 0x27/*7*/,
								 0x7F/*8*/, 0x6F/*9*/, 0x77/*A*/, 0x7C/*b*/,
								 0x39/*C*/, 0x5E/*d*/, 0x79/*E*/, 0x71/*F*/,

								 0x3D/*0x10:G*/, 0x76/*0x11:H*/, 0x04/*0x12:I*/, 0x1E/*0x13:J*/,
								 0x38/*0x14:L*/, 0x54/*0x15:n*/, 0x5C/*0x16:o*/, 0x73/*0x17:P*/,
								 0x67/*0x18:q*/, 0x50/*0x19:r*/, 0x6D/*0x1A:S,5*/, 0x78/*0x1B:t*/,
								 0x1C/*0x1C:u*/, 0x6E/*0x1D:y*/, 0x08/*0x1E:_*/, 0x40/*0x1F:-*/,
								 0x01/*0x20:^*/, 0x80/*0x21:.*/, 0x10/*0x22:,*/, 0x00/*0x23:(blank)*/
								};

void showAtt_7SEG()
{
	if (Target1.getAttStep() >= ATT_STEP_MAX)
	{
		sendChars[0] = segments_i8con[0x1F];
		sendChars[1] = segments_i8con[0x1F];
		sendChars[2] = segments_i8con[0x1F];
		sendChars[3] = segments_i8con[0x1F];
	}
	else
	{
		rat_d1 = (-1.0*attLv) / 10.0;
		rat_d2 = fmod((-1.0*attLv), 10.0);
		rat_d3 = fmod((attLv * -10.0), 10.0);
		if((int8_t)rat_d1 != 0)
		{
		sendChars[0] = segments_i8con[0x1F];
		sendChars[1] = segments_i8con[(int8_t)rat_d1];
		}
		else
		{
		sendChars[0] = segments_i8con[0x23];
		sendChars[1] = segments_i8con[0x1F];
		}
		sendChars[2] = (segments_i8con[(int8_t)rat_d2] | 0x80);
		sendChars[3] = segments_i8con[(int8_t)rat_d3];
	}
	
	digitalWrite(CS_7SEG, LOW);
	SPI.transfer(sendChars, DIGITS);
	digitalWrite(CS_7SEG, HIGH);
}

void showAtten(uint8_t attArg)
{
	if(attArg < 96)
	{
		attLv = -0.5*(float)attArg;
	}
	else
	{
		attLv = -48.0-(float)(attArg-96);
	}

	#ifdef USING_SERIAL
	if(attArg < ATT_STEP_MAX)
	{
		Serial.print(attArg);
		Serial.print(" : ");
		Serial.print(attArg);
		Serial.print("dB\r\n");
	}
	else
	{
		Serial.print("MUTE\r\n");
	}
	#endif

	showAtt_7SEG();
}

void setup() {
// put your setup code here, to run once:
	#ifdef USING_SERIAL
	Serial.begin(115200);
	#endif

	pinMode(ENC_UP, INPUT);
	pinMode(ENC_DOWN, INPUT);
	pinMode(MUTE_UNMUTE, INPUT);

	Target1.mute();
	Target1.applyAtt();
	showAtten(Target1.getAttStep());
}

void loop()
{
// put your main code here, to run repeatedly:
	
	#ifdef USING_SERIAL
	if(Serial.available())
	{
		serialData = Serial.read();
		if((serialData == 'd')||(serialData == 'D'))
		{
			Target1.attenuate();
		}
		if((serialData == 'u')||(serialData == 'U'))
		{
			Target1.amplify();    
		}
		if((serialData == 'm')||(serialData == 'M'))
		{
			Target1.mute();
		}
		if((serialData == 'r')||(serialData == 'R'))
		{
			Target1.recall();
		}
		if((serialData == 'f')||(serialData == 'F'))
		{
			Target1.full();
		}
		Target1.applyAtt();
		showAtten(Target1.getAttStep());
	}
	#endif

	if(digitalRead(ENC_UP) == HIGH)
	{
		Target1.amplify();
		Target1.applyAtt();
		showAtten(Target1.getAttStep());
		while(digitalRead(ENC_UP) == HIGH){}
	}
	if(digitalRead(ENC_DOWN) == HIGH)
	{
		Target1.attenuate();
		Target1.applyAtt();
		showAtten(Target1.getAttStep());
		while(digitalRead(ENC_DOWN) == HIGH){}
	}
	if(digitalRead(MUTE_UNMUTE)==HIGH)
	{
		if(!Target1.getMuteStatus())
		{
			Target1.mute();
		}
		else
		{
			Target1.recall();
		}
		Target1.applyAtt();
		showAtten(Target1.getAttStep());
		while(digitalRead(MUTE_UNMUTE) == HIGH){}   
	}
}
