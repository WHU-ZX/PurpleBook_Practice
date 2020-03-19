#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
static map<char, vector<string> > m;
static set<string> s;

bool findStr(string str)//寻找map中是否有字符串str
{
	if (m.count(str[0]) == 1)
	{
		int size = m[str[0]].size();
		for (int i = 0; i < size; i++)
			if (m[str[0]][i] == str) return true;
	}
	return false;
}

int UVa_10391()
{
	const char* input = "datas/UVa_10391_input.txt";
	const char* output = "datas/UVa_10391_output.txt";
	freopen(input, "r", stdin);

	string str;
	bool first = true;
	while (cin >> str)
	{
		char hC = str[0];
		if (m.count(hC) == 1)//存在
		{
			m[hC].push_back(str);
		}
		else//不存在
		{
			vector<string> tV;
			tV.push_back(str);
			//m.insert(pair<char, vector<string> >(hC, tV));
			m[hC] = tV;
		}
	}
	map<char, vector<string> >::iterator iter;
	for (iter = m.begin(); iter != m.end(); iter++)
	{
		vector<string> v = iter->second;
		int size = v.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				int idx = v[j].find(v[i]);
				if (idx == 0)//是子串
				{
					string subStr = v[j].substr(v[i].size(), v[j].size() - v[i].size());
					if (findStr(subStr))
					{
						s.insert(v[j]);
					}
				}
			}
		}
	}
	set<string>::iterator sIter;
	for (sIter = s.begin(); sIter != s.end(); sIter++)
	{
		cout << *sIter << endl;
	}
	return 0;
}