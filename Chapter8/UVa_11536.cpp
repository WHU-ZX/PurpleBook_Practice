#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#pragma warning(disable:4996)
using namespace std;
static int N, M, K;// mod M   1~K  N numbers
const static int MAXN = 1000000, MAXM = 1000, MAXK = 100;
static int numbers[MAXN];
static map<int, int> m;

int UVa_11536()
{
	const char* input = "inputs/a.txt";
	//const char* input = "inputs/11536.txt";
	//const char* output = "outputs/11536.txt";
	freopen(input, "r", stdin);
	int testCase, cas = 1;
	cin >> testCase;
	while (testCase--)
	{
		cin >> N >> M >> K;
		numbers[0] = 1;
		numbers[1] = 2;
		numbers[2] = 3;
		if (cas == 10)
		{
			cout << "";
		}
		for (int i = 3; i < N; ++i)
			numbers[i] = (numbers[i - 1] + numbers[i - 2] + numbers[i - 3]) % M + 1;
		int leftIndex = 0, rightIndex = -1;
		int mL = -10000000, mR = -1;
		
		m.clear();
		while (rightIndex < N - 1)
		{
			while (m.size() != K && rightIndex < N - 1)
			{
				rightIndex++;
				if (numbers[rightIndex] <= K)
				{
					if (m.find(numbers[rightIndex]) != m.end())
						m[numbers[rightIndex]]++;
					else
						m[numbers[rightIndex]] = 1;
				}
			}
			//leftIndex向左移
			if (m.size() == K)
			{
				if (rightIndex - leftIndex < mR - mL)
				{
					mL = leftIndex; mR = rightIndex;
				}
				while (m.size() == K)
				{
					if (numbers[leftIndex] <= K)
					{
						if (m[numbers[leftIndex]] > 1)
							m[numbers[leftIndex]]--;
						else // = 1
							m.erase(numbers[leftIndex]);
					}
					++leftIndex;
				}
				if (mL < leftIndex && rightIndex - leftIndex + 1 < mR - mL)
				{
					mL = leftIndex - 1;
					mR = rightIndex;
				}
			}
		}
		//此处要将leftIndex左移
		if (m.size() == K)
		{
			if (rightIndex - leftIndex < mR - mL)
			{
				mL = leftIndex; mR = rightIndex;
			}
			while (m.size() == K)
			{
				if (numbers[leftIndex] <= K)
				{
					if (m[numbers[leftIndex]] > 1)
						m[numbers[leftIndex]]--;
					else // = 1
						m.erase(numbers[leftIndex]);
				}
				++leftIndex;
			}
			if (mL < leftIndex && rightIndex - leftIndex + 1 < mR - mL)
			{
				mL = leftIndex - 1;
				mR = rightIndex;
			}
		}
		if (mR != -1)
			cout << "Case " << cas << ": " << mR - mL + 1<< endl;
		else
			cout << "Case " << cas << ": sequence nai" << endl;
		++cas;
	}
	return 0;
}