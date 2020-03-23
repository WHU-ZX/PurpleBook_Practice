#include <cstdio>
#include <iostream>

//using namespace std;
static std::string preOrder, inOrder;
static const int max_node = 1024 * 4 + 1;

static int left[max_node], right[max_node];//����ָ��   �ǵ�ÿ�ζ�������ʼ��Ϊ0
static char node[max_node];//�ڵ��ֵ
static int n;//�ڵ���  1-n

static void init()
{
	for (int i = 0; i < max_node; i++)
	{
		left[i] = right[i] = -1;
		node[i] = '\0';
	}
}

static int build(int L_pre, int R_pre, int L_in, int R_in)//��preOrder��inOrder�е�ǰ���������������������±�
{
	//L_pre�±�����Ӧ���ַ���Ϊ���ڵ��ַ�,�ݴ��ҵ���������еĸ��ڵ㣬Ȼ���ٷ����ҽ��еݹ����
	if (L_pre > R_pre) return -1;//����
	char root = preOrder[L_pre];
	int p = L_in;
	while (inOrder[p] != root) p++;
	int leftNodeCnt = p - L_in;//�����������
	left[L_pre] = build(L_pre + 1, L_pre + leftNodeCnt, L_in, p - 1);
	right[L_pre] = build(L_pre + leftNodeCnt + 1, R_pre, p + 1, R_in);
	node[L_pre] = root;
	return L_pre;
}

static void postOrder(int idx)//������������
{
	if (left[idx] >= 0) postOrder(left[idx]);
	if (right[idx] >= 0) postOrder(right[idx]);
	std::cout << node[idx];
}

int UVa_536()
{
	const char* input = "inputs/536.txt";
	const char* output = "outputs/536.txt";
	freopen(input, "r", stdin);

	while (std::cin>> preOrder)
	{
		std::cin >> inOrder;
		//����
		init();
		int root = build(0, preOrder.length() - 1, 0, inOrder.length() - 1);
		postOrder(root);
		std::cout << std::endl;
	}
	return 0;
}