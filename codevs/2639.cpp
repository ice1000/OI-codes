/*
 * 作者:千里冰封
 * 题目:p2639 约会计划
 *
 * 用C++是没办法的事。
 * 为啥我写出来的并查集和题解一模一样但是就是WA啊
 * 这不科学啊
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using std::string;
using std::cin;

int father[2020];
std::map<string, int> name;

int find(int n) {
	if (father[n] != n) father[n] = find(father[n]);
	return father[n];
}

void merge(int a, int b) {
	int t1 = find(a), t2 = find(b);
	if (t1 != t2) father[t1] = t2;
}

int main(int argc, char* argv[]) {
	int i, j, k, l, n, m, p;
	string t1, t2;
	scanf("%i %i %i", &n, &m, &p);
	for (i = 0; i < n; ++i) {
		cin>>t1;
		father[i] = i;
		name[t1] = i;
	}
	for (i = 0; i < m; ++i) {
		std::cin>>t1>>t2;
		merge(name[t1], name[t2]);
	}
	for (i = 0; i < p; ++i) {
		cin>>t1>>t2;
		if (find(name[t1]) == find(name[t2]))
			printf("safe\n");
		else
			printf("cc cry\n");
	}
	return 0;
}
