#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#pragma warning(disable:4996)
using namespace std;

const static int MAXN = 15001;
static int cur, n, cn;
static int ans[MAXN];

static void move(int step)
{
	cur += step;
	ans[cn++] = cur;
}
static void print()
{
	for (int i = 0; i < n - 1; ++i)
		cout << ans[i] << ' ';
	cout << ans[n - 1] << endl;
}

int UVa_1621()
{
	//const char* input = "inputs/a.txt";
	const char* input = "inputs/1621.txt";
	//const char* output = "outputs/1621.txt";
	freopen(input, "r", stdin);
	int a, b, c;
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		cin >> a >> b >> c;
		n = a + b + c + 1;
		cn = cur = 0;
		ans[cn++] = 0;
		if (c % 3 == 0)
		{
			for (int i = 0; i < c / 3; ++i) move(3);
			move(1); --a;
			for (int i = 0; i < c / 3; ++i) move(-3);
			move(1); --a;
			for (int i = 0; i < c / 3; ++i) move(3);
		}
		else if (c % 3 == 1)
		{
			for (int i = 0; i < c / 3 + 1; ++i) move(3);
			move(-2); --b;
			for (int i = 0; i < c / 3; ++i) move(-3);
			move(1); --a;
			for (int i = 0; i < c / 3; ++i) move(3);
			move(2); --b;
		}
		else // c % 3 == 2
		{
			for (int i = 0; i < c / 3 + 1; ++i) move(3);
			move(-2); --b;
			for (int i = 0; i < c / 3; ++i) move(-3);
			move(1); --a;
			for (int i = 0; i < c / 3 + 1; ++i) move(3);
			move(-1); --a;
			move(2); --b;
		}
		c = 0;
		while (a > 1)
		{
			move(1); --a;
		}
		while (b && cur + 2 <= n - 1)
		{
			move(2); --b;
		}
		if (cur == n - 1) move(-1);
		else move(1);
		--a;
		while (b--) move(-2);
		print();
	}
	return 0;
}