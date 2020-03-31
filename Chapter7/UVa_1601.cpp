#include <cstdio>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

static int w, h, n;//w是宽度，h是高度
const static int maxw = 18, maxh = 16;//还要存储\n
static char board[maxh][maxw];
static int deg[maxw * maxh];//表示G[i]中的有效结点个数
static int G[maxw * maxh][5];//G[i][j]表示结点i经过第j种走法到达的结点下标

static int id[maxh][maxw];
static int src[3], des[3];//src是3个结点abc的idx

static int x[maxh * maxw], y[maxh * maxw];//x[i],y[i]分别表示第i个结点在board中的x、y坐标

static int cnt;//总结点个数

static int dx[] = { 0,0,0,1,-1 };
static int dy[] = { 0,1,-1,0,0 };
int dSrc[maxh * maxw][maxh * maxw][maxh * maxw], dDes[maxh * maxw][maxh * maxw][maxh * maxw];
static int ID(int a, int b, int c)//将鬼的位置压缩为整数
{
	return (a << 16) | (b << 8) | c;
}

static void init()//初始化内存
{
	cnt = 0;
	memset(id, 0, sizeof(id));
	memset(board, 0, sizeof(board));
	memset(src, -1, sizeof(src));
	memset(des, -1, sizeof(des));
	memset(dSrc, -1, sizeof(dSrc));
	memset(dDes, -1, sizeof(dDes));
	//memset(deg, 0, sizeof(deg));
	//memset(G, 0, sizeof(G));
	//memset(x, 0, sizeof(x));
	//memset(y, 0, sizeof(y));
}

static bool canGo(int x, int y)
{
	return x >= 0 && x < h && y >= 0 && y < w && board[x][y] != '#';
}

static bool isWrong(int a, int a1, int b, int b1)//判断a->a1和b->b1的走法是否违规
{
	return a1 == b1 || a1 == b && b1 == a;
}

static int bfs()
{
	queue<int> Q1,Q2;//q存下标
	Q1.push(ID(src[0], src[1], src[2]));
	Q2.push(ID(des[0], des[1], des[2]));
	dSrc[src[0]][src[1]][src[2]] = dDes[des[0]][des[1]][des[2]] = 0;
	while (!Q1.empty() && !Q2.empty())
	{
		//正向BFS
		int Id = Q1.front(); Q1.pop();
		int idA = (Id >> 16) & 0xff, idB = (Id >> 8) & 0xff, idC = Id & 0xff;
		for (int i = 0; i < deg[idA]; i++)
		{
			int nIdA = G[idA][i];
			for (int j = 0; j < deg[idB]; j++)
			{
				int nIdB = G[idB][j];
				if (!isWrong(idA, nIdA, idB, nIdB))//a和b的移动不冲突
					for (int k = 0; k < deg[idC]; k++)
					{
						int nIdC = G[idC][k];
						if (!isWrong(idA, nIdA, idC, nIdC) && !isWrong(idB, nIdB, idC, nIdC))//c和a、b的移动不冲突
						{
							if (dSrc[nIdA][nIdB][nIdC]==-1)//没到过这个点
							{
								dSrc[nIdA][nIdB][nIdC] = dSrc[idA][idB][idC] + 1;
								if (dDes[nIdA][nIdB][nIdC]!=-1) return dDes[nIdA][nIdB][nIdC] + dSrc[nIdA][nIdB][nIdC];
								Q1.push(ID(nIdA, nIdB, nIdC));
							}
						}
					}
			}
		}
		//反向BFS
		Id = Q2.front(); Q2.pop();
		idA = (Id >> 16) & 0xff; idB = (Id >> 8) & 0xff; idC = Id & 0xff;
		for (int i = 0; i < deg[idA]; i++)
		{
			int nIdA = G[idA][i];
			for (int j = 0; j < deg[idB]; j++)
			{
				int nIdB = G[idB][j];
				if (!isWrong(idA, nIdA, idB, nIdB))//a和b的移动不冲突
					for (int k = 0; k < deg[idC]; k++)
					{
						int nIdC = G[idC][k];
						if (!isWrong(idA, nIdA, idC, nIdC) && !isWrong(idB, nIdB, idC, nIdC))//c和a、b的移动不冲突
						{
							if (dDes[nIdA][nIdB][nIdC]==-1)
							{
								dDes[nIdA][nIdB][nIdC] = dDes[idA][idB][idC] + 1;
								if (dSrc[nIdA][nIdB][nIdC]!=-1) return dDes[nIdA][nIdB][nIdC] + dSrc[nIdA][nIdB][nIdC];
								Q2.push(ID(nIdA, nIdB, nIdC));
							}
						}
					}
			}
		}
	}
	return -1;
}

int UVa_1601()//感觉没问题，为什么一到oj上就错误？
{
	const char* input = "inputs/1601.txt";
	//const char* output = "outputs/1601.txt";
	freopen(input, "r", stdin);
	string line;
	while (scanf("%d%d%d\n", &w, &h, &n) == 3 && n)
	{
		init();
		for (int i = 0; i < h; i++)
		{
			//gets(board[i], maxh, stdin);
			//gets(board[i]);
			//getline(cin, line);
			fgets(board[i], maxw, stdin);
			for (int j = 0; j < w; j++)
			{
				//board[i][j] = line[j];
				if (board[i][j] != '#')
				{
					x[cnt] = i; y[cnt] = j; id[i][j] = cnt;
					if (islower(board[i][j])) src[board[i][j] - 'a'] = cnt;
					else if (isupper(board[i][j]))des[board[i][j] - 'A'] = cnt;
					cnt++;
				}
			}
		}
		
		for (int i = 0; i < cnt; i++)
		{
			deg[i] = 0;
			for (int j = 0; j < 5; j++)
			{
				int newX = x[i] + dx[j], newY = y[i] + dy[j];
				if (canGo(newX, newY)) G[i][deg[i]++] = id[newX][newY];

			}
		}
		if (n <= 2) { deg[cnt] = 1; G[cnt][0] = cnt; src[2] = des[2] = cnt++; }//没有第三个点，添加第三个点
		if (n <= 1) { deg[cnt] = 1; G[cnt][0] = cnt; src[1] = des[1] = cnt++; }//只包含一个点，仍然满足的话，添加第二个点

		cout << bfs() << endl;
	}


	return 0;
}