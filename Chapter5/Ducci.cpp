#include <cstdio>
#include <queue>
#include <cmath>

const int maxn = 15;
int list[maxn] = { 0 };
int maxStep = 1000;
int checkStep = 50;
int numberNum;

bool allZero()
{
	for (int i = 0; i < numberNum; i++)
	{
		if (list[i]) return false;
	}
	return true;
}

void go()
{
	int first = list[0];
	for (int i = 0; i < numberNum - 1; i++)
	{
		list[i] = abs(list[i] - list[i + 1]);
	}
	list[numberNum - 1] = abs(list[numberNum - 1] - first);
}

void Ducci()
{
	const char* input = "DucciInput.txt";
	const char* output = "DucciOutput.txt";
	freopen(input, "r", stdin);
	freopen(output, "w", stdout);
	int gameNum;
	scanf("%d", &gameNum);
	while (gameNum--)
	{
		
		scanf("%d", &numberNum);
		for (int i = 0; i < numberNum; i++)
		{
			int t;
			scanf("%d", &t);
			list[i] = t;
		}
		int cStep = 0;
		for (int i = 0; i < maxStep; i++)
		{
			go();
			cStep++;
			cStep %= checkStep;
			if (!cStep && allZero())//cStep = 0
				break;
		}
		
		if (allZero())
		{
			printf("ZERO\n");
		}
		else
		{
			printf("LOOP\n");
		}
	}
}