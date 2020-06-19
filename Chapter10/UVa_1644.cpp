#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;
static const int maxn = 1300000;
static bool vis[maxn];

int UVa_1644()
{
	const char* input = "inputs/1644.txt";
	freopen(input, "r", stdin);
	memset(vis, false, sizeof vis);
	//打素数表，vis=1表示不是素数，vis=0表示是素数
	int m = sqrt(maxn + 0.5);
	for (int i = 2; i <= m; ++i) 
		if (!vis[i]) for (int j = i * i; j <= maxn; j += i) vis[j] = 1;
	int n;
	while (cin >> n && n)
	{
		if (vis[n]) //不是素数
		{
			int left = n;
			int right = n;
			while (vis[left]) --left;
			while (vis[right])++right;
			printf("%d\n", right - left);
		}
		else // 是素数
		{
			printf("0\n");
		}
	}
	return 0;
}