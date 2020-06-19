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
	//��������vis=1��ʾ����������vis=0��ʾ������
	int m = sqrt(maxn + 0.5);
	for (int i = 2; i <= m; ++i) 
		if (!vis[i]) for (int j = i * i; j <= maxn; j += i) vis[j] = 1;
	int n;
	while (cin >> n && n)
	{
		if (vis[n]) //��������
		{
			int left = n;
			int right = n;
			while (vis[left]) --left;
			while (vis[right])++right;
			printf("%d\n", right - left);
		}
		else // ������
		{
			printf("0\n");
		}
	}
	return 0;
}