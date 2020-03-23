#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;
static const int maxn = 100500;
static vector<int> E[maxn];// E[i]��ʾ��i�����ܵ���ĵ��vector����
static vector<int> color[maxn];//color[i][j]��Ӧ��E[i][j]����ɫ

int length[maxn];
int ans[maxn];
bool vis[maxn];//��ʾ�Ƿ���ʹ��ڵ�

int n, m;//nΪ��������mΪ����

const int Inf = INT32_MAX;

void reverse_dfs()//���յ㿪ʼdfs���ҳ�ÿ���㵽�յ����̾���
{
	queue<int> Q;
	memset(length, 0, sizeof(length));
	Q.push(n);
	int l = 0;
	memset(vis, false, sizeof(vis));//��ʼ��
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
	memset(vis, false, sizeof(vis));//��ʼ��
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
					int c = color[v][i];//v �� t��·����color
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
		for (int i = 1; i <= n; i++)//��ʼ��
		{
			E[i].clear();
			color[i].clear();
		}
		int a, b, c;
		for (int i = 0; i < m; i++)//��������
		{
			scanf("%d%d%d", &a, &b, &c);
			E[a].push_back(b);
			E[b].push_back(a);
			color[a].push_back(c);
			color[b].push_back(c);
		}
		reverse_dfs();//�ҳ�ÿ���ڵ㵽��n�����·��
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