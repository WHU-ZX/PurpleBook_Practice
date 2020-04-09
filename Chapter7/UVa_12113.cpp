#include "normal_header.h"

const static int MAXR = 5, MAXC = 15;
static bool vis[10];
static char aim[MAXR][MAXC], p[MAXR][MAXC];

static bool theSame()
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 9; ++j)
			if (aim[i][j] != p[i][j]) return false;
	return true;
}

static bool dfs(int depth)
{
	if (theSame()) return true;
	if (depth >= 6)return false;

	//temp用于保存改变前的p，以便复原
	char temp[5][9];
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 9; ++j)
			temp[i][j] = p[i][j];

	for (int i = 0; i < 9; ++i)
	{
		if (vis[i]) continue;
		vis[i] = true;

		int row = i / 3, col = (i % 3) * 2;
		p[row][col + 1] = p[row][col + 3] = p[row + 2][col + 1] = p[row + 2][col + 3] = '_';
		p[row + 1][col] = p[row + 2][col] = p[row + 1][col + 4] = p[row + 2][col + 4] = '|';
		p[row + 1][col + 2] = p[row + 2][col + 2] = p[row + 1][col + 1] = p[row + 1][col + 3] = ' ';
		if (dfs(depth + 1))
			return true;

		//复原
		vis[i] = false;
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 9; ++j)
				p[i][j] = temp[i][j];
	}
	return false;
}

int UVa_12113()
{
	const char* input = "inputs/12113.txt";
	//const char* output = "outputs/12113.txt";
	freopen(input, "r", stdin);
	int cas = 0;
	while (true)
	{
		for (int i = 0; i < 5; ++i)
		{
			fgets(aim[i], MAXC, stdin);
		}
		if (aim[0][0] == '0') return 0;
		printf("Case %d: ", ++cas);
		//初始化
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 9; ++j) p[i][j] = ' ';
		memset(vis, false, sizeof vis);
		if (dfs(0))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}