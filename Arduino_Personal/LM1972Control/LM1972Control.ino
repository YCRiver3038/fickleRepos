#include "SPI.h"

#define SS 10
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

void sendData(uint8_t addr, uint8_t sdata)
{
	digitalWrite(SS, LOW);
	delayMicroseconds(4);
	SPI.transfer(addr);
	delayMicroseconds(4);
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
		Serial.println(attLv);
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
		if(serialData == 'u')
		{
			atten++;
			isMute = false;
			if(atten > ATT_STEP_MAX)
			{
				atten = ATT_STEP_MAX;
			}
		}
		if(serialData == 'd')
		{
			if(atten != 0)
			{
				atten--;
				isMute = false;
			}			
		}
		if(serialData == 'm')
		{
			if(!isMute)
			{
				prevAtt = atten;
			}
			isMute = true;
			atten = ATT_STEP_MAX;
		}
		if(serialData == 'r')
		{
			atten = prevAtt;
			isMute = false;
		}
		if(serialData == 'f')
		{
			atten = 0;
			isMute = false;
		}
		sendData(CH1, atten);
		sendData(CH2, atten);
		showAtten(atten);
	}
}
