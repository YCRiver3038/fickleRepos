#include <stdio.h>
#include <stdlib.h>
#include "mods.h"

int main()
{
	int nExit = 1;
	unsigned int Base = 0;

	FILE *FdispC = NULL;

	FdispC = fopen("dispChars.bat", "w");

	if (FdispC == NULL)
	{
		printf("バッチファイルが作成できませんでした。\n");
	}
	else
	{
		fprintf(FdispC, "@echo off\n");
		fprintf(FdispC, "dispChars\n");
		fprintf(FdispC, "PAUSE\n");
		fprintf(FdispC, "exit\n");
		fclose(FdispC);
		system("start \"文字列一覧\" dispChars.bat");
	}

	printf("初代ポケモンのバグ技に関連する各種計算などを行います。\n");
	printf("\n一部の機能において、ポケモン緑(00A　後期)以外では違う結果になる可能性があります。\n");

	while (nExit != 0) 
	{
		printf("\n利用する機能を選んでください\n\n");
		printf("16進数から\t\t：16\n");
		printf("10進数から\t\t：10\n");
		printf("内部コード値からの変換\t：255\n");
		printf("データ検索\t\t：512\n");
		printf("やめる\t\t\t：0\n");
		if (scanf("%d", &Base) == 1)
		{
			fseek(stdin, (long)0, SEEK_SET);
			if (Base == 16) 
			{ 
				Spls16(); 
			}
			else if (Base == 10) 
			{ 
				Spls10(); 
			}
			else if (Base == 255) 
			{ 
				CV_Code();
			}
			else if (Base == 512)
			{
				CodeFind();
			}
			else if(Base == 0)
			{ 
				nExit = 0; 
			}
		}
		else
		{
			fseek(stdin, (long)0, SEEK_SET);
			printf("正しい数値を入力してください。\n");
		}
	}

	return 0;
}

/*
** 動作検証に利用したサイト（トップページ）一覧：
** http://www.geocities.jp/kattempla/pokebug/index.html
** http://www.msmrrenda.net/~renda/select/
*/
