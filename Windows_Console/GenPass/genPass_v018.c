#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define CCODE_NUMBER_START 48
#define CCODE_NUMBER_END 57
#define CCODE_ROMAN_CAPS_START 65
#define CCODE_ROMAN_CAPS_END 90
#define CCODE_ROMAN_SMALLER_START 97
#define CCODE_ROMAN_SMALLER_END 122
#define DIGITS_MAX 255
#define TARGET_USABLE 1
#define TARGET_UNUSABLE 0
#define ENCOUNTED_EXCEPTION -1

#define RAND_A 257
#define RAND_B 587
#define RAND_M 1073741824

unsigned int randNum = 2885;

unsigned int genRand32()//(AX+B)modM
{
	randNum = ( (RAND_A * randNum) + RAND_B ) % RAND_M;
	return randNum;
}

void setRand32(unsigned int number)
{
	randNum = number;
}

int genRand(void)
{
    unsigned int tempRand = 0;

	tempRand = genRand32();
	tempRand = tempRand ^ (genRand32() << 18);
	tempRand = tempRand ^ (genRand32() >> 16);
	tempRand = tempRand ^ genRand32();
	
	tempRand = tempRand << 11;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 7;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 5;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 13;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 3;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 7;

	tempRand = tempRand ^ (genRand32() << 18);
	tempRand = tempRand ^ (genRand32() >> 16);
	tempRand = tempRand ^ genRand32();

    return tempRand;
}

int jUsable( unsigned char target )
{
    if( ((target >= CCODE_NUMBER_START) && (target <= CCODE_NUMBER_END)) || 
        ((target >= CCODE_ROMAN_CAPS_START) && (target <= CCODE_ROMAN_CAPS_END)) ||
        ((target >= CCODE_ROMAN_SMALLER_START) && (target <= CCODE_ROMAN_SMALLER_END)) )
    {
        return TARGET_USABLE;
    }
    else
    {
        return TARGET_UNUSABLE;
    }

    return ENCOUNTED_EXCEPTION;
}

int main(void)
{
    unsigned int randNumber = 0;
    int digits = 0;
    int ctr1 = 0;
    int ctr2 = 0;
    int returnedNumber = 0;
    unsigned char Number[DIGITS_MAX] = {0};

    system("@echo off\n");

    setRand32( (unsigned int)time(NULL) );

    printf("I(大文字アイ)とl(小文字エル)、0(ゼロ)とO(大文字オー)を区別できるフォントで表示することを推奨します。\n");
    printf("桁数は？→");
    scanf("%d", &digits);
    digits %= DIGITS_MAX + 1;

    printf("\n");
    ctr1 = 0;
    ctr2 = 0;
    while(ctr2 < digits)
    {
        randNumber = genRand();

        Number[0] = (unsigned char)( randNumber & 0x000000FF );
        Number[1] = (unsigned char)( (randNumber >> 8) & 0x000000FF );
        Number[2] = (unsigned char)( (randNumber >> 16) & 0x000000FF );
        Number[3] = (unsigned char)( (randNumber >> 24) & 0x000000FF );

        //printf("0x%2X 0x%2X 0x%2X 0x%2X\n", Number[0], Number[1], Number[2], Number[3]);
        ctr1 = 0;
        while(ctr1 < 4)
        {
            returnedNumber = jUsable(Number[ctr1]);
            if(returnedNumber == TARGET_USABLE)
            {
                printf("%c", Number[ctr1]);
                ctr2++;
                if(ctr2 > digits)
                {
                    break;
                }
            }
            else if(returnedNumber == ENCOUNTED_EXCEPTION)
            {
                printf("不明なエラーが発生しました\n");
                exit(EXIT_FAILURE);
            }
            else
            {}

            ctr1++;
        }
    }
    printf("\n");

    system("pause");
    return 0;
}