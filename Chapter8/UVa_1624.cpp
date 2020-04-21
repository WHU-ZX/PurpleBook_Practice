#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#pragma warning(disable:4996)
using namespace std;
const static int MAXL = 1000000;
static struct Node
{
	int left, right, face;
};
static Node nodes[MAXL];
static int L, P;
static int layer[MAXL];
static void del(int u)
{
	nodes[nodes[u].left].right = nodes[u].right;
	nodes[nodes[u].right].left = nodes[u].left;
	layer[u] = 0;
}

int UVa_1624()//参考：https://blog.csdn.net/qq_36973725/article/details/88050611
{
	const char* input = "inputs/1624.txt";
	//const char* output = "outputs/1624.txt";
	freopen(input, "r", stdin);
	int testCase, cas = 1;
	cin >> testCase;
	while (testCase--)
	{
		cin >> L >> P;
		memset(layer, 0, sizeof layer);
		for (int i = 0; i < L; ++i)
		{
			nodes[i].left = i - 1;
			nodes[i].right = i + 1;
		}
		nodes[0].left = L - 1;
		nodes[L - 1].right = 0;
		int u, v;
		for (int i = 0; i < P; ++i)
		{
			cin >> u >> v;
			nodes[u].face = v;
			nodes[v].face = u;
			layer[u] = 1;
			layer[v] = -1;
		}
		for (int i = 0; i < L; ++i) if (!layer[i]) del(i);
		int cnt = 2 * P, k = 0;
		while (cnt)
		{
			int notFind = true;
			while (!layer[k])++k;
			for (int i = nodes[k].right; i != k && notFind; i = nodes[i].right)//为什么i从k开始就不行? --> 如果i从k开始，第一个就不满足了
			{
				u = i; v = nodes[i].right;
				if (layer[u] == layer[v] && (nodes[nodes[u].face].right == nodes[v].face ||
					nodes[nodes[v].face].right == nodes[u].face))
				{
					del(u); del(v); del(nodes[u].face); del(nodes[v].face);
					cnt -= 4;
					notFind = false;
				}
				else if (nodes[u].face == v)
				{
					del(u); del(v);
					cnt -= 2;
					notFind = false;
				}
			}
			if (notFind) break;
		}
		cout << "Case #" << cas++ << ": " << (cnt ? "NO\n" : "YES\n");
	}
	return 0;
}