#define LOCAL
#include <stdio.h>
#include <string.h>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
#define INF 0x3f3f3f3f
static const int maxn = 100 + 5;
static const int maxm = 30 + 5;
static int a[maxm];
static int dp[maxn][maxm], cost[maxn][maxm];

static void solve(int n, int m) {
    // init
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // not choose j
            dp[i][j] = dp[i][j - 1];
            // choose j
            for (int k = 1; k <= i; k++) {
                int x;
                if (k == i) x = a[j] / k;
                else x = min(a[j] / k, dp[i - k][j - 1]);

                if (x > dp[i][j]) {
                    dp[i][j] = x;
                }
            }
        }
    }

    memset(cost, INF, sizeof(cost));
    memset(cost[0], 0, sizeof(cost[0]));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cost[i][j] = cost[i][j - 1];
            for (int k = 1; k <= i; k++) {
                int safe = a[j] / k;
                if (safe >= dp[n][m]) {
                    cost[i][j] = min(cost[i][j], cost[i - k][j - 1] + a[j]);
                }
            }
        }
    }
}

int test() {
#ifdef LOCAL
    freopen("inputs/10163.txt", "r", stdin);
    //freopen("data.out", "w", stdout);
#endif
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        for (int i = 1; i <= m; i++) {
            scanf("%d", &a[i]);
        }
        solve(n, m);
        printf("%d %d\n", dp[n][m], dp[n][m] == 0 ? 0 : cost[n][m]);
    }
    return 0;
}