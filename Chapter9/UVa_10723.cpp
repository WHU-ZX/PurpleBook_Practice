#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
const static int MAXL = 30 + 1;
static string gene1, gene2;
static int d[MAXL][MAXL];//d[i][j]表示gene1取前i个字符，gene2取前j个字符的LCS,答案为len1+len2-LCS
static long long ansNum[MAXL][MAXL];

int UVa_10723()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/10723.txt";
	//const char* output = "outputs/10723.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	int cas = 1;
	int L1, L2;
	while (testCase--)
	{
		cin >> gene1 >> gene2;
		memset(d, 0, sizeof d);
		memset(ansNum, 0, sizeof ansNum);
		L1 = gene1.length(); L2 = gene2.length();
		for (int i = 0; i <= L1; ++i) ansNum[i][0] = 1;
		for (int j = 0; j <= L2; ++j) ansNum[0][j] = 1;
		for (int i = 1; i <= L1; ++i)
		{
			for (int j = 1; j <= L2; ++j)
			{
				if (gene1[i - 1] == gene2[j - 1])
				{
					d[i][j] = d[i - 1][j - 1] + 1;
					ansNum[i][j] = ansNum[i - 1][j - 1];
				}
				else if (d[i - 1][j] > d[i][j - 1])
				{
					d[i][j] = d[i - 1][j];
					ansNum[i][j] = ansNum[i - 1][j];
				}
				else if (d[i - 1][j] < d[i][j - 1])
				{
					d[i][j] = d[i][j - 1];
					ansNum[i][j] = ansNum[i][j - 1];
				}
				else // d[i - 1][j] == d[i][j - 1]
				{
					d[i][j] = d[i - 1][j];
					ansNum[i][j] = ansNum[i - 1][j] + ansNum[i][j - 1];
					/*已经满足了gene1[i-1]!=gene2[j-1]，故ansNum[i - 1][j]种情况以gene1[i-1]结尾,
						ansNum[i][j - 1]种情况以gene2[j-1]结尾，肯定不会出现重复的情况
					*/
				}
			}
		}
		printf("Case #%d: %d %lld\n", cas++, L1 + L2 - d[L1][L2], ansNum[L1][L2]);
	}
	return 0;
}