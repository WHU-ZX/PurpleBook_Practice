#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const static int MAXN = 5000;
static int n;
struct Rect
{
	int id = 0;
	int xl = 0, yl = 0;
	int xr = 0, yr = 0;
	int x = 0, y = 0;//选中的x和y
};
static Rect rects[MAXN + 1];
static bool vis[MAXN + 1];
static bool cmpId(Rect r1, Rect r2)
{
	return r1.id < r2.id;
}
static bool cmpX(Rect r1, Rect r2)
{
	return r1.xr < r2.xr;
}
static bool cmpY(Rect r1, Rect r2)
{
	return r1.yr < r2.yr;
}

int UVa_11134()
{
	const char* input = "inputs/11134.txt";
	//const char* output = "outputs/11134.txt";
	freopen(input, "r", stdin);

	while (cin >> n && n)
	{
		for (int i = 0; i < n; ++i)
		{
			rects[i].id = i + 1;
			cin >> rects[i].xl >> rects[i].yl >> rects[i].xr >> rects[i].yr;
		}
		//先处理X方向
		sort(rects, rects + n, cmpX); // 按区间右值升序排列
		for (int i = 0; i < n; ++i)
		{
			cout << rects[0].id;
		}

		//再处理Y方向


	}
	return 0;
}