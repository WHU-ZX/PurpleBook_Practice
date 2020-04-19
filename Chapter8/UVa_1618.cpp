#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
static int n;
const static int MAXN = 5000;
static int numbers[MAXN];
static vector<int> L[MAXN], R[MAXN]; // l[i]表示在numbers[i]左侧且比numbers[i]小的数，r[i]表示在numbers[i]右侧且比numbers[i]大的数

static bool solve()
{
	//构造
	for (int i = 0; i < n; ++i)
	{
		L[i].clear(); R[i].clear();
		for (int jl = i - 1; jl >= 0; --jl)
			if (numbers[jl] < numbers[i]) L[i].push_back(numbers[jl]);
		for (int jr = i + 1; jr < n; ++jr)
			if (numbers[jr] > numbers[i]) R[i].push_back(numbers[jr]);
		sort(L[i].begin(), L[i].end());
		sort(R[i].begin(), R[i].end());
	}
	//求解
	for (int q = 0; q < n; ++q)
	{
		for (int r = q + 1; r < n; ++r)
		{
			int p = upper_bound(L[q].begin(), L[q].end(), numbers[r]) - L[q].begin();//Nq左边小于Nq的第一个大于Nr的
			int s = lower_bound(R[r].begin(), R[r].end(), numbers[q]) - R[r].begin();//Nr右边大于Nr的第一个不小于Nq的
			if (s == 0 || p == L[q].size())continue;//没找到
			if (L[q][p] < R[r][s - 1]) return true;
		}
	}
	return false;
}

int UVa_1618()
{
	const char* input = "inputs/1618.txt";
	//const char* output = "outputs/1618.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> numbers[i];
		if (solve())
		{
			cout << "YES" << endl;
			continue;
		}
		reverse(numbers, numbers + n);
		if (solve())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}