#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>

typedef long long LL;
using namespace std;
static int maxd;
static LL k[5];
static int k_num;
static LL ans[105], v[105];
static LL gcd(LL m, LL n)//m >= n --> 辗转相除法
{
	if (m < n)
	{
		LL t = m;
		m = n;
		n = t;
	}
	while (n != 0)
	{
		LL t = m % n;
		m = n;
		n = t;
	}
	return m;
}

static bool inK(LL num)
{
	return binary_search(k, k + k_num, num);
}

static LL get_first(LL a, LL b)//返回满足1/c <= a/b的最小的c，且c要满足题意 --> b <= ac
{
	LL c;
	for (c = b / a;; c++)
		if (b <= a * c) break;
	return c;
}

static bool better(int d)
{
	for (int i = d; i >= 0; --i)
		if (ans[i] != v[i])
			return ans[i] == -1 || v[i] < ans[i];
	return false;
}

//当前深度为d,分母不小于from,分数之和恰好为aa/bb
static bool dfs(int d, int from, LL aa, LL bb)
{
	if (d == maxd)
	{
		if (bb % aa) return false;//不能整除
		v[d] = bb / aa;
		if (inK(v[d])) return false;
		if (better(d)) memcpy(ans, v, sizeof(LL) * (d + 1));
		return true;
	}
	bool ok = false;
	LL t = get_first(aa, bb);
	from = from > t ? from : t;//枚举的起点
	for (int i = from;; ++i)//只要有一条路可以成功就返回true
	{
		if (bb * (maxd + 1 - d) <= aa * i) break;
		if (inK(i)) continue;
		v[d] = i;
		//计算aa/bb - 1/i
		LL a2 = aa * i - bb;
		LL b2 = bb * i;
		LL g = gcd(a2, b2);
		if (dfs(d + 1, v[d] + 1, a2 / g, b2 / g)) ok = true;
	}
	return ok;
}

int UVa_12558()
{
	const char* input = "inputs/12558.txt";
	//const char* input = "inputs/a.txt";
	//const char* output = "outputs/12558.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	LL a, b;
	for (int i = 1; i <= testCase; ++i)
	{
		cin >> a >> b >> k_num;
		for (int j = 0; j < k_num; ++j)
			cin >> k[j];
		//对k进行排序
		sort(k, k + k_num);
		//ans、v初始化为-1,ans_num初始化为0
		memset(v, -1, sizeof v);
		bool ok = false;
		for (maxd = 1;; ++maxd)
		{
			memset(ans, -1, sizeof ans);
			if (dfs(0, get_first(a, b), a, b))
			{
				ok = true; break;
			}
		}
		if (ok)
		{
			printf("Case %d: %d/%d=", i, a, b);
			for (int n = 0; n < maxd; ++n)
			{
				printf("1/%lld+", ans[n]);
			}
			printf("1/%lld\n", ans[maxd]);
		}
	}
	return 0;
}