#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef unsigned long long number;

using std::string;
using std::vector;

vector<string> deep_dark_fantasy = *new vector<string>();
string str, tmp;

bool judge(string s) {
	number i;
	for (i = 0; i < (s.length() >> 1); ++i)
		if (s[i] != s[s.length() - i - 1]) return false;
	return true;
}

void dfs(number idx, string s) {
	if (judge(s)) deep_dark_fantasy.push_back(s);
	if (idx >= str.length()) return;
	dfs(idx + 1, s);
	dfs(idx + 1, s.append(tmp = str.at(idx)));
}

int main(int argc, const char *argv[]) {
	freopen("pailn.in", "r", stdin);
	freopen("pailn.out", "w", stdout);
	std::cin >> str;
	dfs(0x00ll, "");
	std::sort(deep_dark_fantasy.begin(), deep_dark_fantasy.end());
	std::cout << deep_dark_fantasy[deep_dark_fantasy.size() - 1];
	return 0;
}

/*
 * bowwowwow
 */

