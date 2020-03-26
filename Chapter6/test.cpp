#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <utility>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>
#define CLEAR(a, b) memset(a, b, sizeof(a))
#define IN() freopen("in.txt", "r", stdin)
#define OUT() freopen("out.txt", "w", stdout)
#define LL long long
#define maxn 200005
#define maxm 100005
#define mod 1000000007
#define INF 1000000007
#define eps 1e-5
#define PI 3.1415926535898
#define N 26
using namespace std;
//-------------------------CHC------------------------------//
static vector<deque<int>> deq;
static set<vector<deque<int>>> s;
static int cur, cnt;

static void init() {
	deq.clear();
	s.clear();
	cur = -1;
	cnt = 7;
	for (int i = 0; i < 8; ++i)
		deq.push_back(deque<int>());
}

static bool can(int a, int b, int c) {
	return (a + b + c) == 10 || (a + b + c) == 20 || (a + b + c) == 30;
}

static void reuse(int a, int b, int c) {
	deque<int>& D = deq[7];
	D.push_back(a);
	D.push_back(b);
	D.push_back(c);
}

static bool op1(deque<int>& d) {
	int b1, b2, b3;
	b1 = d.back(), d.pop_back();
	b2 = d.back(), d.pop_back();
	b3 = d.back(), d.pop_back();
	if (can(b1, b2, b3)) {
		reuse(b3, b2, b1);
		return true;
	}
	else {
		d.push_back(b3);
		d.push_back(b2);
		d.push_back(b1);
		return false;
	}
}

static bool op2(deque<int>& d) {
	int f1, f2, f3, f4;
	f1 = d.front(), d.pop_front();
	f2 = d.front(), d.pop_front();
	f3 = d.front(), d.pop_front();
	f4 = d.front(), d.pop_front();
	if (can(f1, f2, f4)) {
		d.push_front(f3);
		reuse(f1, f2, f4);
		return true;
	}
	else if (can(f1, f3, f4)) {
		d.push_front(f2);
		reuse(f1, f3, f4);
		return true;
	}
	else if (can(f2, f3, f4)) {
		d.push_back(f1);
		reuse(f2, f3, f4);
		return true;
	}
	else {
		d.push_back(f1);
		d.push_back(f2);
		d.push_back(f3);
		d.push_back(f4);
		return false;
	}
}

static bool op3(deque<int>& d) {
	int f1, f2, b1, b2, b3;
	f1 = d.front(), d.pop_front();
	f2 = d.front(), d.pop_front();
	b1 = d.back(), d.pop_back();
	b2 = d.back(), d.pop_back();
	b3 = d.back(), d.pop_back();
	if (can(f1, f2, b1)) {
		d.push_back(b3);
		d.push_back(b2);
		reuse(f1, f2, b1);
		return true;
	}
	else if (can(f1, b1, b2)) {
		d.push_front(f2);
		d.push_back(b3);
		reuse(f1, b2, b1);
		return true;
	}
	else if (can(b1, b2, b3)) {
		d.push_front(f2);
		d.push_front(f1);
		reuse(b3, b2, b1);
		return true;
	}
	else {
		d.push_front(f2);
		d.push_front(f1);
		d.push_back(b3);
		d.push_back(b2);
		d.push_back(b1);
		return false;
	}
}

static bool solve(deque<int>& d) {
	bool ret = false;
	if (d.size() < 3) return false;
	if (d.size() == 3) ret = op1(d);
	else if (d.size() == 4) ret = op2(d);
	else if (d.size() >= 5) ret = op3(d);
	return ret;
}

static int check() {
	bool ok = true;
	//cout << deq[7].size() << endl;
	for (int i = 0; i < 7; ++i) {
		//printf("deq %d: %d\n", i + 1, deq[i].size());
		if (deq[i].size()) ok = false;
	}
	if (ok) return 1;
	if (s.count(deq)) return -1;
	else s.insert(deq);
	return 0;
}

static void move() {
	++cur, cur %= 7;
	while (deq[cur].size() == 0) ++cur, cur %= 7;
}

int test() {
	const char* input = "inputs/WF_246.txt";
	const char* output = "outputs/WF_246.txt";
	freopen(input, "r", stdin);
	int x;
	while (scanf("%d", &x) && x) {
		init();
		deq[7].push_back(x);
		for (int i = 1; i < 52; ++i)
			scanf("%d", &x), deq[7].push_back(x);
		for (int i = 0; i < 7; ++i) {
			x = deq[7].front();
			deq[7].pop_front();
			deq[i].push_back(x);
		}
		int win = 0;
		s.insert(deq);
		while (win == 0) {
			if (deq[7].empty()) { win = -1; break; }
			move();
			int card = deq[7].front(); deq[7].pop_front();
			deque<int>& d = deq[cur];
			d.push_back(card);
			while (solve(d));	//	зЂвт
			cnt++;
			int res = check();
			if (res == 1) win = 1;
			else if (res == -1) break;
		}
		if (win == 1) printf("Win : %d\n", cnt);
		else if (win == -1) printf("Loss: %d\n", cnt);
		else printf("Draw: %d\n", cnt);
	}
	return 0;
}