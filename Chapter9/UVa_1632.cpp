#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 10001, Inf = 0x1FFFFFFF;
static int n;
static int x[MAXN], limit[MAXN];
static int d[MAXN][MAXN][2];//d[i][j][k]表示已经访问i~j，现在在k端所使用的最短时间,0在i端，1在j端

int UVa_1632()
{
	const char* input = "inputs/1632.txt";
	//const char* output = "outputs/1632.txt";
	freopen(input, "r", stdin);
	while (cin >> n && n)
	{
		/* 超时
		for (int i = 0; i < n; ++i) cin >> x[i] >> limit[i];
		memset(d, 0, sizeof d);
		for (int L = 1; L <= n - 1; ++L)
			for (int i = 0; i < n - L; ++i)//i + L < n
			{
				int j = i + L;
				d[i][j][0] = min(d[i + 1][j][0] + x[i + 1] - x[i], d[i + 1][j][1] + x[j] - x[i]);
				d[i][j][1] = min(d[i][j - 1][0] + x[j] - x[i], d[i][j - 1][1] + x[j] - x[j - 1]);
				if (d[i][j][0] > limit[i])d[i][j][0] = Inf;
				if (d[i][j][1] > limit[j])d[i][j][1] = Inf;
			}
		int ans = min(d[0][n - 1][0], d[0][n - 1][1]);
		if (ans >= Inf)cout << "No solution" << endl;
		else cout << ans << endl;
		*/

		/* WA
		for (int i = 0; i < n; ++i) cin >> x[i] >> limit[i];
		memset(d, 0, sizeof d);
		for (int i = n - 2; i >= 0; --i)
			for (int j = i + 1; j < n; ++j)
			{
				d[i][j][0] = min(d[i + 1][j][0] + x[i + 1] - x[i], d[i + 1][j][1] + x[j] - x[i]);
				d[i][j][1] = min(d[i][j - 1][0] + x[j] - x[i], d[i][j - 1][1] + x[j] - x[j - 1]);
				if (d[i][j][0] > limit[i])d[i][j][0] = Inf;
				if (d[i][j][1] > limit[j])d[i][j][1] = Inf;
			}
		int ans = min(d[0][n - 1][0], d[0][n - 1][1]);
		if (ans >= Inf)cout << "No solution" << endl;
		else cout << ans << endl;
		*/

		/* 超时了
		for (int i = 0; i < n; ++i)cin >> x[i] >> limit[i];
		memset(d, 0, sizeof d);
		for (int i = 0; i < n; ++i) d[i][i][0] = d[i][i][1] = 0;
		for (int L = 0; L <= n - 2; ++L)
			for (int i = 0; i + L < n; ++i)
			{
				int j = i + L;
			
				//int& ans0 = d[i][j][0], & ans1 = d[i][j][1];
				//int d_im1Toj_0 = d[i - 1][j][0], d_im1Toj_1 = d[i - 1][j][1];
				int d0 = d[i][j][0], d1 = d[i][j][1];
				if (d0 >= 0)//在i点 -- 如果小于0则表示没有这种情况
				{
					if (i > 0 && x[i] - x[i - 1] + d0 <= limit[i - 1])
					{
						if (d[i - 1][j][0] == -1) d[i - 1][j][0] = x[i] - x[i - 1] + d0;
						else d[i - 1][j][0] = min(d[i - 1][j][0], x[i] - x[i - 1] + d0);
					}
					if (j < n - 1 && x[j + 1] - x[i] + d0 <= limit[j + 1])
					{
						if (d[i][j + 1][1] == -1)d[i][j + 1][1] = x[j + 1] - x[i] + d0;
						else d[i][j + 1][1] = min(d[i][j + 1][1], x[j + 1] - x[i] + d0);
					}
				}
				if (d1 >= 0)//在j点
				{
					if (i > 0 && x[j] - x[i - 1] + d1 <= limit[i - 1])
					{
						if (d[i - 1][j][0] == -1)d[i - 1][j][0] = x[j] - x[i - 1] + d1;
						else d[i - 1][j][0] = min(d[i - 1][j][0], x[j] - x[i - 1] + d1);
					}
					if (j < n - 1 && x[j + 1] - x[j] + d1 <= limit[j + 1])
					{
						if (d[i][j + 1][1] == -1)d[i][j + 1][1] = x[j + 1] - x[j] + d1;
						else d[i][j + 1][1] = min(d[i][j + 1][1], x[j + 1] - x[j] + d1);
					}
				}
			}
		if (d[0][n - 1][0] == -1 && d[0][n - 1][1] == -1)//无解
			cout << "No solution" << endl;
		else
		{
			int Min = Inf;
			if (d[0][n - 1][0] != -1)Min = min(Min, d[0][n - 1][0]);
			if (d[0][n - 1][1] != -1)Min = min(Min, d[0][n - 1][1]);
			cout << Min << endl;
		}
		*/
	}
	return 0;
}

/* 这个通过OJ了 就比那个WA的多了一步d[i][i][0]=d[i][i][1]=0;
# include<iostream>
# include<cstdio>
# include<cstring>
# include<algorithm>
using namespace std;

int dp[10005][10005][2];
int x[10005],t[10005],n;

const int INF=1000000000;

int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=0;i<n;++i)
			scanf("%d%d",x+i,t+i),dp[i][i][0]=dp[i][i][1]=0;

		for(int i=n-2;i>=0;--i){
			for(int j=i+1;j<n;++j){
				dp[i][j][0]=min(dp[i+1][j][0]+x[i+1]-x[i],dp[i+1][j][1]+x[j]-x[i]);
				if(dp[i][j][0]>=t[i]) dp[i][j][0]=INF;
				dp[i][j][1]=min(dp[i][j-1][0]+x[j]-x[i],dp[i][j-1][1]+x[j]-x[j-1]);
				if(dp[i][j][1]>=t[j]) dp[i][j][1]=INF;
			}
		}
		if(dp[0][n-1][1]==INF&&dp[0][n-1][0]==INF) printf("No solution\n");
		else printf("%d\n",min(dp[0][n-1][0],dp[0][n-1][1]));
	}
	return 0;
}
*/