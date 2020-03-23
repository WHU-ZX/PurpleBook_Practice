#include <cstdio>
#include <iostream>
#include <string.h>
#include <queue>

static const int maxn = 8;
static std::string from, to;

static int rf, cf, rt, ct;

static int dr[8] = { 1,1,-1,-1,2,2,-2,-2 };
static int dc[8] = { 2,-2,2,-2,1,-1,1,-1 };
static int length[maxn][maxn];


static bool legalMove(int r, int c, int direct)//在棋盘内且未访问过
{
	int newR = r + dr[direct];
	int newC = c + dc[direct];
	return newR >= 0 && newR < maxn && newC >= 0 && newC < maxn && length[newR][newC] == 0;
}


int UVa_439()//注意from和to相同的情况？
{
	const char* input = "inputs/439.txt";
	const char* output = "outputs/439.txt";
	freopen(input, "r", stdin);

	while (std::cin >> from)
	{
		std::cin >> to;
		memset(length, 0, sizeof(length));
		rf = from[1] - '1'; cf = from[0] - 'a';
		rt = to[1] - '1', ct = to[0] - 'a';
		std::queue<int> qr, qc;
		qr.push(rf); qc.push(cf);
		while (!qr.empty())
		{
			int r = qr.front(); qr.pop();
			int c = qc.front(); qc.pop();
			if (r == rt && c == ct)
				break;
			for (int i = 0; i < maxn; i++)
			{
				if (legalMove(r, c, i))
				{
					qr.push(r + dr[i]);
					qc.push(c + dc[i]);
					length[r + dr[i]][c + dc[i]] = length[r][c] + 1;
				}
			}
		}
		std::cout << "To get from " << from << " to " << to << " takes " << length[rt][ct] << " knight moves." << std::endl;
	}
	return 0;
}