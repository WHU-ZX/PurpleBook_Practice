#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
#define Local
using namespace std;
const static int MAXN = 31, MAXM = 1001, Inf = 0x3f3f3f3f;
const static double eps = 1e-6;
static int N, M;//N为边数，M为灯的数目
static struct Point
{
	double x, y;
};
static struct Session
{
	int L, R, C;
	bool contains(int idx)
	{
		if (L <= R) return idx >= L && idx <= R;
		else return idx >= R || idx <= L;
	}
};
static Point Ps[MAXN];
static Session Sess[MAXM];
//static int d[MAXN][MAXN];
static int d[MAXN * 2];//d[i]表示已经覆盖了点i的最小花费
static bool choosed[MAXM];//choosed表示是否选择此灯
/*
	如果OA×OB = xa*yb-xb*ya > 0，则A绕O按逆时针转才能转到B, = 0则三点共线, < 0 则A绕O按顺时针转才能转到B
*/
static bool judge(Point p0, Point p1, Point p2)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y) < -eps;
}

static Session construct(Point p, int c)
{
	Session sess;
	sess.C = c;
	bool flag[MAXN * 2] = { false };
	for (int i = 0; i < N; ++i)
		if (judge(p, Ps[i], Ps[i + 1])) flag[i] = true;

	if (flag[0] && flag[N - 1])
	{
		int L = N - 1, R = N;
		while (flag[L - 1]) --L;
		while (flag[R - N + 1]) ++R;
		sess.L = L; sess.R = R;
	}
	else
	{
		int L = 0, R = N - 1;
		while (!flag[L]) ++L;
		while (!flag[R]) --R;
		sess.L = L; sess.R = R;
	}
	if (sess.R < sess.L)sess.R += N;
	return sess;
}

static void solve()//不是太懂
{
	int ans = Inf;
	for (int i = 0; i < N; ++i)//枚举起点i
	{
		memset(d, Inf, sizeof d);
		d[i] = 0;
		for (int j = 0; j < N; ++j)
		{
			int r = i + j;//从第i个点开始往后数了j个；多定义这么一个层次，可以使状态的转移变得有序
			for (int k = 0; k < M; ++k)
			{
				if (Sess[k].L > r) continue;//该区间无法覆盖到此i~j
				if (Sess[k].R < r) continue;//剪枝，不再考虑不会成为最优解的情况
				int now = min(Sess[k].R + 1, i + N);//根据区间右端点往后更新，但是一旦更新过了i+n就要将端点定为i+n；
				d[now] = min(d[now], d[r] + Sess[k].C);
			}
		}
		ans = min(ans, d[i + N]);
	}
	if(ans==Inf) printf("Impossible.\n");
	else printf("%d\n", ans);
}

int UVa_10641()
{
#ifdef Local
	const char* input = "inputs/10641.txt";
	//const char* output = "outputs/10641.txt";
	freopen(input, "r", stdin);
#endif
	while (cin >> N && N)
	{
		for (int i = 0; i < N; ++i)cin >> Ps[i].x >> Ps[i].y;
		Ps[N] = Ps[0];
		cin >> M;
		for (int i = 0; i < M; ++i)
		{
			Point tp;
			int c;
			cin >> tp.x >> tp.y >> c;
			Sess[i] = construct(tp, c);
		}
		//然后就是选区间覆盖0~N-1这N个点，使得使用的花费最小
		solve();
	}
	return 0;
}