#ifndef SD1IFREG_HEADER_INCLUDED
#define SD1IFREG_HEADER_INCLUDED

#include "stdint.h"

struct _IADRDEF
{
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CLKE_RESERVED	:7;
			unsigned D0				:1;
		} BIT;
	} CLKE;	//#0 Clock Enable

	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned D7				:1;
			unsigned ALRST_RESERVED	:7;
		} BIT;
	} ALRST; //#1 Reset

	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned AP_RESERVED	:4;
			unsigned AP				:4;
		} BITSET;
		struct 
		{
			unsigned AP_RESERVED	:4;
			unsigned AP3			:1;
			unsigned AP2			:1;
			unsigned AP1			:1;
			unsigned AP0			:1;
		} BIT;
	} AP; //#2 Analog Block Power-down control

	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned GAIN_RESERVED	:6;
			unsigned GAIN			:2;
		} BITSET;
		struct 
		{
			unsigned GAIN_RESERVED	:6;
			unsigned GAIN1			:1;
			unsigned GAIN0			:1;
		} BIT;
	} GAIN; //#3 Speaker Amplifier Gain Setting

	uint8_t HW_ID; //#4 Hardware ID
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned INT_RESERVED1	:3;
			unsigned EMP_DW			:1;
			unsigned INT_RESERVED2	:1;
			unsigned FIFO			:1;
			unsigned INT_RESERVED3	:1;
			unsigned SQ_STP			:1;
		} BIT;
	} INTERRUPT; //#5 Interrupt

	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned INT2_RESERVED1	:1;
			unsigned EIRQ			:1;
			unsigned INT2_RESERVED2	:1;
			unsigned EEMP_DW		:1;
			unsigned INT_RESERVED3	:1;
			unsigned EFIFO			:1;
			unsigned INT_RESERVED4	:1;
			unsigned ESQ_STP		:1;
		} BIT;
	} INTERRUPT2; //#6
	
	union
	{
		uint8_t DT;
		struct 
		{
			unsigned DT7			:1;
			unsigned DT6			:1;
			unsigned DT5			:1;
			unsigned DT4			:1;
			unsigned DT3			:1;
			unsigned DT2			:1;
			unsigned DT1			:1;
			unsigned DT0			:1;
		} BIT;
	} CONTENTS_DATA_REG; //#7 Contents Data Write Port
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned ALL_KEY_OFF	:1;
			unsigned ALL_MUTE		:1;
			unsigned ALL_EG_RST		:1;
			unsigned R_FIFOR		:1;
			unsigned REP_SQ			:1;
			unsigned R_SEQ			:1;
			unsigned R_FIFO			:1;
			unsigned START			:1;
		} BIT;
	} SEQ_SET; //#8 Sequencer Setting

	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned SEQ_VOL			:5;
			unsigned DIR_SV				:1;
			unsigned SEQ_VOL_RESERVED	:1;
			unsigned SIZE8				:1;
		} BITSET;
		struct 
		{
			unsigned SEQ_VOL4			:1;
			unsigned SEQ_VOL3			:1;
			unsigned SEQ_VOL2			:1;
			unsigned SEQ_VOL1			:1;
			unsigned SEQ_VOL0			:1;
			unsigned DIR_SV				:1;
			unsigned SEQ_VOL_RESERVED	:1;
			unsigned SIZE8				:1;
		} BIT;
	} SEQ_VOL1; //#9
	
	union
	{
		uint8_t SIZE;
		struct 
		{
			unsigned SIZE7	:1;
			unsigned SIZE6	:1;
			unsigned SIZE5	:1;
			unsigned SIZE4	:1;
			unsigned SIZE3	:1;
			unsigned SIZE2	:1;
			unsigned SIZE1	:1;
			unsigned SIZE0	:1;
		} BIT;
	} SEQ_VOL2; //#10
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRGD_VNO_RESERVED	:4;
			unsigned CRGD_VNO			:4;
		} BITSET;
		struct 
		{
			unsigned CRGD_VNO_RESERVED	:4;
			unsigned CRGD_VNO3			:1;
			unsigned CRGD_VNO2			:1;
			unsigned CRGD_VNO1			:1;
			unsigned CRGD_VNO0			:1;
		} BIT;
	} CRGD_VNO; //#11 Synthesizer Setting
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR1_RESERVED1	:1;
			unsigned VOVOL				:5;
			unsigned CRWR1_RESERVED2	:2;
		} BITSET;
		struct 
		{
			unsigned CRWR1_RESERVED1	:1;
			unsigned VOVOL4				:1;
			unsigned VOVOL3				:1;
			unsigned VOVOL2				:1;
			unsigned VOVOL1				:1;
			unsigned VOVOL0				:1;
			unsigned CRWR1_RESERVED2	:2;
		} BIT;
	} CRWR1; //#12 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR2_RESERVED		:2;
			unsigned FNUM_H				:3;
			unsigned BLOCK				:3;
		} BITSET;
		struct 
		{
			unsigned CRWR2_RESERVED		:2;
			unsigned FNUM9				:1;
			unsigned FNUM8				:1;
			unsigned FNUM7				:1;
			unsigned BLOCK2				:1;
			unsigned BLOCK1				:1;
			unsigned BLOCK0				:1;
		} BIT;
	} CRWR2; //#13 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR3_RESERVED		:1;
			unsigned FNUM				:7;
		} BITSET;
		struct 
		{
			unsigned CRWR3_RESERVED		:1;
			unsigned FNUM6				:1;
			unsigned FNUM5				:1;
			unsigned FNUM4				:1;
			unsigned FNUM3				:1;
			unsigned FNUM2				:1;
			unsigned FNUM1				:1;
			unsigned FNUM0				:1;
		} BIT;
	} CRWR3; //#14 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR4_RESERVED		:1;
			unsigned KEY_ON				:1;
			unsigned MUTE				:1;
			unsigned EG_RST				:1;
			unsigned TONENUM			:4;
		} BITSET;
		struct 
		{
			unsigned CRWR4_RESERVED		:1;
			unsigned KEY_ON				:1;
			unsigned MUTE				:1;
			unsigned EG_RST				:1;
			unsigned TONENUM3			:1;
			unsigned TONENUM2			:1;
			unsigned TONENUM1			:1;
			unsigned TONENUM0			:1;
		} BIT;
	} CRWR4; //#15 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR5_RESERVED1	:1;
			unsigned CHVOL				:5;
			unsigned CRWR5_RESERVED2	:1;
			unsigned DIR_CV				:1;
		} BITSET;
		struct 
		{
			unsigned CRWR5_RESERVED1		:1;
			unsigned CHVOL4				:1;
			unsigned CHVOL3				:1;
			unsigned CHVOL2				:1;
			unsigned CHVOL1				:1;
			unsigned CHVOL0				:1;
			unsigned CRWR5_RESERVED2		:1;
			unsigned DIR_CV				:1;
		} BIT;
	} CRWR5; //#16 Control Register Write Registers

	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR6_RESERVED		:5;
			unsigned XVB				:3;
		} BITSET;
		struct 
		{
			unsigned CRWR6_RESERVED		:5;
			unsigned XVB2				:1;
			unsigned XVB1				:1;
			unsigned XVB0				:1;
		} BIT;
	} CRWR6; //#17 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR7_RESERVED		:3;
			unsigned CRWR7_INT			:2;
			unsigned FRAC_H				:3;
		} BITSET;
		struct 
		{
			unsigned CRWR7_RESERVED		:3;
			unsigned CRWR7_INT1			:1;
			unsigned CRWR7_INT0			:1;
			unsigned FRAC8				:1;
			unsigned FRAC7				:1;
			unsigned FRAC6				:1;
		} BIT;
	} CRWR7; //#18 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR8_RESERVED1	:1;
			unsigned FRAC				:6;
			unsigned CRWR8_RESERVED2	:1;
		} BITSET;
		struct 
		{
			unsigned CRWR8_RESERVED1	:1;
			unsigned FRAC5				:1;
			unsigned FRAC4				:1;
			unsigned FRAC3				:1;
			unsigned FRAC2				:1;
			unsigned FRAC1				:1;
			unsigned FRAC0				:1;	
			unsigned CRWR8_RESERVED2	:1;
		} BIT;
	} CRWR8; //#19 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRWR9_RESERVED	:7;
			unsigned DIR_MT			:1;
		} BIT;
	} CRWR9; //#20 Control Register Write Registers
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned RDADR_CRG7	:1;
			unsigned RDADR_CRG6	:1;
			unsigned RDADR_CRG5	:1;
			unsigned RDADR_CRG4	:1;
			unsigned RDADR_CRG3	:1;
			unsigned RDADR_CRG2	:1;
			unsigned RDADR_CRG1	:1;	
			unsigned RDADR_CRG0	:1;
		} BIT;
	} RDADR; //#21 Control Register Read Port
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned CRRP2_RESERVED	:1;
			unsigned RDDATA_CRG		:7;
		} BITSET;
		struct 
		{
			unsigned CRRP2_RESERVED	:1;
			unsigned RDDATA_CRG6	:1;
			unsigned RDDATA_CRG5	:1;
			unsigned RDDATA_CRG4	:1;
			unsigned RDDATA_CRG3	:1;
			unsigned RDDATA_CRG2	:1;
			unsigned RDDATA_CRG1	:1;	
			unsigned RDDATA_CRG0	:1;
		} BIT;
	} RDDATA; //#22
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned STUS1_RESERVED	:1;
			unsigned MS_S_H			:7;
		} BITSET;
		struct 
		{
			unsigned STUS1_RESERVED	:1;
			unsigned MS_S13			:1;
			unsigned MS_S12			:1;
			unsigned MS_S11			:1;
			unsigned MS_S10			:1;
			unsigned MS_S9			:1;
			unsigned MS_S8			:1;	
			unsigned MS_S7			:1;
		} BIT;
	} STUS1; //#23 Sequencer Time unit Setting
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned STUS2_RESERVED	:1;
			unsigned MS_S_L			:7;
		} BITSET;
		struct 
		{
			unsigned STUS2_RESERVED	:1;
			unsigned MS_S6			:1;
			unsigned MS_S5			:1;
			unsigned MS_S4			:1;
			unsigned MS_S3			:1;
			unsigned MS_S2			:1;
			unsigned MS_S1			:1;	
			unsigned MS_S0			:1;
		} BIT;
	} STUS2; //#24
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned MASTER_VOL_DATA		:6;
			unsigned MASTER_VOL_RESERVED	:2;	
		} BITSET;
		struct 
		{
			unsigned MASTER_VOL5			:1;
			unsigned MASTER_VOL4			:1;
			unsigned MASTER_VOL3			:1;
			unsigned MASTER_VOL2			:1;
			unsigned MASTER_VOL1			:1;
			unsigned MASTER_VOL0			:1;
			unsigned MASTER_VOL_RESERVED	:2;	
		} BIT;
	} MASTER_VOL; //#25 Master Volume
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned SFTRST7	:1;
			unsigned SFTRST6	:1;
			unsigned SFTRST5	:1;
			unsigned SFTRST4	:1;
			unsigned SFTRST3	:1;
			unsigned SFTRST2	:1;
			unsigned SFTRST1	:1;	
			unsigned SFTRST0	:1;
		} BIT;
	} SFTRST; //#26 Soft Reset
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned MUTE_ITIME_RESERVED	:1;
			unsigned DADJT					:1;
			unsigned MUTE_ITIME				:2;
			unsigned CHVOL_ITIME			:2;
			unsigned MVOL_ITIME				:2;	
		} BITSET;
		struct 
		{
			unsigned MUTE_ITIME_RESERVED	:1;
			unsigned DADJT					:1;
			unsigned MUTE_ITIME1			:1;
			unsigned MUTE_ITIME0			:1;
			unsigned CHVOL_ITIME1			:1;
			unsigned CHVOL_ITIME0			:1;
			unsigned MVOL_ITIME1			:1;	
			unsigned MVOL_ITIME0			:1;
		} BIT;
	} MUTE_ITIME; //#27	Sequencer Delay, Recovery Function Setting, Volume Interpolation Setting
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned LFO_RST_RESERVED	:7;
			unsigned D0					:1;
		} BIT;
	} LFO_RST; //#28 LFO Reset
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned DRV_SEL_RESERVED	:7;
			unsigned D0					:1;
		} BIT;
	} DRV_SEL; //#29 Power Rail Selection
	
	uint8_t reserved30; //#30 Reserved
	uint8_t reserved31; //#31 Reserved
	
	uint8_t W_CEQ0; //#32 EQ BAND0 coefficient Write Port
	uint8_t W_CEQ1; //#33 EQ BAND1 coefficient Write Port
	uint8_t W_CEQ2; //#34 EQ BAND2 coefficient Write Port
	
	uint8_t CEQ00[3]; //#35~37 Equalizer Coefficient Read Ports
	uint8_t CEQ01[3]; //#38~40 Equalizer Coefficient Read Ports
	uint8_t CEQ02[3]; //#41~43 Equalizer Coefficient Read Ports
	uint8_t CEQ03[3]; //#44~46 Equalizer Coefficient Read Ports
	uint8_t CEQ04[3]; //#47~49 Equalizer Coefficient Read Ports
	uint8_t CEQ10[3]; //#50~52 Equalizer Coefficient Read Ports
	uint8_t CEQ11[3]; //#53~55 Equalizer Coefficient Read Ports
	uint8_t CEQ12[3]; //#56~58 Equalizer Coefficient Read Ports
	uint8_t CEQ13[3]; //#59~61 Equalizer Coefficient Read Ports
	uint8_t CEQ14[3]; //#62~64 Equalizer Coefficient Read Ports
	uint8_t CEQ20[3]; //#65~67 Equalizer Coefficient Read Ports
	uint8_t CEQ21[3]; //#68~70 Equalizer Coefficient Read Ports
	uint8_t CEQ22[3]; //#71~73 Equalizer Coefficient Read Ports
	uint8_t CEQ23[3]; //#74~76 Equalizer Coefficient Read Ports
	uint8_t CEQ24[3]; //#77~79 Equalizer Coefficient Read Ports
	
	union
	{
		uint8_t DR_U8;
		struct 
		{
			unsigned COMM7	:1;
			unsigned COMM6	:1;
			unsigned COMM5	:1;
			unsigned COMM4	:1;
			unsigned COMM3	:1;
			unsigned COMM2	:1;
			unsigned COMM1	:1;	
			unsigned COMM0	:1;
		} BIT;
	} COMM; //#80 Software test communication
	
	enum
	{
		ADDR_CLKE,					// #0
		ADDR_ALRST,					// #1
		ADDR_AP,					// #2
		ADDR_GAIN,					// #3
		ADDR_HW_ID,					// #4
		ADDR_INTERRUPT,				// #5
		ADDR_INTERRUPT2,			// #6
		ADDR_CONTENTS_DATA_REG,		// #7
		ADDR_SEQ_SET,				// #8
		ADDR_SEQ_VOL1,				// #9
		ADDR_SEQ_VOL2,				// #10
		ADDR_CRGD_VNO,				// #11
		ADDR_CRWR1,					// #12
		ADDR_CRWR2,					// #13
		ADDR_CRWR3,					// #14
		ADDR_CRWR4,					// #15
		ADDR_CRWR5,					// #16
		ADDR_CRWR6,					// #17
		ADDR_CRWR7,					// #18
		ADDR_CRWR8,					// #19
		ADDR_CRWR9,					// #20
		ADDR_RDADR_CRG,				// #21
		ADDR_RDDATA_CRG,			// #22
		ADDR_STUS1,					// #23
		ADDR_STUS2,					// #24
		ADDR_MASTER_VOL,			// #25
		ADDR_SFTRST,				// #26
		ADDR_MUTE_ITIME,			// #27
		ADDR_LFO_RST,				// #28
		ADDR_DRV_SEL,				// #29
		ADDR_RESERVED1,				// #30
		ADDR_RESERVED2,				// #31
		ADDR_W_CEQ0,				// #32
		ADDR_W_CEQ1,				// #33
		ADDR_W_CEQ2,				// #34
		ADDR_CEQ00_23_16,			// #35
		ADDR_CEQ00_15_8,			// #36
		ADDR_CEQ00_7_0,				// #37
		ADDR_CEQ01_23_16,			// #38
		ADDR_CEQ01_15_8,			// #39
		ADDR_CEQ01_7_0,				// #40
		ADDR_CEQ02_23_16,			// #41
		ADDR_CEQ02_15_8,			// #42
		ADDR_CEQ02_7_0,				// #43
		ADDR_CEQ03_23_16,			// #44
		ADDR_CEQ03_15_8,			// #45
		ADDR_CEQ03_7_0,				// #46
		ADDR_CEQ04_23_16,			// #47
		ADDR_CEQ04_15_8,			// #48
		ADDR_CEQ04_7_0,				// #49
		ADDR_CEQ10_23_16,			// #50
		ADDR_CEQ10_15_8,			// #51
		ADDR_CEQ10_7_0,				// #52
		ADDR_CEQ11_23_16,			// #53
		ADDR_CEQ11_15_8,			// #54
		ADDR_CEQ11_7_0,				// #55
		ADDR_CEQ12_23_16,			// #56
		ADDR_CEQ12_15_8,			// #57
		ADDR_CEQ12_7_0,				// #58
		ADDR_CEQ13_23_16,			// #59
		ADDR_CEQ13_15_8,			// #60
		ADDR_CEQ13_7_0,				// #61
		ADDR_CEQ14_23_16,			// #62
		ADDR_CEQ14_15_8,			// #63
		ADDR_CEQ14_7_0,				// #64
		ADDR_CEQ20_23_16,			// #65
		ADDR_CEQ20_15_8,			// #66
		ADDR_CEQ20_7_0,				// #67
		ADDR_CEQ21_23_16,			// #68
		ADDR_CEQ21_15_8,			// #69
		ADDR_CEQ21_7_0,				// #70
		ADDR_CEQ22_23_16,			// #71
		ADDR_CEQ22_15_8,			// #72
		ADDR_CEQ22_7_0,				// #73
		ADDR_CEQ23_23_16,			// #74
		ADDR_CEQ23_15_8,			// #75
		ADDR_CEQ23_7_0,				// #76
		ADDR_CEQ24_23_16,			// #77
		ADDR_CEQ24_15_8,			// #78
		ADDR_CEQ24_7_0,				// #79
		ADDR_COMM					// #80
	} _SD1ADRDEF;
} I_ADR;

union ToneSettings
{
	uint8_t DATA[30];
	struct
	{
		union
		{
			uint8_t ETS_DARR[2];
			struct 
			{
				uint8_t ETS_PARAM1;
				uint8_t ETS_PARAM2;	
			}U8;
			struct
			{
				unsigned RESERVED1	:6;
				unsigned BO 		:2;
				unsigned LFO		:2;
				unsigned RESERVED2	:3;
				unsigned ALG		:3;
			}BITSET;	
			struct
			{
				unsigned RESERVED1	:6;
				unsigned BO1 		:1;
				unsigned BO0		:1;			
				unsigned LFO1		:1;
				unsigned LFO0		:1;
				unsigned RESERVED2	:3;
				unsigned ALG2		:1;
				unsigned ALG1		:1;
				unsigned ALG0		:1;
			}BIT;
		} ETS; //Entire Tone Setting
		
		union
		{
			uint8_t OP_DARR[7];
			struct
			{
				uint8_t OP_PARAM1;
				uint8_t OP_PARAM2;
				uint8_t OP_PARAM3;
				uint8_t OP_PARAM4;
				uint8_t OP_PARAM5;
				uint8_t OP_PARAM6;
				uint8_t OP_PARAM7;
			} U8;
			struct
			{
				unsigned SR			:4;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR			:4;
				unsigned DR			:4;
				unsigned AR			:4;
				unsigned SL			:4;
				unsigned TL			:6;
				unsigned KSL		:2;
				unsigned RESERVED2	:1;
				unsigned DAM		:2;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB		:2;
				unsigned EVB		:1;
				unsigned MULTI		:4;
				unsigned RESERVED4	:1;
				unsigned DT			:3;
				unsigned WS			:5;
				unsigned FB			:3;
			} BITSET;		
			struct
			{
				unsigned SR3		:1;
				unsigned SR2		:1;
				unsigned SR1		:1;
				unsigned SR0		:1;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR3		:1;
				unsigned RR2		:1;
				unsigned RR1		:1;
				unsigned RR0		:1;
				unsigned DR3		:1;
				unsigned DR2		:1;
				unsigned DR1		:1;
				unsigned DR0		:1;
				unsigned AR3		:1;
				unsigned AR2		:1;
				unsigned AR1		:1;
				unsigned AR0		:1;
				unsigned SL3		:1;
				unsigned SL2		:1;
				unsigned SL1		:1;
				unsigned SL0		:1;
				unsigned TL5		:1;
				unsigned TL4		:1;
				unsigned TL3		:1;
				unsigned TL2		:1;
				unsigned TL1		:1;
				unsigned TL0		:1;
				unsigned KSL1		:1;
				unsigned KSL0		:1;
				unsigned RESERVED2	:1;
				unsigned DAM1		:1;
				unsigned DAM0		:1;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB1		:1;
				unsigned DVB0		:1;
				unsigned EVB		:1;
				unsigned MULTI3		:1;
				unsigned MULTI2		:1;
				unsigned MULTI1		:1;
				unsigned MULTI0		:1;
				unsigned RESERVED4	:1;
				unsigned DT2		:1;
				unsigned DT1		:1;
				unsigned DT0		:1;
				unsigned WS4		:1;
				unsigned WS3		:1;
				unsigned WS2		:1;
				unsigned WS1		:1;
				unsigned WS0		:1;
				unsigned FB2		:1;
				unsigned FB1		:1;
				unsigned FB0		:1;
			} BIT;	
		} OP1;

		union
		{
			uint8_t OP_DARR[7];
			struct
			{
				uint8_t OP_PARAM1;
				uint8_t OP_PARAM2;
				uint8_t OP_PARAM3;
				uint8_t OP_PARAM4;
				uint8_t OP_PARAM5;
				uint8_t OP_PARAM6;
				uint8_t OP_PARAM7;
			} U8;
			struct
			{
				unsigned SR			:4;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR			:4;
				unsigned DR			:4;
				unsigned AR			:4;
				unsigned SL			:4;
				unsigned TL			:6;
				unsigned KSL		:2;
				unsigned RESERVED2	:1;
				unsigned DAM		:2;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB		:2;
				unsigned EVB		:1;
				unsigned MULTI		:4;
				unsigned RESERVED4	:1;
				unsigned DT			:3;
				unsigned WS			:5;
				unsigned FB			:3;
			} BITSET;		
			struct
			{
				unsigned SR3		:1;
				unsigned SR2		:1;
				unsigned SR1		:1;
				unsigned SR0		:1;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR3		:1;
				unsigned RR2		:1;
				unsigned RR1		:1;
				unsigned RR0		:1;
				unsigned DR3		:1;
				unsigned DR2		:1;
				unsigned DR1		:1;
				unsigned DR0		:1;
				unsigned AR3		:1;
				unsigned AR2		:1;
				unsigned AR1		:1;
				unsigned AR0		:1;
				unsigned SL3		:1;
				unsigned SL2		:1;
				unsigned SL1		:1;
				unsigned SL0		:1;
				unsigned TL5		:1;
				unsigned TL4		:1;
				unsigned TL3		:1;
				unsigned TL2		:1;
				unsigned TL1		:1;
				unsigned TL0		:1;
				unsigned KSL1		:1;
				unsigned KSL0		:1;
				unsigned RESERVED2	:1;
				unsigned DAM1		:1;
				unsigned DAM0		:1;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB1		:1;
				unsigned DVB0		:1;
				unsigned EVB		:1;
				unsigned MULTI3		:1;
				unsigned MULTI2		:1;
				unsigned MULTI1		:1;
				unsigned MULTI0		:1;
				unsigned RESERVED4	:1;
				unsigned DT2		:1;
				unsigned DT1		:1;
				unsigned DT0		:1;
				unsigned WS4		:1;
				unsigned WS3		:1;
				unsigned WS2		:1;
				unsigned WS1		:1;
				unsigned WS0		:1;
				unsigned FB2		:1;
				unsigned FB1		:1;
				unsigned FB0		:1;
			} BIT;	
		} OP2;

		union
		{
			uint8_t OP_DARR[7];
			struct
			{
				uint8_t OP_PARAM1;
				uint8_t OP_PARAM2;
				uint8_t OP_PARAM3;
				uint8_t OP_PARAM4;
				uint8_t OP_PARAM5;
				uint8_t OP_PARAM6;
				uint8_t OP_PARAM7;
			} U8;
			struct
			{
				unsigned SR			:4;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR			:4;
				unsigned DR			:4;
				unsigned AR			:4;
				unsigned SL			:4;
				unsigned TL			:6;
				unsigned KSL		:2;
				unsigned RESERVED2	:1;
				unsigned DAM		:2;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB		:2;
				unsigned EVB		:1;
				unsigned MULTI		:4;
				unsigned RESERVED4	:1;
				unsigned DT			:3;
				unsigned WS			:5;
				unsigned FB			:3;
			} BITSET;		
			struct
			{
				unsigned SR3		:1;
				unsigned SR2		:1;
				unsigned SR1		:1;
				unsigned SR0		:1;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR3		:1;
				unsigned RR2		:1;
				unsigned RR1		:1;
				unsigned RR0		:1;
				unsigned DR3		:1;
				unsigned DR2		:1;
				unsigned DR1		:1;
				unsigned DR0		:1;
				unsigned AR3		:1;
				unsigned AR2		:1;
				unsigned AR1		:1;
				unsigned AR0		:1;
				unsigned SL3		:1;
				unsigned SL2		:1;
				unsigned SL1		:1;
				unsigned SL0		:1;
				unsigned TL5		:1;
				unsigned TL4		:1;
				unsigned TL3		:1;
				unsigned TL2		:1;
				unsigned TL1		:1;
				unsigned TL0		:1;
				unsigned KSL1		:1;
				unsigned KSL0		:1;
				unsigned RESERVED2	:1;
				unsigned DAM1		:1;
				unsigned DAM0		:1;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB1		:1;
				unsigned DVB0		:1;
				unsigned EVB		:1;
				unsigned MULTI3		:1;
				unsigned MULTI2		:1;
				unsigned MULTI1		:1;
				unsigned MULTI0		:1;
				unsigned RESERVED4	:1;
				unsigned DT2		:1;
				unsigned DT1		:1;
				unsigned DT0		:1;
				unsigned WS4		:1;
				unsigned WS3		:1;
				unsigned WS2		:1;
				unsigned WS1		:1;
				unsigned WS0		:1;
				unsigned FB2		:1;
				unsigned FB1		:1;
				unsigned FB0		:1;
			} BIT;	
		} OP3;

		union
		{
			uint8_t OP_DARR[7];
			struct
			{
				uint8_t OP_PARAM1;
				uint8_t OP_PARAM2;
				uint8_t OP_PARAM3;
				uint8_t OP_PARAM4;
				uint8_t OP_PARAM5;
				uint8_t OP_PARAM6;
				uint8_t OP_PARAM7;
			} U8;
			struct
			{
				unsigned SR			:4;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR			:4;
				unsigned DR			:4;
				unsigned AR			:4;
				unsigned SL			:4;
				unsigned TL			:6;
				unsigned KSL		:2;
				unsigned RESERVED2	:1;
				unsigned DAM		:2;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB		:2;
				unsigned EVB		:1;
				unsigned MULTI		:4;
				unsigned RESERVED4	:1;
				unsigned DT			:3;
				unsigned WS			:5;
				unsigned FB			:3;
			} BITSET;		
			struct
			{
				unsigned SR3		:1;
				unsigned SR2		:1;
				unsigned SR1		:1;
				unsigned SR0		:1;
				unsigned XOF		:1;
				unsigned RESERVED1	:2;
				unsigned KSR		:1;
				unsigned RR3		:1;
				unsigned RR2		:1;
				unsigned RR1		:1;
				unsigned RR0		:1;
				unsigned DR3		:1;
				unsigned DR2		:1;
				unsigned DR1		:1;
				unsigned DR0		:1;
				unsigned AR3		:1;
				unsigned AR2		:1;
				unsigned AR1		:1;
				unsigned AR0		:1;
				unsigned SL3		:1;
				unsigned SL2		:1;
				unsigned SL1		:1;
				unsigned SL0		:1;
				unsigned TL5		:1;
				unsigned TL4		:1;
				unsigned TL3		:1;
				unsigned TL2		:1;
				unsigned TL1		:1;
				unsigned TL0		:1;
				unsigned KSL1		:1;
				unsigned KSL0		:1;
				unsigned RESERVED2	:1;
				unsigned DAM1		:1;
				unsigned DAM0		:1;
				unsigned EAM		:1;
				unsigned RESERVED3	:1;
				unsigned DVB1		:1;
				unsigned DVB0		:1;
				unsigned EVB		:1;
				unsigned MULTI3		:1;
				unsigned MULTI2		:1;
				unsigned MULTI1		:1;
				unsigned MULTI0		:1;
				unsigned RESERVED4	:1;
				unsigned DT2		:1;
				unsigned DT1		:1;
				unsigned DT0		:1;
				unsigned WS4		:1;
				unsigned WS3		:1;
				unsigned WS2		:1;
				unsigned WS1		:1;
				unsigned WS0		:1;
				unsigned FB2		:1;
				unsigned FB1		:1;
				unsigned FB0		:1;
			} BIT;	
		} OP4;
	} Params;
};

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


#endif