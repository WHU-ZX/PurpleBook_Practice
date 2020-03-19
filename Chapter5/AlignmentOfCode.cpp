#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
static const int MAXN = 1005;
static vector<string> File[MAXN];
static int maxlen[200];


void AlignmentOfCode()
{
	const char* input = "datas/AlignmentOfCodeInput.txt";
	const char* output = "datas/AlignmentOfCodeOutput.txt";
	freopen(input, "r", stdin);
	freopen(output, "w", stdout);

    string line;
    int row = 0;
    //�����ļ�
    while (getline(cin, line)) {
        stringstream ss(line);//����һ���ַ�����
        int col = 0;
        string buf;
        while (ss >> buf) {//��һ���ַ��������һ��������ʽ���ַ���
            File[row].push_back(buf);
            if (!row || maxlen[col] < buf.length())//��¼ÿһ����ĵ��ʳ���
                maxlen[col] = buf.length();
            col++;
        }
        row++;
    }

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < File[r].size(); c++)
        {
            int dir = maxlen[c] - File[r][c].length();
            cout << File[r][c];
            if (c < File[r].size() - 1)
                for (int i = 0; i <= dir; i++)
                    cout << ' ';
        }
        cout << endl;
    }
}