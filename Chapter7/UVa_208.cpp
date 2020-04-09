#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
const static int MAXN = 21;
static int streetcorner;
static int m, n;
static int cnt;
static int gameNum = 1;
static bool G[MAXN][MAXN];
static bool vis[MAXN];
static int P[MAXN * MAXN];
static int pCnt;

static void init()
{
	cnt = 0;
	memset(G, false, sizeof G);
}

static bool canGo()
{
	memset(vis, false, sizeof vis);
	queue<int> Q;
	Q.push(1);
	while (!Q.empty())
	{
		int s = Q.front(); Q.pop();
		for (int i = 1; i < MAXN; ++i)
			if (G[s][i] && !vis[i])
			{
				if (i == streetcorner) return true;
				Q.push(i);
				vis[i] = true;
			}
	}
	return false;
}

static void print_path(int cur)
{
	if (cur == streetcorner)
	{
		//Êä³ö
		for (int i = 0; i < pCnt; ++i)
			printf("%d ", P[i]);
		printf("%d\n", streetcorner);
		++cnt;
	}
	else
	{
		vis[cur] = true;
		for (int i = 1; i < MAXN; ++i)
		{
			if (G[cur][i] && !vis[i])
			{
				P[pCnt] = cur;
				pCnt++;
				print_path(i);
				pCnt--;
			}
		}
		vis[cur] = false;
	}
}

int WF_UVa_208()
{
	const char* input = "inputs/WF_208.txt";
	//const char* output = "outputs/WF_208.txt";
	freopen(input, "r", stdin);

	while (scanf("%d\n", &streetcorner) != EOF)
	{
		init();
		while (scanf("%d %d\n", &m, &n) == 2 && m && n)
		{
			G[m][n] = G[n][m] = true;
		}
		printf("CASE %d:\n", gameNum);
		if (canGo())
		{
			memset(vis, false, sizeof vis);
			pCnt = 0;
			print_path(1);

		}
		printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, streetcorner);
		++gameNum;
	}
	return 0;
}