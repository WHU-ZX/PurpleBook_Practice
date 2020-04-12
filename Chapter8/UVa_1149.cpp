#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 100000;
static int n, M;
static int bins[MAXN + 1];

int UVa_1149()
{
	const char* input = "inputs/1149.txt";
	//const char* output = "outputs/1149.txt";
	freopen(input, "r", stdin);
	int caseNum;
	cin >> caseNum;
	while (caseNum--)
	{
		cin >> n >> M;
		for (int i = 0; i < n; ++i)
			cin >> bins[i];
		//≈≈–Ú
		int ans = 0;
		sort(bins, bins + n);
		int minn = 0, maxn = n - 1;
		while (minn <= maxn)
		{
			while (minn <= maxn && bins[minn] + bins[maxn] > M)
			{
				ans++; maxn--;
			}
			if (minn <= maxn)
			{
				ans++; minn++; maxn--;
			}
		}
		//if (minn == maxn)ans++;
		cout << ans << endl;
		if (caseNum) cout << endl;
	}
	return 0;
}