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















// ���ٰ�..
///*
//	lastLevelNum:��һ��һ���ж��ٸ�
//	restNum:����һ�㻹ʣ�¶��ٸ�
//	���뱣֤restNum��0������lastLevelNum��������
//*/
//static int get(int lastLevelNum, int restNum)
//{
//	if (restNum == 0) return 1;
//	//restNum��lastLevelNum��������
//	int ans = 0;
//	int maxNum = restNum / lastLevelNum;
//	for (int newLevelNum = 1; newLevelNum <= maxNum; ++newLevelNum)
//	{
//		int newRestNum = maxNum - newLevelNum;
//		if (newRestNum % newLevelNum == 0) // ��ʾ��ô����֮�󣬺��滹������ȥ��newRestNumΪ0ʱҲ����
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