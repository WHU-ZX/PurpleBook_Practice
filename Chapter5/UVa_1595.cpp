#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include<algorithm>
using namespace std;
static int gameNum;
static int pointNum;
struct Point
{
	int x;
	int y;
};
static map<int, vector<Point> > m;

bool cmp(Point p1, Point p2)
{
	return p1.x < p2.x;
}

int UVa_1595()
{
	const char* input = "datas/UVa_1595_input.txt";
	const char* output = "datas/UVa_1595_output.txt";
	freopen(input, "r", stdin);

	cin >> gameNum;
	while (gameNum--)
	{
		m.clear();
		cin >> pointNum;
		Point p;
		while (pointNum--)
		{
			cin >> p.x >> p.y;
			p.x *= 2;//保证p.x是偶数
			if (m.find(p.y) != m.end())//存在此vector
			{
				m[p.y].push_back(p);
			}
			else//不存在此vector
			{
				vector<Point> tP;
				tP.push_back(p);
				m[p.y] = tP;
			}
		}
		map<int, vector<Point> >::iterator iter;
		bool hasLine = true;
		int cX = 0;
		bool initial = true;
		for (iter = m.begin(); iter != m.end(); iter++)
		{
			vector<Point> v = iter->second;
			//检验v中是否是对称的，若不是，令hasLine=false并break
			sort(v.begin(), v.end(), cmp);
			bool naturalFinish = true;
			for (int i = 0,j = v.size() - 1; i <= j; i++, j--)
			{
				if (initial)
				{
					cX = (v[i].x + v[j].x) / 2;
					initial = false;
				}
				else
				{
					if ((v[i].x + v[j].x) / 2 != cX)
					{
						naturalFinish = false;
						break;
					}
				}
			}
			if (!naturalFinish)//break退出，表示已经检测到没有对称轴
			{
				hasLine = false;
				break;
			}
		}
		if (hasLine)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}