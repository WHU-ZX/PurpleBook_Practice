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

static void dfs(int* a, int d, int num)//d为当前的进程id，num为当前进程完成后的时间
{
	if (d == 10)
	{
		//ans = min(ans, num);
		ans = num < ans ? num : ans;
		return;
	}
	//否则
	if (num + jump[0] * (10 - d) > ans) return; //剪枝2,最好的情况下时间大于ans，剪枝
	for (int i = 0; i < ch; ++i)
	{
		if (judge(a, jump[i]))
		{
			int tU[N];
			for (int j = 0; j < N; ++j)
				tU[j] = (a[j] >> jump[i]) ^ u[j];//a[j] >> jump[j]其实是上一个进程的状态，右移舍掉的位是当前进程开始后，上一进程已经完成的部分
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
		ans = 10 * n;//最坏时间
		char tC[MAXN + 1];// = 0;
		for (int i = 0; i < 5; ++i)
		{
			scanf("%s", tC);
			for (int j = 0; j < n; ++j) if (tC[j] == 'X') u[i] |= 1 << j;
			//getchar();
		}
		for (int i = 0; i <= n; ++i) if (judge(u, i)) jump[ch++] = i;//剪枝1，找出所有可能的间隔
		dfs(u, 1, n);
		printf("%d\n", ans);
	}
	
	return 0;
}