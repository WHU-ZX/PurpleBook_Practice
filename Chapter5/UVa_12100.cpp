#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;
static queue<int> q;
static priority_queue<int> pq;
int gameNum;
static void clear() {
	if (!q.empty())
	{
		queue<int> empty;
		swap(empty, q);
	}
	if (!pq.empty())
	{
		priority_queue<int> empty;
		swap(empty, pq);
	}
}
//思路：优先级队列+普通队列，普通队列按顺序存，优先级队列可以将最大优先级放在队首
int UVa_12100()
{
	const char* input = "datas/UVa_12100_input.txt";
	const char* output = "datas/UVa_12100_output.txt";
	freopen(input, "r", stdin);

	cin >> gameNum;
	while (gameNum--)
	{
		clear();
		int taskNum, pos;
		cin >> taskNum >> pos;
		int priority;
		while (taskNum--)
		{
			cin >> priority;
			q.push(priority);
			pq.push(priority);
		}
		int t = 0;
		while (!q.empty())
		{
			if (q.front() < pq.top())
			{
				q.push(q.front());
				q.pop();
				if (pos == 0)
					pos = q.size() - 1;
				else
					pos--;
			}
			else
			{
				t++;
				if (pos == 0)
					break;
				else
				{
					q.pop();
					pq.pop();
					pos--;
				}
			}
		}
		cout << t << endl;
	}
	return 0;
}