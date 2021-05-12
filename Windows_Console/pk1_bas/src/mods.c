#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dats.h"
#include "GBCPU_MNE.h"
//#include "Z80_MNE.h"

#define LF_CHAR 1
#define LF_TOOL 2
#define LF_SKIL 3
#define LF_PNAM 4

unsigned int code = 0;
unsigned int Expl = 0;
unsigned int Spls = 0;
int find = 0;
int Ctr = 0;
char mode[24] = { 0 };
int isFound = FOUND;

int bExit() {
	int nExitF = 1;
	printf("\n続ける：1　/　もどる：0\n");
	scanf("%d", &nExitF);
	fseek(stdin, (long)0, SEEK_SET);
	return nExitF;
}

void vError() {
	if (isFound == NOT_FOUND)
	{
		printf("\n見つかりませんでした。\n");
	}
	else if (isFound == FIND_ERROR)
	{
		printf("不明なエラーが発生しました。\n");
	}
}

int vInfo(int fSpls) {
	if (fSpls < 166 || fSpls>195) { 
		printf("\nわざ名：%s\n", Skl[fSpls]); 
	}
	else { 
		printf("\n第1世代(赤緑青ピカ)に於いては、対応するわざは本来ありません。(バグ名称)\n"); 
	}

	printf("\n文字：%s\n", Chl[fSpls]);

	if (Spls > 200) { 
		printf("\nトレーナー名：%s\n", pNum[fSpls]); 
	}
	else { 
		printf("\nポケモン名：%s\n", pNum[fSpls]); 
	}

	printf("\nどうぐ名：%s\n", Tols[fSpls]);

	return 0;
}

int judgeExceptNumber(int SourceNumber[], int TargetNumber, int numSourceMember) {
	int ctr1 = 0;

	while (ctr1 < numSourceMember) {
		if (TargetNumber == SourceNumber[ctr1]) {
			return IS_EXCEPT_NUMBER;
		}
		else {
			ctr1++;
		}
	}
	return NOT_EXCEPT_NUMBER;
}

int code1BtoChar() {
	printf("\n値を入力してください。(16進数)\n注：下2桁以外は無視されます。\n");
	while (scanf("%x", &code) == EOF) {
		fseek(stdin, (long)0, SEEK_SET);
		printf("正しい値(16進数)を入力してください。\n");
	}
	fseek(stdin, (long)0, SEEK_SET);
	printf("\n");

	code = code & 0x000000FF;

	printf("内部コード：0x%02X\n", code);

	printf("\n文字：%s\n", Chl[code]);

	if (code < 166 || code > 195) {
		printf("\nわざ名：%s\n", Skl[code]);
	}
	else {
		printf("\n第1世代(赤緑青ピカ)に於いては、対応するわざは本来ありません。(バグ名称)\n");
	}

	if (code > 200) {
		printf("\nトレーナー名：%s\n", pNum[code]);
	}
	else {
		printf("\nポケモン名：%s\n", pNum[code]);
	}

	printf("\nどうぐ名：%s\n", Tols[code]);

	return 0;
}

int mbToAsm(int codeLength, int inCodeINT_F[]) {
	FILE *outAsm = NULL;
	int isOpen = 1;
	outAsm = fopen("AsmOut.txt", "w");
	if (outAsm == NULL) {
		printf("ファイルが作成できませんでした。\n");
		isOpen = 0;
	}
	else {
		isOpen = 1;
	}
	printf("\nアセンブリ言語化：\n");

	Ctr = 0;
	while (Ctr < codeLength) {
		if (inCodeINT_F[Ctr] == 0xCB) {
			printf("%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
			printf(CBxxMnemonic[inCodeINT_F[Ctr + 1]]);
			printf("\n");

			if (isOpen == 1) {
				fprintf(outAsm, "%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
				fprintf(outAsm, CBxxMnemonic[inCodeINT_F[Ctr + 1]]);
				fprintf(outAsm, "\n");
			}

			Ctr += 2;
		}

#ifdef Z80_MNE_H
		else if (inCodeINT_F[Ctr] == 0xDD) {
			if (judgeExceptNumber(DDXX_MN_1B, inCodeINT_F[Ctr + 1], DDXX_1B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
				printf("%02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2]);
				printf(DDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2]);
				printf("\n");

				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, DDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, "\n");
				}

				Ctr += 3;
			}
			else if (judgeExceptNumber(DDXX_MN_2B, inCodeINT_F[Ctr + 1], DDXX_2B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
				printf("%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);

				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
				}

				if (inCodeINT_F[Ctr + 1] != 0x36) {
					printf(DDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 3], inCodeINT_F[Ctr + 2]);
					if (isOpen == 1) {
						fprintf(outAsm, DDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 3], inCodeINT_F[Ctr + 2]);
					}

				}
				else {
					printf(DDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					if (isOpen == 1) {
						fprintf(outAsm, DDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					}
				}
				printf("\n");

				if (isOpen == 1) {
					fprintf(outAsm, "\n");
				}

				Ctr += 4;
			}
			else if (inCodeINT_F[Ctr + 1] == 0xCB) {
				printf("%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
				printf(DDCBMnemonic[inCodeINT_F[Ctr + 3]], inCodeINT_F[Ctr + 2]);
				printf("\n");

				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					fprintf(outAsm, DDCBMnemonic[inCodeINT_F[Ctr + 3]], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, "\n");
				}

				Ctr += 4;
			}
			else {
				printf("%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
				printf(DDxxMnemonic[inCodeINT_F[Ctr + 1]]);
				printf("\n");

				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
					fprintf(outAsm, DDxxMnemonic[inCodeINT_F[Ctr + 1]]);
					fprintf(outAsm, "\n");
				}

				Ctr += 2;
			}
		}
		else if (inCodeINT_F[Ctr] == 0xFD) {
			if (judgeExceptNumber(FDXX_MN_1B, inCodeINT_F[Ctr + 1], FDXX_1B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
				printf("%02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2]);
				printf(FDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2]);
				printf("\n");
				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, FDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, "\n");
				}

				Ctr += 3;
			}
			else if (judgeExceptNumber(FDXX_MN_2B, inCodeINT_F[Ctr + 1], FDXX_2B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
				printf("%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
				}

				if (inCodeINT_F[Ctr + 1] != 0x36) {
					printf(FDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 3], inCodeINT_F[Ctr + 2]);
					if (isOpen == 1) {
						fprintf(outAsm, FDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 3], inCodeINT_F[Ctr + 2]);
					}

				}
				else {
					printf(FDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					if (isOpen == 1) {
						fprintf(outAsm, FDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					}

				}
				printf("\n");
				if (isOpen == 1) {
					fprintf(outAsm, "\n");
				}

				Ctr += 4;
			}
			else if (inCodeINT_F[Ctr + 1] == 0xCB) {
				printf("%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
				printf(FDCBMnemonic[inCodeINT_F[Ctr + 3]], inCodeINT_F[Ctr + 2]);
				printf("\n");
				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					fprintf(outAsm, FDCBMnemonic[inCodeINT_F[Ctr + 3]], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, "\n");
				}

				Ctr += 4;
			}
			else {
				printf("%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
				printf(FDxxMnemonic[inCodeINT_F[Ctr + 1]]);
				printf("\n");
				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
					fprintf(outAsm, FDxxMnemonic[inCodeINT_F[Ctr + 1]]);
					fprintf(outAsm, "\n");
				}

				Ctr += 2;
			}
		}
		else if (inCodeINT_F[Ctr] == 0xED) {
			if (judgeExceptNumber(EDXX_MN_2B, inCodeINT_F[Ctr + 1], EDXX_2B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
				printf("%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
				printf(EDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 3], inCodeINT_F[Ctr + 2]);
				printf("\n");
				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 3]);
					fprintf(outAsm, EDxxMnemonic[inCodeINT_F[Ctr + 1]], inCodeINT_F[Ctr + 3], inCodeINT_F[Ctr + 2]);
					fprintf(outAsm, "\n");
				}

				Ctr += 4;
			}
			else {
				printf("%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
				printf(EDxxMnemonic[inCodeINT_F[Ctr + 1]]);
				printf("\n");
				if (isOpen == 1) {
					fprintf(outAsm, "%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
					fprintf(outAsm, EDxxMnemonic[inCodeINT_F[Ctr + 1]]);
					fprintf(outAsm, "\n");
				}

				Ctr += 2;
			}
		}
#endif

		else if (judgeExceptNumber(BASIC_MN_1BYTE, inCodeINT_F[Ctr], BASIC_1B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
			printf("%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
			printf(basicMnemonic[inCodeINT_F[Ctr]], inCodeINT_F[Ctr + 1]);
			printf("\n");

			if (isOpen == 1) {
				fprintf(outAsm, "%02X %02X\t|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1]);
				fprintf(outAsm, basicMnemonic[inCodeINT_F[Ctr]], inCodeINT_F[Ctr + 1]);
				fprintf(outAsm, "\n");
			}

			Ctr += 2;
		}
		else if (judgeExceptNumber(BASIC_MN_2BYTE, inCodeINT_F[Ctr], BASIC_2B_EX_MEMBERS) == IS_EXCEPT_NUMBER) {
			printf("%02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2]);
			printf(basicMnemonic[inCodeINT_F[Ctr]], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 1]);
			printf("\n");

			if (isOpen == 1) {
				fprintf(outAsm, "%02X %02X %02X|\t", inCodeINT_F[Ctr], inCodeINT_F[Ctr + 1], inCodeINT_F[Ctr + 2]);
				fprintf(outAsm, basicMnemonic[inCodeINT_F[Ctr]], inCodeINT_F[Ctr + 2], inCodeINT_F[Ctr + 1]);
				fprintf(outAsm, "\n");
			}

			Ctr += 3;
		}
		else {
			printf("%02X\t|\t", inCodeINT_F[Ctr]);
			printf(basicMnemonic[inCodeINT_F[Ctr]]);
			printf("\n");
			if (isOpen == 1) {
				fprintf(outAsm, "%02X\t|\t", inCodeINT_F[Ctr]);
				fprintf(outAsm, basicMnemonic[inCodeINT_F[Ctr]]);
				fprintf(outAsm, "\n");
			}

			Ctr++;
		}
	}
	Ctr = 0;

	if (isOpen == 1) {
		fclose(outAsm);
	}

	return 0;
}

int codeToInfo(char Data[CNUM][TNLENG], int Length, int Code_F[], int lfMode) {
	int nStrLength = 0;
	int isOpenedCTI = 0;
	FILE *outFileChar = NULL;
	FILE *outFileTool = NULL;

	if(lfMode == LF_CHAR) {
		outFileChar = fopen("strOut.txt", "w");
		if(outFileChar == NULL)	{
			printf("ファイルが開けませんでした。");
			isOpenedCTI = 0;
		}
		else {
			isOpenedCTI = 1;
		}
	}
	if(lfMode == LF_TOOL) {
		outFileTool = fopen("toolsOut.txt", "w");
		if(outFileTool == NULL)	{
			printf("ファイルが開けませんでした。");
			isOpenedCTI = 0;
		}
		else {
			isOpenedCTI = 1;
		}
	}
	
	Ctr = 0;
	while (Ctr < Length) {
		if (lfMode == LF_CHAR) {
			printf("%s", Data[Code_F[Ctr]]);
			if(isOpenedCTI == 1) {
				fprintf(outFileChar, "%s", Data[Code_F[Ctr]]);
			}
			if (Code_F[Ctr] == 0x50) {
				printf("\n");
				if(isOpenedCTI == 1) {
					fprintf(outFileChar, "\n");
				}
			}
			Ctr++;
		}
		else if (lfMode == LF_TOOL) {
			nStrLength = strlen(Data[Code_F[Ctr]]);
			
			printf("%s", Data[Code_F[Ctr]]);
			
			if(isOpenedCTI == 1) {
				fprintf(outFileTool, "%s", Data[Code_F[Ctr]]);
			}
			
			if (nStrLength < 8) {
				printf("\t\t\t");
				if(isOpenedCTI == 1) {
					fprintf(outFileTool, "\t\t\t");
				}
			}
			else if (nStrLength < 16) {
				printf("\t\t");
				if(isOpenedCTI == 1) {
					fprintf(outFileTool, "\t\t");
				}
			}
			else {
				printf("\t");
				if(isOpenedCTI == 1) {
					fprintf(outFileTool, "\t");
				}

			}
			
			printf("x%d\n", Code_F[Ctr+1]);
			if(isOpenedCTI == 1) {
				fprintf(outFileTool, "x%d\n", Code_F[Ctr+1]);
			}

			Ctr += 2;
		}
		else {
			printf("\n");
			Ctr++;
		}
	}
	printf("\n");
	if(outFileChar != NULL) {
		fclose(outFileChar);
	}	
	if(outFileTool != NULL)	{
		fclose(outFileTool);
	}
	return 0;
}

int readMbCode() {
	char inCode[ (CODEMAX * 2) + 1 ] = {0};
	char tempCode[3] = {0};
	int inCodeINT[CODEMAX] = { 0 };
	int ctr2 = 0;

	int numberChar = 0;

	int codeCount = 0;

	printf("\nコード列(16進数)を入力してください。\n");
	printf("\n（意図しない「00」が入った場合は無視してください。）");
	printf("\n一桁のコードは頭を0で埋めてください。");
	printf("\n入力を終わる時は、Enterキーを押したあとEOFを入力してください。\n");
	printf("\n※最大：スペース含めて%dバイト分(%dケタ)\n\n", CODEMAX - 1, (CODEMAX - 1) * 2 );
	
	numberChar = fread(inCode, sizeof(char), CODEMAX * 2, stdin);
	fseek(stdin, (long)0, SEEK_SET);
	printf("入力された文字数：%d\n", numberChar - 1);
	if (numberChar != 0) {
		inCode[numberChar - 1] = '\0';
	}

	Ctr = 0;
	while (inCode[Ctr] != '\0') {
		while ( (inCode[Ctr] < 0x21) || (inCode[Ctr] == 0x7F) ) {
			Ctr++;
		}

		tempCode[0] = inCode[Ctr];
		tempCode[1] = inCode[Ctr + 1];

		sscanf(tempCode, "%2x", &inCodeINT[ctr2]);
		printf("%02X ", inCodeINT[ctr2]);

		Ctr += 2;
		if (Ctr > (CODEMAX * 2)) {
			Ctr = (CODEMAX * 2);
		}

		ctr2++;
		if (ctr2 > CODEMAX) {
			break;
		}
	}
	printf("\n\n");

	printf("文字列：\n");
	codeToInfo(Chl, ctr2, inCodeINT, LF_CHAR);
	printf("道具名：\n");
	codeToInfo(Tols, ctr2, inCodeINT, LF_TOOL);

	mbToAsm(ctr2, inCodeINT);

	memset(inCode, 0, ((CODEMAX * 2) + 1));
	return 0;
}

int CV_Code() {
	int selMode = 0;
	int continueF = 1;
	int continueFI = 1;

	printf("\n内部コード値→各種変換\n");
	while (continueF == 1) {
		printf("\nコード(1バイト)→文字：0\nコード列→文字：1\n");
		while (scanf("%d", &selMode) == EOF) {
			fseek(stdin, (long)0, SEEK_SET);
			printf("半角数字で選択してください。\n");
		}
		fseek(stdin, (long)0, SEEK_SET);

		if (selMode > 1) {
			selMode = 1;
		}

		if (selMode == 0) {
			while (continueFI == 1) {
				code1BtoChar();
				continueFI = bExit();
			}
		}
		else {
			while (continueFI == 1) {
				readMbCode();
				continueFI = bExit();
			}
		}

		printf("\n内部コード値→各種変換から");
		continueF = bExit();
		continueFI = continueF;
	} 

	return 0;
}

int Spls10() {
	printf("\n数値を入力してください。(10進数)\n");
	scanf("%d", &Expl);
	fseek(stdin, (long)0, SEEK_SET);
	printf("\n");

	Spls = Expl % 256;

	printf("\n256で割った余りは %d \n16進数：%02X\n", Spls, Spls);

	vInfo(Spls);

	return 0;
}

int Spls16() {
	printf("\n数値を入力してください。(16進数)\n");
	while (scanf("%x", &Expl) == EOF) {
		fseek(stdin, (long)0, SEEK_SET);
		printf("\n正しい値を入力してください。\n");
	}
	fseek(stdin, (long)0, SEEK_SET);

	Spls = Expl % 256;

	printf("\n256で割った余りは %02X \n10進数：%u\n", Spls, Spls);//%xは16進数表示

	vInfo(Spls);

	return 0;
}

int codeComp(char compStr[CNUM][TNLENG], char findString[]) {
	Ctr = 0;

	while (strcmp(findString, compStr[Ctr]) != 0) { 
		Ctr++; 
		if (Ctr >= CNUM) {
			break;
		}
	}

	if (Ctr == CNUM) { 
		return NOT_FOUND;
	}
	else if( (Ctr >= 0) && (Ctr < CNUM) ) {
		return FOUND;
	}
	else {
		return FIND_ERROR;
	}
}

int CodeFind() {
	int SetCtr = 0;
	int findl = 0;
	int condContinue = 1;
	char fSkill[48] = { 0 };

	fseek(stdin, (long)0, SEEK_SET);
	Ctr = 0;

	while (condContinue == 1) {
		printf("\n何を検索しますか？\n\nわざ：1\n文字/文字列：2\nポケモン/トレーナー名：3\nどうぐ：4\nもどる：0\n");
		while (scanf("%d", &findl) == EOF) {
			fseek(stdin, (long)0, SEEK_SET);
			printf("\n半角数字で選んでください。\n");
		}
		fseek(stdin, (long)0, SEEK_SET);

		if (findl == 1) {
			printf("\n検索するわざ名を入力してください。\n");
			scanf("%49s", &fSkill);
			fseek(stdin, (long)0, SEEK_SET);

			isFound = codeComp(Skl, fSkill);

			if (isFound == FOUND) {
				printf("\n内部コード：0x%02X　%s\n", Ctr, Skl[Ctr]);
			}
			else {
				vError();
			}

		}
		else if (findl == 2) {
			int isStrFind = 0;
			int findCount = 0;
			char tempFindC[3] = { 0 };
			char findString[STRING_MAX] = { 0 };
			int codeFromStr[STRING_MAX] = { 0 };
			int ctrCFStr = 0;

			printf("\n検索対象は？\n1文字だけ検索：0\n文字列から1文字ずつ検索：1\n");
			scanf("%d", &isStrFind);
			fseek(stdin, (long)0, SEEK_SET);

			if (isStrFind == 0) {
				printf("\n検索する文字を入力してください。\n");
				scanf("%49s", &fSkill);
				fseek(stdin, (long)0, SEEK_SET);

				isFound = codeComp(Chl, fSkill);

				if (isFound == FOUND) {
					printf("\n内部コード：0x%02X　%s\n", Ctr, Chl[Ctr]);
				}
				else {
					vError();
				}
			}
			else {
				printf("注：1文字ずつ比較するため、以下の文字(列)に関しては、コードとの対応が正しくない場合があります。\n");
				
				for (int ctr1 = 0; ctr1 <= 0x04; ctr1++) { 
					printf("0x%02X %s\n", ctr1, Chl[ctr1]); 
				}
				for (int ctr1 = 0x14; ctr1 <= 0x18; ctr1++) {
					printf("0x%02X %s\n", ctr1, Chl[ctr1]);
				}
				for (int ctr1 = 0x1D; ctr1 <= 0x25; ctr1++) {
					printf("0x%02X %s\n", ctr1, Chl[ctr1]);
				}
				for (int ctr1 = 0x35; ctr1 <= 0x39; ctr1++) {
					printf("0x%02X %s\n", ctr1, Chl[ctr1]);
				}
				printf("0x%02X %s\n", 0x3F, Chl[0x3F]);
				for (int ctr1 = 0x49; ctr1 <= 0x5E; ctr1++) {
					printf("0x%02X %s\n", ctr1, Chl[ctr1]);
				}
				printf("0x%02X %s\n", 0x7F, Chl[0x7F]);
				for (int ctr1 = 0xEC; ctr1 <= 0xED; ctr1++) {
					printf("0x%02X %s\n", ctr1, Chl[ctr1]);
				}

				memset(findString, 0, STRING_MAX);
				printf("\n文字列を入力してください。\n( 半角(1文字分)+全角(2文字分) = 合計%d文字まで )\n", STRING_MAX - 1);
				printf("改行したところには自動的に [End_of_text](0x50) がセットされます。");
				printf("\n入力を終わる時は、EOFを入力してください。\n\n");

				fread(findString, sizeof(char), STRING_MAX - 1, stdin);
				fseek(stdin, (long)0, SEEK_SET);
				printf("\n");

				findCount = 0;
				while ( (findCount < STRING_MAX) && (findString[findCount] != '\0') ) {
					if ((findString[findCount] > 0x00) && (findString[findCount] < 0x7F)) {
						tempFindC[0] = findString[findCount];
						tempFindC[1] = '\0';
						tempFindC[2] = '\0';
						findCount++;
					}
					else {
						tempFindC[0] = findString[findCount];
						tempFindC[1] = findString[findCount + 1];
						tempFindC[2] = '\0';
						findCount += 2;
					}

					if (codeComp(Chl, tempFindC) == FOUND) {
						printf("0x%02X %s\n", Ctr, Chl[Ctr]);
						codeFromStr[ctrCFStr] = Ctr;
						ctrCFStr++;
					}
					else if (tempFindC[0] == '\n') {
						printf("0x%02X %s\n", 0x50, Chl[0x50]);
						codeFromStr[ctrCFStr] = 0x50;
						ctrCFStr++;
					}
					else {}
				}
				mbToAsm(ctrCFStr, codeFromStr);
				ctrCFStr = 0;
			}

		}
		else if (findl == 3) {
			printf("\n検索するポケモン/トレーナー名を入力してください。\n");
			scanf("%49s", &fSkill);
			fseek(stdin, (long)0, SEEK_SET);

			isFound = codeComp(pNum, fSkill);

			if (isFound == FOUND) {
				if (Ctr > 200) {
					printf("\n内部コード：0x%02X　(トレーナー名)%s\n", Ctr, pNum[Ctr]);
				}
				else {
					printf("\n内部コード：0x%02X　%s\n", Ctr, pNum[Ctr]);
				}
			}
			else {
				vError();
			}
		}
		else if (findl == 4) {
			printf("\n検索するどうぐ名を入力してください。\n");
			scanf("%49s", &fSkill);
			fseek(stdin, (long)0, SEEK_SET);

			isFound = codeComp(Tols, fSkill);

			if (isFound == FOUND) {
				printf("\n内部コード：0x%02X　%s\n", Ctr, Tols[Ctr]);
			}
			else {
				vError();
			}
		}
		else  {
			break;
		}
		condContinue = bExit();
	}
	return 0;
}
