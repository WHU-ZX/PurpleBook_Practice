#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 1000;
const static int Inf = 1 << 31 - 1;
static int n;

static string strs[MAXN];
int UVa_1610()
{
	const char* input = "inputs/1610.txt";
	//const char* output = "outputs/1610.txt";
	freopen(input, "r", stdin);
	while (cin >> n && n)
	{
		int minLen = Inf;
		for (int i = 0; i < n; ++i)
		{
			cin >> strs[i];
			if (strs[i].size() < minLen) minLen = strs[i].size();
		}
			

		sort(strs, strs + n);
		string str1 = strs[(n - 1) / 2], str2 = strs[n / 2];
		//求出大于等于str1、小于str2的字典序最小的字符串
		string tS = "";
		for (int len = 0;; ++len)
		{
			tS = str1.substr(0, len);
			tS += ' ';
			bool ok = false;
			for (char c = 'A'; c <= 'Z'; ++c)
			{
				tS[len] = c;
				if (tS >= str1 && tS < str2)
				{
					ok = true;
					break;
				}
			}
			if (ok) break;
		}
		cout << tS << endl;
	}
	return 0;
}