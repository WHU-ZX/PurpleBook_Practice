#include <cstdio>
#include <iostream>
#include <map>

using namespace std;
struct Node
{
	int a;
	int b;
	void ex()
	{
		int t = a;
		a = b;
		b = t;
	}

};
bool operator < (const Node& a, const Node& b)
{
	if (a.a < b.a) return true;
	else if (a.a == b.a && a.b < b.b) return true;
	else return false;
}
static int n;
static map<Node, int> m;

int UVa_10763()
{
	const char* input = "datas/UVa_10763_input.txt";
	const char* output = "datas/UVa_10763_output.txt";
	freopen(input, "r", stdin);
	Node node;
	while (cin >> n && n)
	{
		if (!m.empty())m.erase(m.begin(), m.end());
		for (int i = 1; i <= n; i++)
		{
			cin >> node.a >> node.b;
			node.ex();
			if (m.count(node) == 1)
			{
				m[node]--;
				if (m[node] == 0) m.erase(node);
			}
			else
			{
				node.ex();//a b 交换回来了
				if (m.count(node) == 1)
					m[node]++;
				else
					m[node] = 1;
			}
		}
		if (m.empty())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}