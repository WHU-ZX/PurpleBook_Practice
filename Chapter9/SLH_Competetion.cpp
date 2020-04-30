#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
static const int MAXN = 100000;
static int n;
static int rows[2 * MAXN];
static int indexs[2 * MAXN];//����i����Ӧ����ż���±�
static bool vis[2 * MAXN];

static void swp(int i, int j,int mode)//�����±�Ϊi��j����,mode = -1�򽻻����±�iƥ���ˣ�1��jƥ���ˣ�0��i��j��ƥ����
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
		rows[i] = numJ; rows[j] = numI;//����i j
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
		rows[i] = numJ; rows[j] = numI;//����i j
	}
}

static bool has2(int i)//�����±�Ϊi���ܷ�ͨ����ĳ��ֵ�����Ӷ�ֱ�����2�Ե�ƥ�䣬�з���true
{
	//idx һ��Ϊż��
	int idxI = indexs[rows[i]];
	int changeIdx;
	if (idxI % 2)//����
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
		if (rows[i] % 2 == 0)//ż��
			indexs[rows[i] + 1] = i;
		else//����
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