#include <cstdio>
#include <iostream>
#include <map>
#include <string.h>

using namespace std;

static int NP;//库所数
static int NT;//事务数
static int NF;//最大模拟次数
const static int maxn = 101;


static struct Transaction
{
	map<int,int> input,output;//map<指向的下标,token数目>
}T[maxn];

static int P[maxn];

static void clear()
{
	memset(P, 0, sizeof(P));
	for (int i = 0; i < maxn; i++)
	{
		if (!T[i].input.empty())
			T[i].input.clear();
		if (!T[i].output.empty())
			T[i].output.clear();
	}
}

static void exec(int tIdx)//执行下标为tIdx的事务
{
	for (map<int, int>::iterator iter = T[tIdx].input.begin(); iter != T[tIdx].input.end(); iter++)
	{
		P[iter->first] -= iter->second;
	}
	for (map<int, int>::iterator iter = T[tIdx].output.begin(); iter != T[tIdx].output.end(); iter++)
	{
		P[iter->first] += iter->second;
	}
}

int WF_UVa_804()
{
	const char* input = "inputs/WF_804.txt";
	const char* output = "outputs/WF_804.txt";
	freopen(input, "r", stdin);
	int gameNum = 1;
	while (cin >> NP && NP != 0)
	{
		clear();
		for (int i = 1; i <= NP; i++)
		{
			cin >> P[i];
		}
		cin >> NT;
		for (int i = 1; i <= NT; i++)
		{
			int temp;
			while (cin >> temp && temp != 0)
			{
				if (temp > 0)
					T[i].output[temp]++;
				else
					T[i].input[-temp]++;
			}
		}
		cin >> NF;
		int finishedNum = 0;//运行到结束完成了多少次事务
		while (finishedNum < NF)
		{
			int i;
			for (i = 1; i <= NT; i++)
			{
				bool flag = true;
				for (map<int, int>::iterator iter = T[i].input.begin(); iter != T[i].input.end(); iter++)
				{
					if (P[iter->first] < iter->second)
					{
						flag = false;
						break;
					}
				}
				if (flag) break;
			}
			if (i <= NT)//找到事务
				exec(i);
			else//没有能够运行的事务
				break;
			finishedNum++;
		}
		if (finishedNum == NF)//完成
			cout << "Case " << gameNum << ": still live after " << NF << " transitions" << endl;
		else//未完成
			cout << "Case " << gameNum << ": dead after " << finishedNum << " transitions" << endl;

		cout << "Places with tokens:";
		for (int i = 1; i <= NP; i++)
			if (P[i] > 0)
				cout << ' ' << i << " (" << P[i] << ')';
		cout << endl << endl;
		gameNum++;
	}
	return 0;
}