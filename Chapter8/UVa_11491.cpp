#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 10000;
static int n, d;
static char number[MAXN];
static string str;

static string solve(int rest, string str)
{
	int start = 0;
	while (rest)
	{
		char max = str[start];
		int idx = start;
		int size = str.size();
		for (int i = start; i < size && i <= start + rest; ++i)
		{
			if (str[i] > max)//不能取等，因为要选最左边的最大值
			{
				max = str[i];
				idx = i;
			}
		}
		if (idx == start)//最大的是start ---- 直接右移
		{
			if (size - start - 1 <= rest)//删除start后所有的
			{
				return str.substr(0, n-d);
			}
			else // start 右移
				++start;
		}
		else
		{
			rest -= idx - start;
			str.replace(start, (long long)idx - start, "");
			++start;
		}
	}
	return str;
}

int UVa_11491()
{
	const char* input = "inputs/11491.txt";
	//const char* output = "outputs/11491.txt";
	freopen(input, "r", stdin);
	while (cin >> n >> d && n && d)
	{
		cin >> str;
		cout << solve(d, str) << endl;
	}
	return 0;
}