#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
static struct Book
{
	int h, w;
	bool operator < (const Book& book)const
	{
		return h > book.h;
	}
};
const static int MAXN = 70 + 1, MAXJ = 1065 + 1, MAXK = 720 + 1, Inf = 0x7FFFFFFF;
static Book books[MAXN];
static int d[2][MAXJ][MAXK], n, A[MAXN];

static void update(int& nD, int D)
{
	if (nD<0 || nD>D) nD = D;
}

int UVa_12099_optimized()
{
	const char* input = "inputs/12099.txt";
	//const char* output = "outputs/12099.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		cin >> n;
		A[0] = 0;
		for (int i = 1; i <= n; ++i)
			cin >> books[i].h >> books[i].w;
		sort(books + 1, books + n + 1);
		for (int i = 1; i <= n; ++i)
			A[i] = A[i - 1] + books[i].w;
		int J = (A[n] + 30) / 2, K = (A[n] + 60) / 3;
		for (int j = 0; j <= J && j<= A[1]; ++j)
			for (int k = 0; k <= K && k <= A[1] - j; ++k) d[1][j][k] = -1;
		d[1][0][0] = 0;
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j <= J && j <= A[i + 1]; ++j)
				for (int k = 0; k <= K && k <= A[i + 1] - j; ++k) d[(i + 1) & 1][j][k] = -1;

			for (int j = 0; j <= J && j <= A[i]; ++j)
				for (int k = 0; k <= K && k <= A[i] - j; ++k)
				{
					if (d[i & 1][j][k] < 0)continue;
					int a = d[i & 1][j][k];
					update(d[(i + 1) & 1][j][k], a);
					int nj = j + books[i + 1].w, nk = k + books[i + 1].w;
					if (nj <= J && nj <= A[i + 1])
						update(d[(i + 1) & 1][nj][k], a + books[i + 1].h * (j == 0));
					if (nk <= K && nk <= A[i + 1] - j)
						update(d[(i + 1) & 1][j][nk], a + books[i + 1].h * (k == 0));
				}
		}
		int ans = Inf;
		//j 和 k 从0开始会出错,因为此时不满足三层书架的条件
		for (int j = 1; j <= J && j <= A[n]; ++j)
			for (int k = 1; k <= K && k <= A[n] - j; ++k)
			{
				if (d[n & 1][j][k] < 0) continue;
				int w = max(max(j, k), A[n] - j - k);
				int h = books[1].h + d[n & 1][j][k];
				ans = min(ans, w * h);
			}
		cout << ans << endl;
	}
	return 0;
}