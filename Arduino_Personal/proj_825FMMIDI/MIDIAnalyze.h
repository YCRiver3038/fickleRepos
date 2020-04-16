#ifndef MIDI_ANALYSE_HEADER_INCLUDED
#define MIDI_ANALYSE_HEADER_INCLUDED

/*
 **** 工事中 -Under construction- ****
 */
#include "stdlib.h"
#include "stdint.h"

#ifndef nullptr
#define nullptr NULL
#endif

#define ALSTAT_CONSTRUCT_FAILED 0xEFFFFFFF
#define ALSTAT_CONSTRUCT_SUCCESS 0x0
#define SYSEX_BUF_SIZE 72
#define SMSG_BUF_SIZE 3

#define ALSTAT_ERR 0xEFFF0000
#define ALSTAT_READY 0x1


struct _RSTATDEF
{
	bool rcv_noteOff;			//0x8n 0x(keyNumber) 0x(velocity), 0x9n 0x(keyNumber) 0x00
	bool rcv_noteOn;			//0x9n 0x(keyNumber) 0x(velocity)
	bool rcv_polyKeyPressure;	//0xAn
	bool rcv_CC;				//0xBn
	bool rcv_PC;				//0xCn
	bool rcv_chPressure;		//0xDn
	bool rcv_pBend;				//0xEn
	bool SysEX_Start;			//0xF0
	bool MTC_QF;				//0xF1
	bool SongPositionPointer;	//0xF2
	bool SongSelect;			//0xF3
	bool TuneRequest;			//0xF6
	bool SysEX_End;				//0xF7
	bool TimingClock;			//0xF8
	bool Start;					//0xFA
	bool Continue;				//0xFB
	bool Stop;					//0xFC
	bool ActiveSensing;			//0xFE
	bool SystemReset;			//0xFF
} rcvStatus;


class MIDIAnalyzer
{
	private:
		uint8_t* SysEX_Buf;
		uint8_t* SingleMsg_Buf;
		uint8_t targetChannel;
		uint8_t rcvmsg;
		uint8_t sysExBufCtr;
		uint8_t sysExCount;
		uint8_t smsgBufCtr;
		uint32_t analyzerStatus;

	public:		
		MIDIAnalyzer()
		{
			SysEX_Buf = (uint8_t*)calloc(SYSEX_BUF_SIZE, sizeof(uint8_t));
			if(SysEX_Buf == nullptr)
			{
				analyzerStatus = ALSTAT_CONSTRUCT_FAILED;
			}
			else
			{
				analyzerStatus = ALSTAT_CONSTRUCT_SUCCESS;
			}

			SingleMsg_Buf = (uint8_t*)calloc(SMSG_BUF_SIZE, sizeof(uint8_t));
			if(SysEX_Buf == nullptr)
			{
				analyzerStatus = ALSTAT_CONSTRUCT_FAILED;
			}
			else
			{
				analyzerStatus = ALSTAT_CONSTRUCT_SUCCESS;
			}

			targetChannel = 0;
			rcvmsg = 0;
			sysExBufCtr = 0;
			smsgBufCtr = 0;
		}

		uint32_t getAnalyzerStatus()
		{
			if(analyzerStatus == ALSTAT_CONSTRUCT_SUCCESS)
			{
				return ALSTAT_ERR;
			}
			else
			{
				return ALSTAT_READY;
			}
		}

		uint32_t pushData(uint8_t data)
		{
			if(data < 0xF0)
			{
				rcvmsg = data&0xF0;
				targetChannel = data&0x0F;
				switch (rcvmsg)
				{
					case 0x80:
						break;

					case 0x90:
						break;

					case 0xA0:
						break;

					case 0xB0:
						break;

					case 0xC0:
						break;

					case 0xD0:
						break;
					
					case 0xE0:
						break;

					default:
						if(rcvStatus.SysEX_Start)
						{
							if(sysExBufCtr < SYSEX_BUF_SIZE)
							{
								SysEX_Buf[sysExBufCtr] = data;
								sysExBufCtr++;
							}
						}
						break;
				}
			}
			else
			{
				switch (data)
				{
					case 0xF0:
						rcvStatus.SysEX_Start = true;
						rcvStatus.SysEX_End = false;
						sysExBufCtr = 0;
						break;
					
					case 0xF7:
						rcvStatus.SysEX_Start = false;
						rcvStatus.SysEX_End = true;
						sysExBufCtr = 0;
						break;

					default:
						break;
				}
			}
		}
};

#endif
