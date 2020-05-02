#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
const static int maxn = 1000 + 10;
const static int INF = 1000000003;

static char s[maxn], s2[maxn];
static int len, a[maxn], b[maxn];
static int d[maxn][11][11][11];

static int dp(int cur, int x, int y, int z) {
    if (cur >= len) return 0;

    int& ans = d[cur][x][y][z];
    if (ans >= 0) return ans;

    ans = INF;
    int down = (b[cur] + 10 - x) % 10, up = (x + 10 - b[cur]) % 10;
    for (int i = 0; i <= down; ++i)//向下
        for (int j = 0; j <= i; ++j)
            ans = min(ans, dp(cur + 1, (y + i) % 10, (z + j) % 10, a[cur + 3]) + down);
    for (int i = 0; i <= up; ++i)//向上
        for (int j = 0; j <= i; ++j)
            ans = min(ans, dp(cur + 1, (y + 10 - i) % 10, (z + 10 - j) % 10, a[cur + 3]) + up);
    return ans;
}


int UVa_1631()
{
	const char* input = "inputs/1631.txt";
	//const char* output = "outputs/1631.txt";
	freopen(input, "r", stdin);
    while (scanf("%s%s", s, s2) == 2) {
        len = strlen(s);
        for (int i = 0; i < len; ++i) a[i] = s[i] - '0';
        for (int i = 0; i < len; ++i) b[i] = s2[i] - '0';
        a[len] = a[len + 1] = a[len + 2] = b[len] = b[len + 1] = b[len + 2] = 0;
        memset(d, -1, sizeof(d));
        printf("%d\n", dp(0, a[0], a[1], a[2]));
    }
    return 0;
}