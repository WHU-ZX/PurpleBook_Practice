#pragma once
#include "PieceDef.h"
#include <cstdio>
#include <map>
int Piece::realRedNum = 0;
Piece* Piece::blackG = nullptr;
Piece* Piece::redPieces = nullptr;
void Xiangqi()
{
	FILE* file = freopen("ChessGameInput.txt", "r", stdin);
	int redNum, bGx, bGy;
	int GameRound = 1;
	std::map<char, TYPE> myMap;
	//初始化map
	myMap['G'] = TYPE::G;
	myMap['H'] = TYPE::H;
	myMap['R'] = TYPE::R;
	myMap['C'] = TYPE::C;
	char _n;
	while (scanf("%d%d%d", &redNum, &bGx, &bGy) == 3 && redNum && bGx && bGy)
	{
		Piece reds[7];
		for (int i = 0; i < redNum; i++)
		{
			scanf("%c", &_n);
			char tC;
			int tX, tY;
			if (scanf("%c%d%d", &tC, &tX, &tY) == 3)
			{
				reds[i] = Piece(tX, tY, myMap[tC], true);
			}
			else
			{
				printf("输入有误！");
				return;
			}
		}
		Piece::initGame(new Piece(bGx, bGy, TYPE::G, false), reds, redNum);
		//printf("Round #%d\n\t", GameRound);
		if (Piece::redWin())
		{
			printf("YES");
		}
		else
		{
			printf("NO");
		}
		printf("\n");
		scanf("%c", &_n);
		scanf("%c", &_n);
		GameRound++;
	}
	fclose(file);
}




//此题输入：
/*
	示例：  每组以空行隔开
	2 1 4       第一个数字代表红方棋子个数，第二个数字表示黑将的x坐标，第三个数字表示黑将的y坐标
	G 10 5      第一个字母表示棋子类型，第二个数字表示x，第三个数字表示y
	R 6 4

	3 1 5
	H 4 5
	G 10 5
	C 7 5

	0 0 0
*/
