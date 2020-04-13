#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;
static int n;
const static int MAXN = 16384 + 5;
const static int Inf = 1 << 31 - 1;
const static int v[8][3] = { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
struct Item
{
	int id;
	int scores[8];
	int rank;
};
static Item items[MAXN];
static bool cmp1(int i1, int i2)
{
	return i1 > i2;
}
static bool cmp2(Item i1, Item i2)
{
	return i1.rank < i2.rank;
}

int UVa_1612()//输入里的n行是按id号给的第1行是id为1的得分
{
	const char* input = "inputs/1612.txt";
	//const char* output = "outputs/1612.txt";
	freopen(input, "r", stdin);
	int cas = 1;
	while (cin >> n && n)
	{
		double temps[3];
		int iTemps[3];
		for (int i = 0; i < n; ++i)
		{
			cin >> temps[0] >> temps[1] >> temps[2];
			for (int j = 0; j < 3; ++j)
				iTemps[j] = (int)round(100 * temps[j]);
			for (int j = 0; j < 8; ++j)
				items[i].scores[j] = v[j][0] * iTemps[0] + v[j][1] * iTemps[1] + v[j][2] * iTemps[2];
			items[i].id = i + 1;
			sort(items[i].scores, items[i].scores + 8, cmp1);
		}
		int t;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			items[t - 1].rank = i + 1;
		}
		sort(items, items + n, cmp2);
		//开始
		bool ok = true;
		int lastScore = Inf, lastId = 0;
		for (int i = 0; i < n; ++i)
		{
			bool f = false;
			for (int j = 0; j < 8; ++j)
			{
				if (items[i].scores[j] < lastScore || items[i].scores[j] == lastScore && items[i].id > lastId)
				{
					f = true;
					lastScore = items[i].scores[j];
					lastId = items[i].id;
					break;
				}
			}
			if (!f)
			{
				ok = false;
				break;
			}
		}
		printf("Case %d: ", cas++);
		if (ok)
			printf("%.2lf\n", lastScore / 100.0);
		else
			printf("No solution\n");
	}
	return 0;
}