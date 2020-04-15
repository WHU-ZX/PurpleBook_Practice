#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

struct Section // Çø¼ä
{
	double l, r;
};
static int n, L, D;
static Section* pSc = NULL;
static bool cmp(Section s1, Section s2)
{
	if (s1.r != s2.r) return s1.r < s2.r;
	return s1.l < s2.l;
}

int UVa_1615()
{
	const char* input = "inputs/1615.txt";
	//const char* output = "outputs/1615.txt";
	freopen(input, "r", stdin);

	while (cin >> L >> D >> n)
	{
		int tx, ty;
		pSc = new Section[n];
		for (int i = 0; i < n; ++i)
		{
			cin >> tx >> ty;
			double dx = sqrt(D * D - ty * ty);
			double l = tx - dx >= 0 ? tx - dx : 0;
			double r = tx + dx <= L ? tx + dx : L;
			pSc[i].l = l;
			pSc[i].r = r;
		}
		sort(pSc, pSc + n, cmp);
		int cur = 0, cnt = 0;
		while (cur < n)
		{
			int limit = pSc[cur].r;
			int i = cur + 1;
			for (;i < n; ++i)
			{
				if (pSc[i].l > limit)
				{
					break;
				}
			}
			cur = i;
			++cnt;
		}
		cout << cnt << endl;
		delete[] pSc;
		pSc = NULL;
	}

	return 0;
}