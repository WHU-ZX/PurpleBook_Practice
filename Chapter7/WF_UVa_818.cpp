#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const static int MAXN = 15;
static int n;
static int gameNum;
static bool G[MAXN + 1][MAXN + 1];
static bool hasLine[MAXN + 1];//�ý���Ƿ���ָ�������ڵ��·��
static bool open[MAXN + 1];
static bool vis[MAXN + 1];
static int openNum;//ö���еĴ򿪵Ļ��ĸ���
static int connectedGraphNum;//δ�򿪵Ļ�����ͨͼ�ĸ���
static int minNum;//��С�򿪵Ļ��ĸ�������ֵ����n�������openNum+(connectedGraphNum-openNum <=1 ? 0:connectedGraphNum-openNum-1)

static bool bfs(int traverseNum)
{
	openNum = 0;
	for (int i = 0; i < n; ++i)//��ʼ��open���飺�±��1��ʼ
		if (1 << i & traverseNum)
		{
			open[i + 1] = true;
			++openNum;
		}
	connectedGraphNum = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (open[i] || vis[i]) continue;
		queue<int> Q;
		Q.push(i); Q.push(-1);//Q�У���1���ǽ�㣬��2���ǽ��ĸ��ף�����i��j����i��j�ĸ��ף�
		int pushNum = 0,time = 0;
		while (!Q.empty() && (pushNum <= 1 || pushNum == 2 && time == 1))
		{
			pushNum = 0;
			int u = Q.front(); Q.pop();
			int father = Q.front(); Q.pop();
			vis[u] = true;
			for (int v = 1; v <= n; ++v)
			{
				if (!G[u][v]) continue;
				if (!open[v])
				{
					if (!vis[v])
					{
						Q.push(v); Q.push(u); pushNum++;
					}
					else if(v != father)//�γɻ�
					{
						return false;
					}
				}
			}
			time++;
		}
		if (!Q.empty()) return false;
		connectedGraphNum++;
	}
	return true;
}

static void bin_traverse()//�ö����Ʒ����б���
{
	minNum = n;
	for (int i = 0; i <= (1 << n) - 1; i++)
	{
		memset(vis, false, sizeof vis);
		memset(open, false, sizeof open);
		if (bfs(i))
		{
			int num = openNum+ ((connectedGraphNum - openNum) <= 1 ? 0 : connectedGraphNum - openNum - 1);
			minNum = min(minNum, num);
		}
	}
}

int WF_UVa_818()
{
	const char* input = "inputs/WF_818.txt";
	//const char* output = "outputs/WF_818.txt";
	freopen(input, "r", stdin);
	int from, to;
	gameNum = 1;
	while (cin >> n && n)
	{
		memset(G, false, sizeof G);
		while (cin >> from >> to && from != -1)
			G[from][to] = G[to][from] = true;
		bin_traverse();
		printf("Set %d: Minimum links to open is %d\n", gameNum++, minNum);
	}
	return 0;
}