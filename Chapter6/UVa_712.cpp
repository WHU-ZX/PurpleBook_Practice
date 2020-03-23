#include <cstdio>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
static const int max_d = 7;

static map<int, int> i2v_map;
static int vLevel[max_d];
static int n, m;//nΪ��ȣ�mΪ���ĸ���

int transfer(string str)
{
	int ret = 0;
	for (int i = 1; i < str.length(); i++)
	{
		ret *= 10;
		ret += str[i] - '0';
	}
	return ret;
}

void initMap(string leafValues)
{
	if (!i2v_map.empty()) i2v_map.clear();
	int firstIdx = 1 << n;//��һ��Ҷ�ӽڵ�ı�� ---- ���Ľڵ��1��ʼ
	for (int i = 0; i < leafValues.length(); i++)
	{
		i2v_map[firstIdx + i] = leafValues[i] - '0';
	}
}


int UVa_712()
{
	const char* input = "inputs/712.txt";
	const char* output = "outputs/712.txt";
	freopen(input, "r", stdin);
	string line,leafValues;
	int gameIndex = 1;
	
	while (scanf("%d", &n) == 1 && n)
	{
		getchar();
		getline(cin, line);
		stringstream ss(line);//����һ���ַ�����
		string buf;
		int idx = 0;
		while (ss >> buf)//��ʼ��vLevel
		{
			vLevel[idx] = transfer(buf) - 1;//vLevel[idx] = a ��ʾ�ڵ�idx��ʹ��������±�Ϊa������
			idx++;
		}
		getline(cin, leafValues);
		initMap(leafValues);//��ʼ����Ҷ�ӽڵ�ı�Ŷ�Ӧ�������ֵ��map
		cin >> m;
		cout << "S-Tree #" << gameIndex << ":" << endl;
		for (int i = 0; i < m; i++)
		{
			string X;
			cin >> X;
			int curLevel = 0, index = 1;
			while (curLevel < n)
			{
				int valueIndex = vLevel[curLevel];
				int value = X[valueIndex] - '0';
				if (value == 0)
					index *= 2;
				else
					index = 2 * index + 1;
				curLevel++;
			}
			cout << i2v_map[index];
		}
		cout << endl << endl;
		gameIndex++;
	}
	return 0;
}