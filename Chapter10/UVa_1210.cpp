#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

const static int maxn = 10001;
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

static void solve(int n)
{
	int solutionCnt = 0;
	int primesCnt = primes[0];
	int left = 0, right = 0;
	int flag = 0;
	while (right < cnt)
	{
		if (primes[right] > n) break;
		while (primesCnt < n && right < cnt - 1)
		{
			++right;
			primesCnt += primes[right];
		}
		if (right == cnt - 1)
		{
			if (primesCnt == n) ++solutionCnt;
			break;
		}
		if (primesCnt == n) // 正好left到right的素数加起来等于n
		{
			++solutionCnt;
			left = min(left + 2, right);
			if (left == right) primesCnt = primes[left];
			else primesCnt -= primes[left - 2] + primes[left - 1];
			if (primesCnt == n)break;
			continue;
		}
		// left到right的素数加起来大于n
		while (primesCnt > n)
		{
			primesCnt -= primes[left];
			++left;
		}
		if (primesCnt == n) // 正好left到right的素数加起来等于n
		{
			++solutionCnt;
			left = min(left + 2, right);
			if (left == right) primesCnt = primes[left];
			else primesCnt -= primes[left - 2] + primes[left - 1];
			if (primesCnt == n)break;
		}
	}
	cout << solutionCnt << endl;
}

int UVa_1210()
{
	const char* input = "inputs/1210.txt";
	freopen(input, "r", stdin);
	makePrimes();
	int n;
	while (cin >> n && n)
	{
		solve(n);
	}
	return 0;
}