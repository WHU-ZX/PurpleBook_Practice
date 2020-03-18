#include <cstdio>
#include <iostream>
using namespace std;

#define REDIRECT_STDIN() freopen("SquaresInput.txt", "r", stdin)
#define REDIRECT_STDOUT() freopen("SquaresOutput.txt", "w", stdin)

const int maxn = 11;
bool H[maxn][maxn], V[maxn][maxn];
int squareNum[maxn];//答案

void Squares()
{
	//输入输出重定向
	REDIRECT_STDIN();
	//REDIRECT_STDOUT();
	//
	int proNum = 0, n, m;
	while (scanf("%d", &n) == 1)
	{
		if(proNum) printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", ++proNum);
		cin >> m;
		char c;
		int vi, vj;
		//初始化
		for (int i = 0; i < maxn; i++)
		{
			for (int j = 0; j < maxn; j++)
			{
				H[i][j] = V[i][j] = false;
			}
		}
		for (int i = 0; i < maxn; i++)
		{
			squareNum[i] = 0;
		}

		for (int i = 0; i < m; i++)
		{
			cin >> c >> vi >> vj;
			if (c == 'H') H[vi][vj] = true;
			else if (c == 'V') V[vj][vi] = true;//看错题的时候写的是V[vi][vj] = true
		}
		bool find = false;
		for (int length = 1; length <= n; length++)//边长
		{
			for (int i = 1; i <= n - length; i++)//左上角顶点的i坐标
			{
				for (int j = 1; j <= n - length; j++)//左上角顶点的j坐标
				{
					int findNotExist = false;
					for (int k = 0; k < length; k++)
					{
						if (!H[i][j + k] || !H[i + length][j + k])//水平线段
						{
							findNotExist = true;
							break;
						}
						if (!V[i + k][j] || !V[i + k][j + length])//竖直线段
						{
							findNotExist = true;
							break;
						}
					}
					if (!findNotExist)//存在此正方形
					{
						squareNum[length]++;
						find = true;
					}
				}
			}
		}
		for (int i = 1; i <= n; i++)//输出结果
		{
			if(squareNum[i] > 0)
				printf("%d square (s) of size %d\n", squareNum[i], i);
		}
		if(!find) printf("No completed squares can be found.\n");
	}
}
