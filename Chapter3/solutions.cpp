#include <iostream>
#include <stdio.h>
using namespace std;

void p1() 
{
	char s[81];
	cin >> s;
	int O_num = 0;
	int totalScore = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == 'O')
		{
			O_num++;
			totalScore += O_num;
		}
		else if (s[i] == 'X')
		{
			O_num = 0;
		}
	}
	cout << totalScore;
}
void p2()
{
	char s[10000];
	double C = 12.01,H=1.008,O = 16.00,N = 14.01;
	cin >> s;
	double total = 0.0;
	char c;
	for (int i = 0; i < strlen(s);)//每次循环找出一个元素的质量
	{
		c = s[i];
		i++;
		int cnt = 0;
		while (i < strlen(s) && s[i]>='0'&&s[i]<='9')
		{
			cnt *= 10;
			cnt += s[i] - '0';
			i++;
		}
		if (cnt == 0)
		{
			cnt = 1;
		}
		switch (c)
		{
		case 'C':
			total += cnt * C;
			break;
		case 'H':
			total += cnt * H;
			break;
		case 'O':
			total += cnt * O;
			break;
		case 'N':
			total += cnt * N;
			break;
		}
	}
	cout << total;
}
//int getlen(int k)//获得k的位数，0是1位
//{
//	int len = 1;
//	while (true)
//	{
//		k = k / 10;
//		if (k  > 0)
//		{
//			len++;
//		}
//		else 
//		{
//			break;
//		}
//	}
//	return len;
//}
void p3()
{
	int count = 0;
	cin >> count;
	int times[10] = { 0 };
	for (int i = 1; i <= count; i++)
	{
		int temp = i;
		//int len = getLen(temp);
		while (temp > 0)
		{
			int last = temp % 10;
			temp /= 10;
			times[last]++;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		cout << times[i]<<' ';
	}
}
void p4()
{
	char s[81];
	cin >> s;
	int length = strlen(s);
	bool found = false;
	for (int T = 1; T <= length; T++)
	{
		if (length % T != 0)
		{
			continue;
		}
		int num = length / T;
		for (int i = 0; i < T; i++)
		{
			bool flag = false;
			char c = s[i];
			for (int j = 1; j < num; j++) {
				if (c != s[i + j * T])
				{
					flag = true;
					break;
				}
			}
			if (flag)
			{
				break;
			}
			if (i == T - 1)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			cout << T;
			break;
		}
	}
}
void p5()
{
	const char* errorStr = "This puzzle has no final configuration";
	char puzzle[5][5];//以$为空位
	char inputs[1000];
	cin >> inputs;
	int emrow = -1, emcol = -1;
	for (int i = 0; i < 25; i++)
	{
		int row = i / 5;
		int col = i % 5;
		puzzle[row][col] = inputs[i];
		if (puzzle[row][col] == '$')
		{
			emrow = row;
			emcol = col;
		}
	}
	int i = 25;
	while (inputs[i] != '0')
	{
		switch (inputs[i])
		{
		case 'A'://up
			if (emrow < 1)
			{
				cout << errorStr;
				return;
			}
			puzzle[emrow][emcol] = puzzle[emrow - 1][emcol];
			puzzle[emrow - 1][emcol] = '$';
			emrow--;
			break;
		case 'B'://down
			if (emrow > 3)
			{
				cout << errorStr;
				return;
			}
			puzzle[emrow][emcol] = puzzle[emrow + 1][emcol];
			puzzle[emrow + 1][emcol] = '$';
			emrow++;
			break;
		case 'L'://left
			if (emcol < 1) {
				cout << errorStr;
				return;
			}
			puzzle[emrow][emcol] = puzzle[emrow][emcol-1];
			puzzle[emrow][emcol-1] = '$';
			emcol--;
			break;
		case 'R'://right
			if (emcol > 3) {
				cout << errorStr;
				return;
			}
			puzzle[emrow][emcol] = puzzle[emrow][emcol + 1];
			puzzle[emrow][emcol +1] = '$';
			emcol++;
			break;
		}
		i++;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << puzzle[i][j]<<' ';
		}
		cout << endl;

	}
}
void p6()//黑格用*表示，白格用W表示
{
	int row, col;
	cout << "输入行数和列数:" << endl;
	cin >> row >> col;
	cout << "输入数据" << endl;
	char s[1000];
	cin >> s;
	if (row < 1 || col>10)
	{
		cout << "行列数不满足要求";
		return;
	}
	if (strlen(s) != row * col)
	{
		cout << "数据输入错误" << endl;
		return;
	}
	
	int indexs[1000] = { -1 };
	for (int i = 1; i < 100; i++)
	{
		indexs[i] = -1;
	}
	int i_num = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int k = col * i + j; // 对应的数组下标
			if(s[k] != '*'&&(i == 0 || j == 0 || s[col*(i-1)+j] == '*'|| s[col * i + j - 1] == '*'))
			{
				indexs[i_num] = k;
				i_num++;
			}
		}
	}
	i_num = 0;
	for (; indexs[i_num] != -1; i_num++)//数据ABC*DEF*GH*IJKLMNO*PQRS*TUVW*XY*Za*bcd*efg
	{
		int trow = indexs[i_num] / col;
		int tcol = indexs[i_num] % col;
		int row_add = 0, col_add = 0;
		while (trow+row_add<row&& tcol + col_add<col&&s[col * (trow + row_add) + (tcol + col_add)] != '*')//纵向
		{
			cout << s[col * (trow + row_add) + (tcol + col_add)];
			row_add++;
		}
		cout << '\t';
		row_add = 0;
		while (trow + row_add < row && tcol + col_add < col && s[col * (trow + row_add) + (tcol + col_add)] != '*')//横向
		{
			cout << s[col * (trow + row_add) + (tcol + col_add)];
			col_add++;
		}
		cout << endl;
	}
}
void p7()//数据TATGATACTAAGCTACAAAGATCCTGAGATACTAAGATGT
{
	int row, col;
	cout << "输入行数和列数:" << endl;
	cin >> row >> col;
	cout << "输入数据" << endl;
	char s[50001];
	char Word[] = { 'A','C','G','T' };
	cin >> s;
	if (row < 4 || row>50 || col < 4 || col>1000)
	{
		cout << "行列数不满足要求";
		return;
	}
	if (strlen(s) != row * col)
	{
		cout << "数据输入错误" << endl;
		return;
	}
	for (int i = 0; i < col; i++)//对每一列进行筛选
	{
		int maxTag = 0;
		int num[] = { 0 ,0,0,0 };
		for (int j = 0; j < row; j++)
		{
			int k = col * j + i;//s中的下标
			switch (s[k])
			{
			case 'A':
				num[0]++;
				break;
			case 'C':
				num[1]++;
				break;
			case 'G':
				num[2]++;
				break;
			case 'T':
				num[3]++;
				break;
			}
		}
		for (int m = 1; m < 4; m++)
		{
			if (num[m] > num[maxTag])
			{
				maxTag = m;
			}
		}
		cout << Word[maxTag];
	}
}
void p8()//未完成
{
	int a, b;
	cout << "输入a和b:" << endl;
	cin >> a >> b;
	if (a < 0 || a>3000 || b < 1 || b>3000)
	{
		cout << "数据输入不满足要求s" << endl;
	}

}
void p9()
{
	char sp[1000], ss[1000];
	cout << "输入父序列" << endl;
	cin >> sp;
	cout << "输入子序列" << endl;
	cin >> ss;
	if (strlen(ss) > strlen(sp))
	{
		cout << "No" << endl;
		return;
	}
	int tp = 0, ts = 0;
	while (tp < strlen(sp) && ts < strlen(ss))
	{
		if (sp[tp] == ss[ts])
		{
			tp++;
			ts++;
		}
		else
		{
			tp++;
		}
	}
	if (tp <= strlen(sp) && ts == strlen(ss))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
}
void p10()//未完成？
{
	int data[12];
	cout << "请输入wi和hi(wi在前，hi在后，如:w1 h1 w2 h2...且每个数字以空格分开)" << endl;
	for (int i = 0; i < 12; i++)
	{
		cin >> data[i];
	}
	cout << endl;
	int width[] = { 0,0,0 }, height[] = { 0,0,0 };
	int cnt[] = { 0,0,0 };
	bool filled[] = { false,false,false };
	for (int i = 0; i < 12; i = i + 2)
	{
		int w = data[i], h = data[i + 1];
		if (filled[0] && filled[1] && filled[2])
		{
			if (w == width[0] && h == height[0])
			{
				cnt[0]++;
			}
			else if (w == width[1] && h == height[1])
			{
				cnt[1]++;
			}
			else if (w == width[2] && h == height[2])
			{
				cnt[2]++;
			}
			else//有了第四种长和宽的组合
			{
				cout << "No";
				return;
			}
		}
		else
		{
			if (filled[0] && w == width[0] && h == height[0])
			{
				cnt[0]++;
			}
			else if (filled[1] && w == width[1] && h == height[1])
			{
				cnt[1]++;
			}
			else if (filled[2] && w == width[2] && h == height[2])
			{
				cnt[2]++;
			}
			else if (!filled[0])
			{
				width[0] = w;
				height[0] = h;
				cnt[0]++;
				filled[0] = true;
			}
			else if (!filled[1])
			{
				width[1] = w;
				height[1] = h;
				cnt[1]++;
				filled[1] = true;
			}
			else if (!filled[2])
			{
				width[2] = w;
				height[2] = h;
				cnt[2]++;
				filled[2] = true;
			}
			else 
			{
				cout << "No";
				return;

			}
		}
	}
	if (cnt[0] + cnt[1]+ cnt[2] == 6 && cnt[0]%2==0 && cnt[1] % 2 == 0 && cnt[2] % 2 == 0)
	{
		if (cnt[0] == 6)
		{
			if (width[0] == height[0])
			{
				cout << "Yes";
				return;
			}
			else
			{
				cout << "No";
				return;
			}
		}
		else if (cnt[0] == 4)
		{
			cnt[0] = 2;
			cnt[2] = 2;
			width[2] = width[0];
			height[2] = height[0];
		}
		else if (cnt[1] == 4)
		{
			cnt[1] = 2;
			cnt[2] = 2;
			width[2] = width[1];
			height[2] = height[1];
		}
		int last = width[0],current = height[0];
		bool chosed[] = { true,false,false };
		int mostTime = 2;
		while ((!chosed[0] || !chosed[1] || !chosed[2])&&mostTime > 0)
		{
			for (int i = 1; i < 3; i++)
			{
				if (chosed[i])
				{
					continue;
				}
				if (current == width[i])
				{
					current = height[i];
					chosed[i] = true;
					mostTime--;
					break;
				}
				else if (current == height[i])
				{
					current = width[i];
					chosed[i] = true;
					mostTime--;
					break;
				}
				else
				{
					cout << "No";
					return;
				}
			}
		}
		if (current == last&&chosed[1]&&chosed[2])
		{
			cout << "Yes";
			return;
		}
		else
		{
			cout << "No";
			return;
		}
	}
	else
	{
		cout << "No";
		return;
	}
}
void p11()
{

}