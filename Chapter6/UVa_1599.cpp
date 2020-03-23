#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;
static const int maxn = 100500;
static vector<int> E[maxn];// E[i]表示从i出发能到达的点的vector集合
static vector<int> color[maxn];//color[i][j]对应边E[i][j]的颜色

int length[maxn];
int ans[maxn];
bool vis[maxn];//表示是否访问过节点

int n, m;//n为顶点数，m为边数

const int Inf = INT32_MAX;

void reverse_dfs()//从终点开始dfs，找出每个点到终点的最短距离
{
	queue<int> Q;
	memset(length, 0, sizeof(length));
	Q.push(n);
	int l = 0;
	memset(vis, false, sizeof(vis));//初始化
	while (!Q.empty())
	{
		int v = Q.front(); Q.pop();
		vis[v] = true;
		for (int i = 0; i < E[v].size(); i++)
		{
			int t = E[v][i];
			if (!vis[t])
			{
				length[t] = length[v] + 1;
				vis[t] = true;
				Q.push(t);
			}
		}
	}
}

void dfs()
{
	set<int> s;
	s.insert(1);
	memset(ans, 0, sizeof(ans));
	memset(vis, false, sizeof(vis));//初始化
	int t = length[1];

	for (int k = 1; k <= t; k++)
	{
		set<int> tS;
		int minC = Inf;
		for (set<int>::iterator iter = s.begin(); iter != s.end(); iter++)
		{
			int v = *iter;
			vis[v] = true;
			for (int i = 0; i < E[v].size(); i++)
			{
				int t = E[v][i];
				if (length[t] == length[v] - 1 && !vis[t])
				{
					int c = color[v][i];//v 到 t的路径的color
					if (c < minC)
					{
						minC = c;
						tS.clear();
						tS.insert(t);
					}
					else if (c == minC)
					{
						tS.insert(t);
					}
				}
			}
		}
		ans[k] = minC;
		s = tS;
	}
}


int UVa_1599()
{
	const char* input = "inputs/WF_1599.txt";
	const char* output = "outputs/WF_1599.txt";
	freopen(input, "r", stdin);

	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= n; i++)//初始化
		{
			E[i].clear();
			color[i].clear();
		}
		int a, b, c;
		for (int i = 0; i < m; i++)//读入数据
		{
			scanf("%d%d%d", &a, &b, &c);
			E[a].push_back(b);
			E[b].push_back(a);
			color[a].push_back(c);
			color[b].push_back(c);
		}
		reverse_dfs();//找出每个节点到点n的最短路径
		dfs();
		cout << length[1] << endl;
		if (ans[1])
		{
			cout << ans[1];
			int i = 2;
			while (ans[i])
			{
				cout << ' ' << ans[i];
				i++;
			}
		}
		cout << endl;
	}
	return 0;
}