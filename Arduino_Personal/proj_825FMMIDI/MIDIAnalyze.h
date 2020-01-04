#ifndef MIDI_ANALYSE_HEADER_INCLUDED
#define MIDI_ANALYSE_HEADER_INCLUDED

/*
 **** 工事中 -Under construction- ****
 */
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

#endif
