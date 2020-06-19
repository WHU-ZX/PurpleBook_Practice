#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;

//0左下   1左上   2上   3右上   4右下   5下
const static int drX[6] = { -1,0,1,1,0,-1 };
const static int drY[6] = { 0,-1,-1,0,1,1 };
static int x[10005], y[10005];


static void init()
{
	x[0] = y[0] = x[1] = y[1] = 0;
	x[2] = -1; y[2] = 1;
	int I = 3;
	int step = 1;
	while (I <= 10000) 
	{
		//左上step
		for (int i = 0; I <= 10000 && i < step - 1; ++i,++I)
		{
			x[I] = x[I - 1] + drX[0];
			y[I] = y[I - 1] + drY[0];
		}
		//上step
		for (int i = 0; I <= 10000 && i < step; ++i, ++I)
		{
			x[I] = x[I - 1] + drX[1];
			y[I] = y[I - 1] + drY[1];
		}
		//右上step
		for (int i = 0; I <= 10000 && i < step; ++i, ++I)
		{
			x[I] = x[I - 1] + drX[2];
			y[I] = y[I - 1] + drY[2];
		}
		//右下step
		for (int i = 0; I <= 10000 && i < step; ++i, ++I)
		{
			x[I] = x[I - 1] + drX[3];
			y[I] = y[I - 1] + drY[3];
		}
		//下step
		for (int i = 0; I <= 10000 && i < step; ++i, ++I)
		{
			x[I] = x[I - 1] + drX[4];
			y[I] = y[I - 1] + drY[4];
		}
		//左下step-1
		for (int i = 0; I <= 10000 && i < step + 1; ++i, ++I)
		{
			x[I] = x[I - 1] + drX[5];
			y[I] = y[I - 1] + drY[5];
		}
		++step;
	}
}


int WF_UVa_808()
{
	const char* input = "inputs/808.txt";
	//const char* output = "outputs/808.txt";
	freopen(input, "r", stdin);
	init();
	int a, b;
	while (cin >> a >> b && (a || b))
	{
		int nX = x[a] - x[b];
		int nY = y[a] - y[b];
		int ans = nX * nY >= 0 ? abs(nX) + abs(nY) : max(abs(nX), abs(nY));
		printf("The distance between cells %d and %d is %d.\n", a, b, ans);
	}
	return 0;
}