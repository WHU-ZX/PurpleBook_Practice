#include <cstdio>
#include <iostream>
#include <stack>
#include <stdio.h>
#include <string.h>


using namespace std;
static string strs[2] = { "No","Yes" };

static void deal(string str)
{
	stack<char> s;
	int ok = 1;
	for (int i = 0; i < str.length(); i++)
	{
		char ch = str[i];
		bool wrong = false;
		switch (ch)
		{
		case '(':
			s.push(ch);
			break;
		case '[':
			s.push(ch);
			break;
		case ')':
			if (s.empty())
				wrong = true;
			else if (s.top() == '(')
				s.pop();
			else
				wrong = true;
			break;
		case ']':
			if (s.empty())
				wrong = true;
			else if (s.top() == '[')
				s.pop();
			else
				wrong = true;
			break;
		}
		if (wrong)
		{
			ok = 0;
			break;
		}
	}
	if (!s.empty()) ok = 0;
	if (str == "") ok = 1;
	cout << strs[ok] << endl;
}

int UVa_673()
{
	const char* input = "inputs/673.txt";
	const char* output = "outputs/673.txt";
	freopen(input, "r", stdin);
	int n;
	cin >> n;
	string strs[2] = { "No","Yes" };
	getchar();//获取换行符

	while(n--)
	{
		char ch[1024];
		string str;
		//scanf("%s", &str);
		//getline(cin, str);
		//cin >> str;
		gets_s(ch);//提交时要改成gets
		deal(ch);
	}
	return 0;
}