#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;
#define LL long long

const static int maxn = 1000001;
static int vis[maxn], primes[maxn], cnt;

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

int UVa_10539()
{
	const char* input = "inputs/10539.txt";
	freopen(input, "r", stdin);

	int testCase;
	cin >> testCase;
	makePrimes();
	LL L, U;
	while (testCase--)
	{
		cin >> L >> U;
		LL ans = 0;
		for (int i = 0; i < cnt && primes[i] < U; ++i)
		{
			LL left = (LL)(log(L - 0.01) / log(primes[i]));
			LL right = (LL)(log(U + 0.01) / log(primes[i]));
			ans += right - left;
			if (primes[i] >= L && primes[i] <= U) --ans;
		}
		printf("%lld\n", ans);
	}
	return 0;
}