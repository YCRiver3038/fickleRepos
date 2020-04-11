#ifndef L1972CTRL_INCLUDED
#define L1972CTRL_INCLUDED

#include "SPI.h"
#include "stdint.h"
#define ATT_STEP_MAX (uint8_t)127

class L1972Dev
{
	private:
		enum
		{
			CH1, CH2, CH3
		}_L1972CHDEF;
		uint8_t atten;
		uint8_t prevAtt;
		uint8_t devSS_PN;
		bool isMute;

		void slaveSelect()
		{
			digitalWrite(devSS_PN, LOW);
		}
		void usWait(uint16_t waitDur)
		{
			delayMicroseconds(waitDur);
		}
		void slaveDeselect()
		{
			digitalWrite(devSS_PN, HIGH);
		}
		void send(uint8_t transData)
		{
			SPI.transfer(transData);
		}

	public:
		L1972Dev(uint8_t SS_PNum)
		{
			devSS_PN = SS_PNum;
			pinMode(devSS_PN, OUTPUT);
			digitalWrite(devSS_PN, HIGH);
			SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
			SPI.begin();
			isMute = false;
			atten = ATT_STEP_MAX;
		}
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
		void applyAtt()
		{
			slaveSelect();
			usWait(4);
			send(CH1);
			send(atten);
			send(CH2);
			send(atten);
			usWait(4);
			slaveDeselect();
		}
		uint8_t getAttStep()
		{
			return atten;
		}

		bool getMuteStatus()
		{
			return isMute;
		}
};
#endif