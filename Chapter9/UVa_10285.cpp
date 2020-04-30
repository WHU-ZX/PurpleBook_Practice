#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
const static int MAXR = 100, MAXC = 100;
static string name;
static int r, c;
static int matrix[MAXR][MAXC];
const static int dx[4] = { 1,-1,0,0 };
const static int dy[4] = { 0,0,1,-1 };
static int d[MAXR][MAXC];


static int DP(int row, int col)
{
	if (d[row][col] > 0) return d[row][col];
	int maxL = 0;
	for (int i = 0; i < 4; ++i)
	{
		int tRow = row + dx[i], tCol = col + dy[i];
		if (tRow < 0 || tRow >= r || tCol < 0 || tCol >= c || matrix[row][col] <= matrix[tRow][tCol])continue;
		int t = DP(tRow, tCol);
		maxL = max(maxL, t);
	}
	return d[row][col] = maxL + 1;
}

int UVa_10285()
{
	const char* input = "inputs/10285.txt";
	//const char* output = "outputs/10285.txt";
	freopen(input, "r", stdin);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		cin >> name >> r >> c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j) cin >> matrix[i][j];
		memset(d, 0, sizeof d);
		int maxL = 0;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j) maxL = max(maxL, DP(i, j));
		cout << name << ": " << maxL << endl;
	}
	return 0;
}
