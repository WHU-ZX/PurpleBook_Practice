#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
static int n, w, h;
const static int MAXN = 10;
const static int HASHSIZE = 100007LL;
static int ans[MAXN + 5][MAXN + 5][MAXN + 5];//ans[n][w][h]��˳��
const static int dir[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
typedef long long LL;//������64λ

//static bool in_map(int x, int y) { return x >= 1 && x <= h && y >= 1 && y <= w; }//�жϸõ��Ƿ���map��
struct Point {
	int x, y;
	Point() 
	{
		x = 0; y = 0;
	}
	Point(int x, int y)
	{
		this->x = x; this->y = y;
	}
	bool operator < (const Point& rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
	bool operator == (const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
};
struct hashNode {
	hashNode* next;
	LL code;
};
static hashNode* hashHead[HASHSIZE + 5], hashEdge[100000], * hashEcnt = hashEdge;;

struct Poly
{
	int cnt;
	Point p[4655 + 5][MAXN + 5];//p[j][k]����j����ͨ��ĵ�k���㣬
};
static Poly poly[MAXN + 5];//poly[n]��ʾ��n�㣬����ͨ�����ĿΪn

static LL encode(Point ps[], int n)
{
	LL code = 0;
	for (int i = 2; i <= n; ++i)//��1��ʼ��n,Ҫ��֤�����ps��˳������һ�µ�---�
	{
		int ox = ps[i].x - ps[i - 1].x;
		int oy = ps[i].y - ps[i - 1].y;
		code = code * 100 + ox * (LL)10 + oy;
	}
	return code;
}

static bool check_in_hash(LL code)
{
	int headIndex = code % HASHSIZE;
	//if (code < 0) return true;
	for (hashNode* p = hashHead[headIndex]; p != NULL; p = p->next)
	{
		if (p->code == code) return true;
	}
	return false;
}

static void normalize(Point p0[], int n) //ƽ�������Ͻ�,������
{
	int minx = INT32_MAX;
	int miny = INT32_MAX;
	sort(p0 + 1, p0 + n + 1);
	for (int i = 1; i <= n; ++i)
	{
		minx = min(p0[i].x, minx);
		miny = min(p0[i].y, miny);
	}
	for (int i = 1; i <= n; ++i)
	{
		p0[i].x -= minx;
		p0[i].y -= miny;
	}
}

static void upside_down(Point p0[], int n) { //���·�ת�����»������Ҷ����ԣ�
	Point p[MAXN + 5];
	for (int i = 1; i <= n; ++i) {
		p[i].x = p0[i].x;
		p[i].y = -p0[i].y;
	}
	normalize(p, n);
	memcpy(p0, p, sizeof p);
}

static void rotate90(Point p0[], int n)//˳ʱ����ת90��,���������Ͻ�
{
	Point p[MAXN + 5];
	for (int i = 1; i <= n; ++i)
	{
		p[i].x = p0[i].y;
		p[i].y = -p0[i].x;
	}
	normalize(p, n);
	memcpy(p0, p, sizeof p);
}
static void rotate180(Point p0[], int n)//��ת180��,���������Ͻ�,ʵ�����ò���������2����ת90�ȼ���
{
	Point p[MAXN + 5];
	for (int i = 1; i <= n; ++i)
	{
		p[i].x = -p0[i].x;
		p[i].y = -p0[i].y;
	}
	normalize(p, n);
	memcpy(p0, p, sizeof p);
}

static void rotate270(Point p0[], int n)//��ת270��,���������Ͻǣ�ʵ�����ò���������3����ת90�ȼ���
{
	Point p[MAXN + 5];
	for (int i = 1; i <= n; ++i)
	{
		p[i].x = -p0[i].y;
		p[i].y = p0[i].x;
	}
	normalize(p, n);
	memcpy(p0, p, sizeof p);
}

static bool try_to_insert(Point p[], int n)
{
	Point p0[MAXN + 5], rp0[MAXN + 5];
	LL code;
	memcpy(p0, p, sizeof(Point) * (MAXN + 5));
	normalize(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code)) return false;
	rotate90(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code)) return false;
	rotate90(p0, n);//90+90 = 180
	code = encode(p0, n);
	if (check_in_hash(code)) return false;
	rotate90(p0, n);//180+90 = 270
	code = encode(p0, n);
	if (check_in_hash(code)) return false;
	//���·�ת���ټ��
	memcpy(rp0, p, sizeof(Point) * (MAXN + 5));
	upside_down(rp0, n);
	normalize(rp0, n);
	code = encode(rp0, n);
	if (check_in_hash(code)) return false;
	rotate90(rp0, n);
	code = encode(rp0, n);
	if (check_in_hash(code)) return false;
	rotate90(rp0, n);//90+90 = 180
	code = encode(rp0, n);
	if (check_in_hash(code)) return false;
	rotate90(rp0, n);//180+90 = 270
	code = encode(rp0, n);
	if (check_in_hash(code)) return false;
	//�������ڣ�����Բ���
	int h = code % HASHSIZE;
	hashNode* hn = hashEcnt;
	hn->code = code;
	hn->next = hashHead[h];
	hashHead[h] = hn;
	++hashEcnt;
	return true;//����ɹ�

	/*Point p0[MAXN + 5], rp0[MAXN + 5];
	LL code;
	memcpy(p0, p, sizeof(Point) * (MAXN + 5));
	normalize(p, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	memcpy(p0, p, sizeof(Point) * (MAXN + 5));
	rotate90(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	memcpy(p0, p, sizeof(Point) * (MAXN + 5));
	rotate180(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	memcpy(p0, p, sizeof(Point) * (MAXN + 5));
	rotate270(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	memcpy(rp0, p, sizeof(Point) * (MAXN + 5));
	upside_down(rp0, n);
	code = encode(rp0, n);
	if (check_in_hash(code))
		return false;
	memcpy(p0, rp0, sizeof rp0);
	rotate90(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	memcpy(p0, rp0, sizeof rp0);
	rotate180(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	memcpy(p0, rp0, sizeof rp0);
	rotate270(p0, n);
	code = encode(p0, n);
	if (check_in_hash(code))
		return false;
	int h = code % HASHSIZE;
	hashNode* hn = hashEcnt;
	hn->next = hashHead[h];
	hn->code = code;
	hashHead[h] = hn;
	++hashEcnt;
	return true;*/
}

static bool find(Point p0[], Point p, int n)//���ֲ��ҿ�������Ҫ����� p �Ƿ��Ѿ������������ͨ���У�p0 ���Ѿ��Ź����
{
	return binary_search(p0 + 1, p0 + n + 1, p);
}



static void getAns()//���ݵ�ǰn,w,h��ȡ��,���û������
{
	poly[1].cnt = 1;
	poly[1].p[1][1] = Point(0, 0); //1 ��ͨ��
	for (int i = 2; i <= MAXN; ++i)
	{
		int& cnt = poly[i].cnt;
		for (int j = 1; j <= poly[i - 1].cnt; ++j)//ö����һ�����ͨ��
		{
			for (int k = 1; k <= i - 1; ++k)//ö��ÿ����
			{
				for (int l = 0; l < 4; ++l)//���ĸ�������չ
				{
					Point p = Point(poly[i - 1].p[j][k].x + dir[l][0], poly[i - 1].p[j][k].y + dir[l][1]);
					if (!find(poly[i - 1].p[j], p, i - 1))//�����������
					{
						Point ps[MAXN + 5];
						memcpy(ps, poly[i - 1].p[j], sizeof poly[i - 1].p[j]);
						ps[i] = p;
						normalize(ps, i);
						if (try_to_insert(ps, i))
							memcpy(poly[i].p[++cnt], ps, sizeof ps); //������ͨ��
					}
				}
			}
		}
	}
	for (int n = 1; n <= MAXN; ++n)
		for (int w = 1; w <= n; ++w)
			for (int h = 1; h <= n; ++h)
			{
				int cnt = 0;
				for (int i = 1; i <= poly[n].cnt; ++i)
				{
					int xmax = INT32_MIN, ymax = INT32_MIN;
					for (int j = 1; j <= n; ++j)
					{
						xmax = max(xmax, poly[n].p[i][j].x);
						ymax = max(ymax, poly[n].p[i][j].y);
					}
					if (min(xmax, ymax) < min(h, w) && max(xmax, ymax) < max(h, w))
						++cnt;
				}
				ans[n][w][h] = cnt;
			}
}

int UVa_1602()
{
	const char* input = "inputs/1602.txt";
	//const char* output = "outputs/1602.txt";
	freopen(input, "r", stdin);

	getAns();
	while (scanf("%d%d%d\n", &n, &w, &h) == 3)
	{
		printf("%d\n", ans[n][w][h]);
	}
	return 0;
}