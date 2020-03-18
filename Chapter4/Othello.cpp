#include <cstdio>
#include <iostream>
#define REDIRECT_STDIN() freopen("OthelloInput.txt", "r", stdin)
#define REDIRECT_STDOUT() freopen("OthelloOutput.txt", "w", stdin)
const int maxn = 9;
char board[maxn][maxn];
char term;//当前是谁的回合
using namespace std;

void print()
{
	for (int i = 1; i < maxn; i++)
	{
		for (int j = 1; j < maxn; j++)
		{
			cout << board[i][j];
		}
		/*if (i != maxn - 1)
			cout << endl;*/
		cout << endl;
	}
}

void Switch()
{
	if (term == 'B') term = 'W';
	else if (term == 'W')term = 'B';
}

int getFlag()
{
	return term == 'W' ? 1 : 0;
}

void initBoard()
{
	for (int i = 0; i < maxn; i++)
	{
		for (int j = 0; j < maxn; j++)
		{
			board[i][j] = '-';
		}
	}
}

bool legal(int r, int c, int flag)//走(r,c)是否合法    flag == 1 表示白子，flag == 0 表示黑子  正在走
{
	//if (r < 1 || r > 8 || c < 1 || c > 8) return false;
	char other = 'B', self = 'W';
	if (flag == 1)
	{
		other = 'B';
		self = 'W';
	}
	else
	{
		other = 'W';
		self = 'B';
	}
	if (board[r - 1][c] == other)//U
	{
		if (r - 2 >= 1)//假设r、c是合法的
		{
			int k = 1;
			while (r - k >= 1 && board[r - k][c] == other) k++;
			if (r - k >= 1 && board[r - k][c] == self)return true;
			//else 不满足
		}
	}
	if (board[r + 1][c] == other)//D
	{
		if (r + 2 <= 8)
		{
			int k = 1;
			while (r + k <= 8 && board[r + k][c] == other)k++;
			if (r + k <= 8 && board[r + k][c] == self)return true;
		}
	}
	if (board[r][c - 1] == other)//L
	{
		if (c - 2 >= 1)
		{
			int k = 1;
			while (c - k >= 1 && board[r][c - k] == other) k++;
			if (c - k >= 1 && board[r][c - k] == self)return true;
		}
	}
	if (board[r][c + 1] == other)//R
	{
		if (c + 2 <= 8)
		{
			int k = 1;
			while (c + k <= 8 && board[r][c + k] == other) k++;
			if (c + k <= 8 && board[r][c + k] == self)return true;
		}
	}
	if (board[r - 1][c - 1] == other)//LU
	{
		if (r - 2 >= 1 && c - 2 >= 1)
		{
			int k = 1;
			while (r - k >= 1 && c - k >= 1 && board[r - k][c - k] == other)k++;
			if (r - k >= 1 && c - k >= 1 && board[r - k][c - k] == self)return true;
		}
	}
	if (board[r + 1][c - 1] == other)//LD
	{
		if (r + 2 <= 8 && c - 2 >= 1)
		{
			int k = 1;
			while (r + k <= 8 && c - k >= 1 && board[r + k][c - k] == other)k++;
			if (r + k <= 8 && c - k >= 1 && board[r + k][c - k] == self) return true;
		}
	}
	if (board[r - 1][c + 1] == other)//RU
	{
		if (r - 2 >= 1 && c + 2 <= 8)
		{
			int k = 1;
			while (r - k >= 1 && c + k <= 8 && board[r - k][c + k] == other)k++;
			if (r - k >= 1 && c + k <= 8 && board[r - k][c + k] == self)return true;
		}
	}
	if (board[r + 1][c + 1] == other)//RD
	{
		if (r + 2 <= 8 && c + 2 <= 8)
		{
			int k = 1;
			while (r + k <= 8 && c + k <= 8 && board[r + k][c + k] == other)k++;
			if (r + k <= 8 && c + k <= 8 && board[r + k][c + k] == self)return true;
		}
	}
	return false;
}

void eat(int r, int c, int flag)
{
	char other = 'B', self = 'W';
	if (flag == 1)
	{
		other = 'B';
		self = 'W';
	}
	else
	{
		other = 'W';
		self = 'B';
	}
	if (board[r - 1][c] == other)//U
	{
		if (r - 2 >= 1)//假设r、c是合法的
		{
			int k = 1;
			while (r - k >= 1 && board[r - k][c] == other) k++;
			if (r - k >= 1 && board[r - k][c] == self)
			{
				for (int m = 1; m < k; m++)
					board[r - m][c] = self;
				board[r][c] = self;
			}
			//else 不满足
		}
	}
	if (board[r + 1][c] == other)//D
	{
		if (r + 2 <= 8)
		{
			int k = 1;
			while (r + k <= 8 && board[r + k][c] == other)k++;
			if (r + k <= 8 && board[r + k][c] == self)
			{
				for (int m = 1; m < k; m++)
					board[r + m][c] = self;
				board[r][c] = self;
			}
		}
	}
	if (board[r][c - 1] == other)//L
	{
		if (c - 2 >= 1)
		{
			int k = 1;
			while (c - k >= 1 && board[r][c - k] == other) k++;
			if (c - k >= 1 && board[r][c - k] == self)
			{
				for (int m = 1; m < k; m++)
					board[r][c - m] = self;
				board[r][c] = self;
			}
		}
	}
	if (board[r][c + 1] == other)//R
	{
		if (c + 2 <= 8)
		{
			int k = 1;
			while (c + k <= 8 && board[r][c + k] == other) k++;
			if (c + k <= 8 && board[r][c + k] == self)
			{
				for (int m = 1; m < k; m++)
					board[r][c + m] = self;
				board[r][c] = self;
			}
		}
	}
	if (board[r - 1][c - 1] == other)//LU
	{
		if (r - 2 >= 1 && c - 2 >= 1)
		{
			int k = 1;
			while (r - k >= 1 && c - k >= 1 && board[r - k][c - k] == other)k++;
			if (r - k >= 1 && c - k >= 1 && board[r - k][c - k] == self)
			{
				for (int m = 1; m < k; m++)
					board[r - m][c - m] = self;
				board[r][c] = self;
			}
		}
	}
	if (board[r + 1][c - 1] == other)//LD
	{
		if (r + 2 <= 8 && c - 2 >= 1)
		{
			int k = 1;
			while (r + k <= 8 && c - k >= 1 && board[r + k][c - k] == other)k++;
			if (r + k <= 8 && c - k >= 1 && board[r + k][c - k] == self)
			{
				for (int m = 1; m < k; m++)
					board[r + m][c - m] = self;
				board[r][c] = self;
			}
		}
	}
	if (board[r - 1][c + 1] == other)//RU
	{
		if (r - 2 >= 1 && c + 2 <= 8)
		{
			int k = 1;
			while (r - k >= 1 && c + k <= 8 && board[r - k][c + k] == other)k++;
			if (r - k >= 1 && c + k <= 8 && board[r - k][c + k] == self)
			{
				for (int m = 1; m < k; m++)
					board[r - m][c + m] = self;
				board[r][c] = self;
			}
		}
	}
	if (board[r + 1][c + 1] == other)//RD
	{
		if (r + 2 <= 8 && c + 2 <= 8)
		{
			int k = 1;
			while (r + k <= 8 && c + k <= 8 && board[r + k][c + k] == other)k++;
			if (r + k <= 8 && c + k <= 8 && board[r + k][c + k] == self)
			{
				for (int m = 1; m < k; m++)
					board[r + m][c + m] = self;
				board[r][c] = self;
			}
				
		}
	}
}

void getNum(int& WNUM, int& BNUM)
{
	WNUM = BNUM = 0;
	for (int i = 1; i < maxn; i++)
	{
		for (int j = 1; j < maxn; j++)
		{
			if (board[i][j] == 'B')
			{
				BNUM++;
			}
			else if (board[i][j] == 'W')
			{
				WNUM++;
			}
		}
	}
}

void list(char term)//输出所有可行解法
{
	bool findSol = false;
	int flag = term == 'W' ? 1 : 0;
	for (int i = 1; i < maxn; i++)
	{
		for (int j = 1; j < maxn; j++)
		{
			if (board[i][j] == '-' && legal(i,j,flag))
			{
				findSol = true;
				cout << '(' << i << ',' << j << ')';
			}
		}
	}
	if (!findSol)
	{
		cout << "No legal move";
	}
	cout << endl;
}


void Othello()
{
	REDIRECT_STDIN();
	int totalGameNum;
	if (scanf("%d",&totalGameNum) == 1)
	{
		for (int gameNum = 1; gameNum <= totalGameNum; gameNum++)
		{
			for (int i = 1; i < maxn; i++)//初始化棋盘
			{
				for (int j = 1; j < maxn; j++)
				{
					cin >> board[i][j];
				}
			}
			cin >> term;
			char OP;//指令
			cin >> OP;
			while (OP != 'Q')
			{
				if (OP == 'L')//打印合法操作
				{
					list(term);
				}
				else if (OP == 'M')//放置棋子
				{
					char cr, cc;
					cin >> cr;
					cin >> cc;
					int r = cr - '0', c = cc - '0';//行和列
					int flag = getFlag();//flag == 1 表示白子，flag == 0 表示黑子
					if (!legal(r, c, flag))
					{
						Switch();
					}
					flag = getFlag();
					eat(r, c, flag);
					Switch();
					int wN = 0, bN = 0;
					getNum(wN, bN);
					cout << "Black - " << bN << " White - " << wN << endl;
				}
				cin >> OP;
			}
			if (OP == 'Q')
			{
				print();
			}
		}
	}
}