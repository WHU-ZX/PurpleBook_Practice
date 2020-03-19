#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;

static int n;
static queue<int> q;

void clear() {
	queue<int> empty;
	swap(empty, q);
}

void ThrowingCardsAway()
{
	const char* input = "datas/ThrowingCardsAwayInput.txt";
	const char* output = "datas/ThrowingCardsAwayOutput.txt";
	freopen(input, "r", stdin);
	//freopen(output, "w", stdout);
	cin >> n;
	bool first = true;
	while (n != 0)
	{
		//处理开始
		if (!first)
			cout << endl;
		else
			first = false;
		if (!q.empty()) clear();
		if (n == 1)
		{
			printf("Discarded cards:\nRemaining card: 1");
		}
		else
		{
			for (int i = 1; i <= n; i++)
			{
				q.push(i);
			}
			bool firstI = true;
			printf("Discarded cards:");
			while (q.size() >= 2)
			{
				if (firstI)
					firstI = false;
				else
					cout << ',';
				printf(" %d", q.front());
				q.pop();
				q.push(q.front());
				q.pop();
			}
			printf("\nRemaining card: %d", q.front());
			q.pop();
		}
		//处理结束
		cin >> n;
	}
	cout << endl;
}