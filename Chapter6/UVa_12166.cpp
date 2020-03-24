#include <cstdio>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

static int gameNum;
static string str;
static map<long long, int> m;
static int sum = 0;

static void dfs(int l, int r, int dep)
{
	if (str[l] == '[')
	{
		int p = 0;
		for (int i = l + 1; i < r; i++)
		{
			if (str[i] == '[')p++;
			else if (str[i] == ']')p--;
			if (p == 0 && str[i] == ',')
			{
				dfs(l + 1, i - 1, dep + 1);
				dfs(i + 1, r - 1, dep + 1);
			}
		}
	}
	else
	{
		long long w = 0;
		for (int i = l; i <= r; i++)
		{
			w *= 10;
			w += str[i] - '0';
		}
		m[w << dep] ++;
		sum++;
	}
}

static void init()
{
	sum = 0;
	m.clear();
}

//此题思路比较巧妙：
/*
	首先，由于要保证天平的平衡，假设此时天平已经平衡了，那么对于任意的一个节点（可以不是叶子节点），若其深度为dep（根节点为0），重量为w
如果不是叶子节点，则计算它下面的所有节点质量之和)，那么，整个天平的总和应该为w<<dep。所以实际上，假设某一层的某个节点的质量一定，那么这棵树的
所有叶子节点的值就定下来了。可以理解为：我们以某个节点为基准，令它不变，那么就改变其他的结点让树达到平衡
	所以，要让改变的更少，则应该对所有节点的值进行遍历。假设某节点的深度为d，值为w，则让树的总质量W为w<<d的节点就多一个，可以用一个map记录让
树的总质量为W的结点的个数。当遍历到结点i时，设其深度di，值为wi，则map[wi<<di]++。最后找到map中因变量最大的值，用总结点数减去其值即为结果。
*/
int UVa_12166()
{
	const char* input = "inputs/12166.txt";
	const char* output = "outputs/12166.txt";
	freopen(input, "r", stdin);

	cin >> gameNum;
	while (gameNum--)
	{
		init();
		cin >> str;
		int maxn = 0;
		dfs(0, str.length() - 1, 0);
		for (map<long long, int>::iterator it = m.begin(); it != m.end(); ++it) {
			maxn = max(maxn, (*it).second);
		}
		cout << sum - maxn << endl;
	}
	return 0;
}