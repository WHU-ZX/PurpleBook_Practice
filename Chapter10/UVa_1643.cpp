#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;




int UVa_1643() // 注意，输入有可能使得 k1<k2
{
	//const char* input = "inputs/1643.txt";
	const char* input = "inputs/a.txt";
	freopen(input, "r", stdin);
	int squareNum;
	double edgeLengthes[10];
	double xa, ya, xb, yb, k1, k2;
	double x1, y1, x2, y2;
	double S_minus, L, S_triangle, S;
	while (cin >> squareNum && squareNum)
	{
		cin >> xa >> ya >> xb >> yb;
		k1 = ya / xa;
		k2 = yb / xb;
		for (int i = 0; i < squareNum; ++i) cin >> edgeLengthes[i];
		S_minus = L = 0;
		for (int i = 0; i < squareNum; ++i)
		{
			S_minus += edgeLengthes[i] * edgeLengthes[i] / 2;
			L += edgeLengthes[i];
		}
		x1 = (k2 + 1) * L / (k1 - k2);
		y1 = x1 * k1;
		x2 = (k1 + 1) * L / (k1 - k2);
		y2 = x2 * k2;
		S_triangle = (x1 > 0 ? (x2 * y1) : (x1 * y2)) - x1 * y1 / 2 - x2 * y2 / 2 - L * L / 2;
		S = S_triangle - S_minus;
		printf("%.3lf\n", S);
	}
	return 0;
}