#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
static const int MAXN = 100000;
static int n;
static int rows[2 * MAXN];
static int indexs[2 * MAXN];//数字i所对应的配偶的下标
static bool vis[2 * MAXN];

static void swp(int i, int j,int mode)//交换下标为i，j的数,mode = -1则交换后下标i匹配了，1则j匹配了，0则i，j都匹配了
{
	if (mode == 0)
	{
		if (i % 2)
			vis[i - 1] = vis[i] = true;
		else
			vis[i + 1] = vis[i] = true;
		if (j % 2)
			vis[j - 1] = vis[j] = true;
		else
			vis[j + 1] = vis[j] = true;
	}
	else if (mode == 1)
	{
		if (j % 2)
			vis[j - 1] = vis[j] = true;
		else
			vis[j + 1] = vis[j] = true;
		int numI = rows[i], numJ = rows[j];
		if (numI % 2)indexs[numI - 1] = j;
		else indexs[numI + 1] = j;
		rows[i] = numJ; rows[j] = numI;//交换i j
	}
	else// -1
	{
		if (i % 2)
			vis[i - 1] = vis[i] = true;
		else
			vis[i + 1] = vis[i] = true;
		int numI = rows[i], numJ = rows[j];
		if (numJ % 2)indexs[numJ - 1] = i;
		else indexs[numJ + 1] = i;
		rows[i] = numJ; rows[j] = numI;//交换i j
	}
}

static bool has2(int i)//返回下标为i的能否通过与某个值交换从而直接完成2对的匹配，有返回true
{
	//idx 一定为偶数
	int idxI = indexs[rows[i]];
	int changeIdx;
	if (idxI % 2)//奇数
		changeIdx = idxI - 1;
	else 
		changeIdx = idxI + 1;
	if (abs(rows[changeIdx] - rows[i + 1]) == 1 && (rows[changeIdx] + rows[i + 1] + 1) % 4)
		return true;
	return false;
}

int Q2()
{
	const char* input = "inputs/Q2.txt";
	//const char* output = "outputs/Q2.txt";
	freopen(input, "r", stdin);
	cin >> n;
	for (int i = 0; i < 2 * n; ++i)
	{
		cin >> rows[i];
		if (rows[i] % 2 == 0)//偶数
			indexs[rows[i] + 1] = i;
		else//奇数
			indexs[rows[i] - 1] = i;
	}
	int twiceNum = 0, visCnt = 0, lastUnVis = 0;
	bool find2 = false, getLastUnVis = false;
	while (visCnt < 2 * n)
	{
		find2 = false;
		lastUnVis = 0;
		int i;
		for (i = 0; i < 2 * n; i += 2)
		{
			if (vis[i]) continue;
			if (has2(i))
			{
				find2 = true;
				break;
			}
			else if (!getLastUnVis)
			{
				lastUnVis = i;
				getLastUnVis = true;
			}
		}
		if (find2)
		{
			int cI = indexs[rows[i]];
			if (cI % 2) swp(i, cI - 1, 0);
			else swp(i, cI + 1, 0);
			visCnt += 4;
			twiceNum += 1;
		}
		else
		{
			int cI = indexs[rows[lastUnVis]];
			if (cI % 2) swp(lastUnVis, cI - 1, 1);
			else swp(lastUnVis, cI + 1, 1);
			visCnt += 2;
		}
	}
	cout << n - twiceNum << endl;
	return 0;
}