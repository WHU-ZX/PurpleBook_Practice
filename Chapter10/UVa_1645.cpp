#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

const static int mod = 1000000007, maxn = 1001;
static int dp[maxn];

static void calculate_table()
{
	memset(dp, 0, sizeof dp);
	dp[1] = 1;
	for (int i = 2; i < maxn; ++i)
	{
		for (int j = 1; j <= i - 1; ++j)
		{
			if ((i - 1) % j == 0)
			{
				dp[i] += dp[(i - 1) / j];
				dp[i] %= mod;
			}
		}
	}
}

int UVa_1645()
{
	const char* input = "inputs/1645.txt";
	freopen(input, "r", stdin);
	int cas = 0;
	int n;
	calculate_table();
	while (cin >> n)
	{
		printf("Case %d: %d\n", ++cas, dp[n]);
	}
	return 0;
}















// 低速版..
///*
//	lastLevelNum:上一层一共有多少个
//	restNum:到这一层还剩下多少个
//	输入保证restNum是0或者是lastLevelNum的整数倍
//*/
//static int get(int lastLevelNum, int restNum)
//{
//	if (restNum == 0) return 1;
//	//restNum是lastLevelNum的整数倍
//	int ans = 0;
//	int maxNum = restNum / lastLevelNum;
//	for (int newLevelNum = 1; newLevelNum <= maxNum; ++newLevelNum)
//	{
//		int newRestNum = maxNum - newLevelNum;
//		if (newRestNum % newLevelNum == 0) // 表示这么做了之后，后面还能做下去，newRestNum为0时也可以
//		{
//			ans += get(newLevelNum * lastLevelNum, newRestNum * lastLevelNum);
//			ans %= mod;
//		}
//	}
//	return ans;
//}
//
//int UVa_1645()
//{
//	const char* input = "inputs/1645.txt";
//	freopen(input, "r", stdin);
//	int cas = 0;
//	int n;
//	while (cin >> n)
//	{
//		printf("Case %d: %d\n", ++cas, get(1, n - 1));
//	}
//	return 0;
//}