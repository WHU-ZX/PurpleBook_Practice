#include <stdio.h>
#include <math.h>
#include <iostream>

int main() {
	int a, b;
	scanf_s("%d%d", &a, &b);

	a ^= b;
	b ^= a;
	a ^= b;
	//a ^= b ^= a ^= b;

	printf("a=%d,b=%d", a, b);



	system("pause");

	return 0;
}