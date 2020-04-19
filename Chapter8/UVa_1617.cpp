#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 100000;
static int n;
static struct Seg
{
	int a, b;
	bool operator < (const Seg s2) const
	{
		return b < s2.b || (b == s2.b && a < s2.a);
	}
};
static Seg segs[MAXN];

int UVa_1617()
{
	const char* input = "inputs/1617.txt";
	//const char* output = "outputs/1617.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;

	while (testCase--)
	{
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> segs[i].a >> segs[i].b;
		}
		sort(segs, segs + n);
		int r = segs[0].b, ans = 0;
		for (int i = 1; i < n; ++i)
		{
			if (r == segs[i].b) continue;
			else if (r < segs[i].a)
			{
				++ans;
				r = segs[i].b;
			}
			else ++r;
		}
		cout << ans << endl;
	}
	return 0;
}