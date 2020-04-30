#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;

const static int MAXN = 40 + 1, Inf = 0x7FFFFFFF;
static int piles[4][MAXN], top[4];
static int d[MAXN][MAXN][MAXN][MAXN];//d[i][j][k][l]表示第1堆拿了i个，第2堆拿了j个。。。之后，兜里最大的糖果对数
static int n;//每堆有n个
static bool vis[21];

static int DP(int k)//k为篮子里的数目
{
	int& ans = d[top[0]][top[1]][top[2]][top[3]];
	if (ans != -1)return ans;
	ans = 0;
	if (k >= 5)return ans;
	for (int i = 0; i < 4; ++i)
	{
		if (top[i] == n) continue;
		++top[i];
		if (vis[piles[i][top[i]-1]])
		{
			vis[piles[i][top[i]-1]] = false;
			ans = max(ans, DP(k - 1) + 1);
			vis[piles[i][top[i]-1]] = true;
		}
		else
		{
			vis[piles[i][top[i]-1]] = true;
			ans = max(ans, DP(k + 1));
			vis[piles[i][top[i]-1]] = false;
		}
		--top[i];
	}
	return ans;
}

int UVa_10118()
{
	const char* input = "inputs/10118.txt";
	//const char* output = "outputs/10118.txt";
	freopen(input, "r", stdin);
	while (cin >> n && n)
	{
		for (int i = 0; i < n; ++i)
			cin >> piles[0][i] >> piles[1][i] >> piles[2][i] >> piles[3][i];
		memset(d, -1, sizeof d);
		memset(top, 0, sizeof top);
		memset(vis, false, sizeof vis);
		printf("%d\n", DP(0));
	}
	return 0;
}

