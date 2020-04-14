#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#pragma warning(disable:4996)
using namespace std;

static int m, n;//m为边的个数，n为顶点个数
const static int MAXN = 9999, MAXM = 100000;
static int color[MAXN + 1], k;
static vector<int> G[MAXN + 1];

static void dfs(int v)
{
	int size = G[v].size();
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 0; i < size; ++i)//收集连通图的颜色
		if (color[G[v][i]] != 0)//没有访问过
			q.push(color[G[v][i]]);
	//处理v
	int t;
	if (q.empty())
		t = 1;
	else
	{
		if (q.top() != 1)
			t = 0;
		else
		{
			t = q.top(); q.pop();
			while (!q.empty())
			{
				int temp = q.top(); q.pop();
				if (t + 1 < temp)
					break;
				else
					t = temp;
			}
		}
		++t;
	}
	color[v] = t;
	if (k < t) k = t;

	for (int i = 0; i < size; ++i)
		if (color[G[v][i]] == 0)
			dfs(G[v][i]);
}

static void print()
{
	if (k % 2 == 0)
		cout << k + 1 << endl;
	else
		cout << k << endl;
	for (int i = 1; i <= n; ++i)
		cout << color[i] << endl;
	cout << endl;
}

int UVa_1613()// 未通过OJ
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/1613.txt";
	//const char* output = "outputs/1613.txt";
	freopen(input, "r", stdin);
	while (cin>>n>>m)
	{
		memset(color, 0, sizeof color);
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		int t1, t2;
		for (int i = 0; i < m; ++i)
		{
			cin >> t1 >> t2;
			G[t1].push_back(t2);
			G[t2].push_back(t1);
		}
		k = 0;
		dfs(1);
		print();
	}
	return 0;
}