#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

static struct Book
{
	string title;
	string writer;

};
bool operator == (const Book& a, const Book& b)
{
	return a.title == b.title && a.writer == b.writer;
}
map<string, Book> m;
vector<Book> v;
vector<Book> retV;
static bool cmp(Book b1, Book b2)
{
	if (b1.writer != b2.writer)
		return b1.writer < b2.writer;
	else
		return b1.title < b2.title;
}

int UVa_230()
{
	const char* input = "datas/UVa_230_input.txt";
	const char* output = "datas/UVa_230_output.txt";
	freopen(input, "r", stdin);

	string line;
	Book book;
	while (getline(cin,line)&&line != "END")//获得数据
	{
		int idx = line.find(" by ");
		book.title = line.substr(0, idx);
		book.writer = line.substr(idx + 4, line.length() - idx - 4);
		v.push_back(book);
		m[book.title] = book;
	}
	//此处对v进行排序
	sort(v.begin(), v.end(), cmp);
	string instruct, title;
	while (getline(cin, line) && line != "END")//获得指令
	{
		if (line == "SHELVE")
		{
			instruct = "SHELVE";
			title = "";
		}
		else
		{
			instruct = line.substr(0, 6);
			title = line.substr(7, line.length() - 7);
		}
		if (instruct == "SHELVE")
		{
			sort(retV.begin(), retV.end(), cmp);
			vector<Book>::iterator iter;
			for (int i = 0; i < retV.size(); i++)
			{
				iter = find(v.begin(), v.end(), retV[i]);
				if (iter != v.end())
				{
					if (iter != v.begin())
					{
						iter--;
						cout << "Put " << retV[i].title << " after " << iter->title << endl;
					}
					else
					{
						cout << "Put " << retV[i].title << " first" << endl;
					}
				}
			}
			retV.clear();
			cout << "END";
		}
		else if (instruct == "BORROW")
		{
			/*vector<Book>::iterator iter = find(v.begin(), v.end(), m[title]);
			v.erase(iter);*/
		}
		else // instruct == "RETURN"
		{
			retV.push_back(m[title]);
		}
	}
	return 0;
}