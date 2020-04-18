#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

const static int MAXN = 5000;
static int n;
static struct Rect
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
	if (r1.xr != r2.xr)
		return r1.xr < r2.xr;
	else
		return r1.xl < r2.xl;
}
static bool cmpY(Rect r1, Rect r2)
{
	if (r1.yr != r2.yr)
		return r1.yr < r2.yr;
	else
		return r1.yl < r2.yl;
}

static bool dealX()//处理X方向
{
	memset(vis, false, sizeof vis);
	sort(rects, rects + n, cmpX); // 按区间右值升序排列
	for (int i = 0; i < n; ++i)
	{
		int right = rects[i].xr;
		int left = rects[i].xl;
		while (left <= right && vis[left])
		{
			++left;
		}
		if (left > right)
		{
			return false;
		}
		rects[i].x = left;
		vis[left] = true;
	}
	return true;
}

static bool dealY()//处理Y方向
{
	memset(vis, false, sizeof vis);
	sort(rects, rects + n, cmpY); // 按区间右值升序排列
	for (int i = 0; i < n; ++i)
	{
		int right = rects[i].yr;
		int left = rects[i].yl;
		while (left <= right && vis[left])
		{
			++left;
		}
		if (left > right)
		{
			return false;
		}
		rects[i].y = left;
		vis[left] = true;
	}
	return true;
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
		
		if (dealX() && dealY())
		{
			sort(rects, rects + n, cmpId); // 按id升序排列
			for (int i = 0; i < n; ++i)
				cout << rects[i].x << ' ' << rects[i].y << endl;
		}
		else
			cout << "IMPOSSIBLE" << endl;

	}
	return 0;
}