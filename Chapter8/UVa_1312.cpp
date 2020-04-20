#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#pragma warning(disable:4996)
using namespace std;

const static int MAXN = 100,MAXW = 10000, MAXH = 10000;
static int N, W, H;
static struct Tree
{
	int x, y;
	bool operator < (const Tree& t)const
	{
		return x < t.x || (x == t.x && y < t.y);
	}
};
static Tree trees[MAXN];
static set<int> s;

int UVa_1312()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/1312.txt";
	//const char* output = "outputs/1312.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		cin >> N >> W >> H;
		s.clear();
		for (int i = 0; i < N; ++i)
		{
			cin >> trees[i].x >> trees[i].y;
			s.insert(trees[i].y);
		}
		s.insert(0); s.insert(H);
		sort(trees, trees + N);//排序
		set<int>::iterator iter1, iter2;
		int maxX = 0, maxY = 0, maxL = 1;
		//set 是有序的
		for (iter1 = s.begin(); iter1 != s.end();)//枚举y的最小值
		{
			int ymin = *iter1;
			for (iter2 = ++iter1; iter2 != s.end(); iter2++)//枚举y的最大值
			{
				int ymax = *iter2;
				int dy = ymax - ymin, dx, dL;
				if (dy <= maxL) continue;
				int lastX = 0;
				for (int i = 0; i < N; ++i)
				{
					if (trees[i].y >= ymax || trees[i].y <= ymin) continue;
					dx = trees[i].x - lastX;
					dL = min(dx, dy);
					if (dL > maxL)
					{
						maxL = dL;
						maxX = lastX;
						maxY = ymin;
					}
					lastX = trees[i].x;
				}
				//处理右边界
				dx = W - lastX;
				dL = min(dx, dy);
				if (dL > maxL)
				{
					maxL = dL;
					maxX = lastX;
					maxY = ymin;
				}
			}
		}
		printf("%d %d %d\n", maxX, maxY, maxL);
		if (testCase) cout << endl;
	}
	return 0;
}