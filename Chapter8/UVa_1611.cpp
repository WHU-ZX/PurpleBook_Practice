#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 10001, MAX_OP_NUM = 531441;
static int numbers[MAXN], n;
static int ans[2][2 * MAXN], ansNum;

static int m_find(int num, int start)
{
	for (int i = start; i <= n; ++i)
	{
		if (numbers[i] == num) return i;
	}
	return 0;
}

static void m_swap(int s, int e)
{
	int e1 = (s + e) / 2;
	int s2 = (s + e + 1) / 2;
	for (int i = s, j = s2; i <= e1 && j <= e; ++i, ++j)
	{
		int tmp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = tmp;
	}
}

int UVa_1611()
{
	const char* input = "inputs/1611.txt";
	//const char* output = "outputs/1611.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		cin >> n;
		for (int i = 1; i <= n; ++i)
			cin >> numbers[i];
			
		int curIdx = 0;
		ansNum = 0;
		while (curIdx != n)
		{
			curIdx++;//目的idx--也是数字
			int idx = m_find(curIdx, curIdx);
			if ((idx - curIdx) % 2 == 0)//奇数
			{
				if (curIdx == idx) continue;
				m_swap(curIdx + 1, idx);
				ans[0][ansNum] = curIdx + 1;
				ans[1][ansNum++] = idx;
				m_swap(curIdx, idx - 1);
				ans[0][ansNum] = curIdx;
				ans[1][ansNum++] = idx - 1;
			}
			else//偶数
			{
				m_swap(curIdx, idx);
				ans[0][ansNum] = curIdx;
				ans[1][ansNum++] = idx;
				if (idx - curIdx >= 3)
				{
					m_swap(curIdx, idx - 2);
					ans[0][ansNum] = curIdx;
					ans[1][ansNum++] = idx - 2;
				}
			}
		}
		cout << ansNum << endl;
		for (int i = 0; i < ansNum; ++i)
		{
			cout << ans[0][i] << ' ' << ans[1][i] << endl;
		}
	}

	return 0;
}