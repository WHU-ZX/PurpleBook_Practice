#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const static int pileMaxNum = 7;
static vector<deque<int>> cardPiles;
static set<vector<deque<int>>> s;

static int time, temp;
static int curIdx;

static bool fit(int i1, int i2, int i3)
{
	return (i1 + i2 + i3) % 10 == 0;
}

static void push_back_3(int i1, int i2, int i3)//在下标为curIdx的牌堆下依次加入三个
{
	cardPiles[pileMaxNum].push_back(i1);
	cardPiles[pileMaxNum].push_back(i2);
	cardPiles[pileMaxNum].push_back(i3);
}

static bool operate()//执行下标为curIdx的牌堆
{
	deque<int>& d = cardPiles[curIdx];
	if (d.size() >= 3)
	{
		int u1, u2, d1, d2, d3;
		u1 = d.front(); d.pop_front();
		u2 = d.front(); d.pop_front();
		d1 = d.back(); d.pop_back();
		if (fit(u1, u2, d1))
		{
			push_back_3(u1, u2, d1);
			return true;
		}
		else
		{
			d.push_back(d1);
			d.push_front(u2);
			d.push_front(u1);
		}
		d1 = d.back(); d.pop_back();
		d2 = d.back(); d.pop_back();
		if (fit(u1, d1, d2))
		{
			d.pop_front();
			push_back_3(u1, d2, d1);
			return true;
		}
		else
		{
			d.push_back(d2);
			d.push_back(d1);
		}
		d1 = d.back(); d.pop_back();
		d2 = d.back(); d.pop_back();
		d3 = d.back(); d.pop_back();
		if (fit(d1, d2, d3))
		{
			push_back_3(d3, d2, d1);
			return true;
		}
		else
		{
			d.push_back(d3);
			d.push_back(d2);
			d.push_back(d1);
		}
		return false;
	}
	else
		return false;
}



static void init()
{
	if (!cardPiles.empty()) cardPiles.clear();
	if (!s.empty()) s.clear();
	for (int i = 0; i < pileMaxNum + 1; i++)
		cardPiles.push_back(deque<int>());
	cardPiles[pileMaxNum].push_back(temp);
	for (int i = 0; i < 51; i++)
	{
		cin >> temp;
		cardPiles[pileMaxNum].push_back(temp);
	}
	for (int i = 0; i < 7; i++)
	{
		int num = cardPiles[pileMaxNum].front(); cardPiles[pileMaxNum].pop_front();
		cardPiles[i].push_back(num);
	}
	s.insert(cardPiles);
	curIdx = 0;
}

static bool move()//返回true表示操作成功，找到非空下标，返回false表示7个牌堆全为空
{
	if (cardPiles[pileMaxNum].size() == 52) return false;
	curIdx++; curIdx %= 7;
	while (cardPiles[curIdx].empty())
	{
		curIdx++; curIdx %= 7;
	}
	return true;
}

int WF_UVa_246()
{
	const char* input = "inputs/WF_246.txt";
	const char* output = "outputs/WF_246.txt";
	freopen(input, "r", stdin);
	while (cin >> temp && temp)
	{
		init();
		//开始处理
		for (time = 8;; time++)
		{
			deque<int>& d = cardPiles[curIdx];
			int nI = cardPiles[pileMaxNum].front(); cardPiles[pileMaxNum].pop_front();
			d.push_back(nI);
			while (operate());
			if (!move())//成功
			{
				printf("Win : %d\n", time);
				break;
			}
			else if (cardPiles[pileMaxNum].empty())//输了
			{
				printf("Loss: %d\n", time);
				break;
			}
			else if (s.find(cardPiles) != s.end())//循环了
			{
				printf("Draw: %d\n", time);
				break;
			}
			s.insert(cardPiles);
		}
	}
	return 0;
}