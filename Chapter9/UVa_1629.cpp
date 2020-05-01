#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 20+1, Inf = 0x2FFFFFFF;
static int mp[MAXN][MAXN];
static int d[MAXN][MAXN][MAXN][MAXN];//d[i][j][k][l]，左上角(i,j),右下角(k,l),是格子的坐标
static int n, m, k;

static int sum(int x1, int y1, int x2, int y2)//(x1,y1)左上角顶点,(x2,y2)右下角顶点区域内的樱桃数,>=2统统返回2
{
	int count = 0;
	for (int i = x1; i <= x2; ++i)
		for (int j = y1; j <= y2; ++j)
			if (mp[i][j])
			{
				++count;
				if (count >= 2) return count;
			}
	return count;
}

static int DP(int x1, int y1, int x2, int y2)//(x1,y1)左上角顶点,(x2,y2)右下角顶点
{
	int& ans = d[x1][y1][x2][y2];
	if (ans != -1) return ans;
	int num = sum(x1, y1, x2, y2);
	if (num == 0)return ans = Inf;
	else if (num == 1)return ans = 0;
	ans = Inf;
	for (int i = x1; i < x2; ++i)
		ans = min(ans, DP(x1, y1, i, y2) + DP(i + 1, y1, x2, y2) + y2 - y1 + 1);
	for (int j = y1; j < y2; ++j)
		ans = min(ans, DP(x1, y1, x2, j) + DP(x1, j + 1, x2, y2) + x2 - x1 + 1);
	return ans;
}


int UVa_1629()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/1629.txt";
	//const char* output = "outputs/1629.txt";
	freopen(input, "r", stdin);
	int cas = 1;
	while (cin >> n >> m >> k)
	{
		memset(mp, 0, sizeof mp);
		memset(d, -1, sizeof d);
		int u, v;
		for (int i = 0; i < k; ++i)
		{
			cin >> u >> v;
			mp[u][v] = 1;
		}
		printf("Case %d: %d\n", cas++, DP(1, 1, n, m));
	}
	return 0;
}