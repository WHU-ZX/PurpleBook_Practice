#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 100000, Inf = 0x7FFFFFFF;
static int n, minLen;
static struct Session
{
	int l, r;
	bool operator < (const Session sr)const
	{
		return l < sr.l;
	}
};
static Session sessions[MAXN];
const static double EPS = 1e-10;

static bool solve(double len) // ��ȱ�ݣ���������1��[0,5]������2��[1,3],������lenΪ2ʱ��ԭ���ǿ���ͨ���ģ����˴��ж�Ϊ������
{
	double last = 0;
	for (int i = 0; i < n; ++i)
	{
		if (sessions[i].l > last)
		{
			if (sessions[i].l + len > sessions[i].r) return false;
			last = sessions[i].l + len;
		}
		else
		{
			if (last + len > sessions[i].r) return false;
			last += len;
		}
	}
	return true;
}

int UVa_1616()
{
	const char* input = "inputs/1616.txt";
	//const char* output = "outputs/1616.txt";
	freopen(input, "r", stdin);
	while (cin >> n)
	{
		int tl, tr;
		minLen = Inf;
		for (int i = 0; i < n; ++i)
		{
			cin >> tl >> tr;
			sessions[i].l = tl;
			sessions[i].r = tr;
			minLen = minLen < (tr - tl) ? minLen : tr - tl;
		}
		sort(sessions, sessions + n);
		double L = 0.0, R = 2.0 * minLen + 1;
		while ((R - L) > EPS)
		{
			double mid = (L + R) / 2.0;
			if (solve(mid)) L = mid;
			else R = mid;
		}
		//С���Ĵ��� ---- ֵ�ý��
		int p = 0, q = 1;
		for (int i = 1; i <= n; i++)
		{
			int k = round(L * i);
			if (fabs((double)k / i - L) < fabs((double)p / q - L))
			{
				p = k;
				q = i;
			}
		}
		printf("%d/%d\n", p, q);
		//cout << R;
	}

	return 0;
}