#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;

int UVa_11040()
{
	const char* input = "inputs/11040.txt";
	//const char* output = "outputs/11040.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		int numbers[9][9] = { 0 };
		for (int i = 0; i < 9; i += 2)
			for (int j = 0; j <= i; j += 2) 
			{
				cin >> numbers[i][j];
			}
		for (int i = 1; i < 9; i += 2) // 计算最后一行
			numbers[8][i] = (numbers[6][i - 1] - numbers[8][i - 1] - numbers[8][i + 1]) / 2;
		for (int i = 7; i > 0; --i) // 7~1行
			for (int j = 0; j <= i; ++j) 
			{
				numbers[i][j] = numbers[i + 1][j] + numbers[i + 1][j + 1];
			}
		//输出
		for (int i = 0; i < 9; ++i)
		{
			cout << numbers[i][0];
			for (int j = 1; j <= i; ++j)
				cout << ' ' << numbers[i][j];
			cout << endl;
		}
	}
	return 0;
}