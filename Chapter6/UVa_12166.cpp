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

//����˼·�Ƚ����
/*
	���ȣ�����Ҫ��֤��ƽ��ƽ�⣬�����ʱ��ƽ�Ѿ�ƽ���ˣ���ô���������һ���ڵ㣨���Բ���Ҷ�ӽڵ㣩���������Ϊdep�����ڵ�Ϊ0��������Ϊw
�������Ҷ�ӽڵ㣬���������������нڵ�����֮��)����ô��������ƽ���ܺ�Ӧ��Ϊw<<dep������ʵ���ϣ�����ĳһ���ĳ���ڵ������һ������ô�������
����Ҷ�ӽڵ��ֵ�Ͷ������ˡ��������Ϊ��������ĳ���ڵ�Ϊ��׼���������䣬��ô�͸ı������Ľ�������ﵽƽ��
	���ԣ�Ҫ�øı�ĸ��٣���Ӧ�ö����нڵ��ֵ���б���������ĳ�ڵ�����Ϊd��ֵΪw����������������WΪw<<d�Ľڵ�Ͷ�һ����������һ��map��¼��
����������ΪW�Ľ��ĸ����������������iʱ���������di��ֵΪwi����map[wi<<di]++������ҵ�map�����������ֵ�����ܽ������ȥ��ֵ��Ϊ�����
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