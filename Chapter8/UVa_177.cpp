#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
static int n;
const static int MAXN = 13, Inf = 1 << 30;
static struct Line
{
	int x;
	int y;
	int dir;//0-右  1-上  2-左  3-下
	char getChar()
	{
		if (dir % 2 == 0)
			return '_';
		else
			return '|';
	}
};
static bool cmp(Line l1, Line l2)
{
	if (l1.y != l2.y) return l1.y < l2.y;
	return l1.x < l2.x;
}
static Line lines[1 << MAXN + 5];

//static int lNum;
static int maxLNum;
static int maxNsince;
const static int dr[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };//从尾部到头部的dr

static void unfold()
{
	int i = maxNsince - 1, j = maxNsince;
	int ox = lines[i].x - dr[lines[i].dir][0];
	int oy = lines[i].y - dr[lines[i].dir][1];
	for (; i >= 0; --i, ++j)
	{
		int dir = (lines[i].dir + 1) % 4;
		lines[j].dir = dir;
		lines[j].x = ox + (lines[i].y - oy) + dr[dir][0];
		lines[j].y = oy + (ox - lines[i].x) + dr[dir][1];
	}
	maxNsince <<= 1;
}

static void print(int N)
{
	int L = 1 << N;
	Line* tLines = new Line[L];
	memcpy(tLines, lines, (sizeof Line) * L);
	int minX = Inf, minY = Inf, maxY = -Inf;
	bool vFirst = false;//下标为0的当中有|
	//标准化
	for (int i = 0; i < L; ++i)
	{
		if (tLines[i].x < minX) minX = tLines[i].x;
		if (tLines[i].y < minY) minY = tLines[i].y;
		if (tLines[i].y > maxY) maxY = tLines[i].y;
	}
	for (int i = 0; i < L; ++i)
	{
		tLines[i].y -= maxY;
		tLines[i].y = -tLines[i].y;
		tLines[i].x -= minX;
		if (tLines[i].x == 0 && tLines[i].dir % 2 == 1) vFirst = true;
		switch (tLines[i].dir)
		{
		case 0://右
			tLines[i].x = 2 * tLines[i].x + 1;
			break;
		case 1://上
			tLines[i].x = 2 * tLines[i].x;
			break;
		case 2://左
			tLines[i].x = 2 * tLines[i].x - 1;
			break;
		case 3://下
			tLines[i].x = 2 * tLines[i].x;
			tLines[i].y = tLines[i].y + 1;
			break;
		}
	}
	if(!vFirst) for (int i = 0; i < L; ++i) tLines[i].x -= 1;
	sort(tLines, tLines + L, cmp);
	int lastY = 0;
	int curX = 0;
	for (int i = 0; i < L; ++i)
	{
		if (tLines[i].y != lastY)
		{
			lastY = tLines[i].y;
			cout << endl;
			curX = 0;
		}
		while (curX != tLines[i].x)
		{
			cout << ' ';
			curX++;
		}
		cout << tLines[i].getChar();
		curX++;
	}
	delete[] tLines;
}

int UVa_177()
{
	const char* input = "inputs/177.txt";
	//const char* output = "outputs/177.txt";
	freopen(input, "r", stdin);
	maxNsince = 0;//所有出现过的最大的N
	//int lNum = 0;
	while (cin >> n && n)
	{
		maxLNum = 1 << n;
		if (maxLNum <= maxNsince)
		{
			print(n);
		}
		else
		{
			if (maxNsince == 0)
			{
				lines[0].x = 0;
				lines[0].y = 0;
				lines[0].dir = 0;
				maxNsince = 1;
			}
			while (maxNsince != maxLNum)
			{
				unfold();
			}
			print(n);
			if (maxLNum > maxNsince) maxNsince = maxLNum;
		}
		cout << endl << '^' << endl;
	}
	return 0;
}