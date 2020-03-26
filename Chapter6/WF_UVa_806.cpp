#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;

const static int maxn = 65;
static int bitmap[maxn][maxn];
static int blackPath[maxn * maxn];
static int n, blackNum;


static int judge(int si, int sj, int ei, int ej)//����ӵ�(si,sj)��(ei,ej)ȫ��һ����ɫ�����ɫ����0����ɫ����1�����в�ͬ��ɫ������-1
{
	int color = bitmap[si][sj];
	for (int i = si; i <= ei; i++)
		for (int j = sj; j <= ej; j++)
			if (bitmap[i][j] != color) return -1;
	return color;
}

static void readGraph(int si, int sj, int ei, int ej, int path)//����ӵ�(si,sj)��(ei,ej)��ͼƬ���е���(si+ei)/2,(sj+ej)/2
{
	int color = judge(si, sj, ei, ej);
	if (color == -1)//��ɫ��ͬ
	{
		readGraph(si, sj, (si + ei) / 2, (sj + ej) / 2, path * 10 + 1);
		readGraph(si, (sj + ej) / 2 + 1, (si + ei) / 2, ej, path * 10 + 2);
		readGraph((si + ei) / 2 + 1, sj, ei, (sj + ej) / 2, path * 10 + 3);
		readGraph((si + ei) / 2 + 1, (sj + ej) / 2 + 1, ei, ej, path * 10 + 4);
	}
	else//��ɫ��ͬ
		if(bitmap[si][sj] == 1)
			blackPath[blackNum++] = path;
}

int myPow(int a, int b)//����a��b�η�
{
	int ret = 1;
	while (b--)
		ret *= a;
	return ret;
}

static int rfive2ten(int fiveNum)//��ת���5����ת10����
{
	int length = ((int)log10(fiveNum)) + 1;//λ��
	int ret = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		ret += fiveNum % 10 * myPow(5, i);
		fiveNum /= 10;
	}
	return ret;
}

static void drawGraph(int num)//n��֪������ʮ��������ͼ
{
	int si = 0, sj = 0, ei = n - 1, ej = n - 1;
	int flag = num % 5;;
	while ( flag != 0)
	{
		switch (flag)
		{
		case 1:
			ei = (si + ei) / 2;
			ej = (sj + ej) / 2;
			break;
		case 2:
			ei = (si + ei) / 2;
			sj = (sj + ej) / 2 + 1;
			break;
		case 3:
			si = (si + ei) / 2 + 1;
			ej = (sj + ej) / 2;
			break;
		case 4:
			si = (si + ei) / 2 + 1;
			sj = (sj + ej) / 2 + 1;
			break;
		}
		num = num / 5;
		flag = num % 5;
	}
	for (int i = si; i <= ei; i++)
		for (int j = sj; j <= ej; j++)
			bitmap[i][j] = 1;
}

static void draw()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (bitmap[i][j] == 0) cout << '.';
			else cout << '*';
		if (i != n - 1) cout << endl;//���һ�к��治���\n
	}
}

int WF_UVa_806()
{
	const char* input = "inputs/WF_806.txt";
	const char* output = "outputs/WF_806.txt";
	freopen(input, "r", stdin);
	bool first = true;
	int gameNum = 1;
	while (cin >> n && n)
	{
		if (n > 0)
		{
			char tChar; scanf("%c", &tChar);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					scanf("%c", &tChar);
					bitmap[i][j] = tChar - '0';
				}
				scanf("%c", &tChar);
			}
			if (first) first = false;
			else  cout << endl;
			cout << "Image " << gameNum << endl;
			//����ת������
			blackNum = 0;
			readGraph(0, 0, n - 1, n - 1, 0);
			if (blackNum == 0)//ȫ��
			{
				cout << "Total number of black nodes = 0" << endl;
			}
			else//�кڵ�
			{
				for (int i = 0; i < blackNum; i++)
					blackPath[i] = rfive2ten(blackPath[i]);
				sort(blackPath, blackPath + blackNum);
				int outNum = 0;
				for (int i = 0; i < blackNum; i++)
				{
					if (outNum == 0 && i != 0) cout << endl;
					if (outNum != 0) cout << ' ';
					cout << blackPath[i];
					outNum = (outNum + 1) % 12;
				}
				cout << endl;
				cout << "Total number of black nodes = " << blackNum << endl;
			}
		}
		else//n < 0  ���ʱҪע�⣬�������һ�к��治Ҫ���\n
		{
			n = -n;
			int tmp;
			blackNum = 0;
			if (first) first = false;
			else cout << endl;
			while (cin >> tmp && tmp != -1)
			{
				blackPath[blackNum] = tmp;
				blackNum++;
			}
			cout << "Image " << gameNum << endl;
			if (blackNum == 1 && blackPath[blackNum-1]==0)//ȫ��
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
						cout << '*';
					cout << endl;//���һ�к��治���\n
				}
			}
			else if(blackNum == 0)//ȫ��
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
						cout << '.';
					cout << endl;//���һ�к��治���\n
				}
			}
			else//����
			{
				memset(bitmap, 0, sizeof(bitmap));
				for (int i = 0; i < blackNum; i++)
					drawGraph(blackPath[i]);
				draw();
				cout << endl;
			}
		}
		gameNum++;
	}
	return 0;
}