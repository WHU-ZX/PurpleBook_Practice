#include <cstdio>
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
static const int dr[4] = { 1,-1,0,0 };
static const int dc[4] = { 0,0,1,-1 };

static const int maxm = 21, maxn = 21;

static int board[maxm][maxn];
static int length[maxm][maxn];

static int k;

static int m, n;
static int gameNum;

static void init()
{
	memset(board, 0, sizeof(board));
	memset(length, 0, sizeof(length));
	//length[m][n] = -1;
}

static bool legalMove(int r, int c, int i, int curK)
{
	int newR = r + dr[i];
	int newC = c + dc[i];
	if (newR < 1 || newR>m || newC<1 || newC>n)return false;//如果超出边界则返回false
	if (length[newR][newC]&& board[newR][newC]==0) return false;//如果此点已经访问过，则返回false --- 要不要去掉？
	//针对：if(length[newR][newC]) return false;
	//如果多条路径都是第i步到达某处，且此处为1，则应该选curK最小的那条
	//如果后面某一步走到了某处，虽然length更长，但是由于他的curK更小，说不定下一步可以直接再到一个为1的点并且大幅缩短路径
	//会出现上述情况吗？
	if (board[newR][newC] == 1) return k - curK > 0;
	return true;
}

int UVa_1600()
{
	const char* input = "inputs/1600.txt";
	const char* output = "outputs/1600.txt";
	freopen(input, "r", stdin);

	cin >> gameNum;
	while (gameNum--)
	{
		cin >> m >> n >> k;
		init();
		for(int i = 1 ; i <= m; i++)
			for (int j = 1; j <= n; j++)
			{
				cin >> board[i][j];
			}
		//进行处理
		queue<int> Qr, Qc, Qk, Qs;
		Qr.push(1); Qc.push(1); Qk.push(0); Qs.push(0);
		while(!Qr.empty())
		{
			int r = Qr.front(); Qr.pop();
			int c = Qc.front(); Qc.pop();
			int curK = Qk.front(); Qk.pop();
			int step = Qs.front(); 
			if (r == m && c == n) break;
			for (int i = 0; i < 4; i++)
			{
				if (legalMove(r, c, i, curK))
				{
					int newK = board[r + dr[i]][c + dc[i]] ? curK + 1 : 0;
					Qr.push(r + dr[i]);
					Qc.push(c + dc[i]);
					Qk.push(newK);
					length[r + dr[i]][c + dc[i]] = length[r][c] + 1;
					Qs.push(step + 1);
				}
			}
			Qs.pop();
		}
		if (Qs.empty())
			length[m][n] = -1;
		else
			length[m][n] = Qs.front();

		cout << length[m][n] << endl;
	}
	return 0;
}