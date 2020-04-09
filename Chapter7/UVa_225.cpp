#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
const static int MAXN = 20, MAXK = 50;

static int step;
static int n;//最后一步的步长
static int Golygons;//游戏数

static pair<int, int> visPoints[MAXN + 1];
static int visNum;

static pair<int, int> blocks[MAXK + 1];
static int blockNum;
static const char dirs[4] = { 'e','n','s','w' };//按字典升序排列的四个方向
static map<char, int> idxMap;
static const int d[4][2] = { {1,0},{0,1},{0,-1},{-1,0} };//四个方向对应的数据

static char ans[MAXN + 1];
static int ansCnt, ansIdx;
static int lastDir;

static bool between(int first, int second, int k)
{
	int k1 = first <= second ? first : second;
	int k2 = first + second - k1;
	return k >= k1 && k <= k2;
}

static bool visited(int x, int y, int dir)
{
	pair<int, int> p(x, y);
	p.first += d[dir][0] * step;
	p.second += d[dir][1] * step;
	if (p.first == 0 && p.second == 0 && step == n)return false;
	for (int i = 0; i < visNum; ++i)
	{
		if (p == visPoints[i]) return true;
	}
	return false;
}

static bool canGo(int x, int y, int dir)
{
	for (int i = 0; i < blockNum; ++i)
	{
		pair<int, int> p = blocks[i];
		if (x == p.first && between(y, y + d[dir][1] * step, p.second) || y == p.second && between(x, x + d[dir][0] * step, p.first))
			return false;
	}
	return !visited(x, y, dir);
}

static void init()
{
	visNum = 0;
	ansCnt = 0;
	step = 1;
	ansIdx = 0;
	lastDir = -1;
	//blockNum = 0;
}

static void solve(int x, int y)
{
	if (x == 0 && y == 0 && step != 1)//终止条件
	{
		for (int i = 0; i < ansIdx; ++i)
			printf("%c", ans[i]);
		printf("%c\n", dirs[lastDir]);
		++ansCnt;
	}
	else
	{
		if (step == n + 1) return;
		int idxs[4];
		int cnt;
		if (lastDir == -1)
		{
			for (int i = 0; i < 4; ++i)
			{
				idxs[i] = i;
			}
			cnt = 4;
		}
		else
		{
			cnt = 2;
			if (lastDir == 0 || lastDir == 3)// e  w
			{
				idxs[0] = 1; idxs[1] = 2;
			}
			else// n  s
			{
				idxs[0] = 0; idxs[1] = 3;
			}
		}
		for (int i = 0; i < cnt; ++i)
		{
			int idx = idxs[i];
			if (canGo(x, y, idx))//如果可以走这个方向
			{
				if (lastDir >= 0) ans[ansIdx++] = dirs[lastDir];
				int tDir = lastDir;
				lastDir = idxs[i];
				++step;
				visPoints[visNum] = pair<int, int>(x, y);
				++visNum;
				solve(x + d[idx][0] * (step - 1), y + d[idx][1] * (step - 1));
				lastDir = tDir;
				--step;
				--visNum;
				if (lastDir >= 0) ansIdx--;
			}
		}
	}
}

int WF_UVa_225()
{
	const char* input = "inputs/WF_225.txt";
	//const char* output = "outputs/WF_225.txt";
	freopen(input, "r", stdin);

	scanf("%d\n", &Golygons);
	while (Golygons--)
	{
		init();
		scanf("%d\n", &n);
		scanf("%d\n", &blockNum);
		int tx, ty;
		for (int i = 0; i < blockNum; i++)
		{
			scanf("%d %d\n", &tx, &ty);
			blocks[i].first = tx;
			blocks[i].second = ty;
		}
		//do something
		solve(0, 0);
		//if (!ansCnt) printf("\n");
		printf("Found %d golygon(s).\n\n", ansCnt);
	}


	return 0;
}