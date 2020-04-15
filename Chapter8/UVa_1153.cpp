#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#pragma warning(disable:4996)
using namespace std;
const static int MAXN = 800000;
static int n;
struct Task
{
	int q;
	int d;//截止时间
	bool operator < (const struct Task& rhs) const {
		return d < rhs.d || (d == rhs.d && q < rhs.q);
	}
};

static Task tasks[MAXN];

int UVa_1153()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/1153.txt";
	//const char* output = "outputs/1153.txt";
	freopen(input, "r", stdin);

	int testCase;
	cin >> testCase;
	bool flag = false;
	while (testCase--)
	{
		cin >> n;
		int tq, td;
		if (flag) cout << endl;
		flag = true;
		for (int i = 0; i < n; ++i)
		{
			cin >> tq >> td;
			tasks[i].q = tq;
			tasks[i].d = td;
		}
		sort(tasks, tasks + n);
		priority_queue<int, vector<int>, less<int> > q;//大的在队首
		int tol = 0, time = 0;
		for (int i = 0; i < n; ++i)
		{
			if (time + tasks[i].q <= tasks[i].d)//可以，要取等吗？
			{
				time += tasks[i].q;
				tol += 1;
				q.push(tasks[i].q);
			}
			else if (!q.empty() && q.top() > tasks[i].q)
			{
				time -= q.top(); q.pop();
				time += tasks[i].q;
				q.push(tasks[i].q);
			}
		}
		cout << tol << endl;
	}

	return 0;
}