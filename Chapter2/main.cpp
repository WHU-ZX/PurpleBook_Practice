#include <iostream>

using namespace std;

void practice1();
void practice2();
void practice3();
void practice4();
bool fit(int abc);
void practice6();
int main() 
{	
	
	//practice1();
	//practice6();
	system("pause");
	return 0;
}

void practice1()
{
	for (int i = 100; i <= 999; i++) 
	{
		int first = i / 100;
		int second = i / 10 % 10;
		int third = i % 10;
		//cout << first << ' ' << second << ' ' << third << endl;
		if (i == first * first * first + second * second * second + third * third * third)cout << i << endl;
	}
}

void practice2()
{
	int a = -1,b = -1,c=-1;
	cin >> a >> b >> c;
	bool found = false;
	for (int i = 10; i <= 100; i++) 
	{
		if (i % 3 == a && i % 5 == b && i % 7 == c) 
		{
			cout << "answer:" << i;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "No answer";
	}
}

void practice3()
{
	int n = -1;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int c_num = 2 * (n-i) - 1;
		const int space_num = i;
		for (int j = 0; j < space_num; j++) cout <<' ';
		for (int j = 0; j < c_num; j++) cout << '#';
		cout << endl;
	}
}

void practice4()
{
	const int MAX = 1000000;
	int n = -1, m = -1;
	cin >> n >> m;
	if (n < m && m < MAX)
	{
		double sum = 0.0;
		for (int i = n; i <= m; i++)
		{
			sum += 1.0 / (i * i);
		}
		cout << sum;
	}
	else {
		cout << "输入不合要求";
	}
}

void practice6()
{
	for (int i = 102; i < 333; i++)
	{
		if (fit(i))
		{
			cout << i <<' '<< 2 * i <<' '<< 3 * i << endl;
		}
	}
	//以下是更好的实现：主要是利用一个数组实现集合（set）的功能
	/*for (int i = 102; i < 333; i++) {
		int a[3];
		a[0] = i;
		a[1] = 2 * i;
		a[2] = 3 * i;


		int hole[10];
		for (int j = 0; j < 10; j++)//初始化hole数组
			hole[j] = 0;

		int flag = 1;
		for (int index = 0; index < 3 && flag == 1; index++) {
			if (hole[a[index] % 10] == 0)//第index个数字的个位作为索引
				hole[a[index] % 10] = 1;
			else
				flag = 0;
			if (hole[a[index] / 10 % 10] == 0)//第index个数字的十位作为索引
				hole[a[index] / 10 % 10] = 1;
			else
				flag = 0;
			if (hole[a[index] / 100] == 0)//第index个数字的百位作为索引
				hole[a[index] / 100] = 1;
			else
				flag = 0;

		}
		if (flag == 1)
			printf("%d %d %d\n", i, 2 * i, 3 * i);
	}*/
}

bool fit(int abc)
{
	if (abc / 100 >= 1 && abc / 100 <= 3)
	{
		int def = 2 * abc;
		int hij = 3 * abc;
		if (hij > 987)
		{
			return false;
		}
		else
		{
			int a = abc / 100;
			int b = abc % 100 / 10;
			int c = abc % 10;
			int d = def / 100;
			int e = def % 100 / 10;
			int f = def % 10;
			int g = hij / 100;
			int h = hij % 100 / 10;
			int i = hij % 10;
			//判断是否为1-9
			if (a + b + c + d + e + f + g + h + i == 45 && a * b * c * d * e * f * g * h * i  == 362880) {
				return true;
			}
			else 
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}