#ifndef SD1COMM_HEADER_INCLUDED
#define SD1COMM_HEADER_INCLUDED

#include "SD1REG.h"
#include "SPI.h"
#define RST_N_DEFAULT 9
#define POWCTRL_DEFAULT 8
#define SPI_SPEED_DEFAULT 8000000
#define SET_POWER_ON HIGH
#define SET_POWER_OFF LOW
#define SS 10
#define TMEM_ALLOC_ERR 0xFF
#define TMEM_ALLOC_SUCCESS 0x00

class SD1Device
{
	private:
		uint8_t RST_N;
		uint8_t dbuf[2];
		uint8_t rcvbuf;
		uint8_t POWCTRL;
		uint16_t dbuf16;
		
		void setPins()
		{
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
			pinMode(SS, OUTPUT);
			digitalWrite(RST_N, LOW);
			digitalWrite(POWCTRL, SET_POWER_OFF);
		}

	public:
		SD1Device()
		{
			RST_N = RST_N_DEFAULT;
			POWCTRL = POWCTRL_DEFAULT;
			setPins();
			SPI.beginTransaction(SPISettings(SPI_SPEED_DEFAULT, MSBFIRST, SPI_MODE0));
			SPI.begin();
		}
		
		SD1Device(uint8_t P_RST_N, uint8_t P_POWCTRL, uint32_t transSpeed)
		{
			RST_N = P_RST_N;
			POWCTRL = P_POWCTRL;
			setPins();
			SPI.beginTransaction(SPISettings(transSpeed, MSBFIRST, SPI_MODE0));
			SPI.begin();
		}

		void sendDataNCS(void* dataBuf, uint16_t buflen)
		{
			SPI.transfer(dataBuf, buflen);
		}
		
		void sendData(uint8_t addr, uint8_t data)
		{
			dbuf[0] = addr;
			dbuf[1] = data;
			digitalWrite(SS, LOW);
			sendDataNCS(dbuf, 2);
			digitalWrite(SS, HIGH);
		}

		void sendData(uint8_t* dataBuf, uint16_t buflen)
		{
			digitalWrite(SS, LOW);
			sendDataNCS(dataBuf, buflen);
			digitalWrite(SS, HIGH);
		}
		
		void readData(uint8_t addr, uint8_t* rdata)
		{
			dbuf16 = ((addr | 0x80)<<8);			
			digitalWrite(SS, LOW);
			*rdata = uint8_t(SPI.transfer16(dbuf16) & 0x00FF);
			digitalWrite(SS, HIGH);
		}
		
		void init()
		{
			digitalWrite(RST_N, LOW);
			digitalWrite(POWCTRL, SET_POWER_ON);
			delayMicroseconds(120);
			digitalWrite(RST_N, HIGH);
			I_ADR.DRV_SEL.BIT.D0 = 0;
			sendData(uint8_t(I_ADR.ADDR_DRV_SEL), I_ADR.DRV_SEL.DR_U8);
			readData(I_ADR.ADDR_AP, &(I_ADR.AP.DR_U8));
			I_ADR.AP.BIT.AP0 = 0;
			sendData(uint8_t(I_ADR.ADDR_AP), I_ADR.AP.DR_U8);
			delay(10);
			I_ADR.CLKE.BIT.D0 = 1;
			sendData(uint8_t(I_ADR.ADDR_CLKE), I_ADR.CLKE.DR_U8);
			I_ADR.ALRST.BIT.D7 = 0;
			sendData(uint8_t(I_ADR.ADDR_ALRST), I_ADR.ALRST.DR_U8);
			I_ADR.SFTRST.DR_U8 = 0xA3;
			sendData(uint8_t(I_ADR.ADDR_SFTRST), I_ADR.SFTRST.DR_U8);
			I_ADR.SFTRST.DR_U8 = 0x00;
			sendData(uint8_t(I_ADR.ADDR_SFTRST), I_ADR.SFTRST.DR_U8);
			delay(40);
			I_ADR.AP.BIT.AP1 = 0;
			I_ADR.AP.BIT.AP3 = 0;
			sendData(uint8_t(I_ADR.ADDR_AP), I_ADR.AP.DR_U8);
			delayMicroseconds(12);
			I_ADR.AP.BIT.AP2 = 0;
			sendData(uint8_t(I_ADR.ADDR_AP), I_ADR.AP.DR_U8);
		}

		void keyOn(uint8_t ch)
		{

		}

		void keyOff(uint8_t ch)
		{
			
		}
};

class SD1Tone
{
	private:
		uint8_t toneNumber;
		uint8_t T_ADR_HEADER;
		uint8_t T_ADR_FOOTER[4];

	public:
		ToneSettings* TSets;

		SD1Tone()
		{
			toneNumber = 0;
			TSets = nullptr;
			T_ADR_FOOTER[0] = 0x80; 
			T_ADR_FOOTER[1] = 0x03;
			T_ADR_FOOTER[2] = 0x81;
			T_ADR_FOOTER[3] = 0x80;			 
		}
		~SD1Tone()
		{
			if(TSets != nullptr)
			{
				free(TSets);
			}
		}
		uint8_t getToneMemory(uint8_t tnmax)
		{
			toneNumber = tnmax;
			if(toneNumber > 15)
			{
				toneNumber = 15;
			}
			TSets = (ToneSettings*)calloc((toneNumber+1), sizeof(ToneSettings));
			if(TSets == nullptr)
			{
				T_ADR_HEADER = 0x80;
				return TMEM_ALLOC_ERR;
			}
			T_ADR_HEADER = 0x80+tnmax;
			return TMEM_ALLOC_SUCCESS;
		}
		void deleteToneMemory()
		{
			if(TSets != nullptr)
			{
				free(TSets);
			}
		}

		uint8_t setToneParams(uint8_t tNumber, OPNUMBERDEF onum, PARAM_NAMEDEF nsel, uint8_t sVal)
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

		void sendToneParams(SD1Device target)
		{
			digitalWrite(SS, LOW);
			target.sendDataNCS(&T_ADR_HEADER, 1);
			target.sendDataNCS(TSets, (sizeof(ToneSettings)*(toneNumber+1)));
			target.sendDataNCS(T_ADR_FOOTER, 4);
			digitalWrite(SS, HIGH);
		}
};
#endif