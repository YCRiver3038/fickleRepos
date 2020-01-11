#include "SPI.h"

#define SS 10
#define MUTE_UNMUTE 6
#define ENC_UP 5
#define ENC_DOWN 8
#define ATT_STEP_MAX (uint8_t)127

uint8_t atten = 0;
uint8_t currentAddr = 0;
uint8_t serialData = 0;
uint8_t combuf[10] = {0};
uint8_t prevAtt = 0;
float attLv = 0.0;
bool isMute = false;

enum
{
	CH1, CH2, CH3
}Address;

void attenuate()
{
	atten++;
	isMute = false;
	if(atten > ATT_STEP_MAX)
	{
		atten = ATT_STEP_MAX;
	}
}
void amplify()
{
	if(atten != 0)
	{
		atten--;
		isMute = false;
	}	
}
void mute()
{
	if(!isMute)
	{
		prevAtt = atten;
	}
	isMute = true;
	atten = ATT_STEP_MAX;
}
void recall()
{
	atten = prevAtt;
	isMute = false;
}
void full()
{
	atten = 0;
	isMute = false;
}

void sendData(uint8_t addr, uint8_t sdata)
{
	digitalWrite(SS, LOW);
	delayMicroseconds(4);
	SPI.transfer(addr);
	SPI.transfer(sdata);
	delayMicroseconds(4);
	digitalWrite(SS, HIGH);
}

void showAtten(uint8_t att)
{
	if(att < 96)
	{
		attLv = -0.5*(float)att;
	}
	else
	{
		attLv = -48.0-(float)(att-96);
	}
	if(att < ATT_STEP_MAX)
	{
		Serial.print(att);
		Serial.print(" : ");
		Serial.print(attLv);
		Serial.print("dB\r\n");
	}
	else
	{
		Serial.print("MUTE\r\n");
		isMute = true;
	}
}

void setup() {
	// put your setup code here, to run once:
	pinMode(SS, OUTPUT);
	pinMode(ENC_UP, INPUT);
	pinMode(ENC_DOWN, INPUT);
	pinMode(MUTE_UNMUTE, INPUT);

	digitalWrite(SS, HIGH);
	SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
	SPI.begin();
	Serial.begin(115200);

	atten = ATT_STEP_MAX;
	sendData(CH1, atten);
	sendData(CH2, atten);	
	showAtten(atten);
}

void loop()
 {
	// put your main code here, to run repeatedly:
	if(Serial.available())
	{
		serialData = Serial.read();
		if((serialData == 'd')||(serialData == 'D'))
		{
			attenuate();
		}
		if((serialData == 'u')||(serialData == 'U'))
		{
			amplify();		
		}
		if((serialData == 'm')||(serialData == 'M'))
		{
			mute();
		}
		if((serialData == 'r')||(serialData == 'R'))
		{
			recall();
		}
		if((serialData == 'f')||(serialData == 'F'))
		{
			full();
		}
		sendData(CH1, atten);
		sendData(CH2, atten);	
		showAtten(atten);
	}

	if(digitalRead(ENC_UP) == HIGH)
	{
		amplify();
		sendData(CH1, atten);
		sendData(CH2, atten);	
		showAtten(atten);
		while(digitalRead(ENC_UP) == HIGH){}
	}
	if(digitalRead(ENC_DOWN) == HIGH)
	{
		attenuate();
		sendData(CH1, atten);
		sendData(CH2, atten);	
		showAtten(atten);
		while(digitalRead(ENC_DOWN) == HIGH){}
	}
	if(digitalRead(MUTE_UNMUTE)==HIGH)
	{
		if(!isMute)
		{
			mute();
		}
		else
		{
			recall();
		}		
		sendData(CH1, atten);
		sendData(CH2, atten);	
		showAtten(atten);
		while(digitalRead(MUTE_UNMUTE) == HIGH){}		
	}
}