#include "normal_header.h"

const static int MAXN = 19;
static int n;
const static int N = 5;
static int u[N];
static int ch, jump[MAXN + 1], ans;

static bool judge(int* a, int k)
{
	for (int i = 0; i < N; ++i) if ((a[i] >> k) & u[i]) return false;
	return true;
}

static void dfs(int* a, int d, int num)//dΪ��ǰ�Ľ���id��numΪ��ǰ������ɺ��ʱ��
{
	if (d == 10)
	{
		//ans = min(ans, num);
		ans = num < ans ? num : ans;
		return;
	}
	//����
	if (num + jump[0] * (10 - d) > ans) return; //��֦2,��õ������ʱ�����ans����֦
	for (int i = 0; i < ch; ++i)
	{
		if (judge(a, jump[i]))
		{
			int tU[N];
			for (int j = 0; j < N; ++j)
				tU[j] = (a[j] >> jump[i]) ^ u[j];//a[j] >> jump[j]��ʵ����һ�����̵�״̬�����������λ�ǵ�ǰ���̿�ʼ����һ�����Ѿ���ɵĲ���
			dfs(tU, d + 1, num + jump[i]);
		}
	}
}

int UVa_690()
{
	const char* input = "inputs/690.txt";
	//const char* output = "outputs/WF_818.txt";
	freopen(input, "r", stdin);
	
	while (scanf("%d\n", &n) == 1 && n)
	{
		memset(u, 0, sizeof u);
		ch = 0;
		ans = 10 * n;//�ʱ��
		char tC[MAXN + 1];// = 0;
		for (int i = 0; i < 5; ++i)
		{
			scanf("%s", tC);
			for (int j = 0; j < n; ++j) if (tC[j] == 'X') u[i] |= 1 << j;
			//getchar();
		}
		for (int i = 0; i <= n; ++i) if (judge(u, i)) jump[ch++] = i;//��֦1���ҳ����п��ܵļ��
		dfs(u, 1, n);
		printf("%d\n", ans);
	}
	
	return 0;
}