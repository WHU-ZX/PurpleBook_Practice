#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 100000;
struct Node
{
	int idx;
	int ans;
	int num;
};
static Node numbers[MAXN + 1];
static int n, cnt;

static bool cmpNum(Node n1, Node n2)
{
	return n1.num < n2.num;
}

static bool cmpIdx(Node n1, Node n2)
{
	return n1.idx < n2.idx;
}

static bool solve()
{
	if (cnt % 2 == 1)
		return false;
	cnt /= 2;
	sort(numbers + 1, numbers + n + 1, cmpNum);
	int k = n;
	while (k >= 1 && cnt > 0)
	{
		if (numbers[k].num <= cnt)
		{
			cnt -= numbers[k].num;
			numbers[k].ans = 1;
		}
		--k;
	}
	if (cnt == 0) return true;
	return false;
}

int UVa_1614()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/1614.txt";
	//const char* output = "outputs/1614.txt";
	freopen(input, "r", stdin);
	while (cin >> n)
	{
		cnt = 0;
		int t;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			numbers[i + 1].num = t;
			numbers[i + 1].idx = i + 1;
			numbers[i + 1].ans = -1;
			cnt += t;
		}
		if (solve())
		{
			cout << "Yes" << endl;
			sort(numbers + 1, numbers + n + 1, cmpIdx);
			cout << numbers[1].ans;
			for (int i = 2; i <= n; ++i)
				cout << ' ' << numbers[i].ans;
			cout << endl;
		}
		else
			cout << "No" << endl;
	}
	return 0;
}