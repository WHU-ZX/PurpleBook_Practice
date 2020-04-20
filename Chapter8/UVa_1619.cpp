#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
static int n;
const static int MAXN = 100000;
static int numbers[MAXN + 2];
static long long sum[MAXN + 2];
static int L[MAXN + 2], R[MAXN + 2];

int UVa_1619()
{
	const char* input = "inputs/1619.txt";
	//const char* output = "outputs/1619.txt";
	freopen(input, "r", stdin);
	int flag = 0;
	while (cin >> n)
	{
		numbers[0] = 0;
		sum[0] = 0;
		for (int i = 1; i <= n; ++i)
		{
			cin >> numbers[i];
			sum[i] = sum[i - 1] + numbers[i];
			L[i] = R[i] = i;
		}
		numbers[n + 1] = 0;
		for (int i = 1; i <= n; ++i)
		{
			while (numbers[i] <= numbers[L[i] - 1]) L[i] = L[L[i] - 1];
		}
		for (int i = n; i >= 1; --i)
		{
			while (numbers[i] <= numbers[R[i] + 1]) R[i] = R[R[i] + 1];
		}
		long long MAX = -1, mL = -1, mR = -1;
		for (int i = 1; i <= n; ++i)
		{
			long long cur = ((long long)sum[R[i]] - sum[L[i] - 1]) * numbers[i];
			if (cur > MAX || (cur == MAX && (R[i] - L[i]) < (mR - mL)))
			{
				mL = L[i]; mR = R[i]; MAX = cur;
			}
		}
		if (flag++) cout << endl;
		printf("%lld\n%d %d\n", MAX, mL, mR);
	}
	return 0;
}

/*  这个就过了，我的就超出时间限制了
#include<iostream>
#include<string.h>
#include<sstream>
#include<set>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<math.h>
using namespace std;
const int maxn = 100000 + 10;

int main() {
	int n;
	int A[maxn];
	int L[maxn], R[maxn];
	long long sum[maxn];
	sum[0] = 0;
	int flag = 0;
	while (cin >> n && n) {
		for (int i = 1; i <= n; i++) {
			cin >> A[i]; L[i] = i, R[i] = i; sum[i] = sum[i - 1] + A[i];
		}
		A[0] = -1, A[n + 1] = -1;
		for (int i = 1; i <= n; i++) {
			while (A[i] <= A[L[i] - 1])L[i] =L[L[i] - 1];//更新最左区间，使得区间里的数小于A[i]，有一点动态规划
		}
		for (int i = n; i >= 1; i--) {
			while (A[i] <= A[R[i] + 1])R[i] = R[R[i] + 1];
		}
		long long maxv = (long long)A[1] * A[1];
		int r = 1, l = 1;
		for (int i = 1; i <= n; i++) {
			long long cur = (sum[R[i]] - sum[L[i] - 1])*A[i];
			if (cur > maxv || (cur == maxv && (R[i] - L[i]) < (r - l))) {
				maxv = cur;
				r = R[i]; l = L[i];
			}
		}
		if (flag++)cout << endl;
		cout << maxv << endl << l << " " << r << endl;
	}

	return 0;
}


*/