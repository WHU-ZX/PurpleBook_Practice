#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
#define Local
using namespace std;
const static int MAXM = 31, MAXN = 101, Inf = 0x3f3f3f3f;
static int d[MAXN][MAXM], cost[MAXN][MAXM], P[MAXM], m, n;

static void solve()
{
	//寻找最大安全值
	memset(d, 0, sizeof d);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			//不选择j
			d[i][j] = d[i][j - 1];
			//选择j
			for (int k = 1; k <= i; ++k)//让j守k个仓库
			{
				int x;
				if (k == i) x = P[j] / k;
				else x = min(P[j] / k, d[i - k][j - 1]);
				if (x > d[i][j]) d[i][j] = x;
			}
		}
	//寻找最小支出
	memset(cost, Inf, sizeof cost);
	memset(cost[0], 0, sizeof cost[0]);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			//假设不选择j
			cost[i][j] = cost[i][j - 1];
			//选择k
			for (int k = 1; k <= i; ++k)
			{
				int safe = P[j] / k;
				if (safe >= d[n][m]) cost[i][j] = min(cost[i][j], (cost[i - k][j - 1] + P[j]));
			}
		}
	}
}


int UVa_10163()
{
#ifdef Local
	const char* input = "inputs/10163.txt";
	//const char* output = "outputs/10163.txt";
	freopen(input, "r", stdin);
#endif // Local
	while (cin >> n >> m && n&& m)
	{
		for (int i = 1; i <= m; ++i) cin >> P[i];
		solve();
		printf("%d %d\n", d[n][m], d[n][m] == 0 ? 0 : cost[n][m]);
	}
	return 0;
}