#ifndef SD1COMM_HEADER_INCLUDED
#define SD1COMM_HEADER_INCLUDED

#include "SD1REG.h"
#include "SPI.h"
#include "stdint.h"

#define TMEM_ALLOC_ERR 0xFF
#define TMEM_ALLOC_SUCCESS 0x00
#define SPI_SPEED_DEFAULT 8000000

//---Microcontroller dependencies---
#define SET_POWER_ON HIGH
#define SET_POWER_OFF LOW
#define SS_DEFAULT 10
#define RST_N_DEFAULT 9
#define POWCTRL_DEFAULT 8
//---Microcontroller dependencies---

const enum PARAM_NAMEDEF
{
	PN_BO,
	PN_LFO,
	PN_ALG,
	PN_SR,
	PN_XOF,
	PN_KSR,
	PN_RR,
	PN_DR,
	PN_AR,
	PN_SL,
	PN_TL,
	PN_KSL,
	PN_DAM,
	PN_EAM,
	PN_DVB,
	PN_EVB,
	PN_MULTI,
	PN_DT,
	PN_WS,
	PN_FB,
}paramName;

const enum OPNUMBERDEF
{
	N_OP1,
	N_OP2,
	N_OP3,
	N_OP4
} OPs;

class SD1Device
{
	private:
		uint8_t dbuf[2];
		uint8_t rcvbuf;
		uint16_t dbuf16;

//---Microcontroller dependencies---
		uint8_t RST_N;
		uint8_t POWCTRL;
		uint8_t devSS;

		void setPins(uint8_t NRST, uint8_t PCTRL, uint8_t SSEL)
		{
			RST_N = NRST;
			POWCTRL = PCTRL;
			devSS = SSEL;

			if(RST_N > 9)
			{
				RST_N = 9;
			}
			if(POWCTRL > 8)
			{
				POWCTRL = 8;
			}
			pinMode(POWCTRL, OUTPUT);
			pinMode(RST_N, OUTPUT);
			pinMode(devSS, OUTPUT);
			digitalWrite(RST_N, LOW);
			digitalWrite(POWCTRL, SET_POWER_OFF);
		}

		void msWait(uint16_t wsec)
		{
			delay(wsec);
		}
		void usWait(uint16_t wsec)
		{
			delayMicroseconds(wsec);
		}
		void dev_reset()
		{
			digitalWrite(RST_N, LOW);
		}
		void dev_nreset()
		{
			digitalWrite(RST_N, HIGH);
		}
		void dev_powerON()
		{
			digitalWrite(POWCTRL, SET_POWER_ON);
		}

	public:
		SD1Device()
		{
			setPins(RST_N_DEFAULT, POWCTRL_DEFAULT, SS_DEFAULT);
			SPI.beginTransaction(SPISettings(SPI_SPEED_DEFAULT, MSBFIRST, SPI_MODE0));
			SPI.begin();
		}
		
		SD1Device(uint8_t P_RST_N, uint8_t P_POWCTRL, uint8_t SS_Using, uint32_t transSpeed)
		{
			setPins(P_RST_N, P_POWCTRL, SS_Using);
			SPI.beginTransaction(SPISettings(transSpeed, MSBFIRST, SPI_MODE0));
			SPI.begin();
		}

		void select()
		{
			digitalWrite(devSS, LOW);
		}

		void deselect()
		{
			digitalWrite(devSS, HIGH);
		}

		void sendDataNCS(void* dataBuf, uint16_t buflen)
		{
			SPI.transfer(dataBuf, buflen);
		}
//---Microcontroller dependencies---

		void sendData(uint8_t addr, uint8_t data)
		{
			dbuf[0] = addr;
			dbuf[1] = data;
			select();
			sendDataNCS(dbuf, 2);
			deselect();
		}

		void sendData(uint8_t* dataBuf, uint16_t buflen)
		{
			select();
			sendDataNCS(dataBuf, buflen);
			deselect();
		}
		
		void readData(uint8_t addr, uint8_t* rdata)
		{
			dbuf16 = ((addr | 0x80)<<8);
			select();
			*rdata = (uint8_t)(SPI.transfer16(dbuf16) & 0x00FF);
			deselect();
		}
		
		void init()
		{
			dev_reset();
			dev_powerON();
			usWait(120);
			dev_nreset();
			I_ADR.DRV_SEL.BIT.D0 = 0;
			sendData(uint8_t(I_ADR.ADDR_DRV_SEL), I_ADR.DRV_SEL.DR_U8);
			readData(I_ADR.ADDR_AP, &(I_ADR.AP.DR_U8));
			I_ADR.AP.BIT.AP0 = 0;
			sendData(uint8_t(I_ADR.ADDR_AP), I_ADR.AP.DR_U8);
			msWait(10);
			I_ADR.CLKE.BIT.D0 = 1;
			sendData(uint8_t(I_ADR.ADDR_CLKE), I_ADR.CLKE.DR_U8);
			I_ADR.ALRST.BIT.D7 = 0;
			sendData(uint8_t(I_ADR.ADDR_ALRST), I_ADR.ALRST.DR_U8);
			I_ADR.SFTRST.DR_U8 = 0xA3;
			sendData(uint8_t(I_ADR.ADDR_SFTRST), I_ADR.SFTRST.DR_U8);
			I_ADR.SFTRST.DR_U8 = 0x00;
			sendData(uint8_t(I_ADR.ADDR_SFTRST), I_ADR.SFTRST.DR_U8);
			msWait(40);
			I_ADR.AP.BIT.AP1 = 0;
			I_ADR.AP.BIT.AP3 = 0;
			sendData(uint8_t(I_ADR.ADDR_AP), I_ADR.AP.DR_U8);
			usWait(12);
			I_ADR.AP.BIT.AP2 = 0;
			sendData(uint8_t(I_ADR.ADDR_AP), I_ADR.AP.DR_U8);
		}

		void keyOn(uint8_t tn, uint8_t fnum_H, uint8_t fnum_L)
		{
			I_ADR.CRGD_VNO.BITSET.CRGD_VNO = tn;
			I_ADR.CRWR2.BITSET.FNUM_H = fnum_H;
			I_ADR.CRWR3.BITSET.FNUM = fnum_L;
			I_ADR.CRWR4.BITSET.KEY_ON = 1;

			sendData(I_ADR.ADDR_CRGD_VNO, I_ADR.CRGD_VNO.DR_U8);
			sendData(I_ADR.ADDR_CRWR2, I_ADR.CRWR2.DR_U8);
			sendData(I_ADR.ADDR_CRWR3, I_ADR.CRWR3.DR_U8);
			sendData(I_ADR.ADDR_CRWR4, I_ADR.CRWR4.DR_U8);
		}

		void keyOff()
		{
			I_ADR.CRWR4.BITSET.KEY_ON = 0;
			sendData(I_ADR.ADDR_CRWR4, I_ADR.CRWR4.DR_U8);
		}
};

class SD1Tone
{
	private:
		uint8_t FIFO_ADDR; 
		uint8_t toneNumber;
		uint8_t T_ADR_HEADER;
		uint8_t T_ADR_FOOTER[4];

	public:
		ToneSettings* TSets;

		SD1Tone()
		{
			FIFO_ADDR = 0x07;
			toneNumber = 0;
			TSets = nullptr;
			T_ADR_FOOTER[0] = 0x80; 
			T_ADR_FOOTER[1] = 0x03;
			T_ADR_FOOTER[2] = 0x81;
			T_ADR_FOOTER[3] = 0x80;			 
		}

		uint8_t getToneMemory(uint8_t tnmax=MAX_VOICE)
		{
			toneNumber = tnmax - 1;
			if(toneNumber > (MAX_VOICE-1))
			{
				toneNumber = (MAX_VOICE-1);
			}
			if(toneNumber < 0)
			{
				toneNumber = 0;
			}
			TSets = (ToneSettings*)calloc((toneNumber + 1), sizeof(ToneSettings));
			if(TSets == nullptr)
			{
				T_ADR_HEADER = 0x80;
				return TMEM_ALLOC_ERR;
			}
			T_ADR_HEADER = 0x80 + tnmax;
			return TMEM_ALLOC_SUCCESS;
		}

		void deleteToneMemory()
		{
			if(TSets != nullptr)
			{
				free(TSets);
			}
		}

		~SD1Tone()
		{
			deleteToneMemory();
		}

		void sendToneParams(SD1Device target)
		{
			target.select();
			target.sendDataNCS(&FIFO_ADDR, 1);
			target.sendDataNCS(&T_ADR_HEADER, 1);
			target.sendDataNCS(TSets, (sizeof(ToneSettings)*(toneNumber+1)));
			target.sendDataNCS(T_ADR_FOOTER, 4);
			target.deselect();
		}

		void setToneParams(uint8_t tNumber, OPNUMBERDEF onum, PARAM_NAMEDEF nsel, uint8_t sVal)
		{
			switch (nsel)
			{
				case PN_BO:
					TSets[tNumber].Params.ETS.BITSET.BO = sVal;
					break;
				case PN_LFO:
					TSets[tNumber].Params.ETS.BITSET.LFO = sVal;
					break;
				case PN_ALG:
					TSets[tNumber].Params.ETS.BITSET.ALG = sVal;
					break;
				case PN_SR:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.SR = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.SR = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.SR = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.SR = sVal;
							break;							
					}				
					break;
				case PN_XOF:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.XOF = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.XOF = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.XOF = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.XOF = sVal;
							break;							
					}				
					break;
				case PN_KSR:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.KSR = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.KSR = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.KSR = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.KSR = sVal;
							break;							
					}				
					break;
				case PN_RR:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.RR = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.RR = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.RR = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.RR = sVal;
							break;							
					}				
					break;
				case PN_DR:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.DR = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.DR = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.DR = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.DR = sVal;
							break;							
					}				
					break;
				case PN_AR:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.AR = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.AR = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.AR = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.AR = sVal;
							break;							
					}				
					break;
				case PN_SL:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.SL = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.SL = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.SL = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.SL = sVal;
							break;							
					}				
					break;
				case PN_TL:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.TL = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.TL = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.TL = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.TL = sVal;
							break;							
					}				
					break;
				case PN_KSL:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.KSL = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.KSL = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.KSL = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.KSL = sVal;
							break;							
					}				
					break;
				case PN_DAM:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.DAM = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.DAM = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.DAM = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.DAM = sVal;
							break;							
					}				
					break;
				case PN_EAM:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.EAM = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.EAM = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.EAM = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.EAM = sVal;
							break;							
					}				
					break;
				case PN_DVB:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.DVB = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.DVB = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.DVB = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.DVB = sVal;
							break;							
					}				
					break;
				case PN_EVB:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.EVB = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.EVB = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.EVB = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.EVB = sVal;
							break;							
					}				
					break;
				case PN_MULTI:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.MULTI = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.MULTI = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.MULTI = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.MULTI = sVal;
							break;							
					}				
					break;
				case PN_DT:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.DT = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.DT = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.DT = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.DT = sVal;
							break;							
					}				
					break;
				case PN_WS:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.WS = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.WS = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.WS = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.WS = sVal;
							break;							
					}				
					break;
				case PN_FB:
					switch (onum)
					{
						case N_OP1:
							TSets[tNumber].Params.OP1.BITSET.FB = sVal;
							break;
						case N_OP2:
							TSets[tNumber].Params.OP2.BITSET.FB = sVal;
							break;
						case N_OP3:
							TSets[tNumber].Params.OP3.BITSET.FB = sVal;
							break;
						case N_OP4:
							TSets[tNumber].Params.OP4.BITSET.FB = sVal;
							break;							
					}				
					break;
				default:
					break;
			}
		}

};
#endif