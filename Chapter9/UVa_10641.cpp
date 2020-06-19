#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
#define Local
using namespace std;
const static int MAXN = 31, MAXM = 1001, Inf = 0x3f3f3f3f;
const static double eps = 1e-6;
static int N, M;//NΪ������MΪ�Ƶ���Ŀ
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
static int d[MAXN * 2];//d[i]��ʾ�Ѿ������˵�i����С����
static bool choosed[MAXM];//choosed��ʾ�Ƿ�ѡ��˵�
/*
	���OA��OB = xa*yb-xb*ya > 0����A��O����ʱ��ת����ת��B, = 0�����㹲��, < 0 ��A��O��˳ʱ��ת����ת��B
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

static void solve()//����̫��
{
	int ans = Inf;
	for (int i = 0; i < N; ++i)//ö�����i
	{
		memset(d, Inf, sizeof d);
		d[i] = 0;
		for (int j = 0; j < N; ++j)
		{
			int r = i + j;//�ӵ�i���㿪ʼ��������j�����ඨ����ôһ����Σ�����ʹ״̬��ת�Ʊ������
			for (int k = 0; k < M; ++k)
			{
				if (Sess[k].L > r) continue;//�������޷����ǵ���i~j
				if (Sess[k].R < r) continue;//��֦�����ٿ��ǲ����Ϊ���Ž�����
				int now = min(Sess[k].R + 1, i + N);//���������Ҷ˵�������£�����һ�����¹���i+n��Ҫ���˵㶨Ϊi+n��
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
		//Ȼ�����ѡ���串��0~N-1��N���㣬ʹ��ʹ�õĻ�����С
		solve();
	}
	return 0;
}