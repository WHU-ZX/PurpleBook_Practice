#include <cstdio>
#include <iostream>

//using namespace std;
static std::string preOrder, inOrder;
static const int max_node = 1024 * 4 + 1;

static int left[max_node], right[max_node];//左右指针   记得每次都把它初始化为0
static char node[max_node];//节点的值
static int n;//节点数  1-n

static void init()
{
	for (int i = 0; i < max_node; i++)
	{
		left[i] = right[i] = -1;
		node[i] = '\0';
	}
}

static int build(int L_pre, int R_pre, int L_in, int R_in)//在preOrder和inOrder中的前序遍历和中序遍历的左右下标
{
	//L_pre下标所对应的字符即为根节点字符,据此找到中序遍历中的根节点，然后再分左右进行递归调用
	if (L_pre > R_pre) return -1;//空树
	char root = preOrder[L_pre];
	int p = L_in;
	while (inOrder[p] != root) p++;
	int leftNodeCnt = p - L_in;//左子树结点数
	left[L_pre] = build(L_pre + 1, L_pre + leftNodeCnt, L_in, p - 1);
	right[L_pre] = build(L_pre + leftNodeCnt + 1, R_pre, p + 1, R_in);
	node[L_pre] = root;
	return L_pre;
}

static void postOrder(int idx)//后序遍历并输出
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
		//处理
		init();
		int root = build(0, preOrder.length() - 1, 0, inOrder.length() - 1);
		postOrder(root);
		std::cout << std::endl;
	}
	return 0;
}