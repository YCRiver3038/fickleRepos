#include "SPI.h"

#define SS 10

#define ATT_STEP_MAX (uint8_t)127

uint8_t atten = 0;
uint8_t currentAddr = 0;
uint8_t serialData = 0;
uint8_t combuf[10] = {0};
float attLv = 0.0;

enum
{
	CH1, CH2, CH3
}Address;

void sendData(uint8_t addr, uint8_t sdata)
{
	digitalWrite(SS, LOW);
	SPI.transfer(addr);
	SPI.transfer(sdata);
	digitalWrite(SS, HIGH);
}

void setup() {
	// put your setup code here, to run once:
	pinMode(SS, OUTPUT);
	digitalWrite(SS, HIGH);
	SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
	SPI.begin();
	atten = ATT_STEP_MAX;
	sendData(CH1, atten);
	sendData(CH2, atten);
	Serial.begin(115200);
	Serial.println(atten);
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
			}
		}
		if(serialData == 'm')
		{
				atten = ATT_STEP_MAX;
		}

		sendData(CH1, atten);
		sendData(CH2, atten);
		if(atten < 96)
		{
				attLv = -0.5*(float)atten;
		}
		else
		{
			attLv = -48.0-(float)(atten-96);
		}
		if(atten < ATT_STEP_MAX)
		{
			Serial.println(attLv);
		}
		else
		{
			Serial.print("MUTE\r\n");
		}
	}
}
