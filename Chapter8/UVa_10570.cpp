#include <cstdio>
#include <iostream>
#include <algorithm>
//#include <map>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 500;
static int n, offset;
static int numbers[MAXN + 1], rMap[MAXN + 1];
static bool vis[MAXN + 1];
//static map<int, int> M;

static int find1(int number)
{
	for (int i = 0; i < n; ++i)
		if ((number + offset) % n == numbers[i]) return i;
	return -1;
}

static int find2(int number)
{
	for (int i = 0; i < n; ++i)
		if ((number + offset + numbers[i]) % n == n - 1) return i;
	return -1;
}

static int getDirectedCurcleNum()
{
	memset(vis, false, sizeof vis);
	int cnt = 0;
	//int orderedNum = 0;
	for (int i = 0; i < n; ++i)
	{
		if (vis[i])
			continue;
		else if (numbers[i] == (i + offset) % n)
		{
			vis[i] = true;
			++cnt;
		}
		else
		{
			int j = i;
			while (!vis[j])
			{
				vis[j] = true;
				j = rMap[(j + offset) % n];
			}
			++cnt;
		}
	}
	return cnt;
}

static int getReverseDirectedCurcleNum()
{
	memset(vis, false, sizeof vis);
	int cnt = 0;
	for (int i = 0; i < n; ++i)
	{
		if (vis[i])
			continue;
		else if ((numbers[i] + i + offset) % n == n - 1)
		{
			vis[i] = true;
			++cnt;
		}
		else
		{
			int j = i;
			while (!vis[j])
			{
				vis[j] = true;
				j = rMap[(2 * n - 1 - j - offset) % n];
			}
			++cnt;
		}
	}
	return cnt;
}

int UVa_10570()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/10570.txt";
	//const char* output = "outputs/10570.txt";
	freopen(input, "r", stdin);
	while (cin >> n && n)
	{
		//M.clear();
		int m = -1, temp;
		for (int i = 0; i < n; ++i)
		{
			cin >> temp;
			numbers[i] = temp - 1;
			rMap[temp - 1] = i;
		}
		for (offset = 0; offset < n; ++offset) // 从 1 到 n，offset是开头
		{
			int cnt = getDirectedCurcleNum();
			m = m > cnt ? m : cnt;
			cnt = getReverseDirectedCurcleNum();
			m = m > cnt ? m : cnt;
		}
		cout << n - m << endl;
	}
	return 0;
}