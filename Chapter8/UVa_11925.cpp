#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 301;
static int n;
static vector<int> v;
static vector<char> ans;

static bool check()
{
	int size = v.size();
	for (int i = 0; i < size; ++i)
		if (v[i] != i + 1) return false;
	return true;
}
static void op1()
{
	int t = v[0];
	v[0] = v[1];
	v[1] = t;
	ans.push_back('1');
}

static void op2()
{
	v.insert(v.begin(), v.back());
	v.pop_back();
	ans.push_back('2');
}

int UVa_11925()
{
	const char* input = "inputs/11925.txt";
	//const char* output = "outputs/11925.txt";
	freopen(input, "r", stdin);
	int temp;
	while (cin >> n && n)
	{
		v.clear();
		ans.clear();
		for (int i = 0; i < n; ++i)
		{
			cin >> temp;
			v.push_back(temp);
		}
		//1表示交换前两个，2表示把最后一个放到第一个
		while (!check())
		{
			if (v.front() == n || v[0] < v[1])
				op2();
			else
				op1();
		}
		int ansSize = ans.size();
		for (int i = ansSize - 1; i >= 0; --i)
			cout << ans[i];
		cout << endl;
	}
	return 0;
}