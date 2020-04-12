#include <cstdio>
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
static int get_result(string S, string T)//��������ִ�в���������޽⣬����-1
{
	int len = S.size();
	int W0 = 0, W1 = 0;//S��Ϊ0��Ϊ1�Ĵ������Ŀ
	int Wq, Wq0 = 0, Wq1 = 0;//Wq���ʺŵĸ�����Wq0���ʺ�����Ҫ��0�ĸ�����Wq1���ʺ�����Ҫ��1�ĸ���
	for (int i = 0; i < len; ++i) // ����
	{
		if (S[i] != T[i])
		{
			if (S[i] == '0') W0 += 1;
			else if (S[i] == '1')W1 += 1;
			else // S[i] = ?
			{
				if (T[i] == '0')Wq0 += 1;
				else Wq1 += 1;
			}
		}
	}
	Wq = Wq0 + Wq1;
	//��ʼ����
	if (W1 + Wq0 > W0 + Wq) return -1;//�޽⣬����-1
	int cnt = 0;
	int minW = W0 >= W1 ? W1 : W0;
	W0 -= minW; W1 -= minW;
	cnt += minW;

	if (W0 > 0) cnt += W0;
	else if (W1 > 0) cnt += W1;
	cnt += Wq;
	return cnt;
}

int UVa_12545()
{
	const char* input = "inputs/12545.txt";
	//const char* output = "outputs/12545.txt";
	freopen(input, "r", stdin);
	int caseNum;
	cin >> caseNum;
	string S, T;
	for (int cas = 1; cas <= caseNum; ++cas)
	{
		cin >> S >> T;
		cout << "Case " << cas << ": " << get_result(S, T) << endl;
	}
	return 0;
}