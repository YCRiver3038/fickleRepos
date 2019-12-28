#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_L7 37
#define NUM_L6 43
#define NUM_ML 31
#define NUMBERS4_MAX 10000
#define NUMBERS3_MAX 1000
#define BINGO5_MAX 40
#define MAX_LOTO_MEMBERS 8 

#define MAX_L7 7
#define MAX_L6 6
#define MAX_ML 5
#define MAX_B5 8

#define NUM_MAX 48

unsigned int myRand()
{
	unsigned int tempRand = 0;

	tempRand = (unsigned int)rand();
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 8;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 4;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 9;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 6;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 12;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 4;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 6;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 7;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 4;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 5;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 10;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 5;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 9;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 6;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 7;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 5;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 7;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand >> 7;
	tempRand = tempRand ^ (unsigned int)rand();
	tempRand = tempRand << 9;
	tempRand = tempRand ^ ((unsigned int)rand() << 17);
	tempRand = tempRand ^ ((unsigned int)rand() << 17);
	tempRand = tempRand ^ (unsigned int)rand();

	return tempRand;
}

void chooseLOTO(int maxNumber, int maxMembers)
{
	unsigned char fromInteger[4] = {0};
	unsigned int nRand = 0;
	int flagCount = 0;
	int Flagged[NUM_MAX] = {0};
	int ctr1 = 0;
	int ctr2 = 0;
	int resultNumber[MAX_LOTO_MEMBERS] = {0};
	int tempNum = 0;
	
	ctr1 = 0;
	printf("結果：");
	while(flagCount < maxMembers)
	{
		nRand = myRand();
		fromInteger[3] = (unsigned char)nRand;
		nRand = nRand >> 8;
		fromInteger[2] = (unsigned char)nRand;
		nRand = nRand >> 8;
		fromInteger[1] = (unsigned char)nRand;
		nRand = nRand >> 8;
		fromInteger[0] = (unsigned char)nRand;
		
		for(int ctr2 = 0; ctr2 < 4; ctr2++)
		{
			fromInteger[ctr2] %= maxNumber;
			fromInteger[ctr2]++;

			if(Flagged[fromInteger[ctr2]] == 0)
			{
				Flagged[fromInteger[ctr2]] = 1;
				flagCount++;
				resultNumber[ctr1] = fromInteger[ctr2];
				ctr1++;
			}
			
			if(flagCount >= maxMembers)
			{
				break;
			}
		}
	}

	/*-小さい順にソート-*/
	ctr1 = 0;
	while( ctr1 < (maxMembers - 1) )
	{
		ctr2 = ctr1 + 1;
		while(ctr2 < maxMembers)
		{
			if(resultNumber[ctr1] > resultNumber[ctr2])
			{
				tempNum = resultNumber[ctr1];
				resultNumber[ctr1] = resultNumber[ctr2];
				resultNumber[ctr2] = tempNum;
			}
			ctr2++;
		}
		ctr1++;
	}
	/*-----------------*/
	
	for(int ctr = 0; ctr < MAX_LOTO_MEMBERS; ctr++)
	{
		if(resultNumber[ctr] != 0)
		{
			printf("%d ", resultNumber[ctr]);
		}
	}
}

void chooseNumbers(int Type)
{
	unsigned int tempNumber = 0;
	
	if (Type == 3)
	{
		tempNumber = myRand();
		tempNumber %= NUMBERS3_MAX;
		printf("結果：%03d\n", tempNumber);	
	}
	else if (Type == 4)
	{
		tempNumber = myRand();
		tempNumber %= NUMBERS4_MAX;
		printf("結果：%04d\n", tempNumber);
	}
	else {}
}

void chooseBingo5()
{
	unsigned char fromInteger[4] = {0};
	unsigned int nRand = 0;
	int flag1_5 = 0;
	int flag6_10 = 0;
	int flag11_15 = 0;
	int flag16_20 = 0;
	int flag21_25 = 0;
	int flag26_30 = 0;
	int flag31_35 = 0;
	int flag36_40 = 0;
	int flagCount = 0;
	int resultNumber[MAX_B5] = {0};
	
	while(flagCount < MAX_B5)
	{
		nRand = myRand();
		fromInteger[3] = (unsigned char)nRand;
		nRand = nRand >> 8;
		fromInteger[2] = (unsigned char)nRand;
		nRand = nRand >> 8;
		fromInteger[1] = (unsigned char)nRand;
		nRand = nRand >> 8;
		fromInteger[0] = (unsigned char)nRand;

		for(int ctr = 0; ctr < 4; ctr++)
		{
			if( (fromInteger[ctr] > 0) && (fromInteger[ctr] < 6) )
			{
				if(flag1_5 == 0)
				{
					resultNumber[0] = fromInteger[ctr];
					flagCount++;
					flag1_5 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 5) && (fromInteger[ctr] < 11) )
			{
				if(flag6_10 == 0)
				{
					resultNumber[1] = fromInteger[ctr];
					flagCount++;
					flag6_10 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 10) && (fromInteger[ctr] < 16) )
			{
				if(flag11_15 == 0)
				{
					resultNumber[2] = fromInteger[ctr];
					flagCount++;
					flag11_15 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 15) && (fromInteger[ctr] < 21) )
			{
				if(flag16_20 == 0)
				{
					resultNumber[3] = fromInteger[ctr];
					flagCount++;
					flag16_20 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 20) && (fromInteger[ctr] < 26) )
			{
				if(flag21_25 == 0)
				{
					resultNumber[4] = fromInteger[ctr];
					flagCount++;
					flag21_25 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 25) && (fromInteger[ctr] < 31) )
			{
				if(flag26_30 == 0)
				{
					resultNumber[5] = fromInteger[ctr];
					flagCount++;
					flag26_30 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 30) && (fromInteger[ctr] < 36) )
			{
				if(flag31_35 == 0)
				{
					resultNumber[6] = fromInteger[ctr];
					flagCount++;
					flag31_35 = 1;
				}
				else{}
			}
			else if( (fromInteger[ctr] > 35) && (fromInteger[ctr] < 41) )
			{
				if(flag36_40 == 0)
				{
					resultNumber[7] = fromInteger[ctr];
					flagCount++;
					flag36_40 = 1;
				}
				else{}
			}
			else{}
		}
	}
	
	for(int ctr = 0; ctr < MAX_B5; ctr++)
	{
		printf("%d ", resultNumber[ctr]);
	}
}

int main(void)
{
	int jDecide = 0;
	unsigned int seed = 0;
	int ctr3 = 0;
	int lotoType = 0;
	
	printf("乱数の初期値は？\n自分で決める：1\n時に任せる：0\n");
	scanf("%d", &jDecide);
	jDecide &= 0xFFFFFFFF;
	fseek(stdin, (long)0, SEEK_SET);

	if(jDecide == 0)
	{
		seed = (unsigned int)time(NULL);
	}
	else
	{
		printf("初期値を入力してください。\n");
		scanf("%d", &seed);
		seed &= 0xFFFFFFFF;
		fseek(stdin, (long)0, SEEK_SET);
	}	
	srand(seed);

	printf("\n宝くじの種類は？\nロト7：7\nロト6：6\nミニロト：50\nBINGO5：51\nNUMBERS4：4\nNUMBERS3：3\n");
	scanf("%d", &lotoType);
	lotoType &= 0xFFFFFFFF;
	fseek(stdin, (long)0, SEEK_SET);	
	printf("\n");

	if(lotoType == 7)
	{
		chooseLOTO(NUM_L7, MAX_L7);
	}
	else if(lotoType == 6)
	{
		chooseLOTO(NUM_L6, MAX_L6);
	}
	else if(lotoType == 50)
	{
		chooseLOTO(NUM_ML, MAX_ML);
	}
	else if(lotoType == 51)
	{
		chooseBingo5();
	}
	else if (lotoType == 4)
	{
		chooseNumbers(4);
	}
	else if (lotoType == 3)
	{
		chooseNumbers(3);
	}
	else{}

	printf("\n");
	system("pause");

	return 0;
}