#ifndef Z80_MNE_H
#define Z80_MNE_H

#include "stdio.h"

#define CDNUM 256
#define NLENGTH 32

#define BASIC_1B_EX_MEMBERS 24
#define BASIC_2B_EX_MEMBERS 25

#define DDXX_1B_EX_MEMBERS 23
#define DDXX_2B_EX_MEMBERS 4

#define EDXX_2B_EX_MEMBERS 6

#define FDXX_1B_EX_MEMBERS 23
#define FDXX_2B_EX_MEMBERS 4

#define IS_EXCEPT_NUMBER 1
#define NOT_EXCEPT_NUMBER 0

int BASIC_MN_1BYTE[BASIC_1B_EX_MEMBERS] = { 0x06 , 0x0E , 0x10 , 0x16 , 0x18 , 0x1E , 0x20 , 0x26 ,
											0x28 , 0x2E , 0x30 , 0x36 , 0x38 , 0x3E , 0xC6 , 0xCE ,
											0xD3 , 0xD6 , 0xDB , 0xDE , 0xE6 , 0xEE , 0xF6 , 0xFE };

int BASIC_MN_2BYTE[BASIC_2B_EX_MEMBERS] = { 0x01 , 0x11 , 0x21 , 0x22 , 0x2A , 0x31 , 0x32 , 0x3A ,
											0xC2 , 0xC3 , 0xC4 , 0xCA , 0xCC , 0xCD , 0xD2 , 0xD4 ,
											0xDA , 0xDC , 0xE2 , 0xE4 , 0xEA , 0xF2 , 0xF4 , 0xFA , 0xFC };

int DDXX_MN_1B[DDXX_1B_EX_MEMBERS]		= { 0x34 , 0x46 , 0x4E , 0x56 , 0x5E , 0x66 , 0x6E , 0x70 ,
											0x71 , 0x72 , 0x73 , 0x74 , 0x75 , 0x77 , 0x7E , 0x86 ,
											0x8E , 0x96 , 0x9E , 0xA6 , 0xAE , 0xB6 , 0xBE };

int DDXX_MN_2B[DDXX_2B_EX_MEMBERS]		= { 0x21 , 0x22 , 0x2A , 0x36 };

int EDXX_MN_2B[EDXX_2B_EX_MEMBERS]		= { 0x43 , 0x4B , 0x53 , 0x5B , 0x73 , 0x7B };

int FDXX_MN_1B[FDXX_1B_EX_MEMBERS]		= { 0x34 , 0x46 , 0x4E , 0x56 , 0x5E , 0x66 , 0x6E , 0x70 ,
											0x71 , 0x72 , 0x73 , 0x74 , 0x75 , 0x77 , 0x7E , 0x86 ,
											0x8E , 0x96 , 0x9E , 0xA6 , 0xAE , 0xB6 , 0xBE };

int FDXX_MN_2B[FDXX_2B_EX_MEMBERS]		= { 0x21 , 0x22 , 0x2A , 0x36 };

char basicMnemonic[CDNUM][NLENGTH] = 
{
	"NOP",						//00
	"LD	BC, 0x%02X%02X",		//01
	"LD	(BC), A",				//02
	"INC	BC",				//03
	"INC	B",					//04
	"DEC	B",					//05
	"LD	B, 0x%02X",				//06
	"RLCA",						//07
	"EX	AF, AF'",				//08
	"ADD	HL, BC",			//09
	"LD	A, (BC)",				//0A
	"DEC	BC",				//0B
	"INC	C",					//0C
	"DEC	C",					//0D
	"LD	C, 0x%02X",				//0E
	"RRCA",						//0F

	"DJNZ	0x%02X",			//10
	"LD	DE, 0x%02X%02X",		//11
	"LD	(DE), A",				//12
	"INC	DE",				//13
	"INC	D",					//14
	"DEC	D",					//15
	"LD	D, 0x%02X",				//16
	"RLA",						//17
	"JR	0x%02X",				//18
	"ADD	HL, DE",			//19
	"LD	A, (DE)",				//1A
	"DEC	DE",				//1B
	"INC	E",					//1C
	"DEC	E",					//1D
	"LD	E, 0x%02X",				//1E
	"RRA",						//1F

	"JR	NZ, 0x%02X",			//20
	"LD	HL, 0x%02X%02X",		//21
	"LD	(0x%02X%02X), HL",		//22
	"INC	HL",				//23
	"INC	H",					//24
	"DEC	H",					//25
	"LD	H, 0x%02X",				//26
	"DAA",						//27
	"JR	Z, 0x%02X",				//28
	"ADD	HL, HL",			//29
	"LD	HL, (0x%02X%02X)",		//2A
	"DEC	HL",				//2B
	"INC	L",					//2C
	"DEC	L",					//2D
	"LD	L, 0x%02X",				//2E
	"CPL",						//2F

	"JR	NC, 0x%02X",			//30
	"LD	SP, 0x%02X%02X",		//31
	"LD	(0x%02X%02X), A",		//32
	"INC	SP",				//33
	"INC	(HL)",				//34
	"DEC	(HL)",				//35
	"LD	(HL), 0x%02X",			//36
	"SCF",						//37
	"JR	C, 0x%02X",				//38
	"ADD	HL, SP",			//39
	"LD	A, (0x%02X%02X)",		//3A
	"DEC	SP",				//3B
	"INC	A",					//3C
	"DEC	A",					//3D
	"LD	A, 0x%02X",				//3E
	"CCF",						//3F

	"LD	B, B",					//40
	"LD	B, C",					//41
	"LD	B, D",					//42
	"LD	B, E",					//43
	"LD	B, H",					//44
	"LD	B, L",					//45
	"LD	B, (HL)",				//46
	"LD	B, A",					//47
	"LD	C, B",					//48
	"LD	C, C",					//49
	"LD	C, D",					//4A
	"LD	C, E",					//4B
	"LD	C, H",					//4C
	"LD	C, L",					//4D
	"LD	C, (HL)",				//4E
	"LD	C, A",					//4F

	"LD	D, B",					//50
	"LD	D, C",					//51
	"LD	D, D",					//52
	"LD	D, E",					//53
	"LD	D, H",					//54
	"LD	D, L",					//55
	"LD	D, (HL)",				//56
	"LD	D, A",					//57
	"LD	E, B",					//58
	"LD	E, C",					//59
	"LD	E, D",					//5A
	"LD	E,	E",					//5B
	"LD	E, H",					//5C
	"LD	E, L",					//5D
	"LD	E, (HL)",				//5E
	"LD	E, A",					//5F

	"LD	H, B",					//60
	"LD	H, C",					//61
	"LD	H, D",					//62
	"LD	H, E",					//63
	"LD	H, H",					//64
	"LD	H, L",					//65
	"LD	H, (HL)",				//66
	"LD	H, A",					//67
	"LD	L ,B",					//68
	"LD	L, C",					//69
	"LD	L, D",					//6A
	"LD	L, E",					//6B
	"LD	L, H",					//6C
	"LD	L, L",					//6D
	"LD	L, (HL)",				//6E
	"LD	L, A",					//6F

	"LD	(HL), B",				//70
	"LD	(HL), C",				//71
	"LD	(HL), D",				//72
	"LD	(HL), E",				//73
	"LD	(HL), H",				//74
	"LD	(HL), L",				//75
	"HALT",						//76
	"LD	(HL), A",				//77
	"LD	A, B",					//78
	"LD	A, C",					//79
	"LD	A, D",					//7A
	"LD	A, E",					//7B
	"LD	A, H",					//7C
	"LD	A, L",					//7D
	"LD	A, (HL)",				//7E
	"LD	A, A",					//7F

	"ADD	A, B",				//80
	"ADD	A, C",				//81
	"ADD	A, D",				//82
	"ADD	A, E",				//83
	"ADD	A, H",				//84
	"ADD	A, L",				//85
	"ADD	A, (HL)",			//86
	"ADD	A, A",				//87
	"ADC	A, B",				//88
	"ADC	A, C",				//89
	"ADC	A, D",				//8A
	"ADC	A, E",				//8B
	"ADC	A, H",				//8C
	"ADC	A, L",				//8D
	"ADC	A, (HL)",			//8E
	"ADC	A, A",				//8F

	"SUB	B",					//90
	"SUB	C",					//91
	"SUB	D",					//92
	"SUB	E",					//93
	"SUB	H",					//94
	"SUB	L",					//95
	"SUB	(HL)",				//96
	"SUB	A",					//97
	"SBC	A, B",				//98
	"SBC	A, C",				//99
	"SBC	A, D",				//9A
	"SBC	A, E",				//9B
	"SBC	A, H",				//9C
	"SBC	A, L",				//9D
	"SBC	A, (HL)",			//9E
	"SBC	A, A",				//9F

	"AND	B",					//A0
	"AND	C",					//A1
	"AND	D",					//A2
	"AND	E",					//A3
	"AND	H",					//A4
	"AND	L",					//A5
	"AND	(HL)",				//A6
	"AND	A",					//A7
	"XOR	B",					//A8
	"XOR	C",					//A9
	"XOR	D",					//AA
	"XOR	E",					//AB
	"XOR	H",					//AC
	"XOR	L",					//AD
	"XOR	(HL)",				//AE
	"XOR	A",					//AF

	"OR	B",						//B0
	"OR	C",						//B1
	"OR	D",						//B2
	"OR	E",						//B3
	"OR	H",						//B4
	"OR	L",						//B5
	"OR	(HL)",					//B6
	"OR	A",						//B7
	"CP	B",						//B8
	"CP	C",						//B9
	"CP	D",						//BA
	"CP	E",						//BB
	"CP	H",						//BC
	"CP	L",						//BD
	"CP	(HL)",					//BE
	"CP	A",						//BF

	"RET	NZ",				//C0
	"POP	BC",				//C1
	"JP	NZ, 0x%02X%02X",		//C2
	"JP	0x%02X%02X",			//C3
	"CALL	NZ, 0x%02X%02X",	//C4
	"PUSH	BC",				//C5
	"ADD	A, 0x%02X",			//C6
	"RST	00H",				//C7
	"RET	Z",					//C8
	"RET",						//C9
	"JP	Z, 0x%02X%02X",			//CA
	"xx",						//CB
	"CALL	Z, 0x%02X%02X",		//CC
	"CALL	0x%02X%02X",		//CD
	"ADC	A, 0x%02X",			//CE
	"RST	08H",				//CF

	"RET	NC",				//D0
	"POP	DE",				//D1
	"JP	NC, 0x%02X%02X",		//D2
	"OUT	0x%02X, A",			//D3
	"CALL	NC, 0x%02X%02X",	//D4
	"PUSH	DE",				//D5
	"SUB	0x%02X",			//D6
	"RST	10H",				//D7
	"RET	C",					//D8
	"EXX",						//D9
	"JP	C, 0x%02X%02X",			//DA
	"IN	A, 0x%02X",				//DB
	"CALL	C, 0x%02X%02X",		//DC
	"xx",						//DD
	"SBC	A, 0x%02X",			//DE
	"RST	18H",				//DF

	"RET	PO",				//E0
	"POP	HL",				//E1
	"JP	PO, 0x%02X%02X",		//E2
	"EX	(SP), HL",				//E3
	"CALL	PO, 0x%02X%02X",	//E4
	"PUSH	HL",				//E5
	"AND	0x%02X",			//E6
	"RST	20H",				//E7
	"RET	PE",				//E8
	"JP	(HL)",					//E9
	"JP	PE, 0x%02X%02X",		//EA
	"EX	DE, HL",				//EB
	"CALL	PE, NN",			//EC
	"xx",						//ED
	"XOR	0x%02X",			//EE
	"RST	28H",				//EF

	"RET	P",					//F0
	"POP	AF",				//F1
	"JP	P, 0x%02X%02X",			//F2
	"DI",						//F3
	"CALL	P, 0x%02X%02X",		//F4
	"PUSH	AF",				//F5
	"OR	0x%02X",				//F6
	"RST	30H",				//F7
	"RET	M",					//F8
	"LD	SP, HL",				//F9
	"JP	M, 0x%02X%02X",			//FA
	"EI",						//FB
	"CALL	M, 0x%02X%02X",		//FC
	"xx",						//FD
	"CP	0x%02X",				//FE
	"RST	38H"				//FF
};

char CBxxMnemonic[CDNUM][NLENGTH] = 
{
	"RLC	B",					//CB 00
	"RLC	C",					//CB 01
	"RLC	D",					//CB 02
	"RLC	E",					//CB 03
	"RLC	H",					//CB 04
	"RLC	L",					//CB 05
	"RLC	(HL)",				//CB 06
	"RLC	A",					//CB 07

	"RRC	B",					//CB 08
	"RRC	C",					//CB 09
	"RRC	D",					//CB 0A
	"RRC	E",					//CB 0B
	"RRC	H",					//CB 0C
	"RRC	L",					//CB 0D
	"RRC	(HL)",				//CB 0E
	"RRC	A",					//CB 0F

	"RL	B",						//CB 10
	"RL	C",						//CB 11
	"RL	D",						//CB 12
	"RL	E",						//CB 13
	"RL	H",						//CB 14
	"RL	L",						//CB 15
	"RL	(HL)",					//CB 16
	"RL	A",						//CB 17
		
	"RR	B",						//CB 18
	"RR	C",						//CB 19
	"RR	D",						//CB 1A
	"RR	E",						//CB 1B
	"RR	H",						//CB 1C
	"RR	L",						//CB 1D
	"RR	(HL)",					//CB 1E
	"RR	A",						//CB 1F

	"SLA	B",					//CB 20
	"SLA	C",					//CB 21
	"SLA	D",					//CB 22
	"SLA	E",					//CB 23
	"SLA	H",					//CB 24
	"SLA	L",					//CB 25
	"SLA	(HL)",				//CB 26
	"SLA	A",					//CB 27

	"SRA	B",					//CB 28
	"SRA	C",					//CB 29
	"SRA	D",					//CB 2A
	"SRA	E",					//CB 2B
	"SRA	H",					//CB 2C
	"SRA	L",					//CB 2D
	"SRA	(HL)",				//CB 2E
	"SRA	A",					//CB 2F

	"[undefined]",				//CB 30
	"[undefined]",				//CB 31
	"[undefined]",				//CB 32
	"[undefined]",				//CB 33
	"[undefined]",				//CB 34
	"[undefined]",				//CB 35
	"[undefined]",				//CB 36
	"[undefined]",				//CB 37

	"SRL	B",					//CB 38
	"SRL	C",					//CB 39
	"SRL	D",					//CB 3A
	"SRL	E",					//CB 3B
	"SRL	H",					//CB 3C
	"SRL	L",					//CB 3D
	"SRL	(HL)",				//CB 3E
	"SRL	A",					//CB 3F

	"BIT	0, B",				//CB 40
	"BIT	0, C",				//CB 41
	"BIT	0, D",				//CB 42
	"BIT	0, E",				//CB 43
	"BIT	0, H",				//CB 44
	"BIT	0, L",				//CB 45
	"BIT	0, (HL)",			//CB 46
	"BIT	0, A",				//CB 47

	"BIT	1, B",				//CB 48
	"BIT	1, C",				//CB 49
	"BIT	1, D",				//CB 4A
	"BIT	1, E",				//CB 4B
	"BIT	1, H",				//CB 4C
	"BIT	1, L",				//CB 4D
	"BIT	1, (HL)",			//CB 4E
	"BIT	1, A",				//CB 4F

	"BIT	2, B",				//CB 50
	"BIT	2, C",				//CB 51
	"BIT	2, D",				//CB 52
	"BIT	2, E",				//CB 53
	"BIT	2, H",				//CB 54
	"BIT	2, L",				//CB 55
	"BIT	2, (HL)",			//CB 56
	"BIT	2, A",				//CB 57

	"BIT	3, B",				//CB 58
	"BIT	3, C",				//CB 59
	"BIT	3, D",				//CB 5A
	"BIT	3, E",				//CB 5B
	"BIT	3, H",				//CB 5C
	"BIT	3, L",				//CB 5D
	"BIT	3, (HL)",			//CB 5E
	"BIT	3, A",				//CB 5F

	"BIT	4, B",				//CB 60
	"BIT	4, C",				//CB 61
	"BIT	4, D",				//CB 62
	"BIT	4, E",				//CB 63
	"BIT	4, H",				//CB 64
	"BIT	4, L",				//CB 65
	"BIT	4, (HL)",			//CB 66
	"BIT	4, A",				//CB 67

	"BIT	5, B",				//CB 68
	"BIT	5, C",				//CB 69
	"BIT	5, D",				//CB 6A
	"BIT	5, E",				//CB 6B
	"BIT	5, H",				//CB 6C
	"BIT	5, L",				//CB 6D
	"BIT	5, (HL)",			//CB 6E
	"BIT	5, A",				//CB 6F

	"BIT	6, B",				//CB 70
	"BIT	6, C",				//CB 71
	"BIT	6, D",				//CB 72
	"BIT	6, E",				//CB 73
	"BIT	6, H",				//CB 74
	"BIT	6, L",				//CB 75
	"BIT	6, (HL)",			//CB 76
	"BIT	6, A",				//CB 77

	"BIT	7, B",				//CB 78
	"BIT	7, C",				//CB 79
	"BIT	7, D",				//CB 7A
	"BIT	7, E",				//CB 7B
	"BIT	7, H",				//CB 7C
	"BIT	7, L",				//CB 7D
	"BIT	7, (HL)",			//CB 7E
	"BIT	7, A",				//CB 7F

	"RES	0, B",				//CB 80
	"RES	0, C",				//CB 81
	"RES	0, D",				//CB 82
	"RES	0, E",				//CB 83
	"RES	0, H",				//CB 84
	"RES	0, L",				//CB 85
	"RES	0, (HL)",			//CB 86
	"RES	0, A",				//CB 87

	"RES	1, B",				//CB 88
	"RES	1, C",				//CB 89
	"RES	1, D",				//CB 8A
	"RES	1, E",				//CB 8B
	"RES	1, H",				//CB 8C
	"RES	1, L",				//CB 8D
	"RES	1, (HL)",			//CB 8E
	"RES	1, A",				//CB 8F

	"RES	2, B",				//CB 90
	"RES	2, C",				//CB 91
	"RES	2, D",				//CB 92
	"RES	2, E",				//CB 93
	"RES	2, H",				//CB 94
	"RES	2, L",				//CB 95
	"RES	2, (HL)",			//CB 96
	"RES	2, A",				//CB 97

	"RES	3, B",				//CB 98
	"RES	3, C",				//CB 99
	"RES	3, D",				//CB 9A
	"RES	3, E",				//CB 9B
	"RES	3, H",				//CB 9C
	"RES	3, L",				//CB 9D
	"RES	3, (HL)",			//CB 9E
	"RES	3, A",				//CB 9F

	"RES	4, B",				//CB A0
	"RES	4, C",				//CB A1
	"RES	4, D",				//CB A2
	"RES	4, E",				//CB A3
	"RES	4, H",				//CB A4
	"RES	4, L",				//CB A5
	"RES	4, (HL)",			//CB A6
	"RES	4, A",				//CB A7

	"RES	5, B",				//CB A8
	"RES	5, C",				//CB A9
	"RES	5, D",				//CB AA
	"RES	5, E",				//CB AB
	"RES	5, H",				//CB AC
	"RES	5, L",				//CB AD
	"RES	5, (HL)",			//CB AE
	"RES	5, A",				//CB AF

	"RES	6, B",				//CB B0
	"RES	6, C",				//CB B1
	"RES	6, D",				//CB B2
	"RES	6, E",				//CB B3
	"RES	6, H",				//CB B4
	"RES	6, L",				//CB B5
	"RES	6, (HL)",			//CB B6
	"RES	6, A",				//CB B7

	"RES	7, B",				//CB B8
	"RES	7, C",				//CB B9
	"RES	7, D",				//CB BA
	"RES	7, E",				//CB BB
	"RES	7, H",				//CB BC
	"RES	7, L",				//CB BD
	"RES	7, (HL)",			//CB BE
	"RES	7, A",				//CB BF

	"SET	0, B",				//CB C0
	"SET	0, C",				//CB C1
	"SET	0, D",				//CB C2
	"SET	0, E",				//CB C3
	"SET	0, H",				//CB C4
	"SET	0, L",				//CB C5
	"SET	0, (HL)",			//CB C6
	"SET	0, A",				//CB C7

	"SET	1, B",				//CB C8
	"SET	1, C",				//CB C9
	"SET	1, D",				//CB CA
	"SET	1, E",				//CB CB
	"SET	1, H",				//CB CC
	"SET	1, L",				//CB CD
	"SET	1, (HL)",			//CB CE
	"SET	1, A",				//CB CF

	"SET	2, B",				//CB D0
	"SET	2, C",				//CB D1
	"SET	2, D",				//CB D2
	"SET	2, E",				//CB D3
	"SET	2, H",				//CB D4
	"SET	2, L",				//CB D5
	"SET	2, (HL)",			//CB D6
	"SET	2, A",				//CB D7

	"SET	3, B",				//CB D8
	"SET	3, C",				//CB D9
	"SET	3, D",				//CB DA
	"SET	3, E",				//CB DB
	"SET	3, H",				//CB DC
	"SET	3, L",				//CB DD
	"SET	3, (HL)",			//CB DE
	"SET	3, A",				//CB DF

	"SET	4, B",				//CB E0
	"SET	4, C",				//CB E1
	"SET	4, D",				//CB E2
	"SET	4, E",				//CB E3
	"SET	4, H",				//CB E4
	"SET	4, L",				//CB E5
	"SET	4, (HL)",			//CB E6
	"SET	4, A",				//CB E7

	"SET	5, B",				//CB E8
	"SET	5, C",				//CB E9
	"SET	5, D",				//CB EA
	"SET	5, E",				//CB EB
	"SET	5, H",				//CB EC
	"SET	5, L",				//CB ED
	"SET	5, (HL)",			//CB EE
	"SET	5, A",				//CB EF

	"SET	6, B",				//CB F0
	"SET	6, C",				//CB F1
	"SET	6, D",				//CB F2
	"SET	6, E",				//CB F3
	"SET	6, H",				//CB F4
	"SET	6, L",				//CB F5
	"SET	6, (HL)",			//CB F6
	"SET	6, A",				//CB F7

	"SET	7, B",				//CB F8
	"SET	7, C",				//CB F9
	"SET	7, D",				//CB FA
	"SET	7, E",				//CB FB
	"SET	7, H",				//CB FC
	"SET	7, L",				//CB FD
	"SET	7, (HL)",			//CB FE
	"SET	7, A"				//CB FF
};

char DDxxMnemonic[CDNUM][NLENGTH] = 
{
	"[undefined]",				//DD 00
	"[undefined]",				//DD 01
	"[undefined]",				//DD 02
	"[undefined]",				//DD 03
	"[undefined]",				//DD 04
	"[undefined]",				//DD 05
	"[undefined]",				//DD 06
	"[undefined]",				//DD 07

	"[undefined]",				//DD 08
	"ADD	IX, BC",			//DD 09
	"[undefined]",				//DD 0A
	"[undefined]",				//DD 0B
	"[undefined]",				//DD 0C
	"[undefined]",				//DD 0D
	"[undefined]",				//DD 0E
	"[undefined]",				//DD 0F

	"[undefined]",				//DD 10
	"[undefined]",				//DD 11
	"[undefined]",				//DD 12
	"[undefined]",				//DD 13
	"[undefined]",				//DD 14
	"[undefined]",				//DD 15
	"[undefined]",				//DD 16
	"[undefined]",				//DD 17

	"[undefined]",				//DD 18
	"ADD	, IX, DE",			//DD 19
	"[undefined]",				//DD 1A
	"[undefined]",				//DD 1B
	"[undefined]",				//DD 1C
	"[undefined]",				//DD 1D
	"[undefined]",				//DD 1E
	"[undefined]",				//DD 1F

	"[undefined]",				//DD 20
	"LD	IX, 0x%02X%02X",		//DD 21
	"LD	(0x%02X%02X), IX",		//DD 22
	"INC	IX",				//DD 23
	"[undefined]",				//DD 24
	"[undefined]",				//DD 25
	"[undefined]",				//DD 26
	"[undefined]",				//DD 27

	"[undefined]",				//DD 28
	"ADD	IX, IX",			//DD 29
	"LD	IX, (0x%02X%02X)",		//DD 2A
	"DEC	IX",				//DD 2B
	"[undefined]",				//DD 2C
	"[undefined]",				//DD 2D
	"[undefined]",				//DD 2E
	"[undefined]",				//DD 2F

	"[undefined]",				//DD 30
	"[undefined]",				//DD 31
	"[undefined]",				//DD 32
	"[undefined]",				//DD 33
	"INC	(IX + 0x%02X)",		//DD 34
	"DEC	(IX+D)",			//DD 35
	"LD	(IX+0x%02X), 0x%02X",	//DD 36
	"[undefined]",				//DD 37

	"[undefined]",				//DD 38
	"ADD	IX, SP",			//DD 39
	"[undefined]",				//DD 3A
	"[undefined]",				//DD 3B
	"[undefined]",				//DD 3C
	"[undefined]",				//DD 3D
	"[undefined]",				//DD 3E
	"[undefined]",				//DD 3F

	"[undefined]",				//DD 40
	"[undefined]",				//DD 41
	"[undefined]",				//DD 42
	"[undefined]",				//DD 43
	"[undefined]",				//DD 44
	"[undefined]",				//DD 45
	"LD	B, (IX+0x%02X)",		//DD 46
	"[undefined]",				//DD 47

	"[undefined]",				//DD 48
	"[undefined]",				//DD 49
	"[undefined]",				//DD 4A
	"[undefined]",				//DD 4B
	"[undefined]",				//DD 4C
	"[undefined]",				//DD 4D
	"LD	C, (IX+0x%02X)",		//DD 4E
	"[undefined]",				//DD 4F

	"[undefined]",				//DD 50
	"[undefined]",				//DD 51
	"[undefined]",				//DD 52
	"[undefined]",				//DD 53
	"[undefined]",				//DD 54
	"[undefined]",				//DD 55
	"LD	D, (IX+0x%02X)",		//DD 56
	"[undefined]",				//DD 57

	"[undefined]",				//DD 58
	"[undefined]",				//DD 59
	"[undefined]",				//DD 5A
	"[undefined]",				//DD 5B
	"[undefined]",				//DD 5C
	"[undefined]",				//DD 5D
	"LD	E, (IX+0x%02X)",		//DD 5E
	"[undefined]",				//DD 5F

	"[undefined]",				//DD 60
	"[undefined]",				//DD 61
	"[undefined]",				//DD 62
	"[undefined]",				//DD 63
	"[undefined]",				//DD 64
	"[undefined]",				//DD 65
	"LD	H, (IX+0x%02X)",		//DD 66
	"[undefined]",				//DD 67

	"[undefined]",				//DD 68
	"[undefined]",				//DD 69
	"[undefined]",				//DD 6A
	"[undefined]",				//DD 6B
	"[undefined]",				//DD 6C
	"[undefined]",				//DD 6D
	"LD	L, (IX+0x%02X)",		//DD 6E
	"[undefined]",				//DD 6F

	"LD	(IX+0x%02X), B",		//DD 70
	"LD	(IX+0x%02X), C",		//DD 71
	"LD	(IX+0x%02X), D",		//DD 72
	"LD	(IX+0x%02X), E",		//DD 73
	"LD	(IX+0x%02X), H",		//DD 74
	"LD	(IX+0x%02X), L",		//DD 75
	"[undefined]",				//DD 76
	"LD	(IX+0x%02X), A",		//DD 77

	"[undefined]",				//DD 78
	"[undefined]",				//DD 79
	"[undefined]",				//DD 7A
	"[undefined]",				//DD 7B
	"[undefined]",				//DD 7C
	"[undefined]",				//DD 7D
	"LD	A, (IX+0x%02X)",		//DD 7E
	"[undefined]",				//DD 7F

	"[undefined]",				//DD 80
	"[undefined]",				//DD 81
	"[undefined]",				//DD 82
	"[undefined]",				//DD 83
	"[undefined]",				//DD 84
	"[undefined]",				//DD 85
	"ADD	A, (IX+0x%02X)",	//DD 86
	"[undefined]",				//DD 87

	"[undefined]",				//DD 88
	"[undefined]",				//DD 89
	"[undefined]",				//DD 8A
	"[undefined]",				//DD 8B
	"[undefined]",				//DD 8C
	"[undefined]",				//DD 8D
	"ADC	A, (IX+0x%02X)",	//DD 8E
	"[undefined]",				//DD 8F

	"[undefined]",				//DD 90
	"[undefined]",				//DD 91
	"[undefined]",				//DD 92
	"[undefined]",				//DD 93
	"[undefined]",				//DD 94
	"[undefined]",				//DD 95
	"SUB	A, (IX+0x%02X)",	//DD 96
	"[undefined]",				//DD 97

	"[undefined]",				//DD 98
	"[undefined]",				//DD 99
	"[undefined]",				//DD 9A
	"[undefined]",				//DD 9B
	"[undefined]",				//DD 9C
	"[undefined]",				//DD 9D
	"SBC	A, (IX+0x%02X)",	//DD 9E
	"[undefined]",				//DD 9F

	"[undefined]",				//DD A0
	"[undefined]",				//DD A1
	"[undefined]",				//DD A2
	"[undefined]",				//DD A3
	"[undefined]",				//DD A4
	"[undefined]",				//DD A5
	"AND	(IX+0x%02X)",		//DD A6
	"[undefined]",				//DD A7

	"[undefined]",				//DD A8
	"[undefined]",				//DD A9
	"[undefined]",				//DD AA
	"[undefined]",				//DD AB
	"[undefined]",				//DD AC
	"[undefined]",				//DD AD
	"XOR	(IX+0x%02X)",		//DD AE
	"[undefined]",				//DD AF

	"[undefined]",				//DD B0
	"[undefined]",				//DD B1
	"[undefined]",				//DD B2
	"[undefined]",				//DD B3
	"[undefined]",				//DD B4
	"[undefined]",				//DD B5
	"OR	(IX+0x%02X)",			//DD B6
	"[undefined]",				//DD B7

	"[undefined]",				//DD B8
	"[undefined]",				//DD B9
	"[undefined]",				//DD BA
	"[undefined]",				//DD BB
	"[undefined]",				//DD BC
	"[undefined]",				//DD BD
	"CP	(IX+0x%02X)",			//DD BE
	"[undefined]",				//DD BF

	"[undefined]",				//DD C0
	"[undefined]",				//DD C1
	"[undefined]",				//DD C2
	"[undefined]",				//DD C3
	"[undefined]",				//DD C4
	"[undefined]",				//DD C5
	"[undefined]",				//DD C6
	"[undefined]",				//DD C7

	"[undefined]",				//DD C8
	"[undefined]",				//DD C9
	"[undefined]",				//DD CA
	"xx",						//DD CB
	"[undefined]",				//DD CC
	"[undefined]",				//DD CD
	"[undefined]",				//DD CE
	"[undefined]",				//DD CF

	"[undefined]",				//DD D0
	"[undefined]",				//DD D1
	"[undefined]",				//DD D2
	"[undefined]",				//DD D3
	"[undefined]",				//DD D4
	"[undefined]",				//DD D5
	"[undefined]",				//DD D6
	"[undefined]",				//DD D7

	"[undefined]",				//DD D8
	"[undefined]",				//DD D9
	"[undefined]",				//DD DA
	"[undefined]",				//DD DB
	"[undefined]",				//DD DC
	"[undefined]",				//DD DD
	"[undefined]",				//DD DE
	"[undefined]",				//DD DF

	"[undefined]",				//DD E0
	"POP	IX",				//DD E1
	"[undefined]",				//DD E2
	"EX	(SP), IX",				//DD E3
	"[undefined]",				//DD E4
	"PUSH	IX",				//DD E5
	"[undefined]",				//DD E6
	"[undefined]",				//DD E7

	"[undefined]",				//DD E8
	"JP	(IX)",					//DD E9
	"[undefined]",				//DD EA
	"[undefined]",				//DD EB
	"[undefined]",				//DD EC
	"[undefined]",				//DD ED
	"[undefined]",				//DD EE
	"[undefined]",				//DD EF

	"[undefined]",				//DD F0
	"[undefined]",				//DD F1
	"[undefined]",				//DD F2
	"[undefined]",				//DD F3
	"[undefined]",				//DD F4
	"[undefined]",				//DD F5
	"[undefined]",				//DD F6
	"[undefined]",				//DD F7

	"[undefined]",				//DD F8
	"LD	SP, IX",				//DD F9
	"[undefined]",				//DD FA
	"[undefined]",				//DD FB
	"[undefined]",				//DD FC
	"[undefined]",				//DD FD
	"[undefined]",				//DD FE
	"[undefined]"				//DD FF
};

char EDxxMnemonic[CDNUM][NLENGTH] = 
{
	"[undefined]",				//ED 00
	"[undefined]",				//ED 01
	"[undefined]",				//ED 02
	"[undefined]",				//ED 03
	"[undefined]",				//ED 04
	"[undefined]",				//ED 05
	"[undefined]",				//ED 06
	"[undefined]",				//ED 07

	"[undefined]",				//ED 08
	"[undefined]",				//ED 09
	"[undefined]",				//ED 0A
	"[undefined]",				//ED 0B
	"[undefined]",				//ED 0C
	"[undefined]",				//ED 0D
	"[undefined]",				//ED 0E
	"[undefined]",				//ED 0F

	"[undefined]",				//ED 10
	"[undefined]",				//ED 11
	"[undefined]",				//ED 12
	"[undefined]",				//ED 13
	"[undefined]",				//ED 14
	"[undefined]",				//ED 15
	"[undefined]",				//ED 16
	"[undefined]",				//ED 17

	"[undefined]",				//ED 18
	"[undefined]",				//ED 19
	"[undefined]",				//ED 1A
	"[undefined]",				//ED 1B
	"[undefined]",				//ED 1C
	"[undefined]",				//ED 1D
	"[undefined]",				//ED 1E
	"[undefined]",				//ED 1F

	"[undefined]",				//ED 20
	"[undefined]",				//ED 21
	"[undefined]",				//ED 22
	"[undefined]",				//ED 23
	"[undefined]",				//ED 24
	"[undefined]",				//ED 25
	"[undefined]",				//ED 26
	"[undefined]",				//ED 27

	"[undefined]",				//ED 28
	"[undefined]",				//ED 29
	"[undefined]",				//ED 2A
	"[undefined]",				//ED 2B
	"[undefined]",				//ED 2C
	"[undefined]",				//ED 2D
	"[undefined]",				//ED 2E
	"[undefined]",				//ED 2F

	"[undefined]",				//ED 30
	"[undefined]",				//ED 31
	"[undefined]",				//ED 32
	"[undefined]",				//ED 33
	"[undefined]",				//ED 34
	"[undefined]",				//ED 35
	"[undefined]",				//ED 36
	"[undefined]",				//ED 37

	"[undefined]",				//ED 38
	"[undefined]",				//ED 39
	"[undefined]",				//ED 3A
	"[undefined]",				//ED 3B
	"[undefined]",				//ED 3C
	"[undefined]",				//ED 3D
	"[undefined]",				//ED 3E
	"[undefined]",				//ED 3F

	"IN	B, (C)",				//ED 40
	"OUT	(C), B",			//ED 41
	"SBC	HL, BC",			//ED 42
	"LD	(0x%02X%02X), BC",		//ED 43
	"NEG",						//ED 44
	"RETN",						//ED 45
	"IM	0",						//ED 46
	"LD	I, A",					//ED 47

	"IN	C, (C)",				//ED 48
	"OUT	(C), C",			//ED 49
	"ADC	HL, BC",			//ED 4A
	"LD	BC, (0x%02X%02X)",		//ED 4B
	"[undefined]",				//ED 4C
	"RETI",						//ED 4D
	"[undefined]",				//ED 4E
	"LD	R, A",					//ED 4F

	"IN	D, (C)",				//ED 50
	"OUT	(C), D",			//ED 51
	"SBC	HL, DE",			//ED 52
	"LD	(0x%02X%02X), DE",		//ED 53
	"[undefined]",				//ED 54
	"[undefined]",				//ED 55
	"IM	1",						//ED 56
	"LD	A, I",					//ED 57

	"IN	E, (C)",				//ED 58
	"OUT	(C), E",			//ED 59
	"ADC	HL, DE",			//ED 5A
	"LD	DE, (0x%02X%02X)",		//ED 5B
	"[undefined]",				//ED 5C
	"[undefined]",				//ED 5D
	"IM	2",						//ED 5E
	"LD	A, R",					//ED 5F

	"IN	H, (C)",				//ED 60
	"OUT	(C), H",			//ED 61
	"SBC	HL, HL",			//ED 62
	"[undefined]",				//ED 63
	"[undefined]",				//ED 64
	"[undefined]",				//ED 65
	"[undefined]",				//ED 66
	"RRD",						//ED 67

	"IN	L, (C)",				//ED 68
	"OUT	(C), L",			//ED 69
	"ADC	HL, HL",			//ED 6A
	"[undefined]",				//ED 6B
	"[undefined]",				//ED 6C
	"[undefined]",				//ED 6D
	"[undefined]",				//ED 6E
	"RLD",						//ED 6F

	"[undefined]",				//ED 70
	"[undefined]",				//ED 71
	"SBC	HL, SP",			//ED 72
	"LD	(0x%02X%02X), SP",		//ED 73
	"[undefined]",				//ED 74
	"[undefined]",				//ED 75
	"[undefined]",				//ED 76
	"[undefined]",				//ED 77

	"IN	A, (C)",				//ED 78
	"OUT	(C), A",			//ED 79
	"ADC	HL, SP",			//ED 7A
	"LD	SP, (0x%02X%02X)",		//ED 7B
	"[undefined]",				//ED 7C
	"[undefined]",				//ED 7D
	"[undefined]",				//ED 7E
	"[undefined]",				//ED 7F

	"[undefined]",				//ED 80
	"[undefined]",				//ED 81
	"[undefined]",				//ED 82
	"[undefined]",				//ED 83
	"[undefined]",				//ED 84
	"[undefined]",				//ED 85
	"[undefined]",				//ED 86
	"[undefined]",				//ED 87

	"[undefined]",				//ED 88
	"[undefined]",				//ED 89
	"[undefined]",				//ED 8A
	"[undefined]",				//ED 8B
	"[undefined]",				//ED 8C
	"[undefined]",				//ED 8D
	"[undefined]",				//ED 8E
	"[undefined]",				//ED 8F

	"[undefined]",				//ED 90
	"[undefined]",				//ED 91
	"[undefined]",				//ED 92
	"[undefined]",				//ED 93
	"[undefined]",				//ED 94
	"[undefined]",				//ED 95
	"[undefined]",				//ED 96
	"[undefined]",				//ED 97

	"[undefined]",				//ED 98
	"[undefined]",				//ED 99
	"[undefined]",				//ED 9A
	"[undefined]",				//ED 9B
	"[undefined]",				//ED 9C
	"[undefined]",				//ED 9D
	"[undefined]",				//ED 9E
	"[undefined]",				//ED 9F

	"LDI",						//ED A0
	"CPI",						//ED A1
	"INI",						//ED A2
	"OUTI",						//ED A3
	"[undefined]",				//ED A4
	"[undefined]",				//ED A5
	"[undefined]",				//ED A6
	"[undefined]",				//ED A7

	"LDD",						//ED A8
	"CPD",						//ED A9
	"IND",						//ED AA
	"OUTD",						//ED AB
	"[undefined]",				//ED AC
	"[undefined]",				//ED AD
	"[undefined]",				//ED AE
	"[undefined]",				//ED AF

	"LDIR",						//ED B0
	"CPIR",						//ED B1
	"INIR",						//ED B2
	"OTIR",						//ED B3
	"[undefined]",				//ED B4
	"[undefined]",				//ED B5
	"[undefined]",				//ED B6
	"[undefined]",				//ED B7

	"LDDR",						//ED B8
	"CPDR",						//ED B9
	"INDR",						//ED BA
	"OTDR",						//ED BB
	"[undefined]",				//ED BC
	"[undefined]",				//ED BD
	"[undefined]",				//ED BE
	"[undefined]",				//ED BF

	"[undefined]",				//ED C0
	"[undefined]",				//ED C1
	"[undefined]",				//ED C2
	"[undefined]",				//ED C3
	"[undefined]",				//ED C4
	"[undefined]",				//ED C5
	"[undefined]",				//ED C6
	"[undefined]",				//ED C7

	"[undefined]",				//ED C8
	"[undefined]",				//ED C9
	"[undefined]",				//ED CA
	"[undefined]",				//ED CB
	"[undefined]",				//ED CC
	"[undefined]",				//ED CD
	"[undefined]",				//ED CE
	"[undefined]",				//ED CF

	"[undefined]",				//ED D0
	"[undefined]",				//ED D1
	"[undefined]",				//ED D2
	"[undefined]",				//ED D3
	"[undefined]",				//ED D4
	"[undefined]",				//ED D5
	"[undefined]",				//ED D6
	"[undefined]",				//ED D7

	"[undefined]",				//ED D8
	"[undefined]",				//ED D9
	"[undefined]",				//ED DA
	"[undefined]",				//ED DB
	"[undefined]",				//ED DC
	"[undefined]",				//ED DD
	"[undefined]",				//ED DE
	"[undefined]",				//ED DF

	"[undefined]",				//ED E0
	"[undefined]",				//ED E1
	"[undefined]",				//ED E2
	"[undefined]",				//ED E3
	"[undefined]",				//ED E4
	"[undefined]",				//ED E5
	"[undefined]",				//ED E6
	"[undefined]",				//ED E7

	"[undefined]",				//ED E8
	"[undefined]",				//ED E9
	"[undefined]",				//ED EA
	"[undefined]",				//ED EB
	"[undefined]",				//ED EC
	"[undefined]",				//ED ED
	"[undefined]",				//ED EE
	"[undefined]",				//ED EF

	"[undefined]",				//ED F0
	"[undefined]",				//ED F1
	"[undefined]",				//ED F2
	"[undefined]",				//ED F3
	"[undefined]",				//ED F4
	"[undefined]",				//ED F5
	"[undefined]",				//ED F6
	"[undefined]",				//ED F7

	"[undefined]",				//ED F8
	"[undefined]",				//ED F9
	"[undefined]",				//ED FA
	"[undefined]",				//ED FB
	"[undefined]",				//ED FC
	"[undefined]",				//ED FD
	"[undefined]",				//ED FE
	"[undefined]"				//ED FF
};

char FDxxMnemonic[CDNUM][NLENGTH] = 
{
	"[undefined]",				//FD 00
	"[undefined]",				//FD 01
	"[undefined]",				//FD 02
	"[undefined]",				//FD 03
	"[undefined]",				//FD 04
	"[undefined]",				//FD 05
	"[undefined]",				//FD 06
	"[undefined]",				//FD 07

	"[undefined]",				//FD 08
	"ADD	IY, BC",			//FD 09
	"[undefined]",				//FD 0A
	"[undefined]",				//FD 0B
	"[undefined]",				//FD 0C
	"[undefined]",				//FD 0D
	"[undefined]",				//FD 0E
	"[undefined]",				//FD 0F

	"[undefined]",				//FD 10
	"[undefined]",				//FD 11
	"[undefined]",				//FD 12
	"[undefined]",				//FD 13
	"[undefined]",				//FD 14
	"[undefined]",				//FD 15
	"[undefined]",				//FD 16
	"[undefined]",				//FD 17

	"[undefined]",				//FD 18
	"ADD	, IY, DE",			//FD 19
	"[undefined]",				//FD 1A
	"[undefined]",				//FD 1B
	"[undefined]",				//FD 1C
	"[undefined]",				//FD 1D
	"[undefined]",				//FD 1E
	"[undefined]",				//FD 1F

	"[undefined]",				//FD 20
	"LD	IY, 0x%02X%02X",		//FD 21
	"LD	(0x%02X%02X), IY",		//FD 22
	"INC	IY",				//FD 23
	"[undefined]",				//FD 24
	"[undefined]",				//FD 25
	"[undefined]",				//FD 26
	"[undefined]",				//FD 27

	"[undefined]",				//FD 28
	"ADD	IY, IY",			//FD 29
	"LD	IY, (0x%02X%02X)",		//FD 2A
	"DEC	IY",				//FD 2B
	"[undefined]",				//FD 2C
	"[undefined]",				//FD 2D
	"[undefined]",				//FD 2E
	"[undefined]",				//FD 2F

	"[undefined]",				//FD 30
	"[undefined]",				//FD 31
	"[undefined]",				//FD 32
	"[undefined]",				//FD 33
	"INC	(IY + 0x%02X)",		//FD 34
	"DEC	(IY+D)",			//FD 35
	"LD	(IY+0x%02X), 0x%02X",	//FD 36
	"[undefined]",				//FD 37

	"[undefined]",				//FD 38
	"ADD	IY, SP",			//FD 39
	"[undefined]",				//FD 3A
	"[undefined]",				//FD 3B
	"[undefined]",				//FD 3C
	"[undefined]",				//FD 3D
	"[undefined]",				//FD 3E
	"[undefined]",				//FD 3F

	"[undefined]",				//FD 40
	"[undefined]",				//FD 41
	"[undefined]",				//FD 42
	"[undefined]",				//FD 43
	"[undefined]",				//FD 44
	"[undefined]",				//FD 45
	"LD	B, (IY+0x%02X)",		//FD 46
	"[undefined]",				//FD 47

	"[undefined]",				//FD 48
	"[undefined]",				//FD 49
	"[undefined]",				//FD 4A
	"[undefined]",				//FD 4B
	"[undefined]",				//FD 4C
	"[undefined]",				//FD 4D
	"LD	C, (IY+0x%02X)",		//FD 4E
	"[undefined]",				//FD 4F

	"[undefined]",				//FD 50
	"[undefined]",				//FD 51
	"[undefined]",				//FD 52
	"[undefined]",				//FD 53
	"[undefined]",				//FD 54
	"[undefined]",				//FD 55
	"LD	D, (IY+0x%02X)",		//FD 56
	"[undefined]",				//FD 57

	"[undefined]",				//FD 58
	"[undefined]",				//FD 59
	"[undefined]",				//FD 5A
	"[undefined]",				//FD 5B
	"[undefined]",				//FD 5C
	"[undefined]",				//FD 5D
	"LD	E, (IY+0x%02X)",		//FD 5E
	"[undefined]",				//FD 5F

	"[undefined]",				//FD 60
	"[undefined]",				//FD 61
	"[undefined]",				//FD 62
	"[undefined]",				//FD 63
	"[undefined]",				//FD 64
	"[undefined]",				//FD 65
	"LD	H, (IY+0x%02X)",		//FD 66
	"[undefined]",				//FD 67

	"[undefined]",				//FD 68
	"[undefined]",				//FD 69
	"[undefined]",				//FD 6A
	"[undefined]",				//FD 6B
	"[undefined]",				//FD 6C
	"[undefined]",				//FD 6D
	"LD	L, (IY+0x%02X)",		//FD 6E
	"[undefined]",				//FD 6F

	"LD	(IY+0x%02X), B",		//FD 70
	"LD	(IY+0x%02X), C",		//FD 71
	"LD	(IY+0x%02X), D",		//FD 72
	"LD	(IY+0x%02X), E",		//FD 73
	"LD	(IY+0x%02X), H",		//FD 74
	"LD	(IY+0x%02X), L",		//FD 75
	"[undefined]",				//FD 76
	"LD	(IY+0x%02X), A",		//FD 77

	"[undefined]",				//FD 78
	"[undefined]",				//FD 79
	"[undefined]",				//FD 7A
	"[undefined]",				//FD 7B
	"[undefined]",				//FD 7C
	"[undefined]",				//FD 7D
	"LD	A, (IY+0x%02X)",		//FD 7E
	"[undefined]",				//FD 7F

	"[undefined]",				//FD 80
	"[undefined]",				//FD 81
	"[undefined]",				//FD 82
	"[undefined]",				//FD 83
	"[undefined]",				//FD 84
	"[undefined]",				//FD 85
	"ADD	A, (IY+0x%02X)",	//FD 86
	"[undefined]",				//FD 87

	"[undefined]",				//FD 88
	"[undefined]",				//FD 89
	"[undefined]",				//FD 8A
	"[undefined]",				//FD 8B
	"[undefined]",				//FD 8C
	"[undefined]",				//FD 8D
	"ADC	A, (IY+0x%02X)",	//FD 8E
	"[undefined]",				//FD 8F

	"[undefined]",				//FD 90
	"[undefined]",				//FD 91
	"[undefined]",				//FD 92
	"[undefined]",				//FD 93
	"[undefined]",				//FD 94
	"[undefined]",				//FD 95
	"SUB	A, (IY+0x%02X)",	//FD 96
	"[undefined]",				//FD 97

	"[undefined]",				//FD 98
	"[undefined]",				//FD 99
	"[undefined]",				//FD 9A
	"[undefined]",				//FD 9B
	"[undefined]",				//FD 9C
	"[undefined]",				//FD 9D
	"SBC	A, (IY+0x%02X)",	//FD 9E
	"[undefined]",				//FD 9F

	"[undefined]",				//FD A0
	"[undefined]",				//FD A1
	"[undefined]",				//FD A2
	"[undefined]",				//FD A3
	"[undefined]",				//FD A4
	"[undefined]",				//FD A5
	"AND	(IY+0x%02X)",		//FD A6
	"[undefined]",				//FD A7

	"[undefined]",				//FD A8
	"[undefined]",				//FD A9
	"[undefined]",				//FD AA
	"[undefined]",				//FD AB
	"[undefined]",				//FD AC
	"[undefined]",				//FD AD
	"XOR	(IY+0x%02X)",		//FD AE
	"[undefined]",				//FD AF

	"[undefined]",				//FD B0
	"[undefined]",				//FD B1
	"[undefined]",				//FD B2
	"[undefined]",				//FD B3
	"[undefined]",				//FD B4
	"[undefined]",				//FD B5
	"OR	(IY+0x%02X)",			//FD B6
	"[undefined]",				//FD B7

	"[undefined]",				//FD B8
	"[undefined]",				//FD B9
	"[undefined]",				//FD BA
	"[undefined]",				//FD BB
	"[undefined]",				//FD BC
	"[undefined]",				//FD BD
	"CP	(IY+0x%02X)",			//FD BE
	"[undefined]",				//FD BF

	"[undefined]",				//FD C0
	"[undefined]",				//FD C1
	"[undefined]",				//FD C2
	"[undefined]",				//FD C3
	"[undefined]",				//FD C4
	"[undefined]",				//FD C5
	"[undefined]",				//FD C6
	"[undefined]",				//FD C7

	"[undefined]",				//FD C8
	"[undefined]",				//FD C9
	"[undefined]",				//FD CA
	"xx",						//FD CB
	"[undefined]",				//FD CC
	"[undefined]",				//FD CD
	"[undefined]",				//FD CE
	"[undefined]",				//FD CF

	"[undefined]",				//FD D0
	"[undefined]",				//FD D1
	"[undefined]",				//FD D2
	"[undefined]",				//FD D3
	"[undefined]",				//FD D4
	"[undefined]",				//FD D5
	"[undefined]",				//FD D6
	"[undefined]",				//FD D7

	"[undefined]",				//FD D8
	"[undefined]",				//FD D9
	"[undefined]",				//FD DA
	"[undefined]",				//FD DB
	"[undefined]",				//FD DC
	"[undefined]",				//FD DD
	"[undefined]",				//FD DE
	"[undefined]",				//FD DF

	"[undefined]",				//FD E0
	"POP	IY",				//FD E1
	"[undefined]",				//FD E2
	"EX	(SP), IY",				//FD E3
	"[undefined]",				//FD E4
	"PUSH	IY",				//FD E5
	"[undefined]",				//FD E6
	"[undefined]",				//FD E7

	"[undefined]",				//FD E8
	"JP	(IY)",					//FD E9
	"[undefined]",				//FD EA
	"[undefined]",				//FD EB
	"[undefined]",				//FD EC
	"[undefined]",				//FD ED
	"[undefined]",				//FD EE
	"[undefined]",				//FD EF

	"[undefined]",				//FD F0
	"[undefined]",				//FD F1
	"[undefined]",				//FD F2
	"[undefined]",				//FD F3
	"[undefined]",				//FD F4
	"[undefined]",				//FD F5
	"[undefined]",				//FD F6
	"[undefined]",				//FD F7

	"[undefined]",				//FD F8
	"LD	SP, IY",				//FD F9
	"[undefined]",				//FD FA
	"[undefined]",				//FD FB
	"[undefined]",				//FD FC
	"[undefined]",				//FD FD
	"[undefined]",				//FD FE
	"[undefined]"				//FD FF
};

char DDCBMnemonic[CDNUM][NLENGTH] = 
{
	"[undefined]",				//DD CB xx 00
	"[undefined]",				//DD CB xx 01
	"[undefined]",				//DD CB xx 02
	"[undefined]",				//DD CB xx 03
	"[undefined]",				//DD CB xx 04
	"[undefined]",				//DD CB xx 05
	"RLC	(IX+0x%02X)",		//DD CB xx 06
	"[undefined]",				//DD CB xx 07

	"[undefined]",				//DD CB xx 08
	"[undefined]",				//DD CB xx 09
	"[undefined]",				//DD CB xx 0A
	"[undefined]",				//DD CB xx 0B
	"[undefined]",				//DD CB xx 0C
	"[undefined]",				//DD CB xx 0D
	"RRC	(IX+0x%02X)",		//DD CB xx 0E
	"[undefined]",				//DD CB xx 0F

	"[undefined]",				//DD CB xx 10
	"[undefined]",				//DD CB xx 11
	"[undefined]",				//DD CB xx 12
	"[undefined]",				//DD CB xx 13
	"[undefined]",				//DD CB xx 14
	"[undefined]",				//DD CB xx 15
	"RL	(IX+0x%02X)",			//DD CB xx 16
	"[undefined]",				//DD CB xx 17

	"[undefined]",				//DD CB xx 18
	"[undefined]",				//DD CB xx 19
	"[undefined]",				//DD CB xx 1A
	"[undefined]",				//DD CB xx 1B
	"[undefined]",				//DD CB xx 1C
	"[undefined]",				//DD CB xx 1D
	"RR	(IX+0x%02X)",			//DD CB xx 1E
	"[undefined]",				//DD CB xx 1F

	"[undefined]",				//DD CB xx 20
	"[undefined]",				//DD CB xx 21
	"[undefined]",				//DD CB xx 22
	"[undefined]",				//DD CB xx 23
	"[undefined]",				//DD CB xx 24
	"[undefined]",				//DD CB xx 25
	"SLA	(IX+0x%02X)",		//DD CB xx 26
	"[undefined]",				//DD CB xx 27

	"[undefined]",				//DD CB xx 28
	"[undefined]",				//DD CB xx 29
	"[undefined]",				//DD CB xx 2A
	"[undefined]",				//DD CB xx 2B
	"[undefined]",				//DD CB xx 2C
	"[undefined]",				//DD CB xx 2D
	"SRA	(IX+0x%02X)",		//DD CB xx 2E
	"[undefined]",				//DD CB xx 2F

	"[undefined]",				//DD CB xx 30
	"[undefined]",				//DD CB xx 31
	"[undefined]",				//DD CB xx 32
	"[undefined]",				//DD CB xx 33
	"[undefined]",				//DD CB xx 34
	"[undefined]",				//DD CB xx 35
	"[undefined]",				//DD CB xx 36
	"[undefined]",				//DD CB xx 37

	"[undefined]",				//DD CB xx 38
	"[undefined]",				//DD CB xx 39
	"[undefined]",				//DD CB xx 3A
	"[undefined]",				//DD CB xx 3B
	"[undefined]",				//DD CB xx 3C
	"[undefined]",				//DD CB xx 3D
	"SRL	(IX+0x%02X)",		//DD CB xx 3E
	"[undefined]",				//DD CB xx 3F

	"[undefined]",				//DD CB xx 40
	"[undefined]",				//DD CB xx 41
	"[undefined]",				//DD CB xx 42
	"[undefined]",				//DD CB xx 43
	"[undefined]",				//DD CB xx 44
	"[undefined]",				//DD CB xx 45
	"BIT	0, (IX+0x%02X)",	//DD CB xx 46
	"[undefined]",				//DD CB xx 47

	"[undefined]",				//DD CB xx 48
	"[undefined]",				//DD CB xx 49
	"[undefined]",				//DD CB xx 4A
	"[undefined]",				//DD CB xx 4B
	"[undefined]",				//DD CB xx 4C
	"[undefined]",				//DD CB xx 4D
	"BIT	1, (IX+0x%02X)",	//DD CB xx 4E
	"[undefined]",				//DD CB xx 4F

	"[undefined]",				//DD CB xx 50
	"[undefined]",				//DD CB xx 51
	"[undefined]",				//DD CB xx 52
	"[undefined]",				//DD CB xx 53
	"[undefined]",				//DD CB xx 54
	"[undefined]",				//DD CB xx 55
	"BIT	2, (IX+0x%02X)",	//DD CB xx 56
	"[undefined]",				//DD CB xx 57

	"[undefined]",				//DD CB xx 58
	"[undefined]",				//DD CB xx 59
	"[undefined]",				//DD CB xx 5A
	"[undefined]",				//DD CB xx 5B
	"[undefined]",				//DD CB xx 5C
	"[undefined]",				//DD CB xx 5D
	"BIT	3, (IX+0x%02X)",	//DD CB xx 5E
	"[undefined]",				//DD CB xx 5F

	"[undefined]",				//DD CB xx 60
	"[undefined]",				//DD CB xx 61
	"[undefined]",				//DD CB xx 62
	"[undefined]",				//DD CB xx 63
	"[undefined]",				//DD CB xx 64
	"[undefined]",				//DD CB xx 65
	"BIT	4, (IX+0x%02X)",	//DD CB xx 66
	"[undefined]",				//DD CB xx 67

	"[undefined]",				//DD CB xx 68
	"[undefined]",				//DD CB xx 69
	"[undefined]",				//DD CB xx 6A
	"[undefined]",				//DD CB xx 6B
	"[undefined]",				//DD CB xx 6C
	"[undefined]",				//DD CB xx 6D
	"BIT	5, (IX+0x%02X)",	//DD CB xx 6E
	"[undefined]",				//DD CB xx 6F

	"[undefined]",				//DD CB xx 70
	"[undefined]",				//DD CB xx 71
	"[undefined]",				//DD CB xx 72
	"[undefined]",				//DD CB xx 73
	"[undefined]",				//DD CB xx 74
	"[undefined]",				//DD CB xx 75
	"BIT	6, (IX+0x%02X)",	//DD CB xx 76
	"[undefined]",				//DD CB xx 77

	"[undefined]",				//DD CB xx 78
	"[undefined]",				//DD CB xx 79
	"[undefined]",				//DD CB xx 7A
	"[undefined]",				//DD CB xx 7B
	"[undefined]",				//DD CB xx 7C
	"[undefined]",				//DD CB xx 7D
	"BIT	7, (IX+0x%02X)",	//DD CB xx 7E
	"[undefined]",				//DD CB xx 7F

	"[undefined]",				//DD CB xx 80
	"[undefined]",				//DD CB xx 81
	"[undefined]",				//DD CB xx 82
	"[undefined]",				//DD CB xx 83
	"[undefined]",				//DD CB xx 84
	"[undefined]",				//DD CB xx 85
	"RES	0, (IX+0x%02X)",	//DD CB xx 86
	"[undefined]",				//DD CB xx 87

	"[undefined]",				//DD CB xx 88
	"[undefined]",				//DD CB xx 89
	"[undefined]",				//DD CB xx 8A
	"[undefined]",				//DD CB xx 8B
	"[undefined]",				//DD CB xx 8C
	"[undefined]",				//DD CB xx 8D
	"RES	1, (IX+0x%02X)",	//DD CB xx 8E
	"[undefined]",				//DD CB xx 8F

	"[undefined]",				//DD CB xx 90
	"[undefined]",				//DD CB xx 91
	"[undefined]",				//DD CB xx 92
	"[undefined]",				//DD CB xx 93
	"[undefined]",				//DD CB xx 94
	"[undefined]",				//DD CB xx 95
	"RES	2, (IX+0x%02X)",	//DD CB xx 96
	"[undefined]",				//DD CB xx 97

	"[undefined]",				//DD CB xx 98
	"[undefined]",				//DD CB xx 99
	"[undefined]",				//DD CB xx 9A
	"[undefined]",				//DD CB xx 9B
	"[undefined]",				//DD CB xx 9C
	"[undefined]",				//DD CB xx 9D
	"RES	3, (IX+0x%02X)",	//DD CB xx 9E
	"[undefined]",				//DD CB xx 9F

	"[undefined]",				//DD CB xx A0
	"[undefined]",				//DD CB xx A1
	"[undefined]",				//DD CB xx A2
	"[undefined]",				//DD CB xx A3
	"[undefined]",				//DD CB xx A4
	"[undefined]",				//DD CB xx A5
	"RES	4, (IX+0x%02X)",	//DD CB xx A6
	"[undefined]",				//DD CB xx A7

	"[undefined]",				//DD CB xx A8
	"[undefined]",				//DD CB xx A9
	"[undefined]",				//DD CB xx AA
	"[undefined]",				//DD CB xx AB
	"[undefined]",				//DD CB xx AC
	"[undefined]",				//DD CB xx AD
	"RES	5, (IX+0x%02X)",	//DD CB xx AE
	"[undefined]",				//DD CB xx AF

	"[undefined]",				//DD CB xx B0
	"[undefined]",				//DD CB xx B1
	"[undefined]",				//DD CB xx B2
	"[undefined]",				//DD CB xx B3
	"[undefined]",				//DD CB xx B4
	"[undefined]",				//DD CB xx B5
	"RES	6, (IX+0x%02X)",	//DD CB xx B6
	"[undefined]",				//DD CB xx B7

	"[undefined]",				//DD CB xx B8
	"[undefined]",				//DD CB xx B9
	"[undefined]",				//DD CB xx BA
	"[undefined]",				//DD CB xx BB
	"[undefined]",				//DD CB xx BC
	"[undefined]",				//DD CB xx BD
	"RES	7, (IX+0x%02X)",	//DD CB xx BE
	"[undefined]",				//DD CB xx BF

	"[undefined]",				//DD CB xx C0
	"[undefined]",				//DD CB xx C1
	"[undefined]",				//DD CB xx C2
	"[undefined]",				//DD CB xx C3
	"[undefined]",				//DD CB xx C4
	"[undefined]",				//DD CB xx C5
	"SET	0, (IX+0x%02X)",	//DD CB xx C6
	"[undefined]",				//DD CB xx C7

	"[undefined]",				//DD CB xx C8
	"[undefined]",				//DD CB xx C9
	"[undefined]",				//DD CB xx CA
	"[undefined]",				//DD CB xx CB
	"[undefined]",				//DD CB xx CC
	"[undefined]",				//DD CB xx CD
	"SET	1, (IX+0x%02X)",	//DD CB xx CE
	"[undefined]",				//DD CB xx CF

	"[undefined]",				//DD CB xx D0
	"[undefined]",				//DD CB xx D1
	"[undefined]",				//DD CB xx D2
	"[undefined]",				//DD CB xx D3
	"[undefined]",				//DD CB xx D4
	"[undefined]",				//DD CB xx D5
	"SET	2, (IX+0x%02X)",	//DD CB xx D6
	"[undefined]",				//DD CB xx D7

	"[undefined]",				//DD CB xx D8
	"[undefined]",				//DD CB xx D9
	"[undefined]",				//DD CB xx DA
	"[undefined]",				//DD CB xx DB
	"[undefined]",				//DD CB xx DC
	"[undefined]",				//DD CB xx DD
	"SET	3, (IX+0x%02X)",	//DD CB xx DE
	"[undefined]",				//DD CB xx DF

	"[undefined]",				//DD CB xx E0
	"[undefined]",				//DD CB xx E1
	"[undefined]",				//DD CB xx E2
	"[undefined]",				//DD CB xx E3
	"[undefined]",				//DD CB xx E4
	"[undefined]",				//DD CB xx E5
	"SET	4, (IX+0x%02X)",	//DD CB xx E6
	"[undefined]",				//DD CB xx E7

	"[undefined]",				//DD CB xx E8
	"[undefined]",				//DD CB xx E9
	"[undefined]",				//DD CB xx EA
	"[undefined]",				//DD CB xx EB
	"[undefined]",				//DD CB xx EC
	"[undefined]",				//DD CB xx ED
	"SET	5, (IX+0x%02X)",	//DD CB xx EE
	"[undefined]",				//DD CB xx EF

	"[undefined]",				//DD CB xx F0
	"[undefined]",				//DD CB xx F1
	"[undefined]",				//DD CB xx F2
	"[undefined]",				//DD CB xx F3
	"[undefined]",				//DD CB xx F4
	"[undefined]",				//DD CB xx F5
	"SET	6, (IX+0x%02X)",	//DD CB xx F6
	"[undefined]",				//DD CB xx F7

	"[undefined]",				//DD CB xx F8
	"[undefined]",				//DD CB xx F9
	"[undefined]",				//DD CB xx FA
	"[undefined]",				//DD CB xx FB
	"[undefined]",				//DD CB xx FC
	"[undefined]",				//DD CB xx FD
	"SET	7, (IX+0x%02X)",	//DD CB xx FE
	"[undefined]"				//DD CB xx FF
};

char FDCBMnemonic[CDNUM][NLENGTH] = 
{
	"[undefined]",				//FD CB xx 00
	"[undefined]",				//FD CB xx 01
	"[undefined]",				//FD CB xx 02
	"[undefined]",				//FD CB xx 03
	"[undefined]",				//FD CB xx 04
	"[undefined]",				//FD CB xx 05
	"RLC	(IY+0x%02X)",		//FD CB xx 06
	"[undefined]",				//FD CB xx 07

	"[undefined]",				//FD CB xx 08
	"[undefined]",				//FD CB xx 09
	"[undefined]",				//FD CB xx 0A
	"[undefined]",				//FD CB xx 0B
	"[undefined]",				//FD CB xx 0C
	"[undefined]",				//FD CB xx 0D
	"RRC	(IY+0x%02X)",		//FD CB xx 0E
	"[undefined]",				//FD CB xx 0F

	"[undefined]",				//FD CB xx 10
	"[undefined]",				//FD CB xx 11
	"[undefined]",				//FD CB xx 12
	"[undefined]",				//FD CB xx 13
	"[undefined]",				//FD CB xx 14
	"[undefined]",				//FD CB xx 15
	"RL	(IY+0x%02X)",			//FD CB xx 16
	"[undefined]",				//FD CB xx 17

	"[undefined]",				//FD CB xx 18
	"[undefined]",				//FD CB xx 19
	"[undefined]",				//FD CB xx 1A
	"[undefined]",				//FD CB xx 1B
	"[undefined]",				//FD CB xx 1C
	"[undefined]",				//FD CB xx 1D
	"RR	(IY+0x%02X)",			//FD CB xx 1E
	"[undefined]",				//FD CB xx 1F

	"[undefined]",				//FD CB xx 20
	"[undefined]",				//FD CB xx 21
	"[undefined]",				//FD CB xx 22
	"[undefined]",				//FD CB xx 23
	"[undefined]",				//FD CB xx 24
	"[undefined]",				//FD CB xx 25
	"SLA	(IY+0x%02X)",		//FD CB xx 26
	"[undefined]",				//FD CB xx 27

	"[undefined]",				//FD CB xx 28
	"[undefined]",				//FD CB xx 29
	"[undefined]",				//FD CB xx 2A
	"[undefined]",				//FD CB xx 2B
	"[undefined]",				//FD CB xx 2C
	"[undefined]",				//FD CB xx 2D
	"SRA	(IY+0x%02X)",		//FD CB xx 2E
	"[undefined]",				//FD CB xx 2F

	"[undefined]",				//FD CB xx 30
	"[undefined]",				//FD CB xx 31
	"[undefined]",				//FD CB xx 32
	"[undefined]",				//FD CB xx 33
	"[undefined]",				//FD CB xx 34
	"[undefined]",				//FD CB xx 35
	"[undefined]",				//FD CB xx 36
	"[undefined]",				//FD CB xx 37

	"[undefined]",				//FD CB xx 38
	"[undefined]",				//FD CB xx 39
	"[undefined]",				//FD CB xx 3A
	"[undefined]",				//FD CB xx 3B
	"[undefined]",				//FD CB xx 3C
	"[undefined]",				//FD CB xx 3D
	"SRL	(IY+0x%02X)",		//FD CB xx 3E
	"[undefined]",				//FD CB xx 3F

	"[undefined]",				//FD CB xx 40
	"[undefined]",				//FD CB xx 41
	"[undefined]",				//FD CB xx 42
	"[undefined]",				//FD CB xx 43
	"[undefined]",				//FD CB xx 44
	"[undefined]",				//FD CB xx 45
	"BIT	0, (IY+0x%02X)",	//FD CB xx 46
	"[undefined]",				//FD CB xx 47

	"[undefined]",				//FD CB xx 48
	"[undefined]",				//FD CB xx 49
	"[undefined]",				//FD CB xx 4A
	"[undefined]",				//FD CB xx 4B
	"[undefined]",				//FD CB xx 4C
	"[undefined]",				//FD CB xx 4D
	"BIT	1, (IY+0x%02X)",	//FD CB xx 4E
	"[undefined]",				//FD CB xx 4F

	"[undefined]",				//FD CB xx 50
	"[undefined]",				//FD CB xx 51
	"[undefined]",				//FD CB xx 52
	"[undefined]",				//FD CB xx 53
	"[undefined]",				//FD CB xx 54
	"[undefined]",				//FD CB xx 55
	"BIT	2, (IY+0x%02X)",	//FD CB xx 56
	"[undefined]",				//FD CB xx 57

	"[undefined]",				//FD CB xx 58
	"[undefined]",				//FD CB xx 59
	"[undefined]",				//FD CB xx 5A
	"[undefined]",				//FD CB xx 5B
	"[undefined]",				//FD CB xx 5C
	"[undefined]",				//FD CB xx 5D
	"BIT	3, (IY+0x%02X)",	//FD CB xx 5E
	"[undefined]",				//FD CB xx 5F

	"[undefined]",				//FD CB xx 60
	"[undefined]",				//FD CB xx 61
	"[undefined]",				//FD CB xx 62
	"[undefined]",				//FD CB xx 63
	"[undefined]",				//FD CB xx 64
	"[undefined]",				//FD CB xx 65
	"BIT	4, (IY+0x%02X)",	//FD CB xx 66
	"[undefined]",				//FD CB xx 67

	"[undefined]",				//FD CB xx 68
	"[undefined]",				//FD CB xx 69
	"[undefined]",				//FD CB xx 6A
	"[undefined]",				//FD CB xx 6B
	"[undefined]",				//FD CB xx 6C
	"[undefined]",				//FD CB xx 6D
	"BIT	5, (IY+0x%02X)",	//FD CB xx 6E
	"[undefined]",				//FD CB xx 6F

	"[undefined]",				//FD CB xx 70
	"[undefined]",				//FD CB xx 71
	"[undefined]",				//FD CB xx 72
	"[undefined]",				//FD CB xx 73
	"[undefined]",				//FD CB xx 74
	"[undefined]",				//FD CB xx 75
	"BIT	6, (IY+0x%02X)",	//FD CB xx 76
	"[undefined]",				//FD CB xx 77

	"[undefined]",				//FD CB xx 78
	"[undefined]",				//FD CB xx 79
	"[undefined]",				//FD CB xx 7A
	"[undefined]",				//FD CB xx 7B
	"[undefined]",				//FD CB xx 7C
	"[undefined]",				//FD CB xx 7D
	"BIT	7, (IY+0x%02X)",	//FD CB xx 7E
	"[undefined]",				//FD CB xx 7F

	"[undefined]",				//FD CB xx 80
	"[undefined]",				//FD CB xx 81
	"[undefined]",				//FD CB xx 82
	"[undefined]",				//FD CB xx 83
	"[undefined]",				//FD CB xx 84
	"[undefined]",				//FD CB xx 85
	"RES	0, (IY+0x%02X)",	//FD CB xx 86
	"[undefined]",				//FD CB xx 87

	"[undefined]",				//FD CB xx 88
	"[undefined]",				//FD CB xx 89
	"[undefined]",				//FD CB xx 8A
	"[undefined]",				//FD CB xx 8B
	"[undefined]",				//FD CB xx 8C
	"[undefined]",				//FD CB xx 8D
	"RES	1, (IY+0x%02X)",	//FD CB xx 8E
	"[undefined]",				//FD CB xx 8F

	"[undefined]",				//FD CB xx 90
	"[undefined]",				//FD CB xx 91
	"[undefined]",				//FD CB xx 92
	"[undefined]",				//FD CB xx 93
	"[undefined]",				//FD CB xx 94
	"[undefined]",				//FD CB xx 95
	"RES	2, (IY+0x%02X)",	//FD CB xx 96
	"[undefined]",				//FD CB xx 97

	"[undefined]",				//FD CB xx 98
	"[undefined]",				//FD CB xx 99
	"[undefined]",				//FD CB xx 9A
	"[undefined]",				//FD CB xx 9B
	"[undefined]",				//FD CB xx 9C
	"[undefined]",				//FD CB xx 9D
	"RES	3, (IY+0x%02X)",	//FD CB xx 9E
	"[undefined]",				//FD CB xx 9F

	"[undefined]",				//FD CB xx A0
	"[undefined]",				//FD CB xx A1
	"[undefined]",				//FD CB xx A2
	"[undefined]",				//FD CB xx A3
	"[undefined]",				//FD CB xx A4
	"[undefined]",				//FD CB xx A5
	"RES	4, (IY+0x%02X)",	//FD CB xx A6
	"[undefined]",				//FD CB xx A7

	"[undefined]",				//FD CB xx A8
	"[undefined]",				//FD CB xx A9
	"[undefined]",				//FD CB xx AA
	"[undefined]",				//FD CB xx AB
	"[undefined]",				//FD CB xx AC
	"[undefined]",				//FD CB xx AD
	"RES	5, (IY+0x%02X)",	//FD CB xx AE
	"[undefined]",				//FD CB xx AF

	"[undefined]",				//FD CB xx B0
	"[undefined]",				//FD CB xx B1
	"[undefined]",				//FD CB xx B2
	"[undefined]",				//FD CB xx B3
	"[undefined]",				//FD CB xx B4
	"[undefined]",				//FD CB xx B5
	"RES	6, (IY+0x%02X)",	//FD CB xx B6
	"[undefined]",				//FD CB xx B7

	"[undefined]",				//FD CB xx B8
	"[undefined]",				//FD CB xx B9
	"[undefined]",				//FD CB xx BA
	"[undefined]",				//FD CB xx BB
	"[undefined]",				//FD CB xx BC
	"[undefined]",				//FD CB xx BD
	"RES	7, (IY+0x%02X)",	//FD CB xx BE
	"[undefined]",				//FD CB xx BF

	"[undefined]",				//FD CB xx C0
	"[undefined]",				//FD CB xx C1
	"[undefined]",				//FD CB xx C2
	"[undefined]",				//FD CB xx C3
	"[undefined]",				//FD CB xx C4
	"[undefined]",				//FD CB xx C5
	"SET	0, (IY+0x%02X)",	//FD CB xx C6
	"[undefined]",				//FD CB xx C7

	"[undefined]",				//FD CB xx C8
	"[undefined]",				//FD CB xx C9
	"[undefined]",				//FD CB xx CA
	"[undefined]",				//FD CB xx CB
	"[undefined]",				//FD CB xx CC
	"[undefined]",				//FD CB xx CD
	"SET	1, (IY+0x%02X)",	//FD CB xx CE
	"[undefined]",				//FD CB xx CF

	"[undefined]",				//FD CB xx D0
	"[undefined]",				//FD CB xx D1
	"[undefined]",				//FD CB xx D2
	"[undefined]",				//FD CB xx D3
	"[undefined]",				//FD CB xx D4
	"[undefined]",				//FD CB xx D5
	"SET	2, (IY+0x%02X)",	//FD CB xx D6
	"[undefined]",				//FD CB xx D7

	"[undefined]",				//FD CB xx D8
	"[undefined]",				//FD CB xx D9
	"[undefined]",				//FD CB xx DA
	"[undefined]",				//FD CB xx DB
	"[undefined]",				//FD CB xx DC
	"[undefined]",				//FD CB xx DD
	"SET	3, (IY+0x%02X)",	//FD CB xx DE
	"[undefined]",				//FD CB xx DF

	"[undefined]",				//FD CB xx E0
	"[undefined]",				//FD CB xx E1
	"[undefined]",				//FD CB xx E2
	"[undefined]",				//FD CB xx E3
	"[undefined]",				//FD CB xx E4
	"[undefined]",				//FD CB xx E5
	"SET	4, (IY+0x%02X)",	//FD CB xx E6
	"[undefined]",				//FD CB xx E7

	"[undefined]",				//FD CB xx E8
	"[undefined]",				//FD CB xx E9
	"[undefined]",				//FD CB xx EA
	"[undefined]",				//FD CB xx EB
	"[undefined]",				//FD CB xx EC
	"[undefined]",				//FD CB xx ED
	"SET	5, (IY+0x%02X)",	//FD CB xx EE
	"[undefined]",				//FD CB xx EF

	"[undefined]",				//FD CB xx F0
	"[undefined]",				//FD CB xx F1
	"[undefined]",				//FD CB xx F2
	"[undefined]",				//FD CB xx F3
	"[undefined]",				//FD CB xx F4
	"[undefined]",				//FD CB xx F5
	"SET	6, (IY+0x%02X)",	//FD CB xx F6
	"[undefined]",				//FD CB xx F7

	"[undefined]",				//FD CB xx F8
	"[undefined]",				//FD CB xx F9
	"[undefined]",				//FD CB xx FA
	"[undefined]",				//FD CB xx FB
	"[undefined]",				//FD CB xx FC
	"[undefined]",				//FD CB xx FD
	"SET	7, (IY+0x%02X)",	//FD CB xx FE
	"[undefined]"				//FD CB xx FF
};

#endif