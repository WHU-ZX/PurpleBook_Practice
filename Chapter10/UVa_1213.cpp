#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

const static int maxn = 1121, maxk = 15;
static int vis[maxn], primes[maxn], cnt;
static int dp[maxn][maxk];

static void makePrimes()
{
	memset(vis, 0, sizeof vis);
	int m = sqrt(maxn + 0.5);
	for (int i = 2; i <= m; ++i)
		if (!vis[i]) for (int j = i * i; j <= maxn; j += i) vis[j] = 1;
	cnt = 0; vis[0] = vis[1] = 1;
	for (int i = 0; i < maxn; ++i)
		if (!vis[i]) primes[cnt++] = i;
}

static void makeTable()
{
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for (int i = 0; i < cnt; ++i)
	{
		for (int n = maxn; n >= primes[i]; --n)//倒着枚举：假设n小的时候选择了数字a，则n更大的时候不能再选择a，否则选了2个a
		{
			for (int k = 1; k < maxk; ++k)
			{
				dp[n][k] += dp[n - primes[i]][k - 1];
			}
		}
	}

}

int UVa_1213()
{
	const char* input = "inputs/1213.txt";
	freopen(input, "r", stdin);
	int n, k;
	makePrimes();
	makeTable();
	while (~scanf("%d%d", &n, &k) && (n || k))
	{
		cout << dp[n][k] << endl;
	}
	return 0;
}