#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const int MAXN = 1005;
vector<string> File[MAXN];
int maxlen[200];


void AlignmentOfCode()
{
	const char* input = "AlignmentOfCodeInput.txt";
	const char* output = "AlignmentOfCodeOutput.txt";
	freopen(input, "r", stdin);
	freopen(output, "w", stdout);

    string line;
    int row = 0;
    //读入文件
    while (getline(cin, line)) {
        stringstream ss(line);//创建一个字符串流
        int col = 0;
        string buf;
        while (ss >> buf) {//将一行字符串，拆成一个单词形式的字符串
            File[row].push_back(buf);
            if (!row || maxlen[col] < buf.length())//记录每一列最长的单词长度
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