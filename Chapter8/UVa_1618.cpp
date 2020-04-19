#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
static int n;
const static int MAXN = 5000;
static int numbers[MAXN];
static vector<int> L[MAXN], R[MAXN]; // l[i]��ʾ��numbers[i]����ұ�numbers[i]С������r[i]��ʾ��numbers[i]�Ҳ��ұ�numbers[i]�����

static bool solve()
{
	//����
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
	//���
	for (int q = 0; q < n; ++q)
	{
		for (int r = q + 1; r < n; ++r)
		{
			int p = upper_bound(L[q].begin(), L[q].end(), numbers[r]) - L[q].begin();//Nq���С��Nq�ĵ�һ������Nr��
			int s = lower_bound(R[r].begin(), R[r].end(), numbers[q]) - R[r].begin();//Nr�ұߴ���Nr�ĵ�һ����С��Nq��
			if (s == 0 || p == L[q].size())continue;//û�ҵ�
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