#include <cstdio>
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
static const int dr[4] = { 1,-1,0,0 };
static const int dc[4] = { 0,0,1,-1 };

static const int maxm = 21, maxn = 21;

static int board[maxm][maxn];
static int length[maxm][maxn];

static int k;

static int m, n;
static int gameNum;

static void init()
{
	memset(board, 0, sizeof(board));
	memset(length, 0, sizeof(length));
	//length[m][n] = -1;
}

static bool legalMove(int r, int c, int i, int curK)
{
	int newR = r + dr[i];
	int newC = c + dc[i];
	if (newR < 1 || newR>m || newC<1 || newC>n)return false;//��������߽��򷵻�false
	if (length[newR][newC]&& board[newR][newC]==0) return false;//����˵��Ѿ����ʹ����򷵻�false --- Ҫ��Ҫȥ����
	//��ԣ�if(length[newR][newC]) return false;
	//�������·�����ǵ�i������ĳ�����Ҵ˴�Ϊ1����Ӧ��ѡcurK��С������
	//�������ĳһ���ߵ���ĳ������Ȼlength������������������curK��С��˵������һ������ֱ���ٵ�һ��Ϊ1�ĵ㲢�Ҵ������·��
	//��������������
	if (board[newR][newC] == 1) return k - curK > 0;
	return true;
}

int UVa_1600()
{
	const char* input = "inputs/1600.txt";
	const char* output = "outputs/1600.txt";
	freopen(input, "r", stdin);

	cin >> gameNum;
	while (gameNum--)
	{
		cin >> m >> n >> k;
		init();
		for(int i = 1 ; i <= m; i++)
			for (int j = 1; j <= n; j++)
			{
				cin >> board[i][j];
			}
		//���д���
		queue<int> Qr, Qc, Qk, Qs;
		Qr.push(1); Qc.push(1); Qk.push(0); Qs.push(0);
		while(!Qr.empty())
		{
			int r = Qr.front(); Qr.pop();
			int c = Qc.front(); Qc.pop();
			int curK = Qk.front(); Qk.pop();
			int step = Qs.front(); 
			if (r == m && c == n) break;
			for (int i = 0; i < 4; i++)
			{
				if (legalMove(r, c, i, curK))
				{
					int newK = board[r + dr[i]][c + dc[i]] ? curK + 1 : 0;
					Qr.push(r + dr[i]);
					Qc.push(c + dc[i]);
					Qk.push(newK);
					length[r + dr[i]][c + dc[i]] = length[r][c] + 1;
					Qs.push(step + 1);
				}
			}
			Qs.pop();
		}
		if (Qs.empty())
			length[m][n] = -1;
		else
			length[m][n] = Qs.front();

		cout << length[m][n] << endl;
	}
	return 0;
}